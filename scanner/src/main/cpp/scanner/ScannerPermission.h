//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPERMISSION_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPERMISSION_H_

#include "ScannerInterface.h"

class ScannerPermission : public ScannerInterface {
 public:
  ScannerPermission() {;};
  virtual ~ScannerPermission() {;};

  virtual bool Scan() override;
  virtual bool Initialize() override;

#if defined(_DEBUG)
  bool ScanUnitTest(std::string file_full_path);
#endif
 private :
  Configure config;
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPERMISSION_H_
