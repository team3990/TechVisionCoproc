/*
 * VisionCommand.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#include "VisionCommand.h"

VisionCommand::VisionCommand() {
	m_pCmdProcessor= NULL;
	m_pLogFile= NULL;
	m_pCameraManager= NULL;
	m_sResult.clear();
}

VisionCommand::~VisionCommand() {
	SendBackResponse();
}

