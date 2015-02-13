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

  // Enums for both immediate and delayed commands. Delayed commands come in pairs
  // since a first request is made to launch execution and a second request should be made 
  // to retrieve the result
  enum {UNKNOWN_CMD=0,STOP,RESET,STATUS,   // "Immediate" commands
	SAVEIMG1, R_SAVEIMG1,  // For saving images captured from camera 1
	SAVEIMG2, R_SAVEIMG2,  // For saving images captured from camera 2
	DETECT_YOTE, R_DETECT_YOTE, // For calling the yellow tote detector
	DETECT_PLATFORM, R_DETECT_PLATFORM, // For calling the scoring platform detector
	TEST, R_TEST,  // Test command (simulates a short -50ms- operation
	LONGTEST, R_LONGTEST, // Test command (simulates a long -2s- operation

	// Insert here: enums for new pair of commands

	BW, R_BW // Command that determines whether image is mostly black or white
  };

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
	bool IsStopCommandReceived(){ return m_bStop; }
private:
	int GetCommandCodeFromString(std::string strcommand);
	thread *m_pCmdProcessingThread;
	CameraManager *m_pCameraManager;
	std::map<std::string,int> m_mapCommands_Immediate;
	std::map<std::string,int> m_mapCommands_Delayed;

	VisionCommand *m_pCommandToProcess;
	std::map<std::string,std::string> m_mapCommandsResponses;
	//	std::map<std::string,std::string> m_mapQueriesCommands;
	mutex m_oResponseMutex;
	bool m_bStop;
};

#endif /* COMMANDPROCESSOR_H_ */
