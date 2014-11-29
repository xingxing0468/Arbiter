#ifndef ARBITERDATALISTENER_H
#define ARBITERDATALISTENER_H
#include "ArbiterThreadObserver.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "sys/un.h"


namespace ArbiterThreadService
{
static std::string          LISTENER = "Arbiter Data Listener";
class DataListener: public ThreadObserver
{
public:
    DataListener(): m_bIsFixedAddr(false),ThreadObserver(LISTENER)
    {

    }

    ArbiterRC                       Init();
    void                            SetFixedAddr(sockaddr_un srcAddr)
    {
        m_sockAddr = srcAddr;
        m_sockAddrLength = sizeof(m_sockAddr);
    }
    void*                           BackgroundExecution();
    std::string                     ReceivedStr()
    {
        return m_receivedStr;
    }

protected:
    ArbiterRC                       ThreadFunc();

private:
    std::string                     m_receivedStr;
    sem_t                           m_semSign;
    bool                            m_bIsFixedAddr;
    sockaddr_un                     m_sockAddr;
    socklen_t                       m_sockAddrLength;

    const static int                LISTEN_TIME_INTERVAL = 1;
};
}
#endif // ARBITERDATALISTENER_H
