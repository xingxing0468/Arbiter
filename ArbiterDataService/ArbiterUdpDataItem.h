#ifndef ARBITERUDPDATAITEM_H
#define ARBITERUDPDATAITEM_H
#include "ArbiterDataServiceItem.h"

using namespace ArbiterTransport;
namespace ArbiterDataService
{

class UdpDataItem : public DataServiceItem
{
public:
    UdpDataItem(){

    }
    ArbiterRC   Update();
    ArbiterRC   Init()
    {
        m_socketDomain = AF_LOCAL;
        m_socketType   = SOCK_DGRAM;
        return DataServiceItem::Init();
    }
    ArbiterRC   ShakeHand(){ return ARBITER_OK; }
protected:

private:

};

}

#endif // ARBITERUDPDATAITEM_H
