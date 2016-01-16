//
//  Connects to the vision coprocessor at port 5555
//  Sends command specified in argv, expects answer
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
int main (int argc, char *argv[])
{

    if(argc!=2){
	printf("Usage:\n\ttestcoproc <command>\n");
	exit(2);
}

    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    socket.connect ("tcp://localhost:5555");

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
