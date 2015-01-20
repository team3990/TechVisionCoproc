/*
 * VisionCommand.h
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#ifndef VISIONCOMMAND_H_
#define VISIONCOMMAND_H_

#include "CommandProcessor.h"

class VisionCommand {
public:
	VisionCommand(CommandProcessor *processor);
	virtual ~VisionCommand();
	virtual bool Execute()=0;

private:
	CommandProcessor *m_pCmdProcessor;
};

#endif /* VISIONCOMMAND_H_ */
