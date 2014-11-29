#ifndef _ARBITER_THREADSUBJECT_H
#define _ARBITER_THREADSUBJECT_H
#include <list>
#include "ArbiterThreadObserver.h"
#include <map>

using namespace ArbiterMaintenance;
namespace ArbiterThreadService
{
class ThreadSubject
{
public:
    ThreadSubject();
    virtual ArbiterRC                       Attach(ThreadObserver* threadOb)
    {
        ArbiterRC rc = ARBITER_OK;
        m_threadObserverList.push_back(threadOb);
        return rc;
    }
    virtual ArbiterRC                       LauchAll()
    {
        ArbiterRC rc = ARBITER_OK;
        for(std::list<ThreadObserver*>::iterator iter = m_threadObserverList.begin();
            iter != m_threadObserverList.end();
            iter++)
        {
            if((rc = (*iter)->Lauch()) != ARBITER_OK)
            {
                ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_THREAD, ArbiterTracer::ACTION_NONE, ArbiterTracer::SERVERITY_ERROR,
                                         "Thread Init Failed!!", (*iter)->ThreadId(), (*iter)->ThreadName());
                ArbiterTracer::Error(ArbiterTracer::CATEGORY_THREAD, ArbiterTracer::ACTION_THREAD_LAUCH, rc);
                goto Exit;
            }



        }
        Exit:
            return rc;
    }
    virtual ArbiterRC                       Detach()
    {
        ArbiterRC rc = ARBITER_OK;

        return rc;
    }
    virtual ~ThreadSubject();
protected:
    std::list<ThreadObserver*>              m_threadObserverList;



private:


};
}
#endif // THREADSUBJECT_H
