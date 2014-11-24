#ifndef _ARBITER_THREADOBSERVER_H
#define _ARBITER_THREADOBSERVER_H
#include <pthread.h>
#include "unistd.h"
#include <sys/wait.h>
#include "time.h"
#include "../ArbiterMaintenance/ArbiterRC.h"

using namespace ArbiterMaintenance;
namespace ArbiterThreadService
{

static std::string          LISTENER;
class ArbiterThreadObserver
{
public:
        ArbiterThreadObserver(): m_threadId(0){

        }
        ArbiterThreadObserver(std::string threadName): m_threadName(threadName)
        {
            ArbiterThreadObserver();
        }

        virtual ArbiterRC               InitArbiterThread()
        {
            ArbiterRC rc = ARBITER_OK;

        Exit:
            return rc;
        }
        virtual ArbiterRC               Lauch() = 0;
        virtual ArbiterRC               Init()  = 0;
        virtual ArbiterRC               Start() = 0;
        virtual ArbiterRC               Pause() = 0;
        virtual ArbiterRC               Stop()  = 0;
protected:
        typedef ArbiterRC               (ArbiterThreadObserver::*FuncPtr)();
        std::string                     m_threadName;
        pthread_t                       m_threadId;
        pthread_attr_t                  m_threadAttr;
        FuncPtr                         m_threadFunDelegate;
private:

};
}
#endif // THREADOBSERVER_H
