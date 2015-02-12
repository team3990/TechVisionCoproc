/*
 * CommandProcessor.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid
 */
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "CommandProcessor.h"
#include "DummyCommand.h"
#include "ImgSaveCommand.h"
#include "config.h"
#include "LoggingService.h"

CommandProcessor::CommandProcessor() {
	m_pCmdProcessingThread=NULL;
	m_pCommandToProcess= NULL;
	m_pCameraManager=new CameraManager;
	
	// Register available commands
	m_mapCommandsAvailable["reset"]=  RESET;
	m_mapCommandsAvailable["status"]=     STATUS;
	m_mapCommandsAvailable["saveimg1"]= SAVEIMG1;
	m_mapCommandsAvailable["saveimg2"]= SAVEIMG2;
	m_mapCommandsAvailable["test"]= TEST;
	m_mapCommandsAvailable["longtest"]= TEST2;
	m_mapCommandsAvailable["r_test"]= R_TEST;
	m_mapCommandsAvailable["r_longtest"]= R_TEST2;
	m_mapCommandsAvailable["bw"]= BW;
	m_mapCommandsAvailable["r_bw"]= R_BW;


	m_mapQueriesCommands["r_test"]="test";
	m_mapQueriesCommands["r_bw"]="bw";
	m_mapQueriesCommands["r_longtest"]="longtest";
	m_mapCommandsAvailable["r_saveimg1"]= R_SAVEIMG1;
	m_mapCommandsAvailable["r_saveimg2"]= R_SAVEIMG2;
	m_mapQueriesCommands["r_saveimg1"]="saveimg1";
	m_mapQueriesCommands["r_saveimg2"]="saveimg2";

	m_pCameraManager->StartCapturing();
}

CommandProcessor::~CommandProcessor() {
	delete m_pCameraManager;
}

std::string CommandProcessor::GetStatus() {
	std::string status="Command processor status:\nVersion "+ std::string(VERSION) + "\nImage dump location: "+ std::string(IMAGE_DUMP_LOCATION) +"\n";

	std::map<std::string,std::string>::iterator iter;
	char str[1024];
	bool bFoundSomething=false;
	for(iter=m_mapCommandsResponses.begin(); iter!=m_mapCommandsResponses.end(); iter++){
		std::string s=iter->first;

		sprintf(str,"  %s: %s\n",(iter->first).c_str(),(iter->second).c_str());
		status=status+std::string(str);
		bFoundSomething=true;
	}
	if(bFoundSomething==false)
		status=status+" No job running\n";
	return status;
}

int CommandProcessor::GetCommandCodeFromString(std::string strcommand)
{
	if(m_mapCommandsAvailable.count(strcommand)==1)
		return m_mapCommandsAvailable[strcommand];

	return UNKNOWN_CMD;
}


void LaunchExecution(void *arg){
	VisionCommand *pCmd=(VisionCommand*)arg;
	pCmd->Execute();

	delete pCmd; // Upon deletion, result is sent back to CommandProcessor
}

void CommandProcessor::ProcessCmd(std::string command, std::string& response)
{
	int nCommandCode= GetCommandCodeFromString(command);

	VisionCommand *pCommandObj=NULL;

	response.clear();

	switch(nCommandCode){
	case UNKNOWN_CMD:
		response="Unknown command";
		break;

	case RESET:
		if(m_pCmdProcessingThread)
			delete m_pCmdProcessingThread;
		m_pCmdProcessingThread= NULL;
		m_mapCommandsResponses.clear();
		response="Done";
		break;
	case STATUS:

		response=GetStatus()+m_pCameraManager->GetStatus();
		break;
	}

	if(response.empty()==false)
		return;

	// Process external exec commands

	switch(nCommandCode){

	case SAVEIMG1:
		pCommandObj= new ImgSaveCommand(std::string(IMAGE_DUMP_LOCATION),0);
		response="Saving";
		break;
	case SAVEIMG2:
		pCommandObj= new ImgSaveCommand(std::string(IMAGE_DUMP_LOCATION),1);
		response="Saving";
		break;
	case TEST:
		pCommandObj=new DummyCommand(1);
		response="Started";
		break;
	case TEST2:
		pCommandObj=new DummyCommand(2);
		response="Started";
		break;

	case BW:
		pCommandObj=new BWCommand();
		response="Started";
		break;

	}

	if(response.empty()==false){
		// check if command not already launched
		if(m_mapCommandsResponses.find(command)!=m_mapCommandsResponses.end()){
			if(pCommandObj)
				delete pCommandObj;
			response="Busy";
			return;
		}


		if(pCommandObj){
			pCommandObj->SetContext(command,this,m_pCameraManager);
			m_mapCommandsResponses[command]="Still thinking";
			m_pCmdProcessingThread = new thread(LaunchExecution, (void *) pCommandObj);
		}
		return;
	}


	switch(nCommandCode){
	case R_TEST:
	case R_TEST2:
	case R_SAVEIMG1:
	case R_SAVEIMG2:
	case R_BW:
		response=m_mapCommandsResponses[m_mapQueriesCommands[command]];
		if(response.compare("Still thinking")!=0)
			m_mapCommandsResponses.erase(m_mapQueriesCommands[command]);

		break;


	}

	if(response.empty())
		response="Error";

}
