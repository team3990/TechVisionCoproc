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
#include <opencv2/opencv.hpp>
#include "tinythread.h"

using namespace tthread;

class CameraManager {
public:
	friend void CaptureFramesCam1(void* p);
	friend void CaptureFramesCam2(void* p);


	CameraManager();
	virtual ~CameraManager();

	cv::Mat GetFrame(int nCameraNo);
	void StartCapturing();

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
	mutex m_oCam1Mutex;
	mutex m_oCam2Mutex;


private:
	thread *m_pCap1Thread, *m_pCap2Thread;
	cv::VideoCapture m_oVideoCap1, m_oVideoCap2;
	cv::Mat m_oCurrentFrame1;
	cv::Mat m_oCurrentFrame2;



};

#endif /* CAMERAMANAGER_H_ */
