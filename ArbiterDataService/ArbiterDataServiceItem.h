#ifndef _ARBITER_DATA_SERVICE_H
#define _ARBITER_DATA_SERVICE_H

#include "../ArbiterTransport/ArbiterTransport.h"
#include "../ArbiterMaintenance/ArbiterRC.h";
using namespace ArbiterTransport;
using namespace ArbiterMaintenance;
namespace ArbiterDataService
{
class DataServiceItem
{
public:
    DataServiceItem(){};


    virtual ArbiterRC Update()  = 0;

private:


protected:
    ArbiterBasicTransport*                  m_transport;
    std::string                             m_sendStr;
    std::string                             m_receivedStr;

};

}









#endif
