/*
 * CUnitContainer.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#include "CUnit_Container.h"
#include "CTexture.h"
#include "include_sfml.h"


CUnit_Container::CUnit_Container(sf::RenderWindow* pWindow, CTile_Container* pGrid)
	: AUserInput()
{
	m_pWindow = pWindow;
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
	for (unsigned int i = 0; i < m_units.size(); ++i)
	{
		delete m_units.at(i);
	}
	m_units.clear();

	delete m_pDebugTexture;
	m_pDebugTexture = NULL;
}


void CUnit_Container::update()
{
	for (unsigned int i = 0; i < m_units.size(); ++i)
	{
		CUnit* pU = m_units.at(i);

		applyPhysics(pU);
		pU->update();
	}
}


void CUnit_Container::render()
{
	for (unsigned int i = 0; i < m_units.size(); ++i)
	{
		m_units.at(i)->render();
	}
}


void CUnit_Container::getCollisiondata(std::list<ARender*>* pList)
{
	for (unsigned int i = 0; i < m_units.size(); ++i)
	{
		pList->push_front(m_units[i]);
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
	m_isMousePressed = true;
	return true;
}


bool CUnit_Container::userInput_mouseRelease(sf::Event* pEvent)
{
	m_isMousePressed = false;
	return true;
}


void CUnit_Container::initUnit(int x, int y)
{
	CUnit* pU = new CUnit(m_pWindow, m_pGrid, m_pDebugTexture, sf::Vector2<int>(1, 1));
	pU->getSprite()->setPosition(x, y);
	m_units.push_back(pU);
}


void CUnit_Container::applyPhysics(CUnit* pUnit)
{
	sf::Time timer = pUnit->m_sPhysics.gravityTimer.getElapsedTime();
	int elapsed = timer.asMilliseconds();
	pUnit->m_sPhysics.velosity_y = (0.01) * (elapsed);
}
