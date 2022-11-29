set(GOOGLETEST_ROOT ${ANDROID_NDK}/sources/third_party/googletest/)
add_library(gtest STATIC ${GOOGLETEST_ROOT}/src/gtest_main.cc ${GOOGLETEST_ROOT}/src/gtest-all.cc)
target_include_directories(gtest PRIVATE ${GOOGLETEST_ROOT})
target_include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../android_navigate)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../scanner)
add_executable(scanner_tester GTestMain.cpp)

add_library(scanner_unit SHARED
        ../utils/logger/Logger.cpp
        ../utils/common/StringTool.cpp
        ../utils/common/CommandLine.cpp
        ../utils/configure/Configure.cpp
        ../utils/configure/ConvertUTF.c
        ../scanner/ScannerBinary.cpp
        ../scanner/ScannerPackage.cpp
        ../scanner/ScannerWhich.cpp
        ../scanner/ScannerPermission.cpp)

find_library(log-lib log)
find_library(android-lib android )
target_link_libraries(scanner_unit  ${log-lib} ${android-lib})
target_link_libraries(scanner_tester gtest scanner_unit)