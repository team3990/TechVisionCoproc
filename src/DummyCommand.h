/*
 * DummyCommand.h
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#ifndef DUMMYCOMMAND_H_
#define DUMMYCOMMAND_H_

#include "VisionCommand.h"

class DummyCommand: public VisionCommand
{
public:
	DummyCommand();
	virtual ~DummyCommand();
	virtual void Execute();

private:
	int m_nSomeInternalData;
};

#endif /* DUMMYCOMMAND_H_ */
