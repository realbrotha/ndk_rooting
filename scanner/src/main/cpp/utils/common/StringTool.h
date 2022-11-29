//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_COMMON_STRINGTOOL_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_COMMON_STRINGTOOL_H_

#include <string>

class StringTool {
 public :
  static std::string Rtrim(std::string input, const char* target = " \t\n\r\f\v");
  static std::vector<std::string> Split(std::string input, char delimiter);
  static std::string FormatString(const char *fmt, ...);
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_COMMON_STRINGTOOL_H_
