#ifndef _ARBITER_TRACE_H
#define _ARBITER_TRACE_H

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "stdlib.h"
#include <sys/types.h>
#include <unistd.h>


namespace ArbiterMaintenance
{
    enum APP_NAME_INDEX
    {
        APP_NAME_SERVER,
        APP_NAME_CLIENT,
    };
    const static std::string Category[]			= {"Message Queue", 		"SOCKET",		      "TCP",
                                                   "Thread"};
    const static std::string Action[]			= {"NONE",			"Create",			"Bind",
                                   "Set Option",		"Listen",			"Accept",
								   "Connect",			"Send",				"Send To",
								   "Receive",			"Receive From",			"Unlink",
					         		   "Close",			"Remove",			"Open File Descriptor",
								   "Close File",		"Read File",		 	"Write FILE",
                                   "Flush File",		"CLose File",           "Disconnect",
                                   "TCP Shake Hand",    "Thread Null Subject",  "Thread Lauch Fail",
                                   "Semaphore Init",    "Semaphore Timed Wait",};

	const static std::string APP_NAME[]			= {"Server",	"Client"};
    class ArbiterTracer
	{
	public:
		enum TRACE_LEVEL
		{
			TRACE_LEVEL_ERROR	= 0,
			TRACE_LEVEL_INFO	= 1,
		};
	
		enum CATEGORY
		{
			CATEGORY_MESSAGE_QUEUE,
			CATEGORY_SOCKET,
            CATEGORY_TCP,
            CATEGORY_THREAD,
		};

		enum ACTION
		{
			ACTION_NONE,
			ACTION_CREATE,
			ACTION_BIND,
			ACTION_SET_OPTION,
			ACTION_LISTEN,
			ACTION_ACCEPT,
			ACTION_CONNECT,
			ACTION_SEND,
			ACTION_SEND_TO,
			ACTION_RECEIVE,
			ACTION_RECEIVE_FROM,
			ACTION_UNLINK,
			ACTION_CLOSE,
			ACTION_REMOVE,
			ACTION_OPEN_FD,
			ACTION_CLOSE_FD,
			ACTION_READ_FP,
			ACTION_WRITE_FP,
			ACTION_FLUSH_FP,
			ACTION_CLOSE_FP,
            ACTION_DISCONNECT,

            ACTION_TCP_SHAKE_HAND,

            ACTION_THREAD_INIT,
            ACTION_THREAD_LAUCH,

            ACTION_SEMAPHORE_INIT,
            ACTION_SEMAPHORE_TIMEWAIT,
		};

		enum SERVERITY
		{
			SERVERITY_INFO		= 0,
			SERVERITY_ERROR		= 1,
		};
	
        static TRACE_LEVEL TraceLevel;
		static std::string AppName;
        static std::string ProcessName;

        static void WriteLine(CATEGORY eCategory, ACTION eAction, SERVERITY eServerity, std::string message,
                              int threadId = 0, std::string threadName = "")
		{
            char threadIdCharStr[10];

            std::string threadInfo = "";
            if(!threadId && (threadName == ""))
            {
                sprintf(threadIdCharStr, "%d", threadId);
                std::string threadIdStr(threadIdCharStr);
                threadInfo = "[TID:" + threadIdStr + "][TName:" + threadName + "]";
            }
			if(eServerity | TraceLevel)
			{
				std::cout << "[PID:"		<<	getpid()		<< "]" 
					  << "[PName:"		<<	ProcessName		<< "]"
					  << "[App:"		<<	AppName			<< "]"
					  << "["		<<	Category[eCategory]	<< "]"
					  << "["		<<	Action[eAction]		<< "]"
                      << ": "		<<	message             << threadInfo
                      << std::endl;
			}
			return;
        }
		static void WriteLine(CATEGORY eCategory, SERVERITY eServerity, std::string message)
		{
			return WriteLine(eCategory, ACTION_NONE, eServerity, message);
        }
		static void Error(CATEGORY eCategory, ACTION eAction, int errorCode)
		{
			char errorCodeCharArray[10];
			std::string errorCodeStr = "";
			sprintf(errorCodeCharArray, "%d", errorCode);
			errorCodeStr.assign(errorCodeCharArray);
			std::string msgStr = "errno [" + errorCodeStr + "]";
			return WriteLine(eCategory, eAction, SERVERITY_ERROR, msgStr);
        }
	};

}

#endif
