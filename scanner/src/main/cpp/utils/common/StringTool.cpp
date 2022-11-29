//
// Created by HyungWoo Lee on 2022/11/08.
//

#include "StringTool.h"

#include <sstream>
#include <vector>

std::string StringTool::Rtrim(std::string input, const char* target)
{
  input.erase(input.find_last_not_of(target) + 1);
  return input;
}

std::vector<std::string> StringTool::Split(std::string input, char delimiter)
{
  std::vector<std::string> result;
  std::stringstream ss(input);

  std::string temp;
  while (getline(ss, temp, delimiter)) {
    result.push_back(temp);
  }

  return result;
};

std::string StringTool::FormatString(const char *fmt, ...) {
  int length = 0;
  char *format_buffer = nullptr;
  std::string result = "";
  va_list args;

  if (fmt == nullptr) {
    return result;
  }

  va_start(args, fmt);

  length = vsnprintf(nullptr, 0, fmt, args);
  va_end(args);
  va_start(args, fmt);

  format_buffer = new char[length + 1];
  memset(format_buffer, 0, length + 1);
  vsnprintf(format_buffer, length + 1, fmt, args);

  result.assign(format_buffer);
  if (format_buffer != nullptr) delete[] format_buffer;

  va_end(args);

  return result;
}