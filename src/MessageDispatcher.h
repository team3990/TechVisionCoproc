/*
 * MessageDispatcher.h
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid
 */

#ifndef MESSAGEDISPATCHER_H_
#define MESSAGEDISPATCHER_H_

#include <list>
#include <string>
#include "zmq.hpp"
#include "tinythread.h"
#include "CommandProcessor.h"

using namespace tthread;

class MessageDispatcher {
public:
	friend void Listen(MessageDispatcher*);
	MessageDispatcher(CommandProcessor *p);
	virtual ~MessageDispatcher();
	void StartListening();
	//bool CheckForIncomingMsg();
	void SendBackResponse(std::string response);
	//bool RetrieveMsg(std::string& msg);
	/*
	void AddCommand(std::string cmd){
		lock_guard<mutex> guard(m_oCmdMutex);
		printf("pushing %s\n",cmd.c_str());
		m_listCommands.push_back(cmd);
	}*/
	void TransferToCommandProcessor(std::string command,std::string& response)
	{
		response="error";
		if(m_pCmdProcessor){
			m_pCmdProcessor->ProcessCmd(command,response);
		}
	}

	zmq::socket_t *m_pSocket;
    mutex m_oCmdMutex;
    mutex m_oSocketMutex;
    CommandProcessor *m_pCmdProcessor;
private:
	zmq::context_t *m_pContext;
	thread *m_pListeningThread;
	std::list<std::string> m_listCommands;


};

#endif /* MESSAGEDISPATCHER_H_ */
