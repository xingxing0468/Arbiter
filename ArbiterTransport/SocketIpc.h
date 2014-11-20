#ifndef SOCKETIPC_H
#define SOCKETIPC_H

#include "ArbiterTransport.h"

#include "errno.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "sys/un.h"


namespace ArbiterTransport {

class SocketIpc : public ArbiterBasicTransport
{
public:
    SocketIpc(): m_socketAddr(DEFAULT_SOCKET_ADDR) {};
    ArbiterRC InitSender();
    ArbiterRC InitReceiver();
private:
    std::string                 m_socketAddr;
    int                         m_socketFd;

    const static std::string    DEFAULT_SOCKET_ADDR     =           "/tmp/MySocketAddr";
};

}

#endif // SOCKETIPC_H
