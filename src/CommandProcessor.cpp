/*
 * CommandProcessor.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid

In order to add new commands, look for the comment tag INSERT_HERE

 */

#include <stdio.h>
#include "CommandProcessor.h"
#include "DummyCommand.h"
#include "ImgSaveCommand.h"
#include "Defs.h"
#include "LoggingService.h"
#include "CameraManager.h"

CommandProcessor::CommandProcessor() {
	m_pCmdProcessingThread= NULL;
	m_pCommandToProcess= NULL;
	m_pCameraManager= new CameraManager;
	m_bStop= false;

	// Register available commands
	m_mapCommands_Immediate["stop"]= STOP;
	m_mapCommands_Immediate["reset"]= RESET;
	m_mapCommands_Immediate["status"]= STATUS;

	m_mapCommands_Delayed["saveimg"]= SAVEIMG;
	m_mapCommands_Delayed["r_saveimg"]= R_SAVEIMG;
	m_mapCommands_Delayed["test"]= TEST;
	m_mapCommands_Delayed["r_test"]= R_TEST;

	// INSERT_HERE: new pair of commands
	// e.g. m_mapCommands_Delayed["mybrandnewcommand"]= MY_BRAND_NEW_COMMAND;
	//      m_mapCommands_Delayed["r_mybrandnewcommand"]= R_MY_BRAND_NEW_COMMAND;

	m_pCameraManager->StartCapturing();
}

CommandProcessor::~CommandProcessor() {
	delete m_pCameraManager;
}


std::string CommandProcessor::GetStatus() {

	std::string status="Command processor status:\nVersion "+ std::string(VERSION) + "\nImage dump location: "+ std::string(IMAGE_DUMP_LOCATION) +"\n";

	std::map<std::string, std::string>::iterator iter;   //One day, auto will be used
	bool bFoundJob= false;

	for(iter=m_mapCommandsResponses.begin(); iter!=m_mapCommandsResponses.end(); iter++){
		status += "  " + iter->first + ": " + iter->second + "\n";
		bFoundJob= true;
	}

	if(bFoundJob == false)
		status += " No job running\n";

	return status;
}

// Returns the enum associated to the command (string format)
int CommandProcessor::GetCommandCodeFromString(std::string strcommand)
{
	if(m_mapCommands_Immediate.count(strcommand)==1)
		return m_mapCommands_Immediate[strcommand];

	if(m_mapCommands_Delayed.count(strcommand)==1)
		return m_mapCommands_Delayed[strcommand];

	return UNKNOWN_CMD;
}

void CommandProcessor::StopCapture()
{
		m_pCameraManager->StopCapturing();
}

void LaunchExecution(void *arg){

	VisionCommand *pCmd=(VisionCommand*)arg;
	pCmd->Execute();

	delete pCmd; // Upon deletion, result is sent back to CommandProcessor
}

// Handles the command: big switch
void CommandProcessor::ProcessCmd(std::string command, std::string& response)
{
	int nCommandCode= GetCommandCodeFromString(command);
	VisionCommand *pCommandObj= NULL;

	response.clear();

	// Process "immediate" commands

	switch(nCommandCode){

	case UNKNOWN_CMD:
		response="Unknown command";
		break;

	case STOP:
		if(m_pCmdProcessingThread)
			delete m_pCmdProcessingThread;
		m_pCmdProcessingThread= NULL;
		m_bStop= true;
		response= "Stopping";
		// TODO: initiate shutdown?
	break;

	case RESET:
		if(m_pCmdProcessingThread)
			delete m_pCmdProcessingThread;

		m_pCmdProcessingThread= NULL;
		m_mapCommandsResponses.clear();
		response= "Done";
		break;

	case STATUS:
		response= GetStatus() + m_pCameraManager->GetStatus();
		break;
	} // end processing immediate comands

	if(response.empty()==false) // We got a response, no need to keep going
		return;


	// Process "delayed", request-type commands

	switch(nCommandCode){

	case SAVEIMG:
		pCommandObj= new ImgSaveCommand(std::string(IMAGE_DUMP_LOCATION), 0); // 0 is for camera number in case we have more than 1
		response= "Working on it";
		break;

	case TEST:
		pCommandObj= new DummyCommand();
		response="Started";
		break;

	// INSERT_HERE new request-type commands
	// Instantiate commmand
	// Variable <response> should be set to something

	}

	if(response.empty()==false){  // We got a response, no need to keep going

		// check if command not already launched
		if(m_mapCommandsResponses.find(command)!= m_mapCommandsResponses.end()){

			if(pCommandObj)
				delete pCommandObj; // Command instantiation was useless after all
			response="Busy";
			return;
		}


		if(pCommandObj){

			pCommandObj->SetContext(command, this, m_pCameraManager);
			m_mapCommandsResponses[command]= "Still thinking";
			m_pCmdProcessingThread = new tthread::thread(LaunchExecution, (void *) pCommandObj);
		}
		return;
	}

	// Process "delayed", response-type commands

	switch(nCommandCode){

	case R_TEST:
	case R_SAVEIMG:
  	  // INSERT_HERE "case XXX:" lines for new response-type commands
	  // e.g. case R_MY_BRAND_NEW_COMMAND:

	  // Deduce initial request, e.g. if command at this point is r_mytest, initial request was mytest
	  std::string initialrequest= command;
	  initialrequest.erase(0,2);  // remove r_

	  response= m_mapCommandsResponses[initialrequest];
	  if(response.compare("Still thinking") != 0)
			m_mapCommandsResponses.erase(initialrequest);  // Job is done, make the initial command available again

	  break;
	}

	if(response.empty())
		response="Error";
}
