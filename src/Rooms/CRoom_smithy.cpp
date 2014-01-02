/*
 * CRoom_smithy.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: zZelman
 */

#include "CRoom_smithy.h"

CRoom_smithy::CRoom_smithy(CTexture* pTexture,
                           const sf::Vector2<int>& currSub)
	: CRoom(pTexture, currSub)
{

}

CRoom_smithy::~CRoom_smithy()
{
}

void CRoom_smithy::update()
{
	CRoom::update();
}
