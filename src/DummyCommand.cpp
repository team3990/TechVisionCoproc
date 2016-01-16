/*
 * DummyCommand.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#include "DummyCommand.h"


DummyCommand::DummyCommand()
{
	m_nSomeInternalData= 0;
}

DummyCommand::~DummyCommand() {
}

void DummyCommand::Execute(){

	// Fake computations...

	int n= 0;
	n++;

	// Prepare output
	char str[256];
	sprintf(str,"Output of dummy_command: result = 42");
	SetResult(str);
}

