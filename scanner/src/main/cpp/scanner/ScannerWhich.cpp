//
// Created by HyungWoo Lee on 2022/11/08.
//

#include "ScannerWhich.h"
#include "logger/Logger.h"
#include "common/CommandLine.h"
#include "common/StringTool.h"

bool ScannerWhich::Initialize() {
  return config.Initialize(CONFIGURE_TYPE::eDIRECTORY) && config.Initialize(CONFIGURE_TYPE::eWHICH);
}

bool ScannerWhich::Scan() {
#if defined(_DEBUG)
  Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "Which scan.");
#endif
  bool scan_result = false;
  ConfigData which_tango_list = config.GetConfigList();
  for (auto &it : which_tango_list) {
    std::string command_line = "which " + it.second;
    std::vector<std::string> cmd_result = CommandLine::ExecuteCmd(command_line.c_str());

    // cmd 라인 실행된 결과가 존재한다면 탐지로 간주한다.
    // (e.g, which ls --> /system/bin/ls, 존재한다면 경로가 넘어옴)
    if(!cmd_result.empty()) {
      scan_result = true;
      Logger::GetInstance().LogToApp(LOG_TYPE::eINFO,
                                     StringTool::FormatString("루팅 관련 파일이 탐지되었습니다. [%s]", it.first.c_str()).c_str());
    }
  }
  return scan_result;
}

#if defined(_DEBUG)
bool ScannerWhich::ScanUnitTest(std::string target) {
  bool scan_result = false;
  std::string command_line = "which " + target;
  std::vector<std::string> cmd_result = CommandLine::ExecuteCmd(command_line.c_str());

  // cmd 라인 실행된 결과가 존재한다면 탐지로 간주한다.
  // (e.g, which ls --> /system/bin/ls, 존재한다면 경로가 넘어옴)
  if(!cmd_result.empty()) {
    scan_result = true;
  }
  return scan_result;
}
#endif