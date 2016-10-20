
/* 参考: frameworks\av\media\mediaserver\Main_mediaserver.cpp */

#define LOG_TAG "TestService"
//#define LOG_NDEBUG 0

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "IHelloService.h"
#include "IGoodbyeService.h"

#define SOCKET_BUFFER_SIZE      (32768U)

using namespace android;

/* 参考:
 * http://blog.csdn.net/linan_nwu/article/details/8222349
 */
class MyThread: public Thread {  
private:
	int fd;
public:  
    MyThread() {}
    MyThread(int fd) { this->fd = fd; }
 
        
    //如果返回true,循环调用此函数,返回false下一次不会再调用此函数  
    bool threadLoop()
    {
		char buf[500];
		int len;
		int cnt = 0;
		
		while(1)
		{
			/* 读数据: test_client发出的数据 */
			len = read(fd, buf, 500);
			buf[len] = '\0';
			ALOGI("%s\n", buf);
			
			/* 向 test_client 发出: Hello, test_client */
			len = sprintf(buf, "Hello, test_client, cnt = %d", cnt++);
			write(fd, buf, len);
		}
		
       	return true;  
    }
  
};  


/* usage : test_server  */
int main(void)
{

	int sockets[2];

	socketpair(AF_UNIX, SOCK_SEQPACKET, 0, sockets);

    int bufferSize = SOCKET_BUFFER_SIZE;
    setsockopt(sockets[0], SOL_SOCKET, SO_SNDBUF, &bufferSize, sizeof(bufferSize));
    setsockopt(sockets[0], SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));
    setsockopt(sockets[1], SOL_SOCKET, SO_SNDBUF, &bufferSize, sizeof(bufferSize));
    setsockopt(sockets[1], SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

	/* 创建一个线程, 用于跟test_client使用socketpiar通信 */
	sp<MyThread> th = new MyThread(sockets[0]);
	th->run();  


	/* addService */

	/* while(1){ read data, 解析数据, 调用服务函数 } */

	/* 打开驱动, mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* 获得BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();

	sm->addService(String16("hello"), new BnHelloService(sockets[1]));
	sm->addService(String16("goodbye"), new BnGoodbyeService());

	/* 循环体 */
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();

	return 0;
}


