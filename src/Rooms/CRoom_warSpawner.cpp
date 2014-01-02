/*
 * CRoom_war.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#include "CRoom_warSpawner.h"

CRoom_warSpawner::CRoom_warSpawner(CTexture* pTexture,
                                   const sf::Vector2<int>& currSub)
	: CRoom(pTexture, currSub)
{

}

CRoom_warSpawner::~CRoom_warSpawner()
{
}

void CRoom_warSpawner::update()
{
	CRoom::update();
}
