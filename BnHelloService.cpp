
/* 参考: frameworks\av\media\libmedia\IMediaPlayerService.cpp */

#define LOG_TAG "HelloService"

#include "IHelloService.h"


namespace android {

BnHelloService::BnHelloService()
{
}

BnHelloService::BnHelloService(int fd)
{
	this->fd = fd;
}

status_t BnHelloService::onTransact( uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags)
{
	/* 解析数据,调用sayhello/sayhello_to */

    switch (code) {
        case HELLO_SVR_CMD_SAYHELLO: {
			sayhello();
			reply->writeInt32(0);  /* no exception */
            return NO_ERROR;
        } break;
		
        case HELLO_SVR_CMD_SAYHELLO_TO: {

			/* 从data中取出参数 */
			int32_t policy =  data.readInt32();
			String16 name16_tmp = data.readString16(); /* IHelloService */
			
			String16 name16 = data.readString16();
			String8 name8(name16);

			int cnt = sayhello_to(name8.string());

			/* 把返回值写入reply传回去 */
			reply->writeInt32(0);  /* no exception */
			reply->writeInt32(cnt);
			
            return NO_ERROR;
        } break;

        case HELLO_SVR_CMD_GET_FD: {
			int fd = this->get_fd();
			reply->writeInt32(0);  /* no exception */

			/* 参考:
			 * frameworks\base\core\jni\android_view_InputChannel.cpp
			 * android_view_InputChannel_nativeWriteToParcel
			 */
			reply->writeDupFileDescriptor(fd);
            return NO_ERROR;
        } break;

		
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

void BnHelloService::sayhello(void)
{
	static int cnt = 0;
	ALOGI("say hello : %d\n", ++cnt);

}

int BnHelloService::sayhello_to(const char *name)
{
	static int cnt = 0;
	ALOGI("say hello to %s : %d\n", name, ++cnt);
	return cnt;
}

int BnHelloService::get_fd(void)
{
	return fd;
}


}

