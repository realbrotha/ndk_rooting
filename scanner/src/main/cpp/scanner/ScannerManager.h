//
// Created by hwoolee-MN2 on 2022/11/07.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERMANAGER_H_
#define ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERMANAGER_H_

#include "ScannerType.h"
#include "ScannerInterface.h"
#include "logger/Logger.h"

#include <atomic>
#include <thread>

class ScannerManager {
 public :
  static ScannerManager &GetInstance();

  bool StartScan();
  void StopScan();

 private :
  ScannerManager();
  ~ScannerManager();

  void InterfaceListClear();
  bool StartScanThread();
  void StopScanThread();

  void ScannerWorker();

  std::atomic<bool> is_running_;
  std::unique_ptr<std::thread> scan_thread_;
  std::vector<std::unique_ptr<ScannerInterface>> scanner_list;
};

#endif //ROOTING_SCANNER_SRC_MAIN_CPP_SCANNER_SCANNERMANAGER_H_
