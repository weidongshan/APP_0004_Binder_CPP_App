
#define LOG_TAG "HelloService"
//#define LOG_NDEBUG 0

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>


using namespace android;

/* ./test_client hello
 * ./test_client hello <name>
 */
int main(int argc, char **argv)
{
	int cnt;
	
	if (argc < 2){
        ALOGI("Usage:\n");
        ALOGI("%s <hello|goodbye>\n", argv[0]);
        ALOGI("%s <hello|goodbye> <name>\n", argv[0]);
        return -1;
	}

	/* getService */
	/* 打开驱动, mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* 获得BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();

    sp<IBinder> binder =
        sm->getService(String16("hello"));

	if (binder == 0)
	{
        ALOGI("can't get hello service\n");
		return -1;
	}

	/* service肯定是BpHelloServie指针 */
    sp<IHelloService> service =
        interface_cast<IHelloService>(binder);


	/* 调用Service的函数 */
	if (argc < 3) {
		service->sayhello();
		ALOGI("client call sayhello");
	}
	else {
		cnt = service->sayhello_to(argv[2]);
		ALOGI("client call sayhello_to, cnt = %d", cnt);
	}
	
	return 0;
}


