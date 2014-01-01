/*
 * CUnit.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#include "CUnit.h"
#include "../Graphics/CTexture.h"
#include "../Graphics/CSprite.h"
#include "../Tiles/CTile_Container.h"
#include "../Graphics/include_sfml.h"
#include <iostream>

CUnit::CUnit(sf::RenderWindow* pWindow,
             CTile_Container* pGrid,
             CTexture* pTexture,
             const sf::Vector2<int>& currSub)
	: AUpdate(), ARender(pWindow, pTexture, currSub), DPhysics()
{
	m_pGrid = pGrid;

	m_sMovement.nullAll();
//	m_sMovement.isLeft	= true;
	m_sMovement.isRight	= true;
//	m_sMovement.isUp 	= true;
	m_sMovement.isDown 	= true;
}


CUnit::~CUnit()
{
}


void CUnit::update()
{
	if (m_isFirstUpdate)
	{
		m_sPhysics.nullAll();
		m_isFirstUpdate = false;
	}


	if (canMove_horizontal())
	{
		stepNormally();
	}

	if (canMove_vertical())
	{
		stepNormally();
	}

}


void CUnit::stepNormally()
{
	int stepSize_y = m_sPhysics.velosity_y;
	m_sPhysics.velosity_x = 5;
	int stepSize_x = m_sPhysics.velosity_x;

	if (m_sMovement.isDown)
	{
		m_pSprite->move(0, stepSize_y);
	}
	else if (m_sMovement.isUp)
	{
		m_pSprite->move(0, -stepSize_y);
	}

	if (m_sMovement.isLeft)
	{
		m_pSprite->move(-stepSize_x, 0);
	}
	else if (m_sMovement.isRight)
	{
		m_pSprite->move(stepSize_x, 0);
	}
}


bool CUnit::canMove_vertical()
{
	sf::FloatRect futureRect = m_pSprite->getGlobalBounds();
	sf::FloatRect unitRect = m_pSprite->getGlobalBounds();

	CSprite* returnedSprite;

	if (m_sMovement.isDown)
	{
		futureRect.top += m_sPhysics.velosity_y; // test the future

		// unit-tile collision detection
		if (m_pGrid->isCollision(futureRect, returnedSprite))
		{
			sf::FloatRect tileRect = returnedSprite->getGlobalBounds();

			int newY = tileRect.top - unitRect.height;
			m_pSprite->setPosition(unitRect.left, newY);

			m_sPhysics.gravityTimer.restart();

			return false;
		}

	}
	else if (m_sMovement.isUp)
	{
		futureRect.top -= m_sPhysics.velosity_y; // test the future

		// unit-tile collision detection
		if (m_pGrid->isCollision(futureRect, returnedSprite))
		{
			sf::FloatRect tileRect = returnedSprite->getGlobalBounds();

			int newY = tileRect.top + tileRect.height;
			m_pSprite->setPosition(unitRect.left, newY);

			m_sPhysics.gravityTimer.restart();

			return false;
		}
	}

	return true;
}


bool CUnit::canMove_horizontal()
{
	sf::FloatRect futureRect = m_pSprite->getGlobalBounds();
	sf::FloatRect unitRect = m_pSprite->getGlobalBounds();

	CSprite* returnedSprite;

	if (m_sMovement.isRight)
	{
		futureRect.left += m_sPhysics.velosity_x; // test the future

		// unit-tile collision detection
		if (m_pGrid->isCollision(futureRect, returnedSprite))
		{
			sf::FloatRect tileRect = returnedSprite->getGlobalBounds();

			int newX = tileRect.left - unitRect.width;
			m_pSprite->setPosition(newX, unitRect.top);

			return false;
		}
	}
	else if (m_sMovement.isLeft)
	{
		futureRect.left -= m_sPhysics.velosity_x; // test the future

		// unit-tile collision detection
		if (m_pGrid->isCollision(futureRect, returnedSprite))
		{
			sf::FloatRect tileRect = returnedSprite->getGlobalBounds();

			int newX = tileRect.left + tileRect.width;
			m_pSprite->setPosition(newX, unitRect.top);

			return false;
		}
	}

//	futureRect.left += m_sPhysics.velosity_x; // test the future
//
//	if (m_pGrid->isCollision(futureRect, returnedSprite))
//	{
//		sf::FloatRect tileRect = returnedSprite->getGlobalBounds();
//
//		if (m_sMovement.isLeft)
//		{
//			int newX = tileRect.left + tileRect.width;
//			m_pSprite->setPosition(newX, unitRect.top);
//		}
//		else if (m_sMovement.isRight)
//		{
//			int newX = tileRect.left - futureRect.width;
//			m_pSprite->setPosition(newX, unitRect.top);
//		}
//
//		return false;
//	}

	return true;
}
