/*
 * DummyCommand.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#include "DummyCommand.h"

DummyCommand::DummyCommand(int mode) : m_nMode(mode)
{
	// TODO Auto-generated constructor stub
}

DummyCommand::~DummyCommand() {
	// TODO Auto-generated destructor stub
}

void DummyCommand::Execute(){

	// Fake computations...
	if(m_nMode==1)
		usleep(50000);  //50 ms
	else sleep(2);   //2s
	char str[128];
	sprintf(str,"Test mode %d: result=%s",m_nMode,(m_nMode==1?"pi":"nan"));
	SetResult(str);
}
