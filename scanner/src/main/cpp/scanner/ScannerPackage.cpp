//
// Created by HyungWoo Lee on 2022/11/08.
//

#include "ScannerPackage.h"

#include "logger/Logger.h"
#include "common/StringTool.h"
#include "common/CommandLine.h"

bool ScannerPackage::Initialize() {
  return config.Initialize(CONFIGURE_TYPE::ePACKAGES);
}

bool ScannerPackage::Scan() {
#if defined(_DEBUG)
  Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "Package scan.");
#endif
  bool scan_result = false;
  std::vector<std::string> package_list = GetPackageListFromADB();

  ConfigData rooting_app_list = config.GetConfigList();
  for (std::string package_name : package_list) {
    for (auto it : rooting_app_list) {
      if (package_name == it.second) {
        scan_result = true;
        Logger::GetInstance().LogToApp(LOG_TYPE::eINFO,
                                       StringTool::FormatString("루팅 앱이 탐지되었습니다. [%s]", it.first.c_str()).c_str());
      }
    }
  }
  return scan_result;
}

std::vector<std::string> ScannerPackage::GetPackageListFromADB()
{
  //"/system/bin/pm list packages -f"
  std::vector<std::string> cmd_result = CommandLine::ExecuteCmd("/system/bin/pm list packages -f");
  std::vector<std::string> package_name_list;
  if (!cmd_result.empty()) {
    for (std::string cmd_line : cmd_result) {
      std::string cut_off = cmd_line.substr(cmd_line.rfind('=')+1);
      // package:/system/priv-app/FusedLocation/FusedLocation.apk=com.android.location.fused => com.android.location.fused
      package_name_list.push_back(cut_off);
    }
  }
  return package_name_list;
}

#if defined(_DEBUG)
bool ScannerPackage::ScanUnitTest(std::string package_name) {
  bool scan_result = false;
  std::vector<std::string> package_list = GetPackageListFromADB();

  for (auto &it : package_list) {
    if (package_name == it) {
      scan_result = true;
      break;
    }
  }
  return scan_result;
}
#endif