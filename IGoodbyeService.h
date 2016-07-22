
/* ²Î¿¼: frameworks\av\include\media\IMediaPlayerService.h */

#ifndef ANDROID_IGOODBYEERVICE_H
#define ANDROID_IGOODBYEERVICE_H

#include <utils/Errors.h>  // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

#define GOODBYE_SVR_CMD_SAYGOODBYE     0
#define GOODBYE_SVR_CMD_SAYGOODBYE_TO  1


namespace android {

class IGoodbyeService: public IInterface
{
public:
    DECLARE_META_INTERFACE(GoodbyeService);
	virtual void saygoodbye(void) = 0;
	virtual int saygoodbye_to(const char *name) = 0;
};

class BnGoodbyeService: public BnInterface<IGoodbyeService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);

	virtual void saygoodbye(void);
	virtual int saygoodbye_to(const char *name);

};
}

#endif

