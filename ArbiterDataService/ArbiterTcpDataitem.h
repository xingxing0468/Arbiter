#ifndef ARBITERTCPDATAITEM_H
#define ARBITERTCPDATAITEM_H
#include "ArbiterDataServiceItem.h"

using namespace ArbiterTransport;
namespace ArbiterDataService {

class TcpDataItem : public DataServiceItem
{
public:
    TcpDataItem(ArbiterBasicTransport *transport)
    {
         m_transport = transport;
    }
    ArbiterRC   Update();
    ArbiterRC   InitConnection();
protected:

private:
    std::string                 m_sendingStr;
    std::string                 m_receivedStr;
};

}
#endif // ARBITERTCPDATAITEM_H
