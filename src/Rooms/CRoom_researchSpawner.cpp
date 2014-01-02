/*
 * CRoom_researchSpawner.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#include "CRoom_researchSpawner.h"

CRoom_researchSpawner::CRoom_researchSpawner(CTexture* pTexture,
        const sf::Vector2<int>& currSub)
	: CRoom(pTexture, currSub)
{

}

CRoom_researchSpawner::~CRoom_researchSpawner()
{
}

void CRoom_researchSpawner::update()
{
	CRoom::update();
}
