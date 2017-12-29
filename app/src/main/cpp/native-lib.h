//
// Created by Administrator on 2017-12-28.
//

#ifndef DAEMONAPP_NATIVE_LIB_H
#define DAEMONAPP_NATIVE_LIB_H

#endif //DAEMONAPP_NATIVE_LIB_H

#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/signal.h>

#define LOG_TAG "kejian"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int child_create_channel();
void child_do_work();
void child_listen_msg();

extern "C"
JNIEXPORT void JNICALL
        Java_com_jianke_daemonapp_Watcher_createWatcher(JNIEnv *env, jobject instance, jstring userid_);

extern "C"
JNIEXPORT void JNICALL
        Java_com_jianke_daemonapp_Watcher_connectToMonitor(JNIEnv *env, jobject instance);