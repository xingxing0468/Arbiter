#ifndef _ARBITER_THREADOBSERVER_H
#define _ARBITER_THREADOBSERVER_H
#include <pthread.h>
#include <semaphore.h>
#include "unistd.h"
#include <sys/wait.h>
#include "time.h"
#include "../ArbiterMaintenance/ArbiterRC.h"

using namespace ArbiterMaintenance;
namespace ArbiterThreadService
{

class ThreadObserver
{
public:
        ThreadObserver(): m_threadId(0){

        }
        ThreadObserver(std::string threadName): m_threadName(threadName), m_threadId(0)
        {

        }
        virtual ~ThreadObserver(){}

        virtual ArbiterRC               Lauch()
        {
            ArbiterRC rc = ARBITER_OK;
            FuncPtr tFunc = &ThreadObserver::BackgroundExecution;
            ThreadPtr p   = *(ThreadPtr*)&tFunc;
            int err = 0;
            if((rc = Init()) != ARBITER_OK)
            {
                rc = CalErrorCode(ArbiterTracer::ACTION_THREAD_INIT);
                goto Exit;
            }
            err = pthread_create(&m_threadId, &m_threadAttr, p, NULL);
            if(err != 0)
            {
                rc = CalErrorCode(ArbiterTracer::ACTION_THREAD_LAUCH);
                goto Exit;
            }

        Exit:
            return rc;
        }
        virtual ArbiterRC               Init() = 0;

        pthread_t                       ThreadId()  { return m_threadId;}
        void                            SetThreadId(pthread_t threadId) { m_threadId = threadId;}
        std::string                     ThreadName(){ return m_threadName;}
        void                            SetThreadName(std::string name) { m_threadName = name;}
protected:
        typedef void*                   (ThreadObserver::*FuncPtr)();
        typedef void*                   (*ThreadPtr)(void*);
        virtual void*                   BackgroundExecution() = 0;
        std::string                     m_threadName;
        pthread_t                       m_threadId;
        pthread_attr_t                  m_threadAttr;

private:

};
}
#endif // THREADOBSERVER_H
