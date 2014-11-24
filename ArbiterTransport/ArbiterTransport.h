#ifndef _ARBITER_TRANSPORT_H
#define _ARBITER_TRANSPORT_H
#include "../ArbiterMaintenance/ArbiterRC.h"
#include "../ArbiterMaintenance/ArbiterTrace.h"
using namespace ArbiterMaintenance;
namespace ArbiterTransport
{

class ArbiterBasicTransport
{
public:
    ArbiterBasicTransport(){}
    ArbiterRC Init(bool isServer)
    {
        if(isServer)
        {
            return InitReceiver();
        }
        else
        {
            return InitSender();
        }
    }

private:


protected:
    virtual ArbiterRC InitSender()          = 0;
    virtual ArbiterRC InitReceiver()        = 0;

};


}





#endif
