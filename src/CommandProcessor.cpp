/*
 * CommandProcessor.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid

In order to add new commands, look for the comment tag //**
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
	m_bStop= false;	
	// Register available commands
	m_mapCommands_Immediate["stop"]= STOP;
	m_mapCommands_Immediate["reset"]=  RESET;
	m_mapCommands_Immediate["status"]=     STATUS;
	m_mapCommands_Delayed["saveimg1"]= SAVEIMG1;
	m_mapCommands_Delayed["r_saveimg1"]= R_SAVEIMG1;
	m_mapCommands_Delayed["saveimg2"]= SAVEIMG2;
	m_mapCommands_Delayed["r_saveimg2"]= R_SAVEIMG2;
	m_mapCommands_Delayed["test"]= TEST;
	m_mapCommands_Delayed["r_test"]= R_TEST;
	m_mapCommands_Delayed["longtest"]= LONGTEST;
	m_mapCommands_Delayed["r_longtest"]= R_LONGTEST;
	m_mapCommands_Delayed["bw"]= BW;
	m_mapCommands_Delayed["r_bw"]= R_BW;

	//**  Insert new pair of commands here 

	//**  End of insertion

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
	if(m_mapCommands_Immediate.count(strcommand)==1)
		return m_mapCommands_Immediate[strcommand];
	if(m_mapCommands_Delayed.count(strcommand)==1)
		return m_mapCommands_Delayed[strcommand];

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

	// Process "immediate" commands

	switch(nCommandCode){
	case UNKNOWN_CMD:
		response="Unknown command";
		break;
	case STOP:
		if(m_pCmdProcessingThread)
			delete m_pCmdProcessingThread;
		m_pCmdProcessingThread= NULL;
		m_bStop=true;	
		response="Stopping";
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

	// Process "delayed" commands

	switch(nCommandCode){

	case SAVEIMG1:
		pCommandObj= new ImgSaveCommand(std::string(IMAGE_DUMP_LOCATION),0);
		response="Working on it";
		break;
	case SAVEIMG2:
		pCommandObj= new ImgSaveCommand(std::string(IMAGE_DUMP_LOCATION),1);
		response="Working on it";
		break;
	case TEST:
		pCommandObj=new DummyCommand(1);
		response="Started";
		break;
	case LONGTEST:
		pCommandObj=new DummyCommand(2);
		response="Started";
		break;

	case BW:
		pCommandObj=new BWCommand();
		response="Started";
		break;
	//** Insert new case here; 
	//** Instantiate commmand
	//** variable <response> should be set to something

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
	case R_LONGTEST:
	case R_SAVEIMG1:
	case R_SAVEIMG2:
	case R_BW:
	  std::string initialrequest=command;
	  initialrequest.erase(0,2);  // remove _r
	  response=m_mapCommandsResponses[initialrequest];
		if(response.compare("Still thinking")!=0)
			m_mapCommandsResponses.erase(initialrequest);

		break;


	}

	if(response.empty())
		response="Error";

}
