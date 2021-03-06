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


class MessageDispatcher {

public:
	friend void Listen(MessageDispatcher *);
	MessageDispatcher(CommandProcessor *p);
	virtual ~MessageDispatcher();

	void StartListening();
	void SendBackResponse(const std::string response);
	void TransferToCommandProcessor(const std::string command,std::string& response)
	{
		response="error";
		if(m_pCmdProcessor){
			m_pCmdProcessor->ProcessCmd(command, response);
		}
	}

	zmq::socket_t *m_pSocket;
    tthread::mutex m_oCmdMutex;
    CommandProcessor *m_pCmdProcessor;

private:
	zmq::context_t *m_pContext;
	tthread::thread *m_pListeningThread;
	std::list<std::string> m_listCommands;

};

#endif /* MESSAGEDISPATCHER_H_ */
