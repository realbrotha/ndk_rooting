#include "logger/Logger.h"
#include "ScannerManager.h"
#include "android_navigate/GlobalContext.hpp"
#include "utils/configure/Configure.h"

#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_hyungwoo_scanner_ScannerNativeWrapper_StartNative(JNIEnv *env, jobject thiz, jobject a_t_activity, jobject a_t_asset_manager) {
	// prepare Context
	JavaVM* jvm_;
	env->GetJavaVM(&jvm_);

	jobject jobject_ = env->NewGlobalRef(thiz);
	AAssetManager *mgr = AAssetManager_fromJava(env, a_t_asset_manager);
	GlobalContext::GetInstance().SetJvm(jvm_);
	GlobalContext::GetInstance().SetAssetManager(mgr);
	GlobalContext::GetInstance().SetGlobalRef(jobject_);

#if defined(_DEBUG)
	Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "Start scan.");
#endif

#if defined(_DEBUG)
	std::string mode = "Debug Mode";
#else
	std::string mode = "Release Mode";
#endif

	Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, mode.c_str());
	ScannerManager::GetInstance().StartScan();
	return true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hyungwoo_scanner_ScannerNativeWrapper_StopNative(JNIEnv *env, jobject thiz) {
#if defined(_DEBUG)
	Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "Stop scan.");
#endif
	ScannerManager::GetInstance().StopScan();
}