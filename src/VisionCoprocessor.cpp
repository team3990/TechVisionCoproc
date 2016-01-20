/*
 * VisionCoprocessor.cpp

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
//
	int zmqmajor, zmqminor,zmqpatch;
	zmq_version (&zmqmajor, &zmqminor, &zmqpatch); 
        std::cout << "* using ZMQ v" << zmqmajor << "."; 
        std::cout << zmqminor << std::endl << std::endl;

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
