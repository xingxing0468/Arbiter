#ifndef _ARBITER_DATA_SERVICE_H
#define _ARBITER_DATA_SERVICE_H

#include "../ArbiterTransport/ArbiterTransport.h"
#include "../ArbiterMaintenance/ArbiterRC.h";

#include "errno.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "sys/un.h"

extern int errno;
using namespace ArbiterTransport;
using namespace ArbiterMaintenance;

namespace ArbiterDataService
{
class DataServiceItem
{
public:
    DataServiceItem(): m_socketFd(0),
                       m_socketDomain(0),
                       m_socketType(0),
                       m_sendStr(""),
                       m_receivedStr("")
    {
        memset(&m_sockAddr, 0, sizeof(sockaddr_un));
        m_socketAddrStr = DataServiceItem::DEFAULT_SOCKET_ADDR;
    }

    void                                    SetSendStr(std::string inputStr)
    {
        m_sendStr = inputStr;
    }
    std::string                             GetReceivedStr()
    {
        return m_receivedStr;
    }
    virtual ArbiterRC                       Init()
    {
        ArbiterRC rc = ARBITER_OK;
        const char* socketAddrStr = m_socketAddrStr.c_str();
        m_sockAddr.sun_family = m_socketDomain;
        memcpy(&m_ockAddr.sun_path, socketAddrStr, strlen(socketAddrStr) + 1);
        if((clientSockFd = socket(m_socketDomain, m_socketType, 0)) < 0)
        {
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_CREATE, errno);
            rc = 1000 * ArbiterTracer::ACTION_CREATE + errno;
            goto Exit;
        }
        rc = ShakeHand();
    Exit:
        return rc;
    }
    virtual ArbiterRC                       ShakeHand() = 0;
    virtual ArbiterRC                       Update()  = 0;
    virtual ArbiterRC                       Disconnect()
    {
        ArbiterRC rc = ARBITER_OK;
        if((close(m_socketFd)) != 0)
        {
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_CLOSE_FD, errno);
            rc = 1000 * ArbiterTracer::ACTION_CLOSE_FD + errno;
        }
        return rc;
    }

private:
    int                                     m_socketFd;
    int                                     m_socketDomain;
    int                                     m_socketType;
    sockaddr_un                             m_sockAddr;
    std::string                             m_socketAddrStr;

    const static std::string                DEFAULT_SOCKET_ADDR     =           "/tmp/MySocketAddr";
protected:
    std::string                             m_sendStr;
    std::string                             m_receivedStr;

};

}

#endif
