
/* 参考: frameworks\av\media\libmedia\IMediaPlayerService.cpp */

#define LOG_TAG "GoodbyeService"

#include "IGoodbyeService.h"


namespace android {

status_t BnGoodbyeService::onTransact( uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags)
{
	/* 解析数据,调用saygoodbye/saygoodbye_to */

    switch (code) {
        case GOODBYE_SVR_CMD_SAYGOODBYE: {
			saygoodbye();
            return NO_ERROR;
        } break;
		
        case GOODBYE_SVR_CMD_SAYGOODBYE_TO: {

			/* 从data中取出参数 */
			int32_t policy =  data.readInt32();
			String16 name16 = data.readString16();
			String8 name8(name16);

			int cnt = saygoodbye_to(name8.string());

			/* 把返回值写入reply传回去 */
			reply->writeInt32(cnt);
			
            return NO_ERROR;
        } break;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

void BnGoodbyeService::saygoodbye(void)
{
	static int cnt = 0;
	ALOGI("say goodbye : %d\n", cnt++);

}

int BnGoodbyeService::saygoodbye_to(const char *name)
{
	static int cnt = 0;
	ALOGI("say goodbye to %s : %d\n", name, cnt++);
	return cnt;
}

}

