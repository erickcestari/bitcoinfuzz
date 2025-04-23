#include "module.h"
#include <jni.h>
#include <string>
#include <optional>
#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <iostream>

// Global variables for JNI
static JavaVM *jvm = nullptr;                 // Java VM
static JNIEnv *env = nullptr;                 // JNI environment
static jclass invoiceClass = nullptr;         // Bolt11Invoice class reference
static jmethodID deserializeMethod = nullptr; // deserialize method reference

namespace fs = std::filesystem;

std::string build_classpath(const std::string &libDir = "./modules/eclair/lib")
{
    std::ostringstream cp;
    cp << "-Djava.class.path=";
    bool first = true;

    for (const auto &entry : fs::directory_iterator(libDir))
    {
        if (entry.path().extension() == ".jar")
        {
            if (!first)
                cp << ":";
            cp << entry.path().string();
            first = false;
        }
    }

    return cp.str();
}

bool init_jvm()
{
    if (jvm != nullptr)
    {
        return true; // Already initialized
    }

    // JVM initialization arguments
    JavaVMInitArgs vm_args;
    JavaVMOption options[2];

    // Set classpath to include the Eclair JAR
    std::string classpathStr = build_classpath("./modules/eclair/lib");
    options[0].optionString = const_cast<char *>(classpathStr.c_str());

    // Adjust heap size if needed
    options[1].optionString = const_cast<char *>("-Xmx512m");

    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 2;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;

    // Create the JVM
    jint res = JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
    if (res != JNI_OK)
    {
        std::cerr << "Failed to create JVM: " << res << std::endl;
        return false;
    }
    jclass localInvoiceObjectClass = env->FindClass("fr/acinq/eclair/payment/Bolt11Invoice");
    if (localInvoiceObjectClass == nullptr)
    {
        std::cerr << "Failed to find Bolt11Invoice class" << std::endl;
        if (env->ExceptionCheck())
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return false;
    }
    invoiceClass = static_cast<jclass>(env->NewGlobalRef(localInvoiceObjectClass));
    env->DeleteLocalRef(localInvoiceObjectClass);

    // Use GetStaticMethodID instead of GetMethodID because fromString is a static method
    deserializeMethod = env->GetStaticMethodID(invoiceClass, "fromString", "(Ljava/lang/String;)Lscala/util/Try;");

    if (deserializeMethod == nullptr)
    {
        std::cerr << "Failed to find fromString method" << std::endl;
        if (env->ExceptionCheck())
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return false;
    }

    return true;
}

// Clean up JVM resources
void cleanup_jvm()
{
    if (jvm != nullptr)
    {
        if (invoiceClass != nullptr && env != nullptr)
        {
            env->DeleteGlobalRef(invoiceClass);
            invoiceClass = nullptr;
        }

        jvm->DestroyJavaVM();
        jvm = nullptr;
        env = nullptr;
        deserializeMethod = nullptr;
    }
}

std::optional<std::string> eclair_des_invoice(const char *invoiceStr)
{
    // Initialize JVM if not already done
    if (!init_jvm())
    {
        return std::nullopt;
    }

    // Attach to the current thread if needed
    JNIEnv *currEnv;
    bool detach = false;
    jint getEnvStat = jvm->GetEnv((void **)&currEnv, JNI_VERSION_1_8);

    if (getEnvStat == JNI_EDETACHED)
    {
        if (jvm->AttachCurrentThread((void **)&currEnv, nullptr) != JNI_OK)
        {
            std::cerr << "Failed to attach thread to JVM" << std::endl;
            return std::nullopt;
        }
        detach = true;
    }
    else if (getEnvStat != JNI_OK)
    {
        std::cerr << "Failed to get JNI environment" << std::endl;
        return std::nullopt;
    }

    // Convert C string to Java string
    jstring jInvoiceStr = currEnv->NewStringUTF(invoiceStr);

    // Call the fromString method to get the invoice object
    jobject invoiceObj = nullptr;
    std::string formattedResult;

    try
    {
        // Get the Try object from invoiceClass.fromString(invoiceStr)
        jobject tryObj = currEnv->CallStaticObjectMethod(invoiceClass, deserializeMethod, jInvoiceStr);

        if (currEnv->ExceptionCheck())
        {
            currEnv->ExceptionDescribe();
            currEnv->ExceptionClear();
            currEnv->DeleteLocalRef(jInvoiceStr);

            if (detach)
            {
                jvm->DetachCurrentThread();
            }

            return std::nullopt;
        }

        // Get the isSuccess method from scala.util.Try
        jclass tryClass = currEnv->GetObjectClass(tryObj);
        jmethodID isSuccessMethod = currEnv->GetMethodID(tryClass, "isSuccess", "()Z");
        jboolean isSuccess = currEnv->CallBooleanMethod(tryObj, isSuccessMethod);

        if (isSuccess)
        {
            // Get the get method from scala.util.Try
            jmethodID getMethod = currEnv->GetMethodID(tryClass, "get", "()Ljava/lang/Object;");
            invoiceObj = currEnv->CallObjectMethod(tryObj, getMethod);

            if (invoiceObj != nullptr)
            {
                // Extract each required field from the invoice object
                std::cout << "Invoice string: " << invoiceStr << std::endl;

                // 1. Get paymentHash
                jmethodID paymentHashMethod = currEnv->GetMethodID(invoiceClass, "paymentHash", "()Lfr/acinq/bitcoin/scalacompat/ByteVector32;");
                jobject paymentHashObj = currEnv->CallObjectMethod(invoiceObj, paymentHashMethod);
                jclass byteVectorClass = currEnv->GetObjectClass(paymentHashObj);
                jmethodID toStringMethod = currEnv->GetMethodID(byteVectorClass, "toString", "()Ljava/lang/String;");
                jstring hashStr = (jstring)currEnv->CallObjectMethod(paymentHashObj, toStringMethod);
                const char *hashCStr = currEnv->GetStringUTFChars(hashStr, nullptr);
                std::string hash(hashCStr);
                currEnv->ReleaseStringUTFChars(hashStr, hashCStr);

                std::cout << "Payment hash: " << hash << std::endl;

                // 2. Get amount
                jmethodID amountOptMethod = currEnv->GetMethodID(invoiceClass, "amount_opt", "()Lscala/Option;");
                jobject amountOptObj = currEnv->CallObjectMethod(invoiceObj, amountOptMethod);
                jclass optionClass = currEnv->GetObjectClass(amountOptObj);
                jmethodID isDefined = currEnv->GetMethodID(optionClass, "isDefined", "()Z");
                jboolean hasAmount = currEnv->CallBooleanMethod(amountOptObj, isDefined);

                std::string amount = "0";
                if (hasAmount)
                {
                    jmethodID getMethod = currEnv->GetMethodID(optionClass, "get", "()Ljava/lang/Object;");
                    jobject amountObj = currEnv->CallObjectMethod(amountOptObj, getMethod);
                    jclass millisatoshiClass = currEnv->GetObjectClass(amountObj);
                    jmethodID toLongMethod = currEnv->GetMethodID(millisatoshiClass, "toLong", "()J");
                    jlong amountLong = currEnv->CallLongMethod(amountObj, toLongMethod);
                    amount = std::to_string(amountLong);
                }

                std::cout << "Amount: " << amount << std::endl;

                // 3. Get description
                jmethodID descriptionMethod = currEnv->GetMethodID(invoiceClass, "description", "()Lscala/util/Either;");
                std::cout << "descriptionMethod: " << descriptionMethod << std::endl;
                jobject descEitherObj = currEnv->CallObjectMethod(invoiceObj, descriptionMethod);
                std::cout << "descEitherObj: " << descEitherObj << std::endl;
                jclass eitherClass = currEnv->GetObjectClass(descEitherObj);
                std::cout << "eitherClass: " << eitherClass << std::endl;
                jmethodID isLeftMethod = currEnv->GetMethodID(eitherClass, "isLeft", "()Z");
                std::cout << "isLeftMethod: " << isLeftMethod << std::endl;
                jboolean isLeft = currEnv->CallBooleanMethod(descEitherObj, isLeftMethod);

                std::string description = "";
                if (isLeft)
                {
                    jclass leftClass = currEnv->FindClass("scala/util/Left");
                    if (currEnv->IsInstanceOf(descEitherObj, leftClass))
                    {
                        jmethodID valueMethod = currEnv->GetMethodID(leftClass, "value", "()Ljava/lang/Object;");
                        jobject valueObj = currEnv->CallObjectMethod(descEitherObj, valueMethod);
                        if (currEnv->ExceptionCheck())
                        {
                            currEnv->ExceptionDescribe();
                            currEnv->ExceptionClear();
                        }

                        if (valueObj != nullptr)
                        {
                            jstring descStr = (jstring)valueObj;
                            const char *descCStr = currEnv->GetStringUTFChars(descStr, nullptr);
                            description = descCStr;
                            currEnv->ReleaseStringUTFChars(descStr, descCStr);
                        }
                    }
                }

                std ::cout << "Description: " << description << std::endl;

                // Let's print out all methods of the class to debug
                jmethodID getClass = currEnv->GetMethodID(invoiceClass, "getClass", "()Ljava/lang/Class;");
                jobject classObj = currEnv->CallObjectMethod(invoiceObj, getClass);
                jclass clsClass = currEnv->GetObjectClass(classObj);
                jmethodID getMethods = currEnv->GetMethodID(clsClass, "getMethods", "()[Ljava/lang/reflect/Method;");
                jobjectArray methodsArray = (jobjectArray)currEnv->CallObjectMethod(classObj, getMethods);

                jsize methodCount = currEnv->GetArrayLength(methodsArray);
                std::cout << "Available methods (" << methodCount << "):" << std::endl;

                jclass methodClass = currEnv->FindClass("java/lang/reflect/Method");
                jmethodID nameMethod = currEnv->GetMethodID(methodClass, "getName", "()Ljava/lang/String;");

                for (jsize i = 0; i < methodCount; i++)
                {
                    jobject methodObj = currEnv->GetObjectArrayElement(methodsArray, i);
                    jstring nameStr = (jstring)currEnv->CallObjectMethod(methodObj, nameMethod);
                    const char *name = currEnv->GetStringUTFChars(nameStr, nullptr);
                    std::cout << "  " << name << std::endl;
                    currEnv->ReleaseStringUTFChars(nameStr, name);
                    currEnv->DeleteLocalRef(methodObj);
                    currEnv->DeleteLocalRef(nameStr);
                }

                // 4. Get nodeId (recipient)
                jmethodID nodeIdMethod = currEnv->GetMethodID(invoiceClass, "nodeId", "()Lfr/acinq/bitcoin/scalacompat/Crypto$PublicKey;");
                if (nodeIdMethod == nullptr)
                {
                    std::cerr << "Failed to find nodeId method" << std::endl;
                }

                // Call the nodeId method to get the PublicKey object
                jobject nodeIdObj = currEnv->CallObjectMethod(invoiceObj, nodeIdMethod);
                if (nodeIdObj == nullptr)
                {
                    std::cerr << "Failed to get nodeId object" << std::endl;
                }

                // Get the PublicKey class
                jclass pubKeyClass = currEnv->GetObjectClass(nodeIdObj);
                if (pubKeyClass == nullptr)
                {
                    std::cerr << "Failed to get PublicKey class" << std::endl;
                }

                // Get the toString method from PublicKey
                toStringMethod = currEnv->GetMethodID(pubKeyClass, "toString", "()Ljava/lang/String;");
                if (toStringMethod == nullptr)
                {
                    std::cerr << "Failed to find toString method" << std::endl;
                }

                // Call toString() on the PublicKey object
                jstring nodeIdStr = (jstring)currEnv->CallObjectMethod(nodeIdObj, toStringMethod);
                if (nodeIdStr == nullptr)
                {
                    std::cerr << "Failed to get nodeId string" << std::endl;
                }

                // Convert Java string to C++ string
                const char *nodeIdCStr = currEnv->GetStringUTFChars(nodeIdStr, nullptr);
                std::string nodeId(nodeIdCStr);
                currEnv->ReleaseStringUTFChars(nodeIdStr, nodeIdCStr);

                // Clean up references
                currEnv->DeleteLocalRef(nodeIdObj);
                currEnv->DeleteLocalRef(pubKeyClass);
                currEnv->DeleteLocalRef(nodeIdStr);

                std::cout << "Node ID: " << nodeId << std::endl;

                // 5. Get expiry
                jmethodID expiryMethod = currEnv->GetMethodID(invoiceClass, "relativeExpiry", "()Lscala/concurrent/duration/FiniteDuration;");
                jobject expiryObj = currEnv->CallObjectMethod(invoiceObj, expiryMethod);
                jclass durationClass = currEnv->GetObjectClass(expiryObj);
                jmethodID toSecondsMethod = currEnv->GetMethodID(durationClass, "toSeconds", "()J");
                jlong expirySeconds = currEnv->CallLongMethod(expiryObj, toSecondsMethod);

                // 6. Get timestamp
                jmethodID timestampMethod = currEnv->GetMethodID(invoiceClass, "createdAt", "()Lfr/acinq/bitcoin/TimestampSecond;");
                jobject timestampObj = currEnv->CallObjectMethod(invoiceObj, timestampMethod);
                jclass timestampClass = currEnv->GetObjectClass(timestampObj);
                jmethodID toSecondsTimestampMethod = currEnv->GetMethodID(timestampClass, "toLong", "()J");
                jlong timestamp = currEnv->CallLongMethod(timestampObj, toSecondsTimestampMethod);

                // 7. Get routing hints count
                jmethodID routingInfoMethod = currEnv->GetMethodID(invoiceClass, "routingInfo", "()Lscala/collection/Seq;");
                jobject routingInfoObj = currEnv->CallObjectMethod(invoiceObj, routingInfoMethod);
                jclass seqClass = currEnv->GetObjectClass(routingInfoObj);
                jmethodID sizeMethod = currEnv->GetMethodID(seqClass, "size", "()I");
                jint routingHints = currEnv->CallIntMethod(routingInfoObj, sizeMethod);

                // 8. Get min final CLTV expiry
                jmethodID minCltvMethod = currEnv->GetMethodID(invoiceClass, "minFinalCltvExpiryDelta", "()Lfr/acinq/eclair/CltvExpiryDelta;");
                jobject minCltvObj = currEnv->CallObjectMethod(invoiceObj, minCltvMethod);
                jclass cltvClass = currEnv->GetObjectClass(minCltvObj);
                jmethodID toIntMethod = currEnv->GetMethodID(cltvClass, "toInt", "()I");
                jint minCltv = currEnv->CallIntMethod(minCltvObj, toIntMethod);

                // Format the result as required
                formattedResult = "HASH=" + hash + ";" +
                                  "AMOUNT=" + amount + ";" +
                                  "DESCRIPTION=" + description + ";" +
                                  "RECIPIENT=" + nodeId + ";" +
                                  "EXPIRY=" + std::to_string(expirySeconds) + ";" +
                                  "TIMESTAMP=" + std::to_string(timestamp) + ";" +
                                  "ROUTING_HINTS=" + std::to_string(routingHints) + ";" +
                                  "MIN_CLTV=" + std::to_string(minCltv);
            }
        }

        // Clean up local references
        currEnv->DeleteLocalRef(tryObj);
        currEnv->DeleteLocalRef(tryClass);
        if (invoiceObj != nullptr)
        {
            currEnv->DeleteLocalRef(invoiceObj);
        }
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception during JNI call" << std::endl;
    }

    // Final cleanup
    currEnv->DeleteLocalRef(jInvoiceStr);

    if (detach)
    {
        jvm->DetachCurrentThread();
    }

    if (formattedResult.empty())
    {
        return std::nullopt;
    }

    std::cout << "Formatted result: " << formattedResult << std::endl;

    return formattedResult;
}

namespace bitcoinfuzz
{
    namespace module
    {
        Eclair::Eclair(void) : BaseModule("Eclair") {}

        std::optional<std::string> Eclair::deserialize_invoice(std::string str) const
        {
            return eclair_des_invoice(str.c_str());
        }
    }
}