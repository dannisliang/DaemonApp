DaemonApp��˫�����ػ�ʵ�ֳɹ�   ��ҫ7  android6.0   ����app�ĺ���  android4.2

12-29 16:13:34.671 11933-11933/? E/kejian: -------------��ʼ����serversocket-----------------
12-29 16:13:34.671 11906-11906/com.jianke.daemonapp E/kejian: ------------- ��ʼ����client socket -----------------
12-29 16:13:34.671 11906-11906/com.jianke.daemonapp E/kejian: client socket �����ɹ�
12-29 16:13:34.671 11906-11906/com.jianke.daemonapp E/kejian: ����ʧ��
12-29 16:13:35.681 11906-11906/com.jianke.daemonapp E/kejian: client socket �����ɹ�
12-29 16:13:35.681 11906-11906/com.jianke.daemonapp E/kejian: -------------client socket �ɹ������� serversocket-----------------
12-29 16:13:35.681 11933-11933/? E/kejian: apk �������������� 42
12-29 16:13:35.681 11933-11933/? E/kejian: -------------��������serversocket-----------------
12-29 16:13:35.681 11933-11933/? E/kejian: -------------child_listen_msg-----------------//����������

12-29 16:15:45.121 11933-11933/? E/kejian: ��ȡ��Ϣǰ 1 42 1
12-29 16:15:45.121 11933-11933/? E/kejian: -------------�������� service-----------------
12-29 16:15:50.181 13958-13958/? E/kejian: -------------��ʼ����serversocket-----------------
12-29 16:15:50.181 13938-13938/com.jianke.daemonapp E/kejian: ------------- ��ʼ����client socket -----------------
12-29 16:15:50.181 13938-13938/com.jianke.daemonapp E/kejian: client socket �����ɹ�
12-29 16:15:50.181 13938-13938/com.jianke.daemonapp E/kejian: ����ʧ��
12-29 16:15:51.181 13938-13938/com.jianke.daemonapp E/kejian: client socket �����ɹ�
12-29 16:15:51.181 13958-13958/? E/kejian: apk �������������� 40
12-29 16:15:51.181 13958-13958/? E/kejian: -------------��������serversocket-----------------
12-29 16:15:51.181 13958-13958/? E/kejian: -------------child_listen_msg-----------------
12-29 16:15:51.181 13938-13938/com.jianke.daemonapp E/kejian: -------------client socket �ɹ������� serversocket-----------------

���裺
1.ͨ��java�еķ���createWatcher����JNI�еķ���child_do_work-> child_create_channel������serversocket�����ڴ˺����������ں���accept�����ȴ�client  socket�����ӡ�

2. ͨ��java�еķ���connectToMonitor����JNI�еķ���Java_com_jianke_daemonapp_Watcher_connectToMonitor�е�connect���������ϵ�1��������serversocket��

3.��������֮�󣬵�һ���е���������child_create_channel�еĺ���accept���������ִ�в�����1��Ȼ���ٻص�child_do_work�У�Ȼ��������child_listen_msg�����м���ִ�С�

4.��child_listen_msg�����л�������select����ֱ���ͻ���socket�Ͽ����ӵ�ʱ�������ݹ�����ʲôʱ��ͻ���socket�������ݹ����أ�Ҳ����apk���̱�ɱ����ʱ�򣬿ͻ���socket�Ͽ����ͻᵼ��selectֹͣ���������������ߣ�ֱ����������service��

5.��������֮�����ظ�������һ��������ظ������Կ����𵽱���Ĺ��ܡ�



