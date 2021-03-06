/*
 * MessageDispatcher.cpp

 Copyright (C) 2016  Marc Lalonde / team 3990 - Tech For Kids

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 =================================================================================================*/


#include <string>
#include <iostream>
#include <unistd.h>
#include "Defs.h"

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
