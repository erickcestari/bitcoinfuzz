#include "module.h"
#include <jni.h>
#include <string>
#include <optional>
#include <iostream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

static bool init_jvm();

class JNIThreadGuard {
private:
    JavaVM* jvm;
    JNIEnv* env;
    bool needsDetach;

public:
    JNIThreadGuard(JavaVM* vm) : jvm(vm), env(nullptr), needsDetach(false) {
        if (!jvm) return;
        
        jint status = jvm->GetEnv((void**)&env, JNI_VERSION_1_8);
        if (status == JNI_EDETACHED) {
            if (jvm->AttachCurrentThread((void**)&env, nullptr) != JNI_OK) {
                std::cerr << "Failed to attach thread to JVM" << std::endl;
                env = nullptr;
            } else {
                needsDetach = true;
            }
        } else if (status != JNI_OK) {
            std::cerr << "Failed to get JNI environment" << std::endl;
            env = nullptr;
        }
    }

    ~JNIThreadGuard() {
        if (jvm && needsDetach) {
            jvm->DetachCurrentThread();
        }
    }

    JNIEnv* getEnv() const { return env; }
};

class LocalRefGuard {
private:
    JNIEnv* env;
    jobject ref;

public:
    LocalRefGuard(JNIEnv* env, jobject obj) : env(env), ref(obj) {}
    
    ~LocalRefGuard() {
        if (env && ref) {
            env->DeleteLocalRef(ref);
        }
    }

    jobject get() const { return ref; }
    
    operator jobject() const { return ref; }
    
    jobject release() {
        jobject result = ref;
        ref = nullptr;
        return result;
    }
};

static JavaVM* jvm = nullptr;
static jclass invoiceClass = nullptr;
static jmethodID deserializeMethod = nullptr;

static std::string cached_classpath;

static const std::string build_classpath() {
    if (!cached_classpath.empty()) return cached_classpath;
    
    std::ostringstream cp;
    cp << "-Djava.class.path=";
    bool first = true;
    
    try {
        for (const auto& entry : fs::directory_iterator("./modules/eclair/lib")) {
            auto ext = entry.path().extension();
            if (ext == ".jar" || ext == ".class") {
                if (!first) cp << ":";
                cp << entry.path().string();
                first = false;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    
    cached_classpath = cp.str();
    return cached_classpath;
}

class JNIHelper {
private:
    JNIEnv* env;

public:
    JNIHelper(JNIEnv* env) : env(env) {}

    // Convert C++ string to Java string with proper UTF-16 handling
    jstring toJString(const std::string& str) const {
        std::vector<jchar> utf16;
        for (unsigned char byte : str) {
            utf16.push_back(static_cast<jchar>(byte));
        }
        return env->NewString(utf16.data(), utf16.size());
    }

    // Convert Java string to C++ string
    std::string fromJString(jstring jstr) const {
        if (!jstr) return "";
        
        const char* chars = env->GetStringUTFChars(jstr, nullptr);
        if (!chars) return "";
        
        std::string result(chars);
        env->ReleaseStringUTFChars(jstr, chars);
        return result;
    }

    jmethodID getMethodID(jclass clazz, const char* name, const char* sig, bool isStatic = false) const {
        jmethodID method = isStatic ? 
            env->GetStaticMethodID(clazz, name, sig) : 
            env->GetMethodID(clazz, name, sig);
            
        if (!method) {
            std::cerr << "Failed to find method: " << name << " with signature " << sig << std::endl;
            checkException();
        }
        return method;
    }

    jobject callObjectMethod(jobject obj, jmethodID method, ...) const {
        va_list args;
        va_start(args, method);
        jobject result = env->CallObjectMethodV(obj, method, args);
        va_end(args);
        
        checkException();
        return result;
    }

    jobject callStaticObjectMethod(jclass clazz, jmethodID method, ...) const {
        va_list args;
        va_start(args, method);
        jobject result = env->CallStaticObjectMethodV(clazz, method, args);
        va_end(args);
        
        checkException();
        return result;
    }

    jboolean callBooleanMethod(jobject obj, jmethodID method) const {
        jboolean result = env->CallBooleanMethod(obj, method);
        checkException();
        return result;
    }

    jlong callLongMethod(jobject obj, jmethodID method) const {
        jlong result = env->CallLongMethod(obj, method);
        checkException();
        return result;
    }

    jint callIntMethod(jobject obj, jmethodID method) const {
        jint result = env->CallIntMethod(obj, method);
        checkException();
        return result;
    }

    bool checkException() const {
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
            return true;
        }
        return false;
    }

    jclass findClass(const char* name) const {
        jclass clazz = env->FindClass(name);
        if (!clazz) {
            std::cerr << "Failed to find class: " << name << std::endl;
            checkException();
        }
        return clazz;
    }

    jobject createGlobalRef(jobject obj) const {
        if (!obj) return nullptr;
        
        jobject globalRef = env->NewGlobalRef(obj);
        if (!globalRef) {
            std::cerr << "Failed to create global reference" << std::endl;
        }
        return globalRef;
    }
};

bool init_jvm() {
    if (jvm != nullptr) {
        return true;
    }

    JavaVMInitArgs vm_args;
    JavaVMOption options[7];

    std::string classpathStr = build_classpath();
    options[0].optionString = const_cast<char*>(classpathStr.c_str());

    options[1].optionString = const_cast<char*>("-Xmx512m");
    options[2].optionString = const_cast<char*>("-XX:+UseSignalChaining");
    options[3].optionString = const_cast<char*>("-XX:+ExitOnOutOfMemoryError");
    options[4].optionString = const_cast<char*>("-XX:ErrorFile=./hs_err_pid%p.log");
    options[5].optionString = const_cast<char*>("-Xrs"); 
    options[6].optionString = const_cast<char*>("-Dsun.misc.SignalHandler.handlers=allow");

    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 7;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    // Create the JVM
    JNIEnv* env = nullptr;
    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (res != JNI_OK) {
        std::cerr << "Failed to create JVM: " << res << std::endl;
        return false;
    }

    JNIHelper helper(env);
    
    jclass localInvoiceClass = helper.findClass("fr/acinq/eclair/payment/Bolt11Invoice");
    if (!localInvoiceClass) {
        return false;
    }
    
    invoiceClass = static_cast<jclass>(helper.createGlobalRef(localInvoiceClass));
    env->DeleteLocalRef(localInvoiceClass);
    
    if (!invoiceClass) {
        return false;
    }

    deserializeMethod = helper.getMethodID(invoiceClass, "fromString", "(Ljava/lang/String;)Lscala/util/Try;", true);
    if (!deserializeMethod) {
        return false;
    }

    return true;
}

std::optional<jobject> processTryResult(JNIEnv* env, jobject tryObj) {
    if (!tryObj) return std::nullopt;
    
    JNIHelper helper(env);
    LocalRefGuard tryGuard(env, tryObj);
    
    jclass tryClass = env->GetObjectClass(tryObj);
    LocalRefGuard tryClassGuard(env, tryClass);
    
    jmethodID isSuccessMethod = helper.getMethodID(tryClass, "isSuccess", "()Z");
    if (!isSuccessMethod) return std::nullopt;
    
    jboolean isSuccess = helper.callBooleanMethod(tryObj, isSuccessMethod);
    if (!isSuccess) {
        return std::nullopt;
    }
    
    jmethodID getMethod = helper.getMethodID(tryClass, "get", "()Ljava/lang/Object;");
    if (!getMethod) return std::nullopt;
    
    jobject result = helper.callObjectMethod(tryObj, getMethod);
    return result ? std::make_optional(result) : std::nullopt;
}

std::optional<std::string> eclair_des_invoice(const char* invoiceStr) {
    if (!init_jvm() || !jvm) {
        abort();
    }

    JNIThreadGuard threadGuard(jvm);
    JNIEnv* env = threadGuard.getEnv();
    if (!env) {
        return "";
    }

    JNIHelper helper(env);
    std::string formattedResult;

    try {
        jstring jInvoiceStr = helper.toJString(invoiceStr);
        LocalRefGuard jInvoiceStrGuard(env, jInvoiceStr);
        
        if (!jInvoiceStr) {
            return "";
        }

        jobject tryObj = helper.callStaticObjectMethod(invoiceClass, deserializeMethod, jInvoiceStr);
        if (!tryObj) {
            return "";
        }
        
        auto invoiceObjOpt = processTryResult(env, tryObj);
        if (!invoiceObjOpt) {
            return "";
        }
        
        jobject invoiceObj = *invoiceObjOpt;
        LocalRefGuard invoiceObjGuard(env, invoiceObj);
        
        // 1. Payment Hash
        jmethodID paymentHashMethod = helper.getMethodID(invoiceClass, "paymentHash", "()Lfr/acinq/bitcoin/scalacompat/ByteVector32;");
        jobject paymentHashObj = helper.callObjectMethod(invoiceObj, paymentHashMethod);
        LocalRefGuard paymentHashGuard(env, paymentHashObj);
        
        jclass byteVectorClass = env->GetObjectClass(paymentHashObj);
        LocalRefGuard byteVectorClassGuard(env, byteVectorClass);
        
        jmethodID toStringMethod = helper.getMethodID(byteVectorClass, "toString", "()Ljava/lang/String;");
        jstring hashStr = (jstring)helper.callObjectMethod(paymentHashObj, toStringMethod);
        LocalRefGuard hashStrGuard(env, hashStr);
        
        std::string hash = helper.fromJString(hashStr);

        // 2. Amount
        jmethodID amountOptMethod = helper.getMethodID(invoiceClass, "amount_opt", "()Lscala/Option;");
        jobject amountOptObj = helper.callObjectMethod(invoiceObj, amountOptMethod);
        LocalRefGuard amountOptGuard(env, amountOptObj);
        
        jclass optionClass = env->GetObjectClass(amountOptObj);
        LocalRefGuard optionClassGuard(env, optionClass);
        
        jmethodID isDefined = helper.getMethodID(optionClass, "isDefined", "()Z");
        jboolean hasAmount = helper.callBooleanMethod(amountOptObj, isDefined);

        std::string amount = "0";
        if (hasAmount) {
            jmethodID getMethod = helper.getMethodID(optionClass, "get", "()Ljava/lang/Object;");
            jobject amountObj = helper.callObjectMethod(amountOptObj, getMethod);
            LocalRefGuard amountObjGuard(env, amountObj);
            
            jclass millisatoshiClass = env->GetObjectClass(amountObj);
            LocalRefGuard millisatoshiClassGuard(env, millisatoshiClass);
            
            jmethodID toLongMethod = helper.getMethodID(millisatoshiClass, "toLong", "()J");
            jlong amountLong = helper.callLongMethod(amountObj, toLongMethod);
            amount = std::to_string(amountLong);
        }

        // 3. Description
        jmethodID descriptionMethod = helper.getMethodID(invoiceClass, "description", "()Lscala/util/Either;");
        jobject descEitherObj = helper.callObjectMethod(invoiceObj, descriptionMethod);
        LocalRefGuard descEitherGuard(env, descEitherObj);
        
        jclass eitherClass = env->GetObjectClass(descEitherObj);
        LocalRefGuard eitherClassGuard(env, eitherClass);
        
        jmethodID isLeftMethod = helper.getMethodID(eitherClass, "isLeft", "()Z");
        jboolean isLeft = helper.callBooleanMethod(descEitherObj, isLeftMethod);

        std::string description = "";
        if (isLeft) {
            jclass leftClass = helper.findClass("scala/util/Left");
            LocalRefGuard leftClassGuard(env, leftClass);
            
            if (env->IsInstanceOf(descEitherObj, leftClass)) {
                jmethodID valueMethod = helper.getMethodID(leftClass, "value", "()Ljava/lang/Object;");
                jobject valueObj = helper.callObjectMethod(descEitherObj, valueMethod);
                
                if (valueObj) {
                    LocalRefGuard valueObjGuard(env, valueObj);
                    jstring descStr = (jstring)valueObj;
                    description = helper.fromJString(descStr);
                }
            }
        }

        // 4. Node ID (recipient)
        jmethodID nodeIdMethod = helper.getMethodID(invoiceClass, "nodeId", "()Lfr/acinq/bitcoin/scalacompat/Crypto$PublicKey;");
        jobject nodeIdObj = helper.callObjectMethod(invoiceObj, nodeIdMethod);
        LocalRefGuard nodeIdGuard(env, nodeIdObj);
        
        jclass pubKeyClass = env->GetObjectClass(nodeIdObj);
        LocalRefGuard pubKeyClassGuard(env, pubKeyClass);
        
        jmethodID nodeToStringMethod = helper.getMethodID(pubKeyClass, "toString", "()Ljava/lang/String;");
        jstring nodeIdStr = (jstring)helper.callObjectMethod(nodeIdObj, nodeToStringMethod);
        LocalRefGuard nodeIdStrGuard(env, nodeIdStr);
        
        std::string nodeId = helper.fromJString(nodeIdStr);

        // 5. Expiry
        jmethodID expiryMethod = helper.getMethodID(invoiceClass, "relativeExpiry", "()Lscala/concurrent/duration/FiniteDuration;");
        jobject expiryObj = helper.callObjectMethod(invoiceObj, expiryMethod);
        LocalRefGuard expiryGuard(env, expiryObj);
        
        jclass durationClass = env->GetObjectClass(expiryObj);
        LocalRefGuard durationClassGuard(env, durationClass);
        
        jmethodID toSecondsMethod = helper.getMethodID(durationClass, "toSeconds", "()J");
        jlong expirySeconds = helper.callLongMethod(expiryObj, toSecondsMethod);

        // 6. Timestamp
        jmethodID timestampMethod = helper.getMethodID(invoiceClass, "createdAt", "()Lfr/acinq/eclair/TimestampSecond;");
        jobject timestampObj = helper.callObjectMethod(invoiceObj, timestampMethod);
        LocalRefGuard timestampGuard(env, timestampObj);
        
        jclass timestampClass = env->GetObjectClass(timestampObj);
        LocalRefGuard timestampClassGuard(env, timestampClass);
        
        jmethodID toSecondsTimestampMethod = helper.getMethodID(timestampClass, "toLong", "()J");
        jlong timestamp = helper.callLongMethod(timestampObj, toSecondsTimestampMethod);

        // 7. Routing hints count
        jmethodID routingInfoMethod = helper.getMethodID(invoiceClass, "routingInfo", "()Lscala/collection/immutable/Seq;");
        jobject routingInfoObj = helper.callObjectMethod(invoiceObj, routingInfoMethod);
        LocalRefGuard routingInfoGuard(env, routingInfoObj);
        
        jclass seqClass = env->GetObjectClass(routingInfoObj);
        LocalRefGuard seqClassGuard(env, seqClass);
        
        jmethodID sizeMethod = helper.getMethodID(seqClass, "size", "()I");
        jint routingHints = helper.callIntMethod(routingInfoObj, sizeMethod);

        // 8. Min final CLTV expiry
        jmethodID minCltvMethod = helper.getMethodID(invoiceClass, "minFinalCltvExpiryDelta", "()Lfr/acinq/eclair/CltvExpiryDelta;");
        jobject minCltvObj = helper.callObjectMethod(invoiceObj, minCltvMethod);
        LocalRefGuard minCltvGuard(env, minCltvObj);
        
        jclass cltvClass = env->GetObjectClass(minCltvObj);
        LocalRefGuard cltvClassGuard(env, cltvClass);
        
        jmethodID toIntMethod = helper.getMethodID(cltvClass, "toInt", "()I");
        jint minCltv = helper.callIntMethod(minCltvObj, toIntMethod);

        formattedResult = "HASH=" + hash + ";" +
                          "AMOUNT=" + amount + ";" +
                          "DESCRIPTION=" + description + ";" +
                          "RECIPIENT=" + nodeId + ";" +
                          "EXPIRY=" + std::to_string(expirySeconds) + ";" +
                          "TIMESTAMP=" + std::to_string(timestamp) + ";" +
                          "ROUTING_HINTS=" + std::to_string(routingHints) + ";" +
                          "MIN_CLTV=" + std::to_string(minCltv);
    } catch (const std::exception& e) {
        std::cerr << "Exception during JNI call: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Unknown exception during JNI call" << std::endl;
        return "";
    }
    
    return formattedResult.empty() ? "" : std::make_optional(formattedResult);
}

namespace bitcoinfuzz {
    namespace module {
        Eclair::Eclair(void) : BaseModule("Eclair") {}

        std::optional<std::string> Eclair::deserialize_invoice(std::string str) const {
            return eclair_des_invoice(str.c_str());
        }
    }
}