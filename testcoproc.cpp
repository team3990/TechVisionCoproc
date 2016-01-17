//
//  Connects to the vision coprocessor at port 5555
//  Sends command specified in argv, expects answer
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include "src/Defs.h"

int main (int argc, char *argv[])
{

    if(argc!=2){
	std::cout << "Usage:"<<std::endl<<"\ttestcoproc <command>" << std::endl;
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
