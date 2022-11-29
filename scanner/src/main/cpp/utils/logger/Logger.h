//
// Created by hwoolee-MN2 on 2022/11/07.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_LOGGER_LOGGER_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_LOGGER_LOGGER_H_

#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "HWHW", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "HWHW", __VA_ARGS__))

enum class LOG_TYPE : int {
  eINFO = 1,
  eERROR = 2
};

class Logger {
 public :
  static Logger &GetInstance();
  bool LogToApp(LOG_TYPE type, const char *message);
 private :
  Logger() {;};
  ~Logger() {;};
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_LOGGER_LOGGER_H_
