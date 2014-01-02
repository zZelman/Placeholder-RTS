/*
 * CRoom_kitchen.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: zZelman
 */

#include "CRoom_kitchen.h"

CRoom_kitchen::CRoom_kitchen(CTexture* pTexture,
                             const sf::Vector2<int>& currSub)
	: CRoom(pTexture, currSub)
{

}

CRoom_kitchen::~CRoom_kitchen()
{
}

void CRoom_kitchen::update()
{
	CRoom::update();
}
