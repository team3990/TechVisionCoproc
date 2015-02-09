/*
 * DummyCommand.h
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#ifndef DUMMYCOMMAND_H_
#define DUMMYCOMMAND_H_

#include "VisionCommand.h"

class DummyCommand: public VisionCommand {
public:
	DummyCommand(int mode);
	virtual ~DummyCommand();
	virtual void Execute();
private:
	int m_nMode;  //1=short exec (50ms), 2=long exec (2s)
};


class BWCommand: public VisionCommand {
public:
	BWCommand(){}
	virtual ~BWCommand(){}
	virtual void Execute();


};


#endif /* DUMMYCOMMAND_H_ */
