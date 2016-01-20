/*
 * LoggingService.cpp

 Copyright (C) 2016  Marc Lalonde / team 3990 - Tech For Kids

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 =================================================================================================*/


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

void LoggingService::LogTrace(const char *fmt,...)
{
	if(m_pFileDescr){
		va_list args;
		va_start(args,fmt);
		vfprintf(m_pFileDescr, fmt, args);
		va_end(args);
	}
}
