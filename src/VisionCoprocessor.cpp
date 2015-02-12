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
#include "LoggingService.h"
#include <iostream>
#include <iomanip>

using namespace std;
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
/* reads from keypress, doesn't echo */
int getch(void)
{
struct termios oldattr, newattr;
int ch;
tcgetattr( STDIN_FILENO, &oldattr );
newattr = oldattr;
newattr.c_lflag &= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
ch = getchar();
tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
return ch;
}
int main() {


	CommandProcessor cmdprocessor;
	MessageDispatcher dispatcher(&cmdprocessor);
	dispatcher.StartListening();
	if(LoggingService::Instance()->OpenLogFile(LOGFILENAME)==false)
		printf("oops, unable to open log file %s\n",LOGFILENAME);
		
	LOG_TRACE("Opening the log file\n");
	
bool done=false;
	while(!done){
		// Empty for now
		usleep(10000);
		if(getch()==27) done=true;

	}
	cmdprocessor.StopCapture();
sleep(2);
LoggingService::Instance()->CloseLogFile();
	return 0;
}
