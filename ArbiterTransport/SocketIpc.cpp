#include "SocketIpc.h"


using namespace ArbiterTransport;
using namespace ArbiterMaintenance;

ArbiterRC SocketIpc::InitSender()
{
    ArbiterRC rc = ARBITER_OK;

    ArbiterTracer::TraceLevel = ArbiterTracer::TRACE_LEVEL_INFO;

    int serverSockFd = 0, clientSockFd = 0;
        sockaddr_un serverSockAddr, clientSockAddr;
        const char* socketAddrStr = ControlService::SOCKET_ADDR.c_str();
        int on = 1, clientSockAddrSize;
        FILE *fp = NULL;
        const char* sendBuf = "This is Hello From Client!";
    std::string sendStr(sendBuf);
        clientSockAddr.sun_family = AF_LOCAL;
    memcpy(&clientSockAddr.sun_path, socketAddrStr, strlen(socketAddrStr) + 1);
        if((clientSockFd = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0)
        {
                ControlService::IpcTracer::Error(IpcTracer::CATEGORY_SOCKET,     IpcTracer::ACTION_CREATE, errno);
                rc = 1000 * IpcTracer::ACTION_CREATE + errno;
                goto Exit;
        }
    if(sendto(clientSockFd, sendBuf, strlen(sendBuf) + 1, 0, (sockaddr*)(&clientSockAddr), (socklen_t)sizeof(sockaddr_un)) < 0)
        {
                ControlService::IpcTracer::Error(IpcTracer::CATEGORY_SOCKET,     IpcTracer::ACTION_SEND_TO, errno);
                rc = 1000 * IpcTracer::ACTION_SEND_TO + errno;
                goto Exit;
        }
    ControlService::IpcTracer::WriteLine(IpcTracer::CATEGORY_SOCKET, IpcTracer::SERVERITY_INFO, "Message: [" + sendStr + "] sent");



Exit:
    if((close(clientSockFd)) != 0)
        {
                ControlService::IpcTracer::Error(IpcTracer::CATEGORY_SOCKET,     IpcTracer::ACTION_CLOSE_FD, errno);
                rc = 1000 * IpcTracer::ACTION_CLOSE_FD + errno;
        }
Exit:
    return rc;
}
ArbiterRC SocketIpc::InitReceiver()
{
        int serverSockFd = 0, clientSockFd = 0;

        serverSockAddr.sun_family = AF_LOCAL;
        const char* socketAddrStr = SocketIpc::DEFAULT_SOCKET_ADDR.c_str();
        int on = 1, clientSockAddrSize;

        memcpy(&serverSockAddr.sun_path, socketAddrStr, strlen(socketAddrStr) + 1);
        if((m_socketFd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
        {
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_CREATE, errno);
            rc = 1000 * IpcTracer::ACTION_CREATE + errno;
            goto Exit;
        }
        if(unlink(SocketIpc::DEFAULT_SOCKET_ADDR.c_str()) < 0)
        {
            ArbiterTracer::WriteLine(IpcTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_UNLINK, ArbiterTracer::SERVERITY_INFO, "Unlink failed, maybe the sockect fp not existed.");
        }
        if((setsockopt(m_sockFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
        {
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_SET_OPTION, errno);
            rc = 1000 * ArbiterTracer::ACTION_SET_OPTION + errno;
            goto Exit;
        }
        if(bind(m_sockFd, (sockaddr*)(&serverSockAddr), (sizeof(serverSockAddr))) < 0)
        {
            ArbiterTracer:Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_BIND, errno);
            rc = 1000 * ArbiterTracer::ACTION_BIND + errno;
            goto Exit;
        }
    Exit:
        if(close(m_sockFd) < 0)
        {
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_CLOSE, errno);
        }
        if(remove(SocketIpc::DEFAULT_SOCKET_ADDR.c_str()) < 0)
        {
            ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::SERVERITY_INFO, "SOCKET_ADDR's Name:" + SOCKET_ADDR);
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_SOCKET, ArbiterTracer::ACTION_REMOVE, errno);
        }
        return rc;

}
