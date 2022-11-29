//
// Created by HyungWoo Lee on 2022/11/08.
//

#include "ScannerPermission.h"

#include "logger/Logger.h"
#include "common/StringTool.h"

#include <sys/stat.h>

bool ScannerPermission::Initialize() {
  return config.Initialize(CONFIGURE_TYPE::ePERMISSION);
}

bool ScannerPermission::Scan() {
#if defined(_DEBUG)
  Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "Permission scan.");
#endif
  bool scan_result = false;
  ConfigData directory_list = config.GetConfigList();
  for (auto &it : directory_list) {
    struct stat dir_status = {0,};

    if (0 == stat(it.second.c_str(), &dir_status)) {
      if (dir_status.st_mode & S_IWOTH) { // other Write
        scan_result = true;
        Logger::GetInstance().LogToApp(LOG_TYPE::eINFO,
                                       StringTool::FormatString("시스템 경로에 권한이 탐지되었습니다. [%s]",
                                                                it.first.c_str()).c_str());
      }
    }
  }
  return scan_result;
}

#if defined(_DEBUG)
bool ScannerPermission::ScanUnitTest(std::string target_path) {
  bool scan_result = false;
  struct stat dir_status = {0,};

  if (0 == stat(target_path.c_str(), &dir_status)) {
    if (dir_status.st_mode & S_IROTH) { // other Read
      scan_result = true;
    }
  }
  return scan_result;
}
#endif
