//
// Created by HyungWoo Lee on 2022/11/09.
//

#include <gtest/gtest.h>
#include "ScannerPackage.h"
#include "ScannerBinary.h"
#include "ScannerPermission.h"
#include "ScannerWhich.h"
//#include "ScannerProp.h"

TEST(ScannerPackage, IsExistOrNot) {
  ScannerPackage scanner_package;
  EXPECT_EQ(true, scanner_package.ScanUnitTest("com.hyungwoo.rooting"));
  EXPECT_EQ(false, scanner_package.ScanUnitTest("com.hyungwoo.rooting.failed"));
}

TEST(ScannerPermission, TrueOrFalse) {
  ScannerPermission scanner_permission;
  EXPECT_EQ(false, scanner_permission.ScanUnitTest("/data"));
  EXPECT_EQ(true, scanner_permission.ScanUnitTest("/debug_ramdisk"));
}

TEST(ScannerWhich, TrueOrFalse) {
  ScannerWhich scanner_which;
  EXPECT_EQ(true, scanner_which.ScanUnitTest("ls"));
  EXPECT_EQ(false, scanner_which.ScanUnitTest("not_exist_command_name"));
}

TEST(ScannerBinary, IsExistOrNot) {
  ScannerBinary scanner_binary;
  EXPECT_EQ(true, scanner_binary.ScanUnitTest("/system/bin/ls"));
  EXPECT_EQ(false, scanner_binary.ScanUnitTest("/system/bin/not_exist_file_name"));
}

/* 테스트 제외 단말기마다 프로퍼티 값이 다를수 있음
TEST(ScannerProp, TrueOrFalse) {
  ScannerProp scanner_prop;
  EXPECT_EQ(true, scanner_prop.ScanUnitTest("ro.debuggable", "1"));
}
*/