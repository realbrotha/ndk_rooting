//
// Created by HyungWoo Lee on 2022/11/09.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPROP_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPROP_H_

#include "ScannerInterface.h"

class ScannerProp : public ScannerInterface {
 public:
  ScannerProp() {;};
  virtual ~ScannerProp() {;};

  virtual bool Scan() override;
  virtual bool Initialize() override;

#if defined(_DEBUG)
  bool ScanUnitTest(std::string prop, std::string match_case);
#endif
 private :
  Configure config;
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERPROP_H_
