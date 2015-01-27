/*
 * ImgSaveCommand.h
 *
 *  Created on: Jan 26, 2015
 *      Author: odroid
 */

#ifndef IMGSAVECOMMAND_H_
#define IMGSAVECOMMAND_H_

#include <string>
#include "VisionCommand.h"

class ImgSaveCommand: public VisionCommand {
public:
	ImgSaveCommand(std::string savedir, int camno);
	virtual ~ImgSaveCommand();
	virtual void Execute();
	std::string m_sSaveDir;
	int m_nImageNo;
	int m_nCamNo;
};

#endif /* IMGSAVECOMMAND_H_ */
