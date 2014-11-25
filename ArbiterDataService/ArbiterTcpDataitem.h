#ifndef ARBITERTCPDATAITEM_H
#define ARBITERTCPDATAITEM_H
#include "ArbiterDataServiceItem.h"
#include "stdio.h"

using namespace ArbiterTransport;

namespace ArbiterDataService {

const static std::string            TCP_SYN;
const static std::string            TCP_ACK;
const static std::string            TCP_FIN;

class TcpDataItem : public DataServiceItem
{
public:
    TcpDataItem(){

    }
    ArbiterRC                           Update();
    ArbiterRC                           Init()
    {
        ArbiterRC rc = ARBITER_OK;
        m_socketDomain = AF_LOCAL;
        m_socketType   = SOCK_STREAM;
        rc = DataServiceItem::Init();
        if(rc != ARBITER_OK)
        {
            goto Exit;
        }

    Exit:
        return rc;
    }
    ArbiterRC                           Disconnect();
    ArbiterRC                           ShakeHand();
protected:

private:
    const static int                    MAX_TCP_CONTENT_LENGTH = 512;
};

}
#endif // ARBITERTCPDATAITEM_H
