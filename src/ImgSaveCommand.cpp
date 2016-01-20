/*
 * ImgSaveCommand.cpp

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
