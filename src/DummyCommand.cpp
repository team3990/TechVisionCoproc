/*
 * DummyCommand.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#include "DummyCommand.h"

DummyCommand::DummyCommand() {
	// TODO Auto-generated constructor stub

}

DummyCommand::~DummyCommand() {
	// TODO Auto-generated destructor stub
}

void DummyCommand::Execute(){

	// Fake computations...
	usleep(50000);  //50 ms
	SetResult("Result of dummy command is pi");
}
