/*
 * CRoom_Container.h
 *
 *  Created on: Dec 10, 2013
 *      Author: zZelman
 */

#ifndef CROOM_CONTAINER_H_
#define CROOM_CONTAINER_H_

#include "../Interfaces/IUpdateable.h"
#include "../Interfaces/IGetCollisionData.h"
#include "../Interfaces/IGetRenderData.h"

#include "../Abstracts/AUserInput.h"

#include "../include_sfml.h"
#include "include_rooms.h"

#include "../Tiles/CTile_Container.h"

#include <list>


struct SNumRooms
{
	int warehouse;
	int kitchen;
	int smithy;
	int powerPlant;
	int warSpawner;
	int researchSpawner;
	int supportSpawner;

	void nullAll();
};



class CRoom_Container: public IUpdateable, public IGetRenderData, public IGetCollisionData
{
public:
	CRoom_Container(CTile_Container* pGrid);
	~CRoom_Container();

	struct SNumRooms* getNumRooms();
	std::list<CRoom*>* getRooms();

	void update();

	void getCollisiondata(std::list<ARenderable*>* pList);
	void getRenderData(std::list<ARenderable*>* pList);

	bool isCollision(const sf::Rect<float>& rect, CRoom*& pRoom);

	// * checks whether or not ANY room can be spawned @ the current mouse x,y
	// * x,y have NOT been normalized to the grid (normalizeToGrid is not used)
	// * returns false if cannot spawn
	// * current spawn conditions:
	//		- not within a current room
	//		- not below a current room (must fall onto the top of the building)
	bool canSpawnAtPos(int x, int y);

	/**
	 * DEBUG.
	 *
	 * Deletes a room at mouse coords (x,y) if there exists one
	 */
	bool deleteRoom(int x, int y);


private:
	CTile_Container* m_pGrid;

	// container for all units
	std::list<CRoom*> m_rooms;

	struct SNumRooms m_sNumRooms;

};

#endif /* CROOM_CONTAINER_H_ */
