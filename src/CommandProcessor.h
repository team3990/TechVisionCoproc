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

class CommandProcessor {
public:
	CommandProcessor();
	virtual ~CommandProcessor();

	bool IsJobCompleted();
	void GetJobResults(std::string& origmsg, std::string& response);



};

#endif /* COMMANDPROCESSOR_H_ */
