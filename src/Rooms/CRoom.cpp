/*
 * CRoom.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#include "CRoom.h"
#include "../include_sfml.h"
#include "../Tiles/CTile_Container.h"
#include "CRoom_Container.h"
#include <iostream>

CRoom::CRoom(sf::RenderWindow* pWindow,
             CTexture* pTexture,
             const sf::Vector2<int>& currSub)
	: ARender(pWindow, pTexture, currSub), AUpdate(), DPhysics()
{
//	m_pGrid = pGrid;
//	m_pRoom_Container = pRoom_Container;
}


CRoom::~CRoom()
{
}


void CRoom::update()
{
	if (m_isFirstUpdate)
	{
		m_sPhysics.nullAll();
		m_isFirstUpdate = false;
	}

//	if (canMove_vertical())
//	{
//		stepNormally();
//	}
}


void CRoom::stepNormally()
{
	int stepSize_y = m_sPhysics.velosity_y;
	m_pSprite->move(0, stepSize_y);
	m_sPhysics.isFalling = true;
}


//bool CRoom::canMove_vertical()
//{
//	sf::FloatRect futureRect = m_pSprite->getGlobalBounds();
//	sf::FloatRect unitRect = m_pSprite->getGlobalBounds();
//
//	// test the future
//	futureRect.top += m_sPhysics.velosity_y;
//
//	// room-tile collision detection
//	CSprite* returnedSprite;
//	if (m_pGrid->isCollision(futureRect, returnedSprite))
//	{
//		sf::FloatRect tileRect = returnedSprite->getGlobalBounds();
//
//		int newY = tileRect.top - unitRect.height;
//		m_pSprite->setPosition(unitRect.left, newY);
//
//		m_sPhysics.gravityTimer.restart();
//
//		m_sPhysics.isFalling = false;
//
//		return false;
//	}
//
//	// room-room collision detection
//	CRoom* returnedRoom;
//	if (m_pRoom_Container->isCollision(futureRect, returnedRoom))
//	{
//		if (returnedRoom != this)
//		{
//			sf::FloatRect tileRect = returnedRoom->getSprite()->getGlobalBounds();
//
//			int newY = tileRect.top - unitRect.height;
//			m_pSprite->setPosition(unitRect.left, newY);
//
//			m_sPhysics.gravityTimer.restart();
//
//			m_sPhysics.isFalling = false;
//
//			return false;
//		}
//	}
//
//	return true;
//}
