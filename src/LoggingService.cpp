#include <stdarg.h>
#include "LoggingService.h"

LoggingService *LoggingService::m_pInstance = NULL;

LoggingService::LoggingService() : m_pFileDescr(NULL)
{
}

LoggingService *LoggingService::Instance(){

if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new LoggingService;

   return m_pInstance;
}

bool LoggingService::OpenLogFile(std::string logfname)
{
	m_pFileDescr= fopen(logfname.c_str(),"a");
	return m_pFileDescr != NULL;
}

void LoggingService::CloseLogFile()
{
	if(m_pFileDescr != NULL)
		fclose(m_pFileDescr);
	m_pFileDescr = NULL;
}

LoggingService::~LoggingService()
{
	CloseLogFile();  // Just in case
}

void LoggingService::LogTrace(char *fmt,...)
{
	if(m_pFileDescr){
		va_list args;
		va_start(args,fmt);
		vfprintf(m_pFileDescr, fmt, args);
		va_end(args);
	}
}
