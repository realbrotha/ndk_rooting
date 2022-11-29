//
// Created by HyungWoo Lee on 2022/11/08.
//

#include "Configure.h"
#include "logger/Logger.h"
#include "GlobalContext.hpp"
#include "common/StringTool.h"

namespace {
constexpr int kPERFECT_CONFIG_DATA_COUNT = 2;
}

std::string Configure::GetSectionName(CONFIGURE_TYPE type) {
  std::string section_name;
  switch (type)
  {
    case CONFIGURE_TYPE::ePACKAGES : section_name = "PACKAGES"; break;
    case CONFIGURE_TYPE::eDIRECTORY : section_name = "DIRECTORY"; break;
    case CONFIGURE_TYPE::eBINARY : section_name = "BINARY"; break;
    case CONFIGURE_TYPE::ePERMISSION : section_name = "PERMISSION"; break;
    case CONFIGURE_TYPE::eWHICH : section_name = "WHICH"; break;
    case CONFIGURE_TYPE::eProp : section_name = "PROP"; break;
    default : section_name = ""; break; // error case
  }
  return section_name;
}

ConfigData Configure::GetConfigList() {
  ConfigData result;
  CSimpleIniA::TNamesDepend::const_iterator it;
  for (it = key_list_.begin(); it != key_list_.end(); ++it) {
    const char* pv = simple_ini_.GetValue(GetSectionName(type_).c_str(), it->pItem);
    std::string value(pv);

    std::vector<std::string> tokenized = StringTool::Split(value, ':');
    if (tokenized.size() == kPERFECT_CONFIG_DATA_COUNT) {
      result.push_back(std::make_pair(tokenized[0], tokenized[1]));
    }
  }
  return result;
}

bool Configure::Initialize(CONFIGURE_TYPE type) {
  type_ = type;
  AAsset *a_asset = AAssetManager_open(GlobalContext::GetInstance().GetAssetManager(), "scanner.cfg", AASSET_MODE_UNKNOWN);

  if (nullptr == a_asset) {
    Logger::GetInstance().LogToApp(LOG_TYPE::eERROR, "load config file failed. (AAsset null)");
    return false;
  }

  int configure_file_size = AAsset_getLength(a_asset);
  if (configure_file_size <= 0) {
    Logger::GetInstance().LogToApp(LOG_TYPE::eERROR, "wrong config file size.");
    return false;
  }

  std::vector<uint8_t> raw_data_(configure_file_size, 0);
  //char * buf = (char *)malloc(sizeof(char) * configure_file_size);
  AAsset_read(a_asset, raw_data_.data(), configure_file_size);
  AAsset_close(a_asset);

  if (SI_OK != simple_ini_.LoadData(reinterpret_cast<char *>(raw_data_.data()), raw_data_.size())) {
    Logger::GetInstance().LogToApp(LOG_TYPE::eERROR, "set ini failed. (simple ini)");
    return false;
  } else {
    simple_ini_.GetAllKeys(GetSectionName(type_).c_str(), key_list_);
  }
  return true;
}
