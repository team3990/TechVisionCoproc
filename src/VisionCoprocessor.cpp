//============================================================================
// Name        : VisionServer.cpp
// Author      : ML
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <unistd.h>
#include <iostream>

#include "MessageDispatcher.h"
#include "CommandProcessor.h"
#include "LoggingService.h"
#include "Defs.h"

using namespace std;

int main() {

	CommandProcessor cmdprocessor;
	MessageDispatcher dispatcher(&cmdprocessor);
	dispatcher.StartListening();
	std::cout << "Hit Ctrl-C to quit" << std::endl;

#ifdef LOGFILENAME
	if(LoggingService::Instance()->OpenLogFile(LOGFILENAME)==false)
		std::cout << "Oops, unable to open log file " << LOGFILENAME << std::endl;
#endif

	LOG_TRACE("Opening the log file\n");
	
bool done=false;
while(!done){
		// Empty for now
		usleep(10000);
		if(cmdprocessor.IsStopCommandReceived()) done=true;
	}
cmdprocessor.StopCapture();

sleep(2);
LoggingService::Instance()->CloseLogFile();
	return 0;
}
