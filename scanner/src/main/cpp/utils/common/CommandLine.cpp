//
// Created by HyungWoo Lee on 2022/11/08.
//

#include "CommandLine.h"
#include "StringTool.h"
#include "logger/Logger.h"

namespace {
constexpr int kLINE_MAX_BUFFER_SIZE = 1024;
}
std::vector<std::string> CommandLine::ExecuteCmd(const char* command_line)
{
  std::vector<std::string> result;

  FILE* fp = popen(command_line, "r");;
  if(fp) {
    char line_buffer[kLINE_MAX_BUFFER_SIZE] = {0, };
    while(0 != fgets(line_buffer, kLINE_MAX_BUFFER_SIZE - 1, fp)) {
      std::string trim = StringTool::Rtrim(line_buffer); // line feed 제거
      result.push_back(trim);
    }
  }

  return result;
}