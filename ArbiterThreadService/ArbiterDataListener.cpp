#include "ArbiterDataListener.h"


using namespace ArbiterThreadService;
using namespace ArbiterMaintenance;
ArbiterRC DataListener::Init()
{
    ArbiterRC rc = ARBITER_OK;
    if(sem_init(&m_semSign, 0, 0) < 0)
    {
        ArbiterTracer::Error(ArbiterTracer::CATEGORY_THREAD, ArbiterTracer::ACTION_SEMAPHORE_INIT, errno);
        rc = CalErrorCode(ArbiterTracer::ACTION_SEMAPHORE_INIT);
        return rc;
    }



    return rc;
}

void* DataListener::BackgroundExecution()
{
    while(1)
    {
        timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += LISTEN_TIME_INTERVAL;
        if(sem_timedwait(&m_semSign, &ts) == 0)
        {
            ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_TCP, ArbiterTracer::ACTION_NONE, ArbiterTracer::SERVERITY_INFO,
                                    "Listen for data...", m_threadId, m_threadName);



        }
        if(errno == ETIMEDOUT)
        {
            ArbiterTracer::WriteLine(ArbiterTracer::CATEGORY_THREAD, ArbiterTracer::ACTION_THREAD_LAUCH, ArbiterTracer::SERVERITY_INFO,
                                     "Listen Thread Has Been Terminated!", m_threadId, m_threadName);
        }
        else
        {
            ArbiterTracer::Error(ArbiterTracer::CATEGORY_THREAD, ArbiterTracer::ACTION_SEMAPHORE_TIMEWAIT, errno);
        }
        break;
    }
    return NULL;
}
