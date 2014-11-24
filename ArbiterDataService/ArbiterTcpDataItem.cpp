#include "ArbiterTcpDataitem.h"

using namespace ArbiterDataService;
using namespace ArbiterMaintenance;

std::string     TCP_SYN     = "SYN";
std::string     TCP_ACK     = "ACK";
std::string     TCP_FIN     = "FIN";
ArbiterRC TcpDataItem::Update()
{
    ArbiterRC rc = ARBITER_OK;
    const char* sendBuf = m_sendStr.c_str();
    char receivedBuf[MAX_TCP_CONTENT_LENGTH];
    if(connect(m_socketFd, (sockaddr*)(&m_sockAddr), sizeof(m_sockAddr)) < 0)
    {
        ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_CONNECT, errno);
        rc = CalErrorCode(ArbiterTracer::ACTION_CONNECT);
        goto Exit;
    }
    if(send(m_socketFd, sendBuf, strlen(sendBuf) + 1, 0) < 0)
    {
        ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_SEND, errno);
        ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_SEND, ArbiterTracer::SERVERITY_INFO,
                                 "Error When Sending: [" + m_sendStr + "]");
        rc = CalErrorCode(ArbiterTracer::ACTION_SEND);
        goto Exit;
    }
    ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::SERVERITY_INFO, "Message: [" + m_sendStr + "] sent");

    {
        ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::SERVERITY_INFO, "Waiting For Server Response....");
        if((recv(m_socketFd, receivedBuf, sizeof(receivedBuf), 0)) < 0)
        {
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_RECEIVE, errno);
            rc = CalErrorCode(ArbiterTracer::ACTION_RECEIVE);
            goto Exit;
        }
        std::string receiveStr(receivedBuf);
        ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::SERVERITY_INFO, "Received Message: [" +  receiveStr + "]");
        m_receivedStr = receiveStr;
    }

Exit:
    return rc;
}

ArbiterRC TcpDataItem::ShakeHand()
{
    ArbiterRC rc = ARBITER_OK;
    m_sendStr = TCP_SHAKE_HAND_SEND_PATTERN;

    rc = Update();
    if(rc != ARBITER_OK)
    {
        goto Exit;
    }

    if(m_receivedStr != TCP_SYN + TCP_ACK)
    {
        ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_TCP, ArbiterTracer::ACTION_TCP_SHAKE_HAND, ArbiterTracer::SERVERITY_ERROR,
                                 "Error Patter Responsed From The Server: \nExpected: ["
                                 + TCP_SYN + TCP_ACK + "], Actual: ["
                                 + m_receivedStr + "]");
        rc = CalErrorCode(ArbiterTracer::ACTION_TCP_SHAKE_HAND);
        goto Exit;
    }

    m_sendStr = TCP_ACK;
    rc = Update();
    if(rc != ARBITER_OK)
    {
        goto Exit;
    }

Exit:
    ArbiterTracer::Error(ArbiterTracer::CATEGORY_TCP, ArbiterTracer::ACTION_TCP_SHAKE_HAND, errno);
    rc = CalErrorCode(ArbiterTracer::ACTION_TCP_SHAKE_HAND);
    return rc;
}

ArbiterRC TcpDataItem::Disconnect()
{
    ArbiterRC rc = ARBITER_OK;
    m_sendStr = TCP_FIN;

    rc = Update();
    if(rc != ARBITER_OK)
    {
        goto Exit;
    }

    if(m_receivedStr != TCP_ACK)
    {
        ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_TCP, ArbiterTracer::ACTION_DISCONNECT, ArbiterTracer::SERVERITY_ERROR,
                                 "Error Patter Responsed From The Server: \nExpected: ["
                                 + TCP_ACK + "], Actual: ["
                                 + m_receivedStr + "]");
        goto Exit;
    }
    return DataServiceItem::Disconnect();
}
