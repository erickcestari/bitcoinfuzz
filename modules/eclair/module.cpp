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
static JavaVM *jvm = nullptr;       // Java VM
static JNIEnv *env = nullptr;       // JNI environment
static jclass invoiceClass = nullptr; // Bolt11Invoice class reference
static jmethodID deserializeMethod = nullptr; // deserialize method reference

namespace fs = std::filesystem;

std::string build_classpath(const std::string& libDir = "./modules/eclair/lib") {
    std::ostringstream cp;
    cp << "-Djava.class.path=";
    bool first = true;

    for (const auto& entry : fs::directory_iterator(libDir)) {
        if (entry.path().extension() == ".jar") {
            if (!first) cp << ":";
            cp << entry.path().string();
            first = false;
        }
    }

    return cp.str();
}

bool init_jvm() {
    if (jvm != nullptr) {
        return true; // Already initialized
    }

    // JVM initialization arguments
    JavaVMInitArgs vm_args;
    JavaVMOption options[2];
    
    // Set classpath to include the Eclair JAR
    std::string classpathStr = build_classpath("./modules/eclair/lib");
    options[0].optionString = const_cast<char*>(classpathStr.c_str());
    
    // Adjust heap size if needed
    options[1].optionString = const_cast<char*>("-Xmx512m");
    
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 2;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;
    
    // Create the JVM
    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (res != JNI_OK) {
        std::cerr << "Failed to create JVM: " << res << std::endl;
        return false;
    }
    jclass localInvoiceObjectClass = env->FindClass("fr/acinq/eclair/payment/Bolt11Invoice");
    if (localInvoiceObjectClass == nullptr) {
        std::cerr << "Failed to find Bolt11Invoice class" << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return false;
    }
    invoiceClass = static_cast<jclass>(env->NewGlobalRef(localInvoiceObjectClass));
    env->DeleteLocalRef(localInvoiceObjectClass);
    
    // Use GetStaticMethodID instead of GetMethodID because fromString is a static method
    deserializeMethod = env->GetStaticMethodID(invoiceClass, "fromString", "(Ljava/lang/String;)Lscala/util/Try;");
    
    if (deserializeMethod == nullptr) {
        std::cerr << "Failed to find fromString method" << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return false;
    }
    
    return true;
}


// Clean up JVM resources
void cleanup_jvm() {
    if (jvm != nullptr) {
        if (invoiceClass != nullptr && env != nullptr) {
            env->DeleteGlobalRef(invoiceClass);
            invoiceClass = nullptr;
        }
        
        jvm->DestroyJavaVM();
        jvm = nullptr;
        env = nullptr;
        deserializeMethod = nullptr;
    }
}

// The actual function to deserialize the invoice
std::optional<std::string> eclair_des_invoice(const char* invoiceStr) {
    std::cout << "Invoice: " << invoiceStr << std::endl;
    // Initialize JVM if not already done
    if (!init_jvm()) {
        return std::nullopt;
    }
    
    // Attach to the current thread if needed
    JNIEnv *currEnv;
    bool detach = false;
    jint getEnvStat = jvm->GetEnv((void **)&currEnv, JNI_VERSION_1_8);
    
    if (getEnvStat == JNI_EDETACHED) {
        if (jvm->AttachCurrentThread((void **)&currEnv, nullptr) != JNI_OK) {
            std::cerr << "Failed to attach thread to JVM" << std::endl;
            return std::nullopt;
        }
        detach = true;
    } else if (getEnvStat != JNI_OK) {
        std::cerr << "Failed to get JNI environment" << std::endl;
        return std::nullopt;
    }
    
    // Convert C string to Java string
    jstring jInvoiceStr = currEnv->NewStringUTF(invoiceStr);

    std::cout << "string converted: " << invoiceStr << std::endl;
    
    // Call the deserialize method
    jobject invoiceObj = nullptr;
    
    try {
        invoiceObj = currEnv->CallStaticObjectMethod(invoiceClass, deserializeMethod, jInvoiceStr);
        
        // Check for exceptions
        if (currEnv->ExceptionCheck()) {
            currEnv->ExceptionDescribe();
            currEnv->ExceptionClear();
            currEnv->DeleteLocalRef(jInvoiceStr);
            
            if (detach) {
                jvm->DetachCurrentThread();
            }
            
            return std::nullopt;
        }
        
        // If deserialization was successful, get the string representation
        if (invoiceObj != nullptr) {
            // Get the toString method from the invoice object
            jmethodID toStringMethod = currEnv->GetMethodID(invoiceClass, "toString", "()Ljava/lang/String;");
            
            if (toStringMethod != nullptr) {
                jstring resultStr = static_cast<jstring>(currEnv->CallObjectMethod(invoiceObj, toStringMethod));
                
                // Convert Java string to C++ string
                const char *cstr = currEnv->GetStringUTFChars(resultStr, nullptr);
                std::string result(cstr);
                currEnv->ReleaseStringUTFChars(resultStr, cstr);
                
                // Clean up local references
                currEnv->DeleteLocalRef(resultStr);
                currEnv->DeleteLocalRef(invoiceObj);
                currEnv->DeleteLocalRef(jInvoiceStr);
                
                if (detach) {
                    jvm->DetachCurrentThread();
                }
                
                return result;
            }
        }
    } catch (...) {
        std::cerr << "Caught unknown exception during JNI call" << std::endl;
    }
    
    // Clean up local references
    if (invoiceObj != nullptr) {
        currEnv->DeleteLocalRef(invoiceObj);
    }
    currEnv->DeleteLocalRef(jInvoiceStr);
    
    if (detach) {
        jvm->DetachCurrentThread();
    }
    
    return std::nullopt;
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