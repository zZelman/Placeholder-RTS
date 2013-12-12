/*
 * CRoom_Container.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: zZelman
 */

#include "CRoom_Container.h"

CRoom_Container::CRoom_Container(sf::RenderWindow* pWindow,
                                 CGrid* pGrid)
{
	m_pWindow = pWindow;
	m_pGrid = pGrid;
	m_pDebugTexture = new CTexture("res/Rooms/room 1x1.png",
	                               sf::Vector2<int>(32, 32),
	                               sf::Vector2<int>(1, 1));

	m_sKeyPress.nullAll();

	m_sKeys.up 		= sf::Keyboard::Up;
	m_sKeys.down 	= sf::Keyboard::Down;
	m_sKeys.left 	= sf::Keyboard::Left;
	m_sKeys.right 	= sf::Keyboard::Right;

	m_isMousePressed = false;

}


CRoom_Container::~CRoom_Container()
{
	for (unsigned int i = 0; i < m_rooms.size(); ++i)
	{
		delete m_rooms.at(i);
	}
	m_rooms.clear();
}


void CRoom_Container::update()
{
	for (unsigned int i = 0; i < m_rooms.size(); ++i)
	{
		CRoom* pR = m_rooms.at(i);

		applyPhysics(pR);
		pR->update();
	}
}


void CRoom_Container::render()
{
	for (unsigned int i = 0; i < m_rooms.size(); ++i)
	{
		m_rooms.at(i)->render();
	}
}


bool CRoom_Container::userInput_keyPress(sf::Event* pEvent)
{
	return false;
}


bool CRoom_Container::userInput_keyRelease(sf::Event* pEvent)
{
	return false;
}


bool CRoom_Container::userInput_mousePress(sf::Event* pEvent)
{

	initRoom(pEvent->mouseButton.x, pEvent->mouseButton.y);
	m_isMousePressed = true;
	return true;

	return false;
}


bool CRoom_Container::userInput_mouseRelease(sf::Event* pEvent)
{
	return false;
}


void CRoom_Container::initRoom(int x, int y)
{
	// x & y represent the mouse location, just need to normalize that to the grid
	sf::Vector2<int> gridSize = m_pGrid->getGridSize();
	sf::Vector2<int> gridSubSize = m_pGrid->getGridSubSize();

	// total pixels in the grid
	int totalX = gridSize.x * gridSubSize.x;
	int totalY = gridSize.y * gridSubSize.y;

	// compute new coords (in GRID space)
	x = (x * gridSize.x) / totalX;
	y = (y * gridSize.y) / totalY;

	// translate from GIRD space to SCREEN space
	x = x * gridSubSize.x;
	y = y * gridSubSize.y;

	// add new room to vector
	CRoom* pR = new CRoom(m_pWindow, m_pGrid, m_pDebugTexture, sf::Vector2<int>(1, 1));
	pR->getSprite()->setPosition(x, y);
	m_rooms.push_back(pR);
}


void CRoom_Container::applyPhysics(CRoom* pRoom)
{
	sf::Time timer = pRoom->m_sPhysics.gravityTimer.getElapsedTime();
	int elapsed = timer.asMilliseconds();
	pRoom->m_sPhysics.velosity_y = (0.01) * (elapsed);
}

