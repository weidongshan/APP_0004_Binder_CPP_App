
/* ²Î¿¼: frameworks\av\include\media\IMediaPlayerService.h */

#ifndef ANDROID_IHELLOERVICE_H
#define ANDROID_IHELLOERVICE_H

#include <utils/Errors.h>  // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

#define HELLO_SVR_CMD_SAYHELLO     1
#define HELLO_SVR_CMD_SAYHELLO_TO  2


namespace android {

class IHelloService: public IInterface
{
public:
    DECLARE_META_INTERFACE(HelloService);
	virtual void sayhello(void) = 0;
	virtual int sayhello_to(const char *name) = 0;
};

class BnHelloService: public BnInterface<IHelloService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);

	virtual void sayhello(void);
	virtual int sayhello_to(const char *name);

};
}

#endif

