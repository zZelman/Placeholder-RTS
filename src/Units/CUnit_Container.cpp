/*
 * CUnitContainer.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#include "CUnit_Container.h"
#include "../Graphics/CTexture.h"
#include "../include_sfml.h"


CUnit_Container::CUnit_Container(CTile_Container* pGrid)
	: AUserInput()
{
	m_pGrid = pGrid;
	m_pDebugTexture = new CTexture("res/Unit Tilesets/debug unit.png",
	                               sf::Vector2<int>(16, 16),
	                               sf::Vector2<int>(1, 1));

	m_sKeys.up 		= sf::Keyboard::Up;
	m_sKeys.down 	= sf::Keyboard::Down;
	m_sKeys.left 	= sf::Keyboard::Left;
	m_sKeys.right 	= sf::Keyboard::Right;
}


CUnit_Container::~CUnit_Container()
{
	for (std::list<CUnit*>::iterator itr = m_units.begin();
	        itr != m_units.end();
	        ++itr)
	{
		delete(*itr);
	}
	m_units.clear();

	delete m_pDebugTexture;
	m_pDebugTexture = NULL;
}


void CUnit_Container::update()
{
	for (std::list<CUnit*>::iterator itr = m_units.begin();
	        itr != m_units.end();
	        ++itr)
	{
		CUnit* pU = (*itr);

//		applyPhysics(pU);
		pU->update();
	}
}


void CUnit_Container::getCollisiondata(std::list<ARenderable*>* pList)
{
	for (std::list<CUnit*>::iterator itr = m_units.begin();
	        itr != m_units.end();
	        ++itr)
	{
		pList->push_front((*itr));
	}
}


void CUnit_Container::getRenderData(std::list<ARenderable*>* pList)
{
	for (std::list<CUnit*>::iterator itr = m_units.begin();
	        itr != m_units.end();
	        ++itr)
	{
		pList->push_front((*itr));
	}
}


bool CUnit_Container::userInput_keyPress(sf::Event* pEvent)
{
	return false;
}


bool CUnit_Container::userInput_keyRelease(sf::Event* pEvent)
{
	return false;
}


bool CUnit_Container::userInput_mousePress(sf::Event* pEvent)
{
	initUnit(pEvent->mouseButton.x, pEvent->mouseButton.y);
	return true;
}


bool CUnit_Container::userInput_mouseRelease(sf::Event* pEvent)
{
	return false;
}


void CUnit_Container::initUnit(int x, int y)
{
	CUnit* pU = new CUnit(m_pGrid, m_pDebugTexture, sf::Vector2<int>(1, 1));
	pU->getSprite()->setPosition(x, y);
	m_units.push_back(pU);
}


void CUnit_Container::applyPhysics(CUnit* pUnit)
{
	sf::Time timer = pUnit->m_sPhysics.gravityTimer.getElapsedTime();
	int elapsed = timer.asMilliseconds();
	pUnit->m_sPhysics.velosity_y = (0.01) * (elapsed);
}
