//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERFACTORY_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERFACTORY_H_

#include "ScannerInterface.h"
#include "ScannerType.h"

#include "ScannerPackage.h"
#include "ScannerBinary.h"
#include "ScannerPermission.h"
#include "ScannerWhich.h"
#include "ScannerProp.h"

class ScannerFactory {
 public:
  static ScannerInterface *CreateScanner(eSCANNER_TYPE scanner_type) {
    switch (scanner_type) {
      case eSCANNER_TYPE::ePACKAGES:    return new ScannerPackage();
      case eSCANNER_TYPE::eBINARY:      return new ScannerBinary();
      case eSCANNER_TYPE::ePERMISSION:  return new ScannerPermission();
      case eSCANNER_TYPE::eWHICH:       return new ScannerWhich();
      case eSCANNER_TYPE::ePROP:        return new ScannerProp();
      default : return nullptr;
    }
  }
};
#endif //ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERFACTORY_H_
