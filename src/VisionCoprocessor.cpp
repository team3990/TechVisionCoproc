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
		// Empty for now
		sleep(1);
	}


	return 0;
}
