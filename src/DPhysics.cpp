/*
 * DPhysics.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#include "DPhysics.h"


DPhysics::DPhysics()
{
	m_sPhysics.nullAll();
}


DPhysics::~DPhysics()
{
}


void DPhysics::SPhysics::nullAll()
{
	gravityTimer.restart();
	velosity_x = 0;
	velosity_y = 0;
	isFalling = false;
}
