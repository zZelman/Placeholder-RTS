/*
 * CRoom_Container.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: zZelman
 */

#include "CRoom_Container.h"

CRoom_Container::CRoom_Container(sf::RenderWindow* pWindow,
                                 CTile_Container* pGrid) : AUserInput()
{
	m_pWindow = pWindow;
	m_pGrid = pGrid;

	init_RoomTextures();

	m_sKeys.up 		= sf::Keyboard::Up;
	m_sKeys.down 	= sf::Keyboard::Down;
	m_sKeys.left 	= sf::Keyboard::Left;
	m_sKeys.right 	= sf::Keyboard::Right;

	m_sRoomSpawnKeys.warehouse = sf::Keyboard::Num1;
	m_sRoomSpawnKeys.kitchen = sf::Keyboard::Num2;

	m_sNumRooms.nullAll();
	m_sRoomSpawnKeyStates.nullAll();
}


void CRoom_Container::init_RoomTextures()
{
	m_pDebugTexture = new CTexture("res/Rooms/room 1x1.png",
	                               sf::Vector2<int>(32, 32),
	                               sf::Vector2<int>(1, 1));

	m_pWarehouseTexture = new CTexture("res/Rooms/warehouse.png",
	                                   sf::Vector2<int>(32, 32),
	                                   sf::Vector2<int>(1, 1));

	m_pKitchenTexture = new CTexture("res/Rooms/kitchen.png",
	                                 sf::Vector2<int>(64, 32),
	                                 sf::Vector2<int>(1, 1));
}


void CRoom_Container::delete_RoomTextures()
{
	delete m_pDebugTexture;
	m_pDebugTexture = NULL;

	delete m_pWarehouseTexture;
	m_pWarehouseTexture = NULL;

	delete m_pKitchenTexture;
	m_pKitchenTexture = NULL;
}


CRoom_Container::~CRoom_Container()
{
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		delete(*itr);
	}
	m_rooms.clear();

	delete_RoomTextures();
}


void CRoom_Container::update()
{
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		CRoom* pR = (*itr);

//		applyPhysics(pR);
		pR->update();
	}
}


void CRoom_Container::render()
{
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		(*itr)->render();
	}
}


void CRoom_Container::getCollisiondata(std::list<ARender*>* pList)
{
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		pList->push_front((*itr));
	}
}


bool CRoom_Container::userInput_keyPress(sf::Event* pEvent)
{
	if (canSpawnRoom_warehouse(true, false, pEvent))
	{
		return true;
	}
	else if (canSpawnRoom_kitchen(true, false, pEvent))
	{
		return true;
	}
	else if (canSpawnRoom_room(true, false, pEvent))
	{
		return true;
	}

//	else if (pEvent->key.code == m_sRoomSpawnKeys.kitchen)
//	{
//		m_sRoomSpawnKeyStates.kitchen = true;
//
//		return true;
//	}

	return false;
}


bool CRoom_Container::userInput_keyRelease(sf::Event* pEvent)
{
	if (canSpawnRoom_warehouse(false, false, pEvent))
	{
		return true;
	}
	else if (canSpawnRoom_kitchen(false, false, pEvent))
	{
		return true;
	}
	else if (canSpawnRoom_room(false, false, pEvent))
	{
		return true;
	}

//	else if (pEvent->key.code == m_sRoomSpawnKeys.kitchen)
//	{
//		m_sRoomSpawnKeyStates.kitchen = false;
//
//		return true;
//	}

	return false;
}


bool CRoom_Container::userInput_mousePress(sf::Event* pEvent)
{
	if (pEvent->mouseButton.button == sf::Mouse::Left)
	{
		if (canSpawnRoom_warehouse(true, true, pEvent))
		{
			return true;
		}
		else if (canSpawnRoom_kitchen(true, true, pEvent))
		{
			return true;
		}
		else if (canSpawnRoom_room(true, true, pEvent))
		{
			return true;
		}


//		else if (m_sRoomSpawnKeyStates.kitchen == true)
//		{
//			initKitchen(x, y);
//		}
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


bool CRoom_Container::userInput_mouseRelease(sf::Event* pEvent)
{
	return false;
}


bool CRoom_Container::isCollision(const sf::Rect<float>& rect, CRoom*& pRoom)
{
	sf::FloatRect roomRect;
	CRoom* pR;
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		pR = (*itr);
		roomRect = pR->getSprite()->getGlobalBounds();
		if (roomRect.intersects(rect))
		{
			pRoom = pR;
			return true;
		}
	}

	pRoom = NULL;
	return false;
}


bool CRoom_Container::canSpawnRoom_room(bool keyPressState, bool isMouse, sf::Event* pEvent)
{
	if (isMouse == true)
	{
		int x = pEvent->mouseButton.x;
		int y = pEvent->mouseButton.y;
		normalizeToGrid(&x, &y);

		if (keyPressState == true)
		{
			spawnRoom_room(x, y);
			return true;
		}
		else
		{

		}
	}
	else
	{
		if (keyPressState == true)
		{
		}
		else
		{

		}
	}

	return false;
}


bool CRoom_Container::canSpawnRoom_warehouse(bool keyPressState, bool isMouse, sf::Event* pEvent)
{
	if (isMouse == true)
	{
		int x = pEvent->mouseButton.x;
		int y = pEvent->mouseButton.y;
		normalizeToGrid(&x, &y);

		if (keyPressState == true && m_sRoomSpawnKeyStates.warehouse == true)
		{
			spawnRoom_warehouse(x, y);
			return true;
		}
		else if (keyPressState == false && m_sRoomSpawnKeyStates.warehouse == true)
		{

		}
	}
	else
	{
		if (keyPressState == true && pEvent->key.code == m_sRoomSpawnKeys.warehouse)
		{
			m_sRoomSpawnKeyStates.warehouse = true;
			return true;
		}
		else if (keyPressState == false && pEvent->key.code == m_sRoomSpawnKeys.warehouse)
		{
			m_sRoomSpawnKeyStates.warehouse = false;
			return true;
		}
	}

	return false;
}


bool CRoom_Container::canSpawnRoom_kitchen(bool keyPressState, bool isMouse, sf::Event* pEvent)
{
	if (isMouse == true)
	{
		int x = pEvent->mouseButton.x;
		int y = pEvent->mouseButton.y;
		normalizeToGrid(&x, &y);

		if (keyPressState == true && m_sRoomSpawnKeyStates.kitchen == true)
		{
			spawnRoom_kitchen(x, y);
			return true;
		}
		else if (keyPressState == false && m_sRoomSpawnKeyStates.kitchen == true)
		{

		}
	}
	else
	{
		if (keyPressState == true && pEvent->key.code == m_sRoomSpawnKeys.kitchen)
		{
			m_sRoomSpawnKeyStates.kitchen = true;
			return true;
		}
		else if (keyPressState == false && pEvent->key.code == m_sRoomSpawnKeys.kitchen)
		{
			m_sRoomSpawnKeyStates.kitchen = false;
			return true;
		}
	}

	return false;
}


void CRoom_Container::normalizeToGrid(int* x, int* y)
{
	// * use the grid function to translate
	// * x and y are now in grid coords
	m_pGrid->screenToGrid(x, y);

	// translate from GIRD space to SCREEN space
	sf::Vector2<int> gridSubSize = m_pGrid->getGridSubSize();
	(*x) = (*x) * gridSubSize.x;
	(*y) = (*y) * gridSubSize.y;
}


void CRoom_Container::spawnRoom_room(int x, int y)
{
	CRoom* pR = new CRoom(m_pWindow, m_pDebugTexture, sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);
}


void CRoom_Container::spawnRoom_warehouse(int x, int y)
{
	CRoom_warehouse* pR = new CRoom_warehouse(m_pWindow, m_pWarehouseTexture, sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.warehouse++;
}

void CRoom_Container::spawnRoom_kitchen(int x, int y)
{
	CRoom_kitchen* pR = new CRoom_kitchen(m_pWindow, m_pKitchenTexture, sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.kitchen++;
}


bool CRoom_Container::deleteRoom(int x, int y)
{
	sf::FloatRect rect;
	CRoom* pR;
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		pR = (*itr);
		rect = pR->getGlobalBounds();
		if (rect.contains(x, y))
		{
			delete pR;
			itr = m_rooms.erase(itr);

			return true;
		}
	}

	return false;
}


//void CRoom_Container::applyPhysics(CRoom* pRoom)
//{
//	sf::Time timer = pRoom->m_sPhysics.gravityTimer.getElapsedTime();
//	int elapsed = timer.asMilliseconds();
//	pRoom->m_sPhysics.velosity_y = (0.01) * (elapsed);
//}


void CRoom_Container::SNumRooms::nullAll()
{
	warehouse = 0;
	kitchen = 0;
}


void CRoom_Container::SRoomSpawnKeyStates::nullAll()
{
	warehouse = false;
	kitchen = false;
}
