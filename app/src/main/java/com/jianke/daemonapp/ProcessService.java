package com.jianke.daemonapp;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.Process;
import android.util.Log;

import java.util.Timer;
import java.util.TimerTask;

public class ProcessService extends Service {
    private static final String TAG = "ProcessService";
    int i = 0;
    boolean isRunnunig = true;
    public ProcessService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        return null;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        isRunnunig = false;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Watcher watcher = new Watcher();
        watcher.createWatcher(String.valueOf(Process.myUid()));
        watcher.connectToMonitor();
//        Timer timer = new Timer();
//        timer.scheduleAtFixedRate(new TimerTask() {
//            @Override
//            public void run() {
//                Log.i(TAG,"服务开启中 "+ i);
//                i++;
//
//            }
//        },0,1000*3);
        new Thread(new Runnable() {
            @Override
            public void run() {
                while(isRunnunig) {
                    Log.i(TAG, "服务开启中 " + i);
                    i++;

                    try {
                        Thread.sleep(3000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }
}
