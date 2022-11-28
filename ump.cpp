#include <iostream>
#include <jni.h>
#include "ump.h"

static JavaVM* jvm = nullptr;

JNIEnv* createJVM() {
    JNIEnv* env = nullptr;
    JavaVMInitArgs args;
    JavaVMOption options;

    // 初始化Java VM Args
    args.version = JNI_VERSION_1_8;
    args.nOptions = 1;
    options.optionString = (char*)"-Djava.class.path=UmpPostMsg.jar";

    // 初始化Java VM Options
    args.options = &options;
    args.ignoreUnrecognized = JNI_TRUE;

    // 创建JVM
    int ret;
    ret = JNI_CreateJavaVM(&jvm, (void**)&env, &args);
    if (ret < 0 || !env) {
        std::cerr << "Unable to launch JVM: " << ret << std::endl;
    } else {
        std::cout << "JVM Launched!" << std::endl;
    }
    return env;
}

int sendCode(const char* phone, const char* code) {
    // 初始化JVM
    JNIEnv* env = nullptr;
    if (jvm == nullptr) {
        env = createJVM();
    } else {
        int status = jvm->AttachCurrentThread((void**)&env, nullptr);
        if (status != JNI_OK) {
            std::cerr << "Cannot initialize JVM" << std::endl;
            return 1;
        }
    }
    if (env == nullptr) {
        std::cerr << "Cannot initialize JVM" << std::endl;
        return 1;
    }

    jclass clazz;
    jobject obj;
    jmethodID initMethod, sendCodeMethod;
    jstring jphone, jcode;
    jint ret;

    // 初始化发送短信的类
    clazz = env->FindClass("com/esms/UmpPostMsg");
    if (clazz == nullptr) {
        std::cerr << "Cannot find class com.esms.UmpPostMsg" << std::endl;
        return 1;
    }

    // 初始化实例
    initMethod = env->GetMethodID(clazz, "<init>", "()V");
    if (initMethod == nullptr) {
        std::cerr << "Cannot find initialize method" << std::endl;
        return 1;
    }
    obj = env->NewObject(clazz, initMethod);
    if (obj == nullptr) {
        std::cerr << "Cannot find initialize class" << std::endl;
        return 1;
    }

    // 初始化发送短信的方法
    sendCodeMethod = env->GetMethodID(clazz, "sendCode", "(Ljava/lang/String;Ljava/lang/String;)I");
    if (sendCodeMethod == nullptr) {
        std::cerr << "Cannot find method sendCode" << std::endl;
        return 1;
    }

    // 调用发送信息的方法
    jphone = env->NewStringUTF(phone);
    jcode = env->NewStringUTF(code);
    ret = env->CallIntMethod(obj, sendCodeMethod, jphone, jcode);

    // 关闭当前线程
    jvm->DetachCurrentThread();
    return ret;
}

const char* showSms(const char* code) {
    // 初始化JVM
    JNIEnv* env = nullptr;
    if (jvm == nullptr) {
        env = createJVM();
    } else {
        int status = jvm->AttachCurrentThread((void**)&env, nullptr);
        if (status != JNI_OK) {
            std::cerr << "Cannot initialize JVM" << std::endl;
            return "";
        }
    }

    jclass clazz;
    jobject obj;
    jmethodID initMethod, showSmsMethod;
    jstring jcode, jresult;

    // 初始化发送短信的类
    clazz = env->FindClass("com/esms/UmpPostMsg");
    if (clazz == nullptr) {
        std::cerr << "Cannot find class com.esms.UmpPostMsg" << std::endl;
        return "";
    }

    // 初始化实例
    initMethod = env->GetMethodID(clazz, "<init>", "()V");
    if (initMethod == nullptr) {
        std::cerr << "Cannot find initialize method" << std::endl;
        return "";
    }
    obj = env->NewObject(clazz, initMethod);
    if (obj == nullptr) {
        std::cerr << "Cannot find initialize class" << std::endl;
        return "";
    }

    // 初始化发送短信的方法
    showSmsMethod = env->GetMethodID(clazz, "showSms", "(Ljava/lang/String;)Ljava/lang/String;");
    if (showSmsMethod == nullptr) {
        std::cerr << "Cannot find method showSms" << std::endl;
        return "";
    }

    // 调用Java方法
    jcode = env->NewStringUTF(code);
    jresult = (jstring)env->CallObjectMethod(obj, showSmsMethod, jcode);

    // 把jstring转换为const char*
    const char* result = env->GetStringUTFChars(jresult, nullptr);

    // 关闭当前线程
    jvm->DetachCurrentThread();
    return result;
}