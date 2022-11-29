//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERINTERFACE_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERINTERFACE_H_

#include "configure/Configure.h"
#include "ScannerType.h"

#define PURE 0

class ScannerInterface {
 public :
  ScannerInterface() {}
  virtual ~ScannerInterface() {}

  virtual bool Scan() = PURE;
  virtual bool Initialize() = PURE;
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERINTERFACE_H_
