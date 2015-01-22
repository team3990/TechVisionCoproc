//============================================================================
// Name        : VisionServer.cpp
// Author      : ML
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <unistd.h>
#include "MessageDispatcher.h"
#include "CommandProcessor.h"


using namespace std;

int main() {


	CommandProcessor cmdprocessor;
	MessageDispatcher dispatcher(&cmdprocessor);
	dispatcher.StartListening();

	while(1){

		/*if(dispatcher.CheckForIncomingMsg()) {

			std::string msg;
			if(dispatcher.RetrieveMsg(msg)) {
				cmdprocessor.ProcessCmd(msg);
			}
		}*/
/*
		if(cmdprocessor.IsJobCompleted()){
			std::string response;
			cmdprocessor.GetJobResults(response);
			printf("sending back %s\n",response.c_str());
			dispatcher.SendBackResponse(response);
		}
*/
		usleep(1000);
	}


	return 0;
}
