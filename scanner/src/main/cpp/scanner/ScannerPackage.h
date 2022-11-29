//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPACKAGE_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPACKAGE_H_

#include "ScannerInterface.h"

class ScannerPackage: public ScannerInterface  {
 public:
  ScannerPackage() {;};
  virtual ~ScannerPackage() {;};

  virtual bool Scan() override;
  virtual bool Initialize() override;
#if defined(_DEBUG)
  bool ScanUnitTest(std::string package_name);
#endif
 private :
  std::vector<std::string> GetPackageListFromADB();

  Configure config;
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPACKAGE_H_
