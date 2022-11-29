//
// Created by HyungWoo Lee on 2022/11/08.
//

#include "ScannerBinary.h"
#include "logger/Logger.h"
#include "common/StringTool.h"

#include <unistd.h>

bool ScannerBinary::Initialize() {
  return config_for_directory.Initialize(CONFIGURE_TYPE::eDIRECTORY) && config_for_binary.Initialize(CONFIGURE_TYPE::eBINARY);
}

bool ScannerBinary::Scan() {
#if defined(_DEBUG)
  Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "Binary scan.");
#endif
  bool scan_result = false;
  ConfigData directory_list = config_for_directory.GetConfigList();
  ConfigData binary_list = config_for_binary.GetConfigList();

  for (auto &directory_it : directory_list) {
    for (auto &binary_it : binary_list) {
      std::string tango_file_full_path = directory_it.second + "/" + binary_it.second;
      if(0 == access(tango_file_full_path.c_str(), F_OK)) {
        scan_result = true;
        Logger::GetInstance().LogToApp(LOG_TYPE::eINFO,
                                       StringTool::FormatString("루팅 관련 파일이 탐지되었습니다. [%s]", tango_file_full_path.c_str()).c_str());
      }
    }
  }
  return scan_result;
}

#if defined(_DEBUG)
bool ScannerBinary::ScanUnitTest(std::string target_path) {
  bool scan_result = false;
  if(0 == access(target_path.c_str(), F_OK)) {
    scan_result = true;
  }
  return scan_result;
}
#endif
