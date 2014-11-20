#ifndef _ARBITER_TRACE__H
#define _ARBITER_TRACE_H

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "stdlib.h"

namespace ArbiterMaintenance
{

	const static std::string Category[]			= {"Message Queue", 		"SOCKET"		      };
	const static std::string Action[]			= {"NONE",			"Create",			"Bind",
								   "Set Option",		"Listen",			"Accept",
								   "Connect",			"Send",				"Send To",
								   "Receive",			"Receive From",			"Unlink",
					         		   "Close",			"Remove",			"Open File Descriptor",
								   "Close File",		"Read File",		 	"Write FILE",
								   "Flush File",		"CLose File"};
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
		};

		enum SERVERITY
		{
			SERVERITY_INFO		= 0,
			SERVERITY_ERROR		= 1,
		};
	
		static TRACE_LEVEL TraceLevel;
		static std::string AppName;

		static void WriteLine(CATEGORY eCategory, ACTION eAction, SERVERITY eServerity, std::string message)
		{
			if(eServerity | TraceLevel)
			{
				std::cout << "[PID:"		<<	getpid()		<< "]" 
					  << "[PName:"		<<	ProcessName		<< "]"
					  << "[App:"		<<	AppName			<< "]"
					  << "["		<<	Category[eCategory]	<< "]"
					  << "["		<<	Action[eAction]		<< "]"
					  << ": "		<<	message			<< std::endl;
			}
			return;
		};
		static void WriteLine(CATEGORY eCategory, SERVERITY eServerity, std::string message)
		{
			return WriteLine(eCategory, ACTION_NONE, eServerity, message);
		};
		static void Error(CATEGORY eCategory, ACTION eAction, int errorCode)
		{
			char errorCodeCharArray[10];
			std::string errorCodeStr = "";
			sprintf(errorCodeCharArray, "%d", errorCode);
			errorCodeStr.assign(errorCodeCharArray);
			std::string msgStr = "errno [" + errorCodeStr + "]";
			return WriteLine(eCategory, eAction, SERVERITY_ERROR, msgStr);
		};
	};
	IpcTracer::TRACE_LEVEL  IpcTracer::TraceLevel	= IpcTracer::TRACE_LEVEL_INFO;
	std::string		IpcTracer::AppName	= APP_NAME[APP_NAME_SERVER];
	std::string 		IpcTracer::ProcessName;
}















#endif
