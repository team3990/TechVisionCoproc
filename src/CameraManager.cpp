/*
 * CameraManager.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: odroid
 */

#include "CameraManager.h"
#include "config.h"

CameraManager::CameraManager() {
	m_oVideoCap1.open(0);
	m_oVideoCap2.open(1);

}

CameraManager::~CameraManager() {
	// TODO Auto-generated destructor stub
}

