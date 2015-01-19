/*
 * MessageDispatcher.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid
 */

#include <string>
#include <iostream>
#include <unistd.h>


#include "MessageDispatcher.h"

void Listen(void *arg){

	MessageDispatcher *dispatcher=(MessageDispatcher*)arg;
	printf("Listening\n");
	while(1){

        zmq::message_t request;

        //  Wait for next request from client
        dispatcher->m_pSocket->recv (&request);
	std::string command((char*)request.data());
        std::cout << "Received " << command << std::endl;
        {
	  lock_guard<mutex> guard(dispatcher->m_oCmdMutex);
	  dispatcher->m_vCommands.push_back(command);
	}
//        zmq::message_t reply (5);
  //             memcpy ((void *) reply.data (), "World", 5);
    //           dispatcher->m_pSocket->send (reply);
        //  Do some 'work'
    	sleep(1);

	}


}


MessageDispatcher::MessageDispatcher() {
    //  Prepare our context and socket
    m_pContext =new zmq::context_t(1);
    m_pSocket =new zmq::socket_t(*m_pContext, ZMQ_REP);
    m_pSocket->bind ("tcp://*:5555");


}

MessageDispatcher::~MessageDispatcher() {
	// TODO Auto-generated destructor stub
}


void MessageDispatcher::StartListening()
{
	printf("Starting thread\n");
	m_pListeningThread = new thread(Listen, (void *) this);
}

bool MessageDispatcher::CheckForIncomingMsg()
{
   lock_guard<mutex> guard(m_oCmdMutex);
	if(m_vCommands.size()>0)
	  return true;
return false;
}
