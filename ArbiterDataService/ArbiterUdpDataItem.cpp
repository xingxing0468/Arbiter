#include "ArbiterUdpDataItem.h"

using namespace ArbiterDataService;
using namespace ArbiterMaintenance;
ArbiterRC UdpDataItem::Update()
{
    ArbiterRC rc = ARBITER_OK;
    const char* sendBuf = m_sendStr.c_str();
    if(sendto(m_socketFd, sendBuf, strlen(sendBuf) + 1, 0, (sockaddr*)(&m_sockAddr), (socklen_t)sizeof(sockaddr_un)) < 0)
    {
        ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_SEND_TO, ArbiterTracer::SERVERITY_INFO,
                                 "Error When Sending: [" + m_sendStr + "]");
        ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_SEND_TO, errno);
        rc = CalErrorCode(ArbiterTracer::ACTION_SEND_TO);
        goto Exit;
    }
    ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::SERVERITY_INFO, "Message: [" + m_sendStr + "] sent successfully!");

Exit:
    return rc;
}
