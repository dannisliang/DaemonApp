package com.jianke.daemonapp;

/**
 * 项目名称：DaemonApp
 * 类描述：
 * 创建人：kejian
 * 创建时间：2017-12-28 17:46
 * 修改人：Administrator
 * 修改时间：2017-12-28 17:46
 * 修改备注：
 */
public class Watcher {
    static {
        System.loadLibrary("native-lib");
    }

    public native void createWatcher(String userId);

    public native void connectToMonitor();
}
