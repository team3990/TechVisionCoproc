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


// Forward declarations

class VisionCommand;
class CameraManager;


class CommandProcessor {
public:

  // Enums for both immediate and delayed commands. Delayed commands come in pairs
  // since a first request is made to launch execution and a second request should be made 
  // to retrieve the result

  enum {
	  	  UNKNOWN_CMD= 0, STOP, RESET, STATUS,   // "Immediate" commands
		  SAVEIMG, R_SAVEIMG,  // For saving images captured using a camera

		  // INSERT HERE: enums for new pair of commands
		  // e.g. MY_BRAND_NEW_COMMAND, R_MY_BRAND_NEW_COMMAND,

		  TEST, R_TEST  // Test command (simulates an operation
  };

	CommandProcessor();
	virtual ~CommandProcessor();

	// Called by VisionCoprocessor
	void ProcessCmd(std::string command,std::string& response);


	// Called by VisionCommand objects
	void StoreResponse(std::string cmd, std::string result){
		tthread::lock_guard<tthread::mutex> guard(m_oResponseMutex);
		m_mapCommandsResponses[cmd]=result;
	}

	std::string GetStatus();

	void StopCapture();

	bool IsStopCommandReceived(){ return m_bStop; }

private:

	int GetCommandCodeFromString(std::string strcommand);
	tthread::thread *m_pCmdProcessingThread;
	CameraManager *m_pCameraManager;
	std::map<std::string, int> m_mapCommands_Immediate;
	std::map<std::string, int> m_mapCommands_Delayed;

	VisionCommand *m_pCommandToProcess;
	std::map<std::string,std::string> m_mapCommandsResponses;

	tthread::mutex m_oResponseMutex;
	bool m_bStop;
};

#endif /* COMMANDPROCESSOR_H_ */
