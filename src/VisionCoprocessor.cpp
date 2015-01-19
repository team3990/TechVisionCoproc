//============================================================================
// Name        : VisionServer.cpp
// Author      : ML
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "MessageDispatcher.h"
#include "CommandProcessor.h"


using namespace std;

int main() {

	MessageDispatcher dispatcher;
	CommandProcessor cmdprocessor;

	dispatcher.StartListening();

	while(1){

		if(dispatcher.CheckForIncomingMsg()) {


		}
		sleep(20);
	}


	return 0;
}
