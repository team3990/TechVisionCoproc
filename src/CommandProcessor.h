/*
 * CommandProcessor.h
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid
 */

#ifndef COMMANDPROCESSOR_H_
#define COMMANDPROCESSOR_H_

#include <string>
#include <map>
#include "tinythread.h"
#include "CameraManager.h"
class VisionCommand;

using namespace tthread;


class CommandProcessor {
public:

	enum {UNKNOWN_CMD=0,RESET,STATUS,SAVEIMG1,SAVEIMG2,DETECT_YOTE,DETECT_PLATFORM,TEST,TEST2,
		  R_DETECT_YOTE,R_DETECT_PLATFORM,R_TEST,R_TEST2,R_SAVEIMG1,R_SAVEIMG2};

	CommandProcessor();
	virtual ~CommandProcessor();

	// Called by VisionCoprocessor
	void ProcessCmd(std::string command,std::string& response);


	// Called by VisionCommand objects
	void StoreResponse(std::string cmd, std::string result){
		lock_guard<mutex> guard(m_oResponseMutex);
		m_mapCommandsResponses[cmd]=result;
	}
	std::string GetStatus();
	void StopCapture(){
		m_pCameraManager->StopCapturing();
	}

private:
	int GetCommandCodeFromString(std::string strcommand);
	thread *m_pCmdProcessingThread;
	CameraManager *m_pCameraManager;
	std::map<std::string,int> m_mapCommandsAvailable;
	VisionCommand *m_pCommandToProcess;
	std::map<std::string,std::string> m_mapCommandsResponses;
	std::map<std::string,std::string> m_mapQueriesCommands;
	mutex m_oResponseMutex;
};

#endif /* COMMANDPROCESSOR_H_ */
