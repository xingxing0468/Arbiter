#include "SocketIpc.h"


using namespace ArbiterTransport;
using namespace ArbiterMaintenance;

ArbiterRC SocketIpc::InitSender()
{
    ArbiterRC rc = ARBITER_OK;

Exit:
    return rc;
}
ArbiterRC SocketIpc::InitReceiver()
{
        int serverSockFd = 0, clientSockFd = 0;
        sockaddr_un serverSockAddr, clientSockAddr;
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
