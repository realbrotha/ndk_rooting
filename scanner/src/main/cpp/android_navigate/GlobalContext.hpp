//
// Created by HyungWoo Lee on 2022/11/08.
//

#ifndef ROOTING_SCANNER_SRC_MAIN_CPP_GLOBALCONTEXT_HPP_
#define ROOTING_SCANNER_SRC_MAIN_CPP_GLOBALCONTEXT_HPP_

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "../utils/logger/Logger.h"

class GlobalContext {
 public :
  static GlobalContext &GetInstance() {
    static GlobalContext instance_;
    return instance_;
 };

 public :
  JavaVM *GetJvm() const {
    return jvm_;
  }
  void SetJvm(JavaVM *jvm) {
    jvm_ = jvm;
  }
  JNIEnv *GetEnv() const {
    return env_;
  }
  void SetEnv(JNIEnv *env) {
    env_ = env;
  }
  const jobject GetGlobalRef() const {
    return global_ref_;
  }
  void SetGlobalRef(const jobject global_ref) {
    global_ref_ = global_ref;
  }
  AAssetManager *GetAssetManager() const {
    return asset_manager_;
  }
  void SetAssetManager(AAssetManager *asset_manager) {
    asset_manager_ = asset_manager;
  }
 private :
  GlobalContext() {;};
  ~GlobalContext() {;};

  JavaVM* jvm_;
  JNIEnv * env_;
  jobject global_ref_;
  AAssetManager*    asset_manager_;
};
#endif //ROOTING_SCANNER_SRC_MAIN_CPP_GLOBALCONTEXT_HPP_
