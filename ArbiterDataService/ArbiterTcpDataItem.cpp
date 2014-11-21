#include "ArbiterTcpDataitem.h"

using namespace ArbiterDataService;
using namespace ArbiterMaintenance;
ArbiterRC TcpDataItem::Update()
{
    ArbiterRC rc = ARBITER_OK;
    const char* sendBuf = m_sendStr.c_str();
    char receivedBuf[MAX_TCP_CONTENT_LENGTH];
    if(connect(m_socketFd, (sockaddr*)(&m_sockAddr), sizeof(m_sockAddr)) < 0)
    {
        ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_CONNECT, errno);
        rc = 1000 * ArbiterTracer::ACTION_CONNECT + errno;
        goto Exit;
    }
    if(send(m_sockFd, sendBuf, strlen(sendBuf) + 1, 0) < 0)
    {
        ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_SEND, errno);
        ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_SEND, "Error When Sending: [" + m_sendStr + "]");
        rc = 1000 * ArbiterTracer::ACTION_SEND + errno;
        goto Exit;
    }
    ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::SERVERITY_INFO, "Message: [" + sendStr + "] sent");

    {
    ArbiterTracer::WriteLine(ArbiterTracerCATEGORY_SOCKET, ArbiterTracerSERVERITY_INFO, "Waiting For Server Response....");
    if((recv(m_socketFd, receivedBuf, sizeof(receivedBuf), 0)) < 0)
    {
        ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_RECEIVE, errno);
        rc = 1000 * ArbiterTracer::ACTION_RECEIVE + errno;
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
    m_sendStr = "SYN";

    rc = Update();
    if(rc != ARBITER_OK)
    {
        goto Exit;
    }

    if(m_receivedStr != "SYNACK")
    {
        ArbiterTracer::WriteLine(ArbiterTracer::SERVERITY_ERROR, ArbiterTracer::ACTION_TCP_SHAKE_HAND, "Error Patter Responsed From The Server: \n" +
                                                                "Expected: [SYNACK], Actual: [" + m_receivedStr + "]");
        goto Exit;
    }

    m_sendStr = "ACK";
    rc = Update();
    if(rc != ARBITER_OK)
    {
        goto Exit;
    }

Exit:
    ArbiterTracer::Error(ArbiterTracer::SERVERITY_ERROR, ArbiterTracer::ACTION_TCP_SHAKE_HAND, errno);
    rc = 1000 * ArbiterTracer::ACTION_TCP_SHAKE_HAND + errno;
    return rc;
}
