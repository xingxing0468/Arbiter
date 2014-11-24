#ifndef ARBITERTCPDATAITEM_H
#define ARBITERTCPDATAITEM_H
#include "ArbiterDataServiceItem.h"
#include "stdio.h"

using namespace ArbiterTransport;
namespace ArbiterDataService {

const static std::string            TCP_SHAKE_HAND_SEND_PATTERN;
const static std::string            TCP_SHAKE_HAND_RECEIVE_PATTERN;

class TcpDataItem : public DataServiceItem
{
public:
    TcpDataItem(){

    }
    ArbiterRC                           Update();
    ArbiterRC                           Init()
    {
        m_socketDomain = AF_LOCAL;
        m_socketType   = SOCK_STREAM;
        return DataServiceItem::Init();
    }
    ArbiterRC                           Disconnect();
    ArbiterRC                           ShakeHand();
protected:

private:
    const static int                    MAX_TCP_CONTENT_LENGTH = 512;
};

}
#endif // ARBITERTCPDATAITEM_H
