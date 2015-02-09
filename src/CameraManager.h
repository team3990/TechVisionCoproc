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
#include "config.h"
#ifndef USE_OPENCV_FOR_CAPTURE
#include "OCVCapture.h"
#endif

using namespace tthread;

class CameraManager {
public:
	friend void CaptureFramesCam1(void* p);
	friend void CaptureFramesCam2(void* p);


	CameraManager();
	virtual ~CameraManager();

	cv::Mat GetFrame(int nCameraNo);
	void StartCapturing();
	bool KeepCapturing(){ return m_bKeepCapturing;}
    void StopCapturing(){ m_bKeepCapturing=false;}
	std::string GetStatus(){
		std::string response="Camera manager: ";
		bool bConnected=false;
#ifdef USE_OPENCV_FOR_CAPTURE
		if(m_oVideoCap1.isOpened()){
			response=response+"\n * camera 1 connected\n";
			bConnected=true;
		}
		if(m_oVideoCap2.isOpened()){
			response=response+"\n * camera 2 connected\n";
			bConnected=true;
		}
#else
		response=response+"todo\n";
#endif
		if(bConnected==false)
			response=response+"No camera connected\n";
		return response;
	}
	mutex m_oCam1Mutex;
	mutex m_oCam2Mutex;
	void SetCapture1ThreadEnded(bool b){m_bCapture1ThreadEnded=b;}
	void SetCapture2ThreadEnded(bool b){m_bCapture2ThreadEnded=b;}

private:
	thread *m_pCap1Thread, *m_pCap2Thread;
#ifdef USE_OPENCV_FOR_CAPTURE
	cv::VideoCapture m_oVideoCap1, m_oVideoCap2;
#else
	OCVCapture m_oVideoCap1, m_oVideoCap2;
#endif
	cv::Mat m_oCurrentFrame1;
	cv::Mat m_oCurrentFrame2;
	bool m_bKeepCapturing;
	bool m_bCapture1ThreadEnded;
	bool m_bCapture2ThreadEnded;


};

#endif /* CAMERAMANAGER_H_ */
