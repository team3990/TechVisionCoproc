/*
 * CameraManager.h
 *
 *  Created on: Jan 19, 2015
 *      Author: odroid
 */

#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include <opencv2/opencv.hpp>
#include <string>


class CameraManager {
public:
	CameraManager();
	virtual ~CameraManager();
	std::string GetStatus(){
		std::string response="Camera manager: ";
		bool bConnected=false;
		if(m_oVideoCap1.isOpened()){
			response=response+"\n * camera 1 connected\n";
			bConnected=true;
		}
		if(m_oVideoCap2.isOpened()){
			response=response+"\n * camera 2 connected\n";
			bConnected=true;
		}
		if(bConnected==false)
			response=response+"No camera connected\n";
		return response;
	}
private:
	cv::VideoCapture m_oVideoCap1, m_oVideoCap2;

};

#endif /* CAMERAMANAGER_H_ */
