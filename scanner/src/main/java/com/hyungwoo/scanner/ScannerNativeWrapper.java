package com.hyungwoo.scanner;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

public class ScannerNativeWrapper {
    private AlertUserCallBack m_AlertUserCallBack = null;

    // Used to load the 'scanner' library on application startup.
    static {
        System.loadLibrary("scanner");
    }

    public native boolean StartNative(Activity a_tActivity, AssetManager a_tAssetManager);
    public native void StopNative();

    public boolean Start(Activity activity, AssetManager assetManager, AlertUserCallBack callback) {
        this.m_AlertUserCallBack = callback;

        return StartNative(activity, assetManager);
    }

    public void Stop() {
        StopNative();
    }

    public static interface AlertUserCallBack {
        void onDetectNotify(int a_nParam, String a_strParam);
    }

    public void LoggerCallback(int a_nCode, String a_strAlertMsg) {
        if (this.m_AlertUserCallBack != null) {
            this.m_AlertUserCallBack.onDetectNotify(a_nCode, a_strAlertMsg);
        }
    }
}