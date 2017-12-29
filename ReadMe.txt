DaemonApp：双进程守护实现成功   荣耀7  android6.0   盒子app的盒子  android4.2

12-29 16:13:34.671 11933-11933/? E/kejian: -------------开始创建serversocket-----------------
12-29 16:13:34.671 11906-11906/com.jianke.daemonapp E/kejian: ------------- 开始创建client socket -----------------
12-29 16:13:34.671 11906-11906/com.jianke.daemonapp E/kejian: client socket 创建成功
12-29 16:13:34.671 11906-11906/com.jianke.daemonapp E/kejian: 连接失败
12-29 16:13:35.681 11906-11906/com.jianke.daemonapp E/kejian: client socket 创建成功
12-29 16:13:35.681 11906-11906/com.jianke.daemonapp E/kejian: -------------client socket 成功连接上 serversocket-----------------
12-29 16:13:35.681 11933-11933/? E/kejian: apk 父进程连接上了 42
12-29 16:13:35.681 11933-11933/? E/kejian: -------------结束创建serversocket-----------------
12-29 16:13:35.681 11933-11933/? E/kejian: -------------child_listen_msg-----------------//阻塞在这里

12-29 16:15:45.121 11933-11933/? E/kejian: 读取消息前 1 42 1
12-29 16:15:45.121 11933-11933/? E/kejian: -------------重新启动 service-----------------
12-29 16:15:50.181 13958-13958/? E/kejian: -------------开始创建serversocket-----------------
12-29 16:15:50.181 13938-13938/com.jianke.daemonapp E/kejian: ------------- 开始创建client socket -----------------
12-29 16:15:50.181 13938-13938/com.jianke.daemonapp E/kejian: client socket 创建成功
12-29 16:15:50.181 13938-13938/com.jianke.daemonapp E/kejian: 连接失败
12-29 16:15:51.181 13938-13938/com.jianke.daemonapp E/kejian: client socket 创建成功
12-29 16:15:51.181 13958-13958/? E/kejian: apk 父进程连接上了 40
12-29 16:15:51.181 13958-13958/? E/kejian: -------------结束创建serversocket-----------------
12-29 16:15:51.181 13958-13958/? E/kejian: -------------child_listen_msg-----------------
12-29 16:15:51.181 13938-13938/com.jianke.daemonapp E/kejian: -------------client socket 成功连接上 serversocket-----------------

步骤：
1.通过java中的方法createWatcher调用JNI中的方法child_do_work-> child_create_channel来创建serversocket，并在此函数中阻塞在函数accept处来等待client  socket的连接。

2. 通过java中的方法connectToMonitor调用JNI中的方法Java_com_jianke_daemonapp_Watcher_connectToMonitor中的connect函数来连上第1步创建的serversocket。

3.连接上了之后，第一步中的阻塞方法child_create_channel中的函数accept会继续往下执行并返回1，然后再回到child_do_work中，然后再跳到child_listen_msg函数中继续执行。

4.在child_listen_msg函数中会阻塞在select处，直到客户端socket断开连接的时候发送数据过来，什么时候客户端socket发送数据过来呢？也就是apk进程被杀死的时候，客户端socket断开，就会导致select停止阻塞，继续往下走，直到重新启动service。

5.重新启动之后，有重复来到第一步。如此重复，所以可以起到保活的功能。



