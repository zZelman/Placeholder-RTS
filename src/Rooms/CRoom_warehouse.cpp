/*
 * CRoom_Warehouse.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: zZelman
 */

#include "CRoom_warehouse.h"

CRoom_warehouse::CRoom_warehouse(CTexture* pTexture,
                                 const sf::Vector2<int>& currSub)
	: CRoom(pTexture, currSub)
{

}

CRoom_warehouse::~CRoom_warehouse()
{
}

void CRoom_warehouse::update()
{
	CRoom::update();
}
