/*
 * CUI.cpp
 *
 *  Created on: Jan 2, 2014
 *      Author: zZelman
 */

#include "CUI.h"

CUI::CUI(CTile_Container* pTile_Container,
         CRoom_Container* pRoom_Container,
         CSpawner* pSpawner)
{
	m_pTile_Container = pTile_Container;
	m_pRoom_Container = pRoom_Container;
	m_pSpawner = pSpawner;

	setRoomKeybinds();

	m_room_keyStates.data_false();
}


void CUI::setRoomKeybinds()
{
	m_room_spawnKeys.warehouse 			= sf::Keyboard::Num1;
	m_room_spawnKeys.kitchen 			= sf::Keyboard::Num2;
	m_room_spawnKeys.smithy 			= sf::Keyboard::Num3;
	m_room_spawnKeys.powerPlant 		= sf::Keyboard::Num4;
	m_room_spawnKeys.warSpawner			= sf::Keyboard::Num5;
	m_room_spawnKeys.researchSpawner	= sf::Keyboard::Num6;
	m_room_spawnKeys.supportSpawner		= sf::Keyboard::Num7;
}


CUI::~CUI()
{
}


void CUI::update()
{
}


bool CUI::userInput_keyPress(sf::Event* pEvent)
{
	// set generic (function wide) values
	m_sSpawnInfo.isMouse = false;
	m_sSpawnInfo.keyPressState = true;
	m_sSpawnInfo.pEvent = pEvent;

	if (roomSwitchBoard() == true)
	{
		return true;
	}

	return false;
}


bool CUI::userInput_keyRelease(sf::Event* pEvent)
{
	m_sSpawnInfo.isMouse = false;
	m_sSpawnInfo.keyPressState = false;
	m_sSpawnInfo.pEvent = pEvent;

	if (roomSwitchBoard() == true)
	{
		return true;
	}

	return false;
}


bool CUI::userInput_mousePress(sf::Event* pEvent)
{
	if (pEvent->mouseButton.button == sf::Mouse::Left)
	{
		// set generic (function wide) values
		m_sSpawnInfo.isMouse = true;
		m_sSpawnInfo.keyPressState = true;
		m_sSpawnInfo.pEvent = pEvent;

		if (roomSwitchBoard() == true)
		{
			return true;
		}

	}
	else if (pEvent->mouseButton.button == sf::Mouse::Right)
	{
		int x = pEvent->mouseButton.x;
		int y = pEvent->mouseButton.y;
		if (deleteRoom(x, y))
		{
			return true;
		}
	}

	return false;
}


bool CUI::userInput_mouseRelease(sf::Event* pEvent)
{
	return false;
}


bool CUI::roomSwitchBoard()
{
	// WAREHOUSE
	setInfo_warehouse();
	if (canSpawnRoom())
	{
		return true;
	}

	// KITCHEN
	setInfo_kitchen();
	if (canSpawnRoom())
	{
		return true;
	}

	// SMITHY
	setInfo_smithy();
	if (canSpawnRoom())
	{
		return true;
	}

	// POWER PLANT
	setInfo_powerPlant();
	if (canSpawnRoom())
	{
		return true;
	}

	// WAR SPAWNER
	setInfo_warSpawner();
	if (canSpawnRoom())
	{
		return true;
	}

	// RESEARCH SPAWNER
	setInfo_researchSpawner();
	if (canSpawnRoom())
	{
		return true;
	}

	// SUPPORT SPAWNER
	setInfo_supportSpawner();
	if (canSpawnRoom())
	{
		return true;
	}

	return false;
}


void CUI::setInfo_warehouse()
{
	m_sSpawnInfo.spawnKey = &m_room_spawnKeys.warehouse;
	m_sSpawnInfo.spawnKeyState = &m_room_keyStates.warehouse;
	m_sSpawnInfo.spawnFunction = &CSpawner::spawnRoom_warehouse;
}


void CUI::setInfo_kitchen()
{
	m_sSpawnInfo.spawnKey = &m_room_spawnKeys.kitchen;
	m_sSpawnInfo.spawnKeyState = &m_room_keyStates.kitchen;
	m_sSpawnInfo.spawnFunction = &CSpawner::spawnRoom_kitchen;
}


void CUI::setInfo_smithy()
{
	m_sSpawnInfo.spawnKey = &m_room_spawnKeys.smithy;
	m_sSpawnInfo.spawnKeyState = &m_room_keyStates.smithy;
	m_sSpawnInfo.spawnFunction = &CSpawner::spawnRoom_smithy;
}


void CUI::setInfo_powerPlant()
{
	m_sSpawnInfo.spawnKey = &m_room_spawnKeys.powerPlant;
	m_sSpawnInfo.spawnKeyState = &m_room_keyStates.powerPlant;
	m_sSpawnInfo.spawnFunction = &CSpawner::spawnRoom_powerPlant;
}


void CUI::setInfo_warSpawner()
{
	m_sSpawnInfo.spawnKey = &m_room_spawnKeys.warSpawner;
	m_sSpawnInfo.spawnKeyState = &m_room_keyStates.warSpawner;
	m_sSpawnInfo.spawnFunction = &CSpawner::spawnRoom_warSpawner;
}


void CUI::setInfo_researchSpawner()
{
	m_sSpawnInfo.spawnKey = &m_room_spawnKeys.researchSpawner;
	m_sSpawnInfo.spawnKeyState = &m_room_keyStates.researchSpawner;
	m_sSpawnInfo.spawnFunction = &CSpawner::spawnRoom_researchSpawner;
}


void CUI::setInfo_supportSpawner()
{
	m_sSpawnInfo.spawnKey = &m_room_spawnKeys.supportSpawner;
	m_sSpawnInfo.spawnKeyState = &m_room_keyStates.supportSpawner;
	m_sSpawnInfo.spawnFunction = &CSpawner::spawnRoom_supportSpawner;
}


bool CUI::canSpawnRoom()
{
	// mouse click (keyPressState describes whether or not it is on or off)
	if (m_sSpawnInfo.isMouse == true)
	{
		int x = m_sSpawnInfo.pEvent->mouseButton.x;
		int y = m_sSpawnInfo.pEvent->mouseButton.y;

		// click needs to be not in a room, and above a
		//	room that is on the same x coords to pass
		if (m_pRoom_Container->canSpawnAtPos(x, y) == false)
		{
			return false;
		}

		// prep the x,y of the mouse for room spawn
		normalizeToGrid(&x, &y);

		// mouse was pressed
		if (m_sSpawnInfo.keyPressState == true
		        && *(m_sSpawnInfo.spawnKeyState) == true)
		{
			// call the specified spawner function by resolving scope to this object,
			//	then derefferenceing the function pointer, and then passing the arguments
			(m_pSpawner->*m_sSpawnInfo.spawnFunction)(x, y);

			return true;
		}
		// Mouse released
		else if (m_sSpawnInfo.keyPressState == false
		         && *(m_sSpawnInfo.spawnKeyState) == true)
		{

		}
	}
	else // key click
	{
		// key pressed
		if (m_sSpawnInfo.keyPressState == true
		        && m_sSpawnInfo.pEvent->key.code == *(m_sSpawnInfo.spawnKey))
		{
			*(m_sSpawnInfo.spawnKeyState) = true;
			return true;
		}
		// key released
		else if (m_sSpawnInfo.keyPressState == false
		         && m_sSpawnInfo.pEvent->key.code == *(m_sSpawnInfo.spawnKey))
		{
			*(m_sSpawnInfo.spawnKeyState) = false;
			return true;
		}
	}

	// Criterion not met to spawn or update the spawn conditions for a room
	return false;
}


void CUI::normalizeToGrid(int* x, int* y)
{
	// * use the grid function to translate
	// * x and y are now in grid coords
	m_pTile_Container->screenToGrid(x, y);

	// translate from GIRD space to SCREEN space
	sf::Vector2<int> gridSubSize = m_pTile_Container->getGridSubSize();
	(*x) = (*x) * gridSubSize.x;
	(*y) = (*y) * gridSubSize.y;
}


bool CUI::deleteRoom(int x, int y)
{
	return m_pRoom_Container->deleteRoom(x, y);
}
