/*
 * CameraManager.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: odroid
 */

#include <stdio.h>
#include "CameraManager.h"
#include "config.h"

CameraManager::CameraManager() {
#ifdef USE_OPENCV_FOR_CAPTURE
	m_oVideoCap1.open(0);
	m_oVideoCap2.open(1);
#else
	bool open1=m_oVideoCap1.open("/dev/video0");
	bool open2=m_oVideoCap2.open("/dev/video1");
#endif

m_pCap1Thread=NULL;
m_pCap2Thread=NULL;
m_bKeepCapturing= true;

}

CameraManager::~CameraManager() {

	StopCapturing();
	while(m_bCapture1ThreadEnded==false);
	while(m_bCapture2ThreadEnded==false);

	if(m_pCap1Thread)
		delete m_pCap1Thread;
	if(m_pCap2Thread)
		delete m_pCap2Thread;
}

void CaptureFramesCam1(void* p)
{
	CameraManager *cammgr=(CameraManager*)p;
	cammgr->SetCapture1ThreadEnded(false);

	if(cammgr->m_oVideoCap1.isOpened())
		while(1){
			{
				lock_guard<mutex>(cammgr->m_oCam1Mutex);
				cammgr->m_oVideoCap1 >> cammgr->m_oCurrentFrame1;
			}

			if(cammgr->KeepCapturing()==false)
				break;

			usleep(1000);
		}
	cammgr->SetCapture1ThreadEnded(true);
}

void CaptureFramesCam2(void* p)
{
	CameraManager *cammgr=(CameraManager*)p;
	cammgr->SetCapture2ThreadEnded(false);
	if(cammgr->m_oVideoCap2.isOpened())
		while(1){
			{
				lock_guard<mutex>(cammgr->m_oCam2Mutex);
				cammgr->m_oVideoCap2 >> cammgr->m_oCurrentFrame2;
			}
			if(cammgr->KeepCapturing()==false)
				break;

			usleep(1000);
		}
	cammgr->SetCapture2ThreadEnded(true);
}

void CameraManager::StartCapturing()
{
	printf("Starting capture\n");
	m_pCap1Thread= new thread(CaptureFramesCam1, (void *) this);
	m_pCap2Thread= new thread(CaptureFramesCam2, (void *) this);

}

cv::Mat CameraManager::GetFrame(int nCameraNo)
{
	cv::Mat frame;

	if(nCameraNo==0){
		lock_guard<mutex> guard(m_oCam1Mutex);
		if(m_oCurrentFrame1.empty()==false)
		frame=m_oCurrentFrame1.clone();
	}

	if(nCameraNo==1)
	{
			lock_guard<mutex> guard(m_oCam2Mutex);
			if(m_oCurrentFrame2.empty()==false)
			frame=m_oCurrentFrame2.clone();
	}


	return frame;
}

