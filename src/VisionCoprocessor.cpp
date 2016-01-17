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
#include "cv.h"

using namespace std;

int main() {

	std::cout << "T4K Vision Coprocessor v" << VERSION << std::endl; 
	std::cout << "----------------------" << std::endl << std::endl;
	std::cout << "* Using OpenCV v" << CV_VERSION << std::endl;
//	cout << "Major version : " << CV_MAJOR_VERSION << endl;
//	cout << "Minor version : " << CV_MINOR_VERSION << endl;
	std::cout << "* Using ZMQ v" << ZMQ_VERSION_MAJOR << ".";
	std::cout << ZMQ_VERSION_MINOR << std::endl << std::endl;

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
