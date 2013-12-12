/*
 * CRoom.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#include "CRoom.h"
#include "CGrid.h"
#include "include_sfml.h"
#include "CGrid.h"

CRoom::CRoom(sf::RenderWindow* pWindow,
             CGrid* pGrid,
             CTexture* pTexture,
             const sf::Vector2<int>& currSub)
{
	m_pGrid = pGrid;

	m_pSprite = new CSprite(pWindow, pTexture, currSub);

	m_isFalling = false;

	m_isFirstUpdate = true;

}


CRoom::~CRoom()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


CSprite* const CRoom::getSprite()
{
	return m_pSprite;
}


void CRoom::update()
{
	if (m_isFirstUpdate)
	{
		m_sPhysics.nullAll();
		m_isFirstUpdate = false;
	}

	m_sPhysics.velosity_y = 5;
	int stepSize_y = m_sPhysics.velosity_y;

	if (canMove_vertical())
	{
		m_pSprite->move(0, stepSize_y);
		m_isFalling = true;
	}
}


void CRoom::render()
{
	m_pSprite->render();
}


bool CRoom::canMove_vertical()
{
	sf::FloatRect futureRect = m_pSprite->getGlobalBounds();
	sf::FloatRect unitRect = m_pSprite->getGlobalBounds();

	CSprite* returnedSprite;

	futureRect.top += m_sPhysics.velosity_y; // test the future

	// room-tile collision detection
	if (m_pGrid->isCollision(futureRect, returnedSprite))
	{
		sf::FloatRect tileRect = returnedSprite->getGlobalBounds();

		int newY = tileRect.top - unitRect.height;
		m_pSprite->setPosition(unitRect.left, newY);

		m_sPhysics.gravityTimer.restart();

		m_isFalling = false;

		return false;
	}

	return true;
}
