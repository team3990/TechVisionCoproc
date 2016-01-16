/*
 * MessageDispatcher.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid
 */

#include <string>
#include <iostream>
#include <unistd.h>
#include "config.h"

#include "MessageDispatcher.h"

void Listen(void *arg){

	MessageDispatcher *dispatcher=(MessageDispatcher*)arg;
	std::cout << "Listening" << std::endl;

	while( true ){
        zmq::message_t request;

        //  Wait for next request from client
        bool bStatusOk= dispatcher->m_pSocket->recv (&request);

        if(bStatusOk){

			char str[128];
			memset(str,'\0',128);
			memcpy(str,(char*)request.data(),request.size());

			std::string command(str);
			std::string response;
			dispatcher->TransferToCommandProcessor(command,response);

			dispatcher->SendBackResponse(response);
        }
    	usleep(1000);  // not necessary?
	}
}


MessageDispatcher::MessageDispatcher(CommandProcessor *p) {

    //  Prepare our context and socket
    m_pContext= new zmq::context_t(1);
    m_pSocket= new zmq::socket_t(*m_pContext, ZMQ_REP);
    char str[1284];
    sprintf(str,"tcp://*:%d",COMM_PORT);
    m_pSocket->bind(str);
    m_pCmdProcessor= p;
    m_pListeningThread= NULL;
}

MessageDispatcher::~MessageDispatcher() {
}


void MessageDispatcher::StartListening()
{
//	printf("Starting thread\n");
	m_pListeningThread = new tthread::thread(Listen, (void *) this);
}

void MessageDispatcher::SendBackResponse(std::string fullmsg)
{

	zmq::message_t reply (fullmsg.size());
	memcpy ((void *) reply.data (), fullmsg.c_str(), fullmsg.size());
	m_pSocket->send (reply);
}
