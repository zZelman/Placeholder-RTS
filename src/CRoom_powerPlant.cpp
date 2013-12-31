/*
 * CRoom_powerPlant.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#include "CRoom_powerPlant.h"

CRoom_powerPlant::CRoom_powerPlant(sf::RenderWindow* pWindow,
        CTexture* pTexture,
        const sf::Vector2<int>& currSub) : CRoom(pWindow, pTexture, currSub) {

}

CRoom_powerPlant::~CRoom_powerPlant() {
}

void CRoom_powerPlant::update()
{
	CRoom::update();
}
