/*
 * CameraManager.h
 *
 *  Created on: Jan 19, 2015
 *      Author: odroid
 */

#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_


#include <string>
#include "tinythread.h"
#include "Defs.h"

#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#endif

#ifndef USE_OPENCV_FOR_CAPTURE
#include "OCVCapture.h"
#endif

#include "LoggingService.h"


class CameraManager {
public:


	CameraManager();
	virtual ~CameraManager();

	friend void CaptureFramesCam1(void* p);

#ifdef USE_OPENCV
	cv::Mat GetFrame(int nCameraNo);
#endif

	void StartCapturing();
	bool KeepCapturing(){ return m_bKeepCapturing; }
    void StopCapturing(){ m_bKeepCapturing= false; }

	std::string GetStatus();
	tthread::mutex m_oCam1Mutex;

	void SetCapture1ThreadEnded(bool b){ m_bCapture1ThreadEnded= b; }

	/* In case second cam is needed
		friend void CaptureFramesCam2(void* p);
		void SetCapture2ThreadEnded(bool b){m_bCapture2ThreadEnded=b;}
		tthread::mutex m_oCam2Mutex;
	*/
	
private:
	tthread::thread *m_pCap1Thread;
	//tthread::thread *m_pCap2Thread;  // in case we need a second cam

#ifdef USE_OPENCV

#ifdef USE_OPENCV_FOR_CAPTURE
	cv::VideoCapture m_oVideoCap1, m_oVideoCap2;
#else
	OCVCapture m_oVideoCap1, m_oVideoCap2;
#endif

	cv::Mat m_oCurrentFrame1;
	cv::Mat m_oCurrentFrame2;
#endif

	bool m_bKeepCapturing;
	bool m_bCapture1ThreadEnded;
	//bool m_bCapture2ThreadEnded; // in case we need a second cam

};

#endif /* CAMERAMANAGER_H_ */
