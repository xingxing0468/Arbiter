#ifndef ARBITERDATALISTENER_H
#define ARBITERDATALISTENER_H
#include "ArbiterThreadObserver.h"

namespace ArbiterThreadService
{
class ArbiterDataListener: ArbiterThreadObserver
{
public:
    ArbiterDataListener()
    {
        ArbiterThreadObserver::ArbiterThreadObserver(LISTENER);
    }
    std::string                     ReceivedStr()
    {
        return m_receivedStr;
    }

private:
    std::string                     m_receivedStr;
};
}
#endif // ARBITERDATALISTENER_H
