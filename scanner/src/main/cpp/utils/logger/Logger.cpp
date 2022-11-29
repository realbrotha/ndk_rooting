//
// Created by HyungWoo Lee on 2022/11/07.
//

#include "Logger.h"
#include "GlobalContext.hpp"

namespace {
constexpr char kCALL_BACK_FUNCTION_NAME[] = "LoggerCallback";
constexpr char kJNI_SIGNATURE[] = "(ILjava/lang/String;)V";
constexpr int kTIME_BUFFER_MAX_SIZE = 50;
}

Logger &Logger::GetInstance() {
	static Logger instance_;
	return instance_;
}

bool Logger::LogToApp(LOG_TYPE type, const char *message) {
	if (message == nullptr) {
		return false;
	}
#if defined(_DEBUG)
	if (message != nullptr) {
		if (LOG_TYPE::eINFO == type) {
			LOGI("%s", message);
		} else if (LOG_TYPE::eERROR == type) {
			LOGE("%s", message);
		}
	}
#endif

	JNIEnv* env = nullptr;
	int env_status = GlobalContext::GetInstance().GetJvm()->GetEnv((void **)&env, JNI_VERSION_1_6);
	if (JNI_OK != env_status) {
		if (GlobalContext::GetInstance().GetJvm()->AttachCurrentThread(&env, nullptr) != 0) { // NOTE : env는 current Thread를 기준으로 동작하므로 worker thread에서 접근을 위해 attach 필요
			LOGE("attach failed.");
			return false;
		}
	}
	jclass j_obj_class = env->GetObjectClass(GlobalContext::GetInstance().GetGlobalRef());
	jmethodID j_method_id = env->GetMethodID(j_obj_class, kCALL_BACK_FUNCTION_NAME, kJNI_SIGNATURE);
	if (nullptr == j_obj_class || nullptr == j_method_id) {
		LOGE("GetObject or methodId failed.");
		return false;
	}

	time_t current_time;
	time(&current_time);
	struct tm* time_buffer = gmtime(&current_time);
	time_buffer->tm_hour += 9; // 간편한 utc +9
	if (time_buffer->tm_hour >= 24) time_buffer->tm_hour -= 24; // +9 이후 24시를 넘길경우 처리

	char timeBuffer[kTIME_BUFFER_MAX_SIZE] = {0,};
	strftime(timeBuffer, kTIME_BUFFER_MAX_SIZE, "%H:%M:%S> ", time_buffer);

	std::string message_out = std::string(timeBuffer) + message;

	env->CallVoidMethod(GlobalContext::GetInstance().GetGlobalRef(), j_method_id, type, env->NewStringUTF(message_out.c_str()));

	if (nullptr != j_obj_class) {
		env->DeleteLocalRef(j_obj_class);
	}

	return true;
}
