//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERBINARY_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERBINARY_H_

#include "ScannerInterface.h"

class ScannerBinary : public ScannerInterface {
 public:
  ScannerBinary() {;};
  virtual ~ScannerBinary() {;};

  virtual bool Scan() override;
  virtual bool Initialize() override;

#if defined(_DEBUG)
  bool ScanUnitTest(std::string file_full_path);
#endif
 private:
  Configure config_for_directory;
  Configure config_for_binary;
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERBINARY_H_
