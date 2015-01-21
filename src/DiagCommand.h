/*
 * DiagCommand.h
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#ifndef DIAGCOMMAND_H_
#define DIAGCOMMAND_H_

#include "VisionCommand.h"

class DiagCommand: public VisionCommand {
public:
	DiagCommand();
	virtual ~DiagCommand();
	virtual void Execute();
};

#endif /* DIAGCOMMAND_H_ */
