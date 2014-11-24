#ifndef _ARBITER_DATA_SERVICE_H
#define _ARBITER_DATA_SERVICE_H

#include "../ArbiterTransport/ArbiterTransport.h"
#include "../ArbiterMaintenance/ArbiterRC.h";
#include "../ArbiterThreadService/ArbiterThreadSubject.h"
#include "../ArbiterThreadService/ArbiterDataListener.h"

#include "sys/socket.h"
#include "sys/types.h"
#include "sys/un.h"

using namespace ArbiterTransport;
using namespace ArbiterMaintenance;
using namespace ArbiterThreadService;
namespace ArbiterDataService
{
class DataServiceItem
{
public:
    DataServiceItem(): m_socketFd(0),
                       m_socketDomain(0),
                       m_socketType(0),
                       m_sendStr(""),
                       m_receivedStr(""),
                       m_threadSubject(NULL),
                       m_recvListener(NULL)
    {
        memset(&m_sockAddr, 0, sizeof(sockaddr_un));
        m_socketAddrStr = DEFAULT_SOCKET_ADDR;
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
        memcpy(&m_sockAddr.sun_path, socketAddrStr, strlen(socketAddrStr) + 1);
        if((m_socketFd = socket(m_socketDomain, m_socketType, 0)) < 0)
        {
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_CREATE, errno);
            rc = CalErrorCode(ArbiterTracer::ACTION_CREATE);
            goto Exit;
        }
        rc = ShakeHand();
        m_threadSubject = new ArbiterThreadObserver();
        m_recvListener = new ArbiterDataListener();
        m_threadSubject->Attach(m_recvListener);

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
            rc = CalErrorCode(ArbiterTracer::ACTION_CLOSE_FD);
        }
        return rc;
    }
    void                                    DeleteObj()
    {
        if(!m_threadSubject) { delete m_threadSubject;}
        if(!m_recvListener)  { delete m_recvListener; }
        return;
    }
    static std::string                      DEFAULT_SOCKET_ADDR;
private:
    std::string                             m_socketAddrStr;

protected:
    std::string                             m_sendStr;
    std::string                             m_receivedStr;
    int                                     m_socketDomain;
    int                                     m_socketType;
    int                                     m_socketFd;
    sockaddr_un                             m_sockAddr;
    ArbiterThreadSubject                    *m_threadSubject;
    ArbiterThreadService                    *m_recvListener;
};

}

#endif
