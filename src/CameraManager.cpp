/*
 * CameraManager.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: odroid
 */

#include "CameraManager.h"


CameraManager::CameraManager() {

#ifdef USE_OPENCV

#ifdef USE_OPENCV_FOR_CAPTURE
	m_oVideoCap1.open(0);
#else
	bool open1=m_oVideoCap1.open("/dev/video0");
#endif

#endif

	m_pCap1Thread= NULL;
	m_bCapture1ThreadEnded= false;
	m_bKeepCapturing= true;
}

CameraManager::~CameraManager() {

	StopCapturing();

	while(m_bCapture1ThreadEnded == false);

	if(m_pCap1Thread)
		delete m_pCap1Thread;
}

void CaptureFramesCam1(void* p)
{
	CameraManager *cammgr= (CameraManager*)p;

	cammgr->SetCapture1ThreadEnded(false);

#ifdef USE_OPENCV

#ifdef USE_OPENCV_FOR_CAPTURE				
	if(cammgr->m_oVideoCap1.isOpened())
#else
	  if(cammgr->m_oVideoCap1.isOpen())
#endif
		while(true){
			{
				tthread::lock_guard<tthread::mutex>(cammgr->m_oCam1Mutex);
#ifdef USE_OPENCV_FOR_CAPTURE				
				cammgr->m_oVideoCap1 >> cammgr->m_oCurrentFrame1;
#else
				if(cammgr->m_oVideoCap1.rgb(cammgr->m_oCurrentFrame1) != true)
					LOG_TRACE("Error grabbing frame from cam\n");
#endif
			}

			if(cammgr->KeepCapturing() == false)
				break;

			usleep(1000);
		}
#endif
	cammgr->SetCapture1ThreadEnded(true);
}


void CameraManager::StartCapturing()
{
	LOG_TRACE("Starting capture\n");
	m_pCap1Thread= new tthread::thread(CaptureFramesCam1, (void *) this);
}

#ifdef USE_OPENCV
cv::Mat CameraManager::GetFrame(int nCameraNo)
{
	cv::Mat frame;

	if(nCameraNo==0){
		tthread::lock_guard<tthread:mutex> guard(m_oCam1Mutex);
		if(m_oCurrentFrame1.empty() == false)
			frame= m_oCurrentFrame1.clone();
	}

	return frame;
}
#endif

std::string CameraManager::GetStatus(){
		std::string response="Camera manager: ";

		bool bConnected=false;

#ifdef USE_OPENCV

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
#else
		return response += "No camera support (opencv not used)";
#endif
}
