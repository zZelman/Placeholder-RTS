/*
 * CRoom_supportSpawner.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#include "CRoom_supportSpawner.h"

CRoom_supportSpawner::CRoom_supportSpawner(CTexture* pTexture,
        const sf::Vector2<int>& currSub)
	: CRoom(pTexture, currSub)
{

}

CRoom_supportSpawner::~CRoom_supportSpawner()
{
	// TODO Auto-generated destructor stub
}

void CRoom_supportSpawner::update()
{
	CRoom::update();
}
