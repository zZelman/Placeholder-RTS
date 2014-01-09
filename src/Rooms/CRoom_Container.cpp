/*
 * CRoom_Container.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: zZelman
 */

#include "CRoom_Container.h"

CRoom_Container::CRoom_Container(CTile_Container* pGrid)
{
	m_pGrid = pGrid;

	m_sNumRooms.nullAll();
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

}


struct SNumRooms* CRoom_Container::getNumRooms()
{
	return &m_sNumRooms;
}


std::list<CRoom*>* CRoom_Container::getRooms()
{
	return &m_rooms;
}


void CRoom_Container::update()
{
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		CRoom* pR = (*itr);

		pR->update();
	}
}


void CRoom_Container::getCollisiondata(std::list<ARenderable*>* pList)
{
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		pList->push_front((*itr));
	}
}


void CRoom_Container::getRenderData(std::list<ARenderable*>* pList)
{
	for (std::list<CRoom*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		pList->push_front((*itr));
	}
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
