/*
 * ImgSaveCommand.cpp

 *
 *  Created on: Jan 26, 2015
 *      Author: odroid
 */
#include <sys/stat.h>
#include <string>
#include "ImgSaveCommand.h"

ImgSaveCommand::ImgSaveCommand(std::string savedir,int camno) : m_sSaveDir(savedir), m_nCamNo(camno), m_nImageNo(0)
{
}

ImgSaveCommand::~ImgSaveCommand()
{
}


void ImgSaveCommand::Execute() {

#ifdef USE_OPENCV

	char str[1024];
	struct stat buffer;

	// We don't want to overwrite already saved images, so
	// loop until a free filename is found.
	do{
		sprintf(str,"%s/frame%03d.png", m_sSaveDir.c_str(), m_nImageNo++);
	} while(stat (str, &buffer) == 0);

	cv::Mat image=m_pCameraManager->GetFrame(m_nCamNo);

	if(image.empty() == false){
		cv::imwrite(str, image);
		SetResult("Saved " + std::string(str));
	}else SetResult("Trying to save empty image!");
#else
	SetResult("Can't save image (no camera support)!");
#endif

}
