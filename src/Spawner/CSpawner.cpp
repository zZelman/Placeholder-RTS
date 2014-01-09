/*
 * CSpawner.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: zZelman
 */

#include "CSpawner.h"
#include "../Templates/SRoomBookkeeping.h"

CSpawner::CSpawner(CRoom_Container* pRoom_Container)
{
	m_spNumRooms = pRoom_Container->getNumRooms();
	m_pRooms = pRoom_Container->getRooms();

	init_roomTextures();

}

CSpawner::~CSpawner()
{
	m_room_textures.data_delete();
}

void CSpawner::init_roomTextures()
{
	m_room_textures.debug = new CTexture("res/Rooms/room 1x1.png",
	                                     sf::Vector2<int>(32, 32),
	                                     sf::Vector2<int>(1, 1));

	m_room_textures.warehouse = new CTexture("res/Rooms/warehouse.png",
	        sf::Vector2<int>(32, 32),
	        sf::Vector2<int>(1, 1));

	m_room_textures.kitchen = new CTexture("res/Rooms/kitchen.png",
	                                       sf::Vector2<int>(64, 32),
	                                       sf::Vector2<int>(1, 1));

	m_room_textures.smithy = new CTexture("res/Rooms/smithy.png",
	                                      sf::Vector2<int>(32, 64),
	                                      sf::Vector2<int>(1, 1));

	m_room_textures.powerPlant = new CTexture("res/Rooms/powerPlant.png",
	        sf::Vector2<int>(64, 64),
	        sf::Vector2<int>(1, 1));

	m_room_textures.warSpawner = new CTexture("res/Rooms/warSpawner.png",
	        sf::Vector2<int>(32, 32),
	        sf::Vector2<int>(1, 1));

	m_room_textures.researchSpawner = new CTexture("res/Rooms/researchSpawner.png",
	        sf::Vector2<int>(64, 32),
	        sf::Vector2<int>(1, 1));

	m_room_textures.supportSpawner = new CTexture("res/Rooms/supportSpawner.png",
	        sf::Vector2<int>(32, 32),
	        sf::Vector2<int>(1, 1));
}


void CSpawner::spawnRoom_warehouse(int x, int y)
{
	CRoom_warehouse* pR = new CRoom_warehouse(m_room_textures.warehouse,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_pRooms->push_back(pR);

	m_spNumRooms->warehouse++;
}


void CSpawner::spawnRoom_kitchen(int x, int y)
{
	CRoom_kitchen* pR = new CRoom_kitchen(m_room_textures.kitchen,
	                                      sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_pRooms->push_back(pR);

	m_spNumRooms->kitchen++;
}


void CSpawner::spawnRoom_smithy(int x, int y)
{
	CRoom_smithy* pR = new CRoom_smithy(m_room_textures.smithy,
	                                    sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_pRooms->push_back(pR);

	m_spNumRooms->smithy++;
}


void CSpawner::spawnRoom_powerPlant(int x, int y)
{
	CRoom_powerPlant* pR = new CRoom_powerPlant(m_room_textures.powerPlant,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_pRooms->push_back(pR);

	m_spNumRooms->powerPlant++;
}


void CSpawner::spawnRoom_warSpawner(int x, int y)
{
	CRoom_warSpawner* pR = new CRoom_warSpawner(m_room_textures.warSpawner,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_pRooms->push_back(pR);

	m_spNumRooms->warSpawner++;
}


void CSpawner::spawnRoom_researchSpawner(int x, int y)
{
	CRoom_researchSpawner* pR = new CRoom_researchSpawner(m_room_textures.researchSpawner,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_pRooms->push_back(pR);

	m_spNumRooms->researchSpawner++;
}


void CSpawner::spawnRoom_supportSpawner(int x, int y)
{
	CRoom_supportSpawner* pR = new CRoom_supportSpawner(m_room_textures.supportSpawner,
	        sf::Vector2<int>(1, 1));
	pR->setPosition(x, y);
	m_pRooms->push_back(pR);

	m_spNumRooms->supportSpawner++;
}

