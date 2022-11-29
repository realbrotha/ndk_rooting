cmake_minimum_required(VERSION 3.18.1)

project("rootscanner")

set(MODULE_NAME scanner)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    ADD_DEFINITIONS(-D_DEBUG)
    add_subdirectory(unit_test) # GTEST 프로젝트, 디버그 빌드만 사용
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/scanner)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/android_navigate)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)

add_library( # Sets the name of the library.
        scanner
        SHARED
        scanner.cpp
        android_navigate/GlobalContext.hpp
        utils/common/StringTool.cpp
        utils/common/CommandLine.cpp
        utils/logger/Logger.cpp
        utils/configure/Configure.cpp
        utils/configure/ConvertUTF.c
        utils/configure/simpleini.h
        scanner/ScannerInterface.h
        scanner/ScannerManager.cpp
        scanner/ScannerWhich.cpp
        scanner/ScannerPermission.cpp
        scanner/ScannerPackage.cpp
        scanner/ScannerProp.cpp
        scanner/ScannerBinary.cpp
        )

find_library(log-lib log)
find_library(android-lib android )

target_link_libraries(${MODULE_NAME} ${android-lib} ${log-lib})


