/*
 * VisionCommand.cpp

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


#include "VisionCommand.h"

VisionCommand::VisionCommand() : m_pCmdProcessor(NULL), m_pCameraManager(NULL) {
	m_sResult.clear();
	m_sCommand.clear();
}

VisionCommand::~VisionCommand() {
	SendBackResponse();
}
