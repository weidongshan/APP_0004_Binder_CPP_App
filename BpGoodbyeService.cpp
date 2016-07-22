
/* 参考: frameworks\av\media\libmedia\IMediaPlayerService.cpp */

#include "IGoodbyeService.h"

namespace android {

class BpGoodbyeService: public BpInterface<IGoodbyeService>
{
public:
    BpGoodbyeService(const sp<IBinder>& impl)
        : BpInterface<IGoodbyeService>(impl)
    {
    }

	void saygoodbye(void)
	{
		/* 构造/发送数据 */

        Parcel data, reply;
        data.writeInt32(0);

        remote()->transact(GOODBYE_SVR_CMD_SAYGOODBYE, data, &reply);
	}
	
	int saygoodbye_to(const char *name)
	{
		/* 构造/发送数据 */
        Parcel data, reply;

        data.writeInt32(0);
        data.writeString16(String16(name));

        remote()->transact(GOODBYE_SVR_CMD_SAYGOODBYE_TO, data, &reply);

		return reply.readInt32();
	}

};

IMPLEMENT_META_INTERFACE(GoodbyeService, "android.media.IGoodbyeService");

}


