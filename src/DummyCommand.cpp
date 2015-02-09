/*
 * DummyCommand.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: odroid
 */

#include "DummyCommand.h"
#include <opencv2/opencv.hpp>

DummyCommand::DummyCommand(int mode) : m_nMode(mode)
{
	// TODO Auto-generated constructor stub
}

DummyCommand::~DummyCommand() {
	// TODO Auto-generated destructor stub
}

void DummyCommand::Execute(){

	// Fake computations...
	if(m_nMode==1)
		usleep(50000);  //50 ms
	else sleep(2);   //2s
	char str[128];
	sprintf(str,"Test mode %d: result=%s",m_nMode,(m_nMode==1?"pi":"nan"));
	SetResult(str);
}

void BWCommand::Execute(){
	std::string str;

cv::Mat image=m_pCameraManager->GetFrame(0);

cv::Mat bwimage(image.rows, image.cols, 1);
cvtColor(image, bwimage, CV_BGR2GRAY);
cv::threshold(bwimage, bwimage, 128, 255, cv::THRESH_BINARY);
int n=cv::countNonZero(bwimage);
printf("n=%d\n",n);
if(n > bwimage.cols * bwimage.rows / 2)
		str = "white!";

else
	str = "black!";


	SetResult(str);
}
