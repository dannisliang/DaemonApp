#include <jni.h>
#include <string>
#include "native-lib.h"


int m_child;
const char* PATH="/data/data/com.jianke.daemonapp/mine.sock";
const char* userId;


JNIEXPORT void JNICALL
Java_com_jianke_daemonapp_Watcher_createWatcher(JNIEnv *env, jobject instance, jstring userid_) {
    userId = env->GetStringUTFChars(userid_, 0);



    //开双进程
    pid_t pid = fork();
    if(pid < 0) {

    } else if(pid == 0) {
        //子进程，守护进程
        child_do_work();
    } else {

        //父进程
    }
    env->ReleaseStringUTFChars(userid_, userId);
}


void child_do_work() {

    if(child_create_channel()) {
        child_listen_msg();
    }
}

//服务端读取信息
int child_create_channel() {
    LOGE("-------------开始创建serversocket-----------------");
    int listenfd = socket(AF_LOCAL,SOCK_STREAM,0);
    struct sockaddr_un addr;
    unlink(PATH);
    memset(&addr,0,sizeof(sockaddr_un));
    addr.sun_family= AF_LOCAL;

    int connfd;
    strcpy(addr.sun_path,PATH);
    if(bind(listenfd,(const sockaddr*)&addr,sizeof(sockaddr_un))<0) {
        LOGE("绑定错误，serversocket 创建失败");
        return 0;
    }
    listen(listenfd,5);
    //保证宿主进程连接成功
    while(1) {
        //返回值  客户端的地址
        if((connfd=accept(listenfd,NULL,NULL))<0) {//阻塞，等待client socket的连接
            if(errno == EINTR) {
                continue;
            } else {
                LOGE("读取错误");
                return 0;
            }
        }
        m_child = connfd;
        LOGE("apk 父进程连接上了 %d",m_child);
        break;
    }
    LOGE("-------------结束创建serversocket-----------------");
    return 1;
}

//创建服务端的socket
void child_listen_msg() {
    LOGE("-------------child_listen_msg-----------------");

    fd_set rfds;

    struct timeval timeout={3,0};
    while(1) {
        //清空内容
        FD_ZERO(&rfds);
        FD_SET(m_child,&rfds);
        //serversocket阻塞在这里，等待客户端socket断开连接的时候发送数据过来
        //apk进程被退出的时候，这个阻塞函数就往下走，知道重新启动service
        int r = select(m_child+1,&rfds,NULL,NULL,&timeout);
//        LOGE("读取消息前 %d %d",r,m_child);
        char pkg[256]={0};
        if (r > 0) {
            int k = FD_ISSET(m_child, &rfds);
            LOGE("读取消息前 %d %d %d", r, m_child, k);
            if (k) {
                int result = read(m_child, pkg, sizeof(pkg));
                LOGE("-------------重新启动 service-----------------");
                execlp("am", "am", "startservice", "--user", userId,
                       "com.jianke.daemonapp/com.jianke.daemonapp.ProcessService", (char *) NULL);
                break;
            }
        }
    }

}

JNIEXPORT void JNICALL
Java_com_jianke_daemonapp_Watcher_connectToMonitor(JNIEnv *env, jobject instance) {
    LOGE("------------- 开始创建client socket -----------------");
    int socked;
    struct sockaddr_un addr;
    while(1) {
        socked = socket(AF_LOCAL,SOCK_STREAM,0);
        if(socked < 0) {
            LOGE("-------------client socket 创建失败-----------------");
            return;
        }
        LOGE("client socket 创建成功");
        memset(&addr,0,sizeof(sockaddr_un));
        addr.sun_family= AF_LOCAL;

        strcpy(addr.sun_path,PATH);
        if(connect(socked,(const sockaddr *)&addr,sizeof(addr))<0) {
            LOGE("连接失败");
            close(socked);
            sleep(1);
            continue;
        }
        LOGE("-------------client socket 成功连接上 serversocket-----------------");
        break;
    }

}



extern "C"
jstring
Java_com_jianke_daemonapp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
