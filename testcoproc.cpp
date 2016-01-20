/*
 * testcoprocessor.cpp

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

//
//  Connects to the vision coprocessor at port specified in src/Defs.h, e.g. 5555
//  Sends command specified in argv, expects answer
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include "src/Defs.h"

int main (int argc, char *argv[])
{
        std::cout << "T4K Vision Coprocessor Test Tool" << std::endl;
	std::cout << "--------------------------------" << std::endl << std::endl; 
        std::cout << "* using ZMQ v" << ZMQ_VERSION_MAJOR << "."; 
        std::cout << ZMQ_VERSION_MINOR << std::endl << std::endl;


    if(argc!=2){
	std::cout << "Usage:"<<std::endl<<"  testcoproc <command>" << std::endl << std::endl;
	std::cout << "where <command> is one of:" << std::endl;
	std::cout << "  reset, status, saveimg, r_saveimg, test, r_test" << std::endl;
	exit(2);
}

    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);
    char server_name[256];
    sprintf(server_name,"tcp://localhost:%d", COMM_PORT);
    socket.connect (server_name);

    //  Do 10 requests, waiting each time for a response
        zmq::message_t request (strlen(argv[1]));
        memcpy ((void *) request.data (), argv[1], strlen(argv[1]));
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
	char str[1024];

	memset(str,'\0',1024);
	memcpy (str,(void *) reply.data (),  reply.size());
        std::cout << str << std::endl;
    return 0;
}
