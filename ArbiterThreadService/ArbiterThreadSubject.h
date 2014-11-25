#ifndef _ARBITER_THREADSUBJECT_H
#define _ARBITER_THREADSUBJECT_H
#include <list>
#include "ArbiterThreadObserver.h"


using namespace ArbiterMaintenance;
namespace ArbiterThreadService
{
class ArbiterThreadSubject
{
public:
    ArbiterThreadSubject();
    virtual ArbiterRC                       Attach(ArbiterThreadObserver* threadOb)
    {
        ArbiterRC rc = ARBITER_OK;
        m_threadObserverList.push_back(threadOb);
    Exit:
        return rc;
    }
    virtual ArbiterRC                       LauchAll()
    {
        ArbiterRC rc = ARBITER_OK;
        for(std::list<ArbiterThreadObserver*>::iterator iter = m_threadObserverList.begin();
            iter != m_threadObserverList.end();
            iter++)
        {

        }
        Exit:
            return rc;
    }
    virtual ArbiterRC                       Detach()
    {
        ArbiterRC rc = ARBITER_OK;

    Exit:
        return rc;
    }
    virtual ~ArbiterThreadSubject();
protected:
    std::list<ArbiterThreadObserver*>       m_threadObserverList;
    virtual ArbiterRC                       Init(){}

private:


};
}
#endif // THREADSUBJECT_H
