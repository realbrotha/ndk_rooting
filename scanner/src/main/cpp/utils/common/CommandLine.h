//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_COMMON_COMMANDLINE_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_COMMON_COMMANDLINE_H_

#include <string>
#include <vector>

class CommandLine {
 public:
  static std::vector<std::string> ExecuteCmd(const char* command_line);
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_UTILS_COMMON_COMMANDLINE_H_
