/*
 * CameraManager.h
 *
 *  Created on: Jan 19, 2015
 *      Author: odroid
 */

#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include <string>
class CameraManager {
public:
	CameraManager();
	virtual ~CameraManager();
	std::string GetStatus(){
		return "Camera manager: no camera connected\n";
	}
};

#endif /* CAMERAMANAGER_H_ */
