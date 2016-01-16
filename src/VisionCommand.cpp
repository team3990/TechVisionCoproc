/*
 * VisionCommand.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#include "VisionCommand.h"

VisionCommand::VisionCommand() : m_pCmdProcessor(NULL), m_pCameraManager(NULL) {
	m_sResult.clear();
	m_sCommand.clear();
}

VisionCommand::~VisionCommand() {
	SendBackResponse();
}
