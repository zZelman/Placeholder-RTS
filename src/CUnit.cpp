/*
 * CUnit.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#include "CUnit.h"
#include "CTexture.h"
#include "CSprite.h"
#include "include_sfml.h"

CUnit::CUnit(sf::RenderWindow* pWindow,
             CTexture* pTexture,
             const sf::Vector2<int>& currSub)
{
	m_pSprite = new CSprite(pWindow, pTexture, currSub);

	m_sMovement.nullAll();
	m_sMovement.isRight = true;
}


CUnit::~CUnit()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


void CUnit::update()
{
	int moveSize = 5;

	if (m_sMovement.isDown)
	{
		m_pSprite->move(0, moveSize);
	}
	else if (m_sMovement.isUp)
	{
		m_pSprite->move(0, -moveSize);

	}
	else if (m_sMovement.isLeft)
	{
		m_pSprite->move(-moveSize, 0);
	}
	else if (m_sMovement.isRight)
	{
		m_pSprite->move(moveSize, 0);
	}
}


void CUnit::render()
{
	m_pSprite->render();
}
