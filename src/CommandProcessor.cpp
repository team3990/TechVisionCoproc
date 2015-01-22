/*
 * CommandProcessor.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid
 */
#include <stdio.h>
#include "CommandProcessor.h"
#include "DiagCommand.h"


CommandProcessor::CommandProcessor() {
	m_pCmdProcessingThread=NULL;
	m_bBusy= false;
	m_pCommandToProcess= NULL;
	m_pCameraManager=new CameraManager;

	// Register available commands
	m_mapCommandsAvailable["killall"]=  KILLALL;
	m_mapCommandsAvailable["status"]=     DIAG;
	m_mapCommandsAvailable["saveimg1"]= SAVEIMG1;
	m_mapCommandsAvailable["saveimg2"]= SAVEIMG2;
	m_mapCommandsAvailable["detectyote"]= DETECT_YOTE;
	m_mapCommandsAvailable["detectplatform"]= DETECT_PLATFORM;
	m_mapCommandsAvailable["q_diag"]= Q_DIAG;
	m_mapCommandsAvailable["q_saveimg1"]= Q_SAVEIMG1;
	m_mapCommandsAvailable["q_saveimg2"]= Q_SAVEIMG2;
	m_mapCommandsAvailable["q_detectyote"]= Q_DETECT_YOTE;
	m_mapCommandsAvailable["q_detectplatform"]= Q_DETECT_PLATFORM;
	m_mapQueriesCommands["q_diag"]="diag";
	m_mapQueriesCommands["q_saveimg1"]="saveimg1";
	m_mapQueriesCommands["q_saveimg2"]="saveimg2";
	m_mapQueriesCommands["q_detectyote"]="detectyote";
	m_mapQueriesCommands["q_detectplatform"]="detectplatform";
}

CommandProcessor::~CommandProcessor() {
	delete m_pCameraManager;
}

std::string CommandProcessor::GetStatus() {
	std::string status="Command processor status:\n";

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
	//static int token=1; // not 0 (reserved)


printf("CP: processing %s\n",command.c_str());


	VisionCommand *pCommandObj=NULL;
	//m_mapTokensCommands[token]=command;


	response.clear();

	switch(nCommandCode){
	case UNKNOWN_CMD:
		response="Unknown command";
		break;

	case KILLALL:
		if(m_pCmdProcessingThread)
			delete m_pCmdProcessingThread;
		m_pCmdProcessingThread= NULL;
		//m_listResponses.clear();
		//m_mapTokensCommands.clear();
		//m_bBusy= false;
		m_mapCommandsResponses.clear();
		response="Command killed";
		break;
	case DIAG:

		response=GetStatus()+m_pCameraManager->GetStatus();
		break;

	}

	if(response.empty()==false)
		return;

	// Process external exec commands

	switch(nCommandCode){

	case SAVEIMG1:
		response="todo";
		break;
	case SAVEIMG2:
		response="todo";
		break;
	case DETECT_YOTE:
		pCommandObj=new DiagCommand;
		response="todo";
		break;
	case DETECT_PLATFORM:
		response="todo";
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
			pCommandObj->SetContext(command,this,m_pCameraManager,NULL);
			m_mapCommandsResponses[command]="Still thinking";
			printf("Launching %s\n",command.c_str());
			m_pCmdProcessingThread = new thread(LaunchExecution, (void *) pCommandObj);
		}
		return;
	}


	switch(nCommandCode){
	case Q_DIAG:
	case Q_SAVEIMG1:
	case Q_SAVEIMG2:
	case Q_DETECT_YOTE:
	case Q_DETECT_PLATFORM:
		response=m_mapCommandsResponses[m_mapQueriesCommands[command]];
		if(response.compare("Still thinking")!=0)
			m_mapCommandsResponses.erase(m_mapQueriesCommands[command]);

		break;
	}

	if(response.empty())
		response="error";

	printf("response is %s\n",response.c_str());
}
