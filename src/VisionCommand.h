/*
 * VisionCommand.h
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#ifndef VISIONCOMMAND_H_
#define VISIONCOMMAND_H_

#include <stdio.h>
#include "CommandProcessor.h"
#include "CameraManager.h"

class VisionCommand {
public:
	VisionCommand();
	virtual ~VisionCommand();
	virtual void Execute()=0;
	void SetContext(std::string command,CommandProcessor *pCP, CameraManager *pCM, FILE *pF){
		m_sCommand= command;
		m_pCmdProcessor= pCP;
		m_pCameraManager= pCM;
		m_pLogFile= pF;
	}


protected:
	// Called by derived objects at the end of Execute()
	void SetResult(std::string s){
		m_sResult=s;
	}
	// Called by derived objects for logging traces
	void LogTrace(char *format,...);

private:
	void SendBackResponse(){
		if(m_pCmdProcessor && m_sResult.size()>0){
			printf("visioncommand trying to send back result\n");
			m_pCmdProcessor->StoreResponse(m_sCommand,m_sResult);
		}
	}

	CommandProcessor *m_pCmdProcessor; // borrowed, do not delete
	CameraManager *m_pCameraManager;  // borrowed, do not delete
	FILE *m_pLogFile;
	std::string m_sResult;
	std::string m_sCommand;
};

#endif /* VISIONCOMMAND_H_ */
