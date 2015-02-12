#include "LoggingService.h"

LoggingService *LoggingService::m_pInstance = NULL;  

LoggingService::LoggingService()
{
}

bool LoggingService::OpenLogFile(std::string logfname)
{
	m_pFileDescr=fopen(logfname.c_str(),"w");
	return m_pFileDescr!=NULL;
}

void LoggingService::CloseLogFile()
{
	if(m_pFileDescr!=NULL)
		fclose(m_pFileDescr);
}

LoggingService::~LoggingService()
{
}

void LoggingService::LogTrace(char *fmt,...)
{
if(m_pFileDescr){
   va_list args;
    va_start(args,fmt);
    vfprintf(m_pFileDescr,fmt,args);
    va_end(args);
}
}