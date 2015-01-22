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
#include <list>
#include "tinythread.h"
#include "CameraManager.h"
class VisionCommand;

using namespace tthread;


class CommandProcessor {
public:

	enum {UNKNOWN_CMD=0,KILLALL,DIAG,SAVEIMG1,SAVEIMG2,DETECT_YOTE,DETECT_PLATFORM,
		  Q_DIAG,Q_SAVEIMG1,Q_SAVEIMG2,Q_DETECT_YOTE,Q_DETECT_PLATFORM};

	CommandProcessor();
	virtual ~CommandProcessor();

	/*// Called by VisionCoprocessor
	bool IsJobCompleted(){
		lock_guard<mutex> guard(m_oResponseMutex);
		if(m_listResponses.size()>0)
			return true;
		return false;
	}

	// Called by VisionCoprocessor
	void GetJobResults(std::string& response){
		if(m_listResponses.size()>0){
			lock_guard<mutex> guard(m_oResponseMutex);
			response=m_listResponses.front();
			printf("popped response=-%s-\n",response.c_str());
			m_listResponses.pop_front();
		}
	}*/
	// Called by VisionCoprocessor
	void ProcessCmd(std::string command,std::string& response);


	// called by a VisionCommand object
	CameraManager* GetCameraManager(){ return m_pCameraManager; }

	// Called by VisionCommand objects
	void StoreResponse(std::string cmd, std::string result){
		lock_guard<mutex> guard(m_oResponseMutex);

		/*
printf("return trip: token=%d result=-%s-\n",token,result.c_str());
		if(token==0)
			m_listResponses.push_back(result);
		else{
			std::map<int,std::string>::iterator iter;


			iter=m_mapTokensCommands.find(token);
			if(iter!=m_mapTokensCommands.end()){
				std::string s=iter->second+"=>"+result;
				printf("response is %s\n",s.c_str());
				m_listResponses.push_back(iter->second+"=>"+result);
				m_mapTokensCommands.erase(iter);
			}else m_listResponses.push_back("error");
		}*/
		m_mapCommandsResponses[cmd]=result;
	}
	std::string GetStatus();

private:
	int GetCommandCodeFromString(std::string strcommand);

	thread *m_pCmdProcessingThread;
	CameraManager *m_pCameraManager;
	std::map<std::string,int> m_mapCommandsAvailable;

	VisionCommand *m_pCommandToProcess;
	//std::string m_sRequest; // Msg received from the dispatcher (=command)
	//std::list<std::string> m_listResponses; // Result to be returned;
	//std::map<int,std::string> m_mapTokensCommands;
	std::map<std::string,std::string> m_mapCommandsResponses;
	std::map<std::string,std::string> m_mapQueriesCommands;
	mutex m_oResponseMutex;
	bool m_bBusy;
};

#endif /* COMMANDPROCESSOR_H_ */
