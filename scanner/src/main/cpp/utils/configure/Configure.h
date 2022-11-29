//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_CONFIGURE_H
#define ROOTING_CONFIGURE_H

#include "simpleini.h"

#include <vector>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

enum class CONFIGURE_TYPE : int {
  ePACKAGES = 0,
  eDIRECTORY,
  eBINARY,
  ePERMISSION,
  eWHICH,
  eProp = 5,
};
namespace {
  using ConfigData = std::vector<std::pair<std::string, std::string>>;
}
class Configure {
 public :
  Configure() {;};
  ~Configure() {;};

  bool Initialize(CONFIGURE_TYPE type);
  ConfigData GetConfigList();
 private :
  std::string GetSectionName(CONFIGURE_TYPE type);

  CONFIGURE_TYPE type_;
  CSimpleIniA simple_ini_;
  CSimpleIniA::TNamesDepend key_list_;
};

#endif //ROOTING_CONFIGURE_H
