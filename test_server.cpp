
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

#include "IHelloService.h"
#include "IGoodbyeService.h"


using namespace android;

/* usage : test_server <file> */
int main(int argc, char **argv)
{

	int fd;

	if (argc == 2)
		fd = open(argv[1], O_RDWR);

	/* addService */

	/* while(1){ read data, 解析数据, 调用服务函数 } */

	/* 打开驱动, mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* 获得BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();

	sm->addService(String16("hello"), new BnHelloService(fd));
	sm->addService(String16("goodbye"), new BnGoodbyeService());

	/* 循环体 */
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();

	return 0;
}


