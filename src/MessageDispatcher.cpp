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
	std::cout "Listening" << std::endl;

	while(1){

        zmq::message_t request;

        //  Wait for next request from client
        dispatcher->m_pSocket->recv (&request);
	std::string command((char*)request.data());
        std::cout << "Received " << command << std::endl;
        {
	  lock_guard<mutex> guard(dispatcher->m_oCmdMutex);
	  dispatcher->m_listCommands.push_back(command);
	}
//        zmq::message_t reply (5);
  //             memcpy ((void *) reply.data (), "World", 5);
    //           dispatcher->m_pSocket->send (reply);
        //  Do some 'work'
    	usleep(1000);  // not necessary?

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
	if(m_listCommands.size()>0)
	  return true;
return false;
}

bool MessageDispatcher::RetrieveMsg(std::string& msg)
{
	msg="";
	if(m_listCommands.size()>0){
		msg=m_listCommands.front();
		m_listCommands.pop_front();
		return true;
	}
	return false;
}

void MessageDispatcher::SendBackResponse(std::string origmsg, std::string response)
{
	std::string fullmsg=origmsg + "=>" + response;

	zmq::message_t reply (fullmsg.size());
	memcpy ((void *) reply.data (), fullmsg.c_str(), fullmsg.size());
	m_pSocket->send (reply);
}
