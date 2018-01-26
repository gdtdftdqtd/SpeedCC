#include <memory>

#include <android/log.h>
#include <jni.h>
#include <gtest/gtest.h>
#include "AppDelegate.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

namespace {
std::unique_ptr<AppDelegate> appDelegate;
}

 void cocos_android_app_init(JNIEnv* env) {
     LOGD("cocos_android_app_init");
//     appDelegate.reset(new AppDelegate());
 }

void printOutput(const std::string& strOutput){
    std::istringstream split(strOutput);
    std::string line;
    while (std::getline(split, line)){
        LOGD("%s",line.c_str());
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_AppActivity_RunTest(
        JNIEnv *env,
        jobject /* this */) {

    LOGD("Begin Unit Test");
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    char ArgArray[] = "abc";
    int argc = 1;
    char* argv[] = {ArgArray};
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    std::string output = testing::internal::GetCapturedStdout();
    printOutput(output);
    std::string error = testing::internal::GetCapturedStderr();
    printOutput(error);

    LOGD("End Unit Test");
    return;
}
