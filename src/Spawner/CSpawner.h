/*
 * CSpawner.h
 *
 *  Created on: Jan 3, 2014
 *      Author: zZelman
 */

#ifndef CSPAWNER_H_
#define CSPAWNER_H_

#include "../Graphics/CTexture.h"
#include "../Templates/SRoomBookkeeping.h"
#include "../Rooms/CRoom_Container.h"


/**
 * Runtime spawns all Rooms/Units in the game
 *
 * Keeps 'singleton' information for the rooms/units
 * (ex: 1 texture used by many rooms)
 */
class CSpawner
{
public:
	CSpawner(CRoom_Container* pRoom_Container);
	~CSpawner();

	// creates a new room
	void spawnRoom_warehouse(int x, int y);
	void spawnRoom_kitchen(int x, int y);
	void spawnRoom_smithy(int x, int y);
	void spawnRoom_powerPlant(int x, int y);
	void spawnRoom_warSpawner(int x, int y);
	void spawnRoom_researchSpawner(int x, int y);
	void spawnRoom_supportSpawner(int x, int y);

private:
	/**
	 * Textures used by all same-type room objects
	 *
	 * Single initialization of these textures means that
	 * multiple same-type rooms will reference the same texture
	 */
	SRoomBookkeeping<CTexture*> m_room_textures;

	/**
	 * Pointer to within CRoom_Container object to the
	 * number room bookkeeping struct.
	 */
	struct SNumRooms* m_spNumRooms;

	/**
	 * Pointer to the data structure that holds the actual rooms.
	 */
	std::list<CRoom*>* m_pRooms;

	/**
	 * Utility function to create the textures needed to spawn each
	 * room type
	 */
	void init_roomTextures();


};

#endif /* CSPAWNER_H_ */
