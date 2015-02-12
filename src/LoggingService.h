/*
 * CommandProcessor.h
 *
 *  Created on: Jan 17, 2015
 *      Author: odroid
 */

#ifndef LOGGINGSERVICE_H
#define LOGGINGSERVICE_H

#include <string>
#include <stdio.h>

#define LOG_TRACE(x) LoggingService::Instance()->LogTrace(x)

class LoggingService{

public:
	static LoggingService* Instance();
	void LogTrace(char *format,...);
	bool OpenLogFile(std::string logFile);
	void CloseLogFile();
	
private:

	LoggingService();
	virtual ~LoggingService();
	LoggingService(LoggingService const&){}
	LoggingService& operator=(LoggingService const&){}
	static LoggingService* m_pInstance;
	FILE *m_pFileDescr;
};

#endif /* LOGGINGSERVICE_H */
