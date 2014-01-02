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

	m_sRoomTextures.init_RoomTextures();

	m_sKeys.up 		= sf::Keyboard::Up;
	m_sKeys.down 	= sf::Keyboard::Down;
	m_sKeys.left 	= sf::Keyboard::Left;
	m_sKeys.right 	= sf::Keyboard::Right;

	setRoomKeybinds();

	m_sNumRooms.nullAll();
	m_sRoomSpawnKeyStates.nullAll();
}


void CRoom_Container::setRoomKeybinds()
{
	m_sRoomSpawnKeys.warehouse 			= sf::Keyboard::Num1;
	m_sRoomSpawnKeys.kitchen 			= sf::Keyboard::Num2;
	m_sRoomSpawnKeys.smithy 			= sf::Keyboard::Num3;
	m_sRoomSpawnKeys.powerPlant 		= sf::Keyboard::Num4;
	m_sRoomSpawnKeys.warSpawner			= sf::Keyboard::Num5;
	m_sRoomSpawnKeys.researchSpawner	= sf::Keyboard::Num6;
	m_sRoomSpawnKeys.supportSpawner		= sf::Keyboard::Num7;

}


void CRoom_Container::SRoomTextures::init_RoomTextures()
{
	debug = new CTexture("res/Rooms/room 1x1.png",
	                     sf::Vector2<int>(32, 32),
	                     sf::Vector2<int>(1, 1));

	warehouse = new CTexture("res/Rooms/warehouse.png",
	                         sf::Vector2<int>(32, 32),
	                         sf::Vector2<int>(1, 1));

	kitchen = new CTexture("res/Rooms/kitchen.png",
	                       sf::Vector2<int>(64, 32),
	                       sf::Vector2<int>(1, 1));

	smithy = new CTexture("res/Rooms/smithy.png",
	                      sf::Vector2<int>(32, 64),
	                      sf::Vector2<int>(1, 1));

	powerPlant = new CTexture("res/Rooms/powerPlant.png",
	                          sf::Vector2<int>(64, 64),
	                          sf::Vector2<int>(1, 1));

	warSpawner = new CTexture("res/Rooms/warSpawner.png",
	                          sf::Vector2<int>(32, 32),
	                          sf::Vector2<int>(1, 1));

	researchSpawner = new CTexture("res/Rooms/researchSpawner.png",
	                               sf::Vector2<int>(64, 32),
	                               sf::Vector2<int>(1, 1));

	supportSpawner = new CTexture("res/Rooms/supportSpawner.png",
	                              sf::Vector2<int>(32, 32),
	                              sf::Vector2<int>(1, 1));
}


void CRoom_Container::SRoomTextures::delete_RoomTextures()
{
	delete debug;
	debug = NULL;

	delete warehouse;
	warehouse = NULL;

	delete kitchen;
	kitchen = NULL;

	delete smithy;
	smithy = NULL;

	delete powerPlant;
	powerPlant = NULL;

	delete warSpawner;
	warSpawner = NULL;

	delete researchSpawner;
	researchSpawner = NULL;

	delete supportSpawner;
	supportSpawner = NULL;
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

	m_sRoomTextures.delete_RoomTextures();
}


const SNumRooms* CRoom_Container::getNumRooms() const
{
	return &m_sNumRooms;
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


void CRoom_Container::getRenderData(std::list<ARender*>* pList)
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
	// set generic (function wide) values
	m_sSpawnInfo.isMouse = false;
	m_sSpawnInfo.keyPressState = true;
	m_sSpawnInfo.pEvent = pEvent;

	if (roomSwitchboard() == true)
	{
		return true;
	}

//	if (canSpawnRoom_debug(true, false, pEvent))
//	{
//		return true;
//	}

	return false;
}


bool CRoom_Container::userInput_keyRelease(sf::Event* pEvent)
{
	// set generic (function wide) values
	m_sSpawnInfo.isMouse = false;
	m_sSpawnInfo.keyPressState = false;
	m_sSpawnInfo.pEvent = pEvent;

	if (roomSwitchboard() == true)
	{
		return true;
	}

//	if (canSpawnRoom_debug(false, false, pEvent))
//	{
//		return true;
//	}

	return false;
}


bool CRoom_Container::userInput_mousePress(sf::Event* pEvent)
{
	if (pEvent->mouseButton.button == sf::Mouse::Left)
	{
		// set generic (function wide) values
		m_sSpawnInfo.isMouse = true;
		m_sSpawnInfo.keyPressState = true;
		m_sSpawnInfo.pEvent = pEvent;

		if (roomSwitchboard() == true)
		{
			return true;
		}

//		if (canSpawnRoom_debug(true, true, pEvent))
//		{
//			return true;
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


bool CRoom_Container::roomSwitchboard()
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


bool CRoom_Container::canSpawnRoom()
{
	// mouse click (keyPressState describes whether or not it is on or off)
	if (m_sSpawnInfo.isMouse == true)
	{
		int x = m_sSpawnInfo.pEvent->mouseButton.x;
		int y = m_sSpawnInfo.pEvent->mouseButton.y;

		// click needs to be not in a room, and above a
		//	room that is on the same x coords to pass
		if (canSpawnAtPos(x, y) == false)
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
			(this->*m_sSpawnInfo.spawnFunction)(x, y);

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


void CRoom_Container::setInfo_warehouse()
{
	m_sSpawnInfo.spawnKey = &m_sRoomSpawnKeys.warehouse;
	m_sSpawnInfo.spawnKeyState = &m_sRoomSpawnKeyStates.warehouse;
	m_sSpawnInfo.spawnFunction = &CRoom_Container::spawnRoom_warehouse;
}


void CRoom_Container::setInfo_kitchen()
{
	m_sSpawnInfo.spawnKey = &m_sRoomSpawnKeys.kitchen;
	m_sSpawnInfo.spawnKeyState = &m_sRoomSpawnKeyStates.kitchen;
	m_sSpawnInfo.spawnFunction = &CRoom_Container::spawnRoom_kitchen;
}


void CRoom_Container::setInfo_smithy()
{
	m_sSpawnInfo.spawnKey = &m_sRoomSpawnKeys.smithy;
	m_sSpawnInfo.spawnKeyState = &m_sRoomSpawnKeyStates.smithy;
	m_sSpawnInfo.spawnFunction = &CRoom_Container::spawnRoom_smithy;
}


void CRoom_Container::setInfo_powerPlant()
{
	m_sSpawnInfo.spawnKey = &m_sRoomSpawnKeys.powerPlant;
	m_sSpawnInfo.spawnKeyState = &m_sRoomSpawnKeyStates.powerPlant;
	m_sSpawnInfo.spawnFunction = &CRoom_Container::spawnRoom_powerPlant;
}


void CRoom_Container::setInfo_warSpawner()
{
	m_sSpawnInfo.spawnKey = &m_sRoomSpawnKeys.warSpawner;
	m_sSpawnInfo.spawnKeyState = &m_sRoomSpawnKeyStates.warSpawner;
	m_sSpawnInfo.spawnFunction = &CRoom_Container::spawnRoom_warSpawner;
}


void CRoom_Container::setInfo_researchSpawner()
{
	m_sSpawnInfo.spawnKey = &m_sRoomSpawnKeys.researchSpawner;
	m_sSpawnInfo.spawnKeyState = &m_sRoomSpawnKeyStates.researchSpawner;
	m_sSpawnInfo.spawnFunction = &CRoom_Container::spawnRoom_researchSpawner;
}


void CRoom_Container::setInfo_supportSpawner()
{
	m_sSpawnInfo.spawnKey = &m_sRoomSpawnKeys.supportSpawner;
	m_sSpawnInfo.spawnKeyState = &m_sRoomSpawnKeyStates.supportSpawner;
	m_sSpawnInfo.spawnFunction = &CRoom_Container::spawnRoom_supportSpawner;
}


bool CRoom_Container::canSpawnRoom_debug(bool keyPressState, bool isMouse, sf::Event* pEvent)
{
	// mouse click (keyPressState describes whether or not it is on or off)
	if (isMouse == true)
	{
		int x = pEvent->mouseButton.x;
		int y = pEvent->mouseButton.y;

		// click needs to be not in a room, and above a
		//	room that is on the same x coords to pass
		if (canSpawnAtPos(x, y) == false)
		{
			return false;
		}

		// prep the x,y of the mouse for room spawn
		normalizeToGrid(&x, &y);

		// mouse was pressed
		if (keyPressState == true)
		{
			spawnRoom_debug(x, y);
			return true;
		}
		else // Mouse released
		{

		}
	}
	else // key click
	{
		// key pressed
		if (keyPressState == true)
		{
		}
		else // key released
		{

		}
	}

	// Criterion not met to spawn or update the spawn conditions for a room
	return false;
}


bool CRoom_Container::canSpawnAtPos(int x, int y)
{
	sf::FloatRect rect;
	CRoom* pR;

	// defined region of space for checking (of the current room)
	int Rx_min = 0;
	int Rx_max = 0;
	int Ry = 0;

	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		pR = (*itr);
		rect = pR->getGlobalBounds();

		Rx_min = rect.left;
		Rx_max = rect.left + rect.width;
		Ry = rect.top;

		// check to see if mouse is within a room
		if (rect.contains(x, y))
		{
			return false;
		}

		// check to see if mouse is above a room that is below the mouse
		if (y >= Ry && (Rx_min <= x && x <= Rx_max))
		{
			return false;
		}
	}

	return true;
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


void CRoom_Container::spawnRoom_debug(int x, int y)
{
	CRoom* pR = new CRoom(m_pWindow,
	                      m_sRoomTextures.debug,
	                      sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);
}


void CRoom_Container::spawnRoom_warehouse(int x, int y)
{
	CRoom_warehouse* pR = new CRoom_warehouse(m_pWindow,
	        m_sRoomTextures.warehouse,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.warehouse++;
}


void CRoom_Container::spawnRoom_kitchen(int x, int y)
{
	CRoom_kitchen* pR = new CRoom_kitchen(m_pWindow,
	                                      m_sRoomTextures.kitchen,
	                                      sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.kitchen++;
}


void CRoom_Container::spawnRoom_smithy(int x, int y)
{
	CRoom_smithy* pR = new CRoom_smithy(m_pWindow,
	                                    m_sRoomTextures.smithy,
	                                    sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.smithy++;
}


void CRoom_Container::spawnRoom_powerPlant(int x, int y)
{
	CRoom_powerPlant* pR = new CRoom_powerPlant(m_pWindow,
	        m_sRoomTextures.powerPlant,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.powerPlant++;
}


void CRoom_Container::spawnRoom_warSpawner(int x, int y)
{
	CRoom_warSpawner* pR = new CRoom_warSpawner(m_pWindow,
	        m_sRoomTextures.warSpawner,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.warSpawner++;
}


void CRoom_Container::spawnRoom_researchSpawner(int x, int y)
{
	CRoom_researchSpawner* pR = new CRoom_researchSpawner(m_pWindow,
	        m_sRoomTextures.researchSpawner,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.researchSpawner++;
}


void CRoom_Container::spawnRoom_supportSpawner(int x, int y)
{
	CRoom_supportSpawner* pR = new CRoom_supportSpawner(m_pWindow,
	        m_sRoomTextures.supportSpawner,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_rooms.push_back(pR);

	m_sNumRooms.supportSpawner++;
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


void SNumRooms::nullAll()
{
	int val = 0;

	warehouse 			= val;
	kitchen 			= val;
	smithy 				= val;
	powerPlant 			= val;
	warSpawner 			= val;
	researchSpawner 	= val;
	supportSpawner		= val;
}


void CRoom_Container::SRoomSpawnKeyStates::nullAll()
{
	bool val = false;

	warehouse 			= val;
	kitchen 			= val;
	smithy 				= val;
	powerPlant 			= val;
	warSpawner 			= val;
	researchSpawner 	= val;
	supportSpawner		= val;
}

