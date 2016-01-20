/*
 * CameraManager.cpp

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

#include "tinythread.h"
#include "CameraManager.h"


CameraManager::CameraManager() {

  std::cout << "Connecting with camera: ";
#ifdef USE_OPENCV

  bool bCamStateOk= m_oVideoCap1.open(CAMERA_NAME);
  if(bCamStateOk)
     std::cout << "Ok";
  else 
     std::cout << "Error";

  std::cout << std::endl;

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

	if(cammgr->m_oVideoCap1.isOpened())
		while(true){
			{
				tthread::lock_guard<tthread::mutex>(cammgr->m_oCam1Mutex);
				cammgr->m_oVideoCap1 >> cammgr->m_oCurrentFrame1;
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
		tthread::lock_guard<tthread::mutex> guard(m_oCam1Mutex);
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
#else
		return response += "No camera support (opencv not used)";
#endif
}
