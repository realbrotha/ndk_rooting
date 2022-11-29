//
// Created by HyungWoo Lee on 2022/11/09.
//

#include "ScannerProp.h"

#include "logger/Logger.h"
#include "common/StringTool.h"
#include "common/CommandLine.h"

bool ScannerProp::Initialize() {
  return config.Initialize(CONFIGURE_TYPE::eProp);
}

bool ScannerProp::Scan() {
#if defined(_DEBUG)
  Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "Prop scan.");
#endif
  bool scan_result = false;
  ConfigData prop_list = config.GetConfigList();
  for (auto &it : prop_list) {
    std::string command_line = "getprop " + it.second;
    std::vector<std::string> cmd_result = CommandLine::ExecuteCmd(command_line.c_str());

    // cmd 결과같 동일 여부 확인
    // e.g) getprop ro.debuggable => 1
    if(!cmd_result.empty() && cmd_result[0] == it.first) {
      scan_result = true;
      Logger::GetInstance().LogToApp(LOG_TYPE::eINFO,
                                     StringTool::FormatString("루팅 관련 Prop.값이 탐지되었습니다. [%s]", it.second.c_str()).c_str());
    }
  }
  return scan_result;
}

#if defined(_DEBUG)
bool ScannerProp::ScanUnitTest(std::string prop, std::string match_case) {
  bool scan_result = false;

  std::string command_line = "getprop " + prop;
  std::vector<std::string> cmd_result = CommandLine::ExecuteCmd(command_line.c_str());
  if(!cmd_result.empty() && cmd_result[0] == match_case) {
    scan_result = true;
  }
  return scan_result;
}
#endif
