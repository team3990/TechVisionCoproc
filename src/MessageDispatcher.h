/*
 * MessageDispatcher.h
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid
 */

#ifndef MESSAGEDISPATCHER_H_
#define MESSAGEDISPATCHER_H_

#include <vector>
#include <string>
#include "zmq.hpp"
#include "tinythread.h"

using namespace tthread;

class MessageDispatcher {
public:
	friend void Listen(MessageDispatcher*);
	MessageDispatcher();
	virtual ~MessageDispatcher();
	void StartListening();
	bool CheckForIncomingMsg();


	zmq::socket_t *m_pSocket;
private:
	zmq::context_t *m_pContext;
	thread *m_pListeningThread;
	std::vector<std::string> m_vCommands;
        mutex m_oCmdMutex;
};

#endif /* MESSAGEDISPATCHER_H_ */