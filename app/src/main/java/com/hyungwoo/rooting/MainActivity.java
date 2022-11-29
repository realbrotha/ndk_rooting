package com.hyungwoo.rooting;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Process;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.hyungwoo.scanner.ScannerNativeWrapper;

public class MainActivity extends AppCompatActivity {
    private final ScannerNativeWrapper scannerSdk = new ScannerNativeWrapper();
    private Activity mainActivity = null;
    private final ScannerNativeWrapper.AlertUserCallBack alertCallBack = new ScannerNativeWrapper.AlertUserCallBack() {
        @Override
        public void onDetectNotify(int a_nParam, String a_strParam) {
            appendLog(a_strParam);
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.mainActivity = this;

        TextView textViewLog = (TextView)findViewById(R.id.log_view);
        textViewLog.setMovementMethod(new ScrollingMovementMethod());

        Button buttonStart = findViewById(R.id.start_button);
        buttonStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                scannerSdk.Start(mainActivity, getApplicationContext().getAssets(), alertCallBack);
            }
        });
        Button buttonStop = findViewById(R.id.stop_button);
        buttonStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                scannerSdk.Stop();
            }
        });
    }
    public void appendLog(String strLog){
        // NOTE : UI에 Direct로 출력할경우 Accessibility content change on non-UI thread. Future Android versions will throw an exception. 발생
        runOnUiThread(new Runnable()
        {
            public void run()
            {
                TextView textViewLog = findViewById(R.id.log_view);
                String logBuffer = textViewLog.getText().toString();
                String lineFeedOrNot = "";

                if(!logBuffer.isEmpty()) lineFeedOrNot = "\n";

                logBuffer += lineFeedOrNot + strLog;
                if(5000 < logBuffer.length())
                {
                    logBuffer = strLog;
                }

                textViewLog.setText(logBuffer);

                int lineTop =  textViewLog.getLayout().getLineTop(textViewLog.getLineCount()) ;
                int scrollY = lineTop - textViewLog.getHeight();
                if (scrollY > 0) {
                    textViewLog.scrollTo(0, scrollY);
                } else {
                    textViewLog.scrollTo(0, 0);
                }
            }
        });
    }
}