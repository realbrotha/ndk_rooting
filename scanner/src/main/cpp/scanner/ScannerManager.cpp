//
// Created by HyungWoo Lee on 2022/11/07.
//

#include "ScannerManager.h"
#include "ScannerType.h"
#include "ScannerFactory.h"

#include <unistd.h>
ScannerManager &ScannerManager::GetInstance() {
  static ScannerManager instance_;
  return instance_;
}

bool ScannerManager::StartScan() {
  return StartScanThread();
}

void ScannerManager::StopScan() {
  StopScanThread();
}

bool ScannerManager::StartScanThread() {
  bool result = false;
  if (scan_thread_.get() && scan_thread_->joinable()) {
    return true;
  }

  try {
    scan_thread_.reset(new std::thread(&ScannerManager::ScannerWorker, std::ref(*this)));
    result = true;
  } catch (std::exception &ex) {
    LOGE("thread ex -1\n");
  } catch (...) {
    LOGE("thread ex -2\n");
  }
  return result;
}

void ScannerManager::StopScanThread() {
  if (scan_thread_.get()) {
    if (std::this_thread::get_id() == scan_thread_->get_id()) {
      scan_thread_->detach();
      InterfaceListClear();   // interface clear
    } else {
      try {
        is_running_ = false;
        scan_thread_->join();
        InterfaceListClear();   // interface clear
      } catch (const std::exception &ex) {
        LOGE("thread stop ex -1 \n");
      } catch (...) {
        LOGE("thread stop ex -2\n");
      }
    }
  }
}

void ScannerManager::ScannerWorker() {
  is_running_ = true;
  Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "Scanner start.");

  for (int type = static_cast<int>(eSCANNER_TYPE::eSCANNER_TYPE_START); type <= static_cast<int>(eSCANNER_TYPE::eSCANNER_TYPE_END); ++type) {
    ScannerInterface *scanner_buffer = ScannerFactory::CreateScanner(static_cast<eSCANNER_TYPE>(type));
    if (scanner_buffer) {
      if (scanner_buffer->Initialize()) {
        scanner_list.emplace_back(scanner_buffer);
      }
    }
  }

  while (is_running_) {
    for (std::unique_ptr<ScannerInterface>& it : scanner_list) {
      if (it) it->Scan();
    }
    usleep(1000 * 1000 * 5 ); // 5 sec
  }
  Logger::GetInstance().LogToApp(LOG_TYPE::eINFO, "bye ~ c u soon ~");
}

void ScannerManager::InterfaceListClear() {
  for (std::unique_ptr<ScannerInterface>& it : scanner_list) {
    it.reset();
  }
  scanner_list.clear();
}

ScannerManager::ScannerManager() : is_running_(false){
  ;
}
ScannerManager::~ScannerManager() {
  InterfaceListClear();
}
