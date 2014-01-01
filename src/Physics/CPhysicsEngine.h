/*
 * CPhysicsEngine.h
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#ifndef CPHYSICSENGINE_H_
#define CPHYSICSENGINE_H_

#include "CQuadTree.h"
#include "../Tiles/CTile_Container.h"
#include "../Rooms/CRoom_Container.h"
#include "../Units/CUnit_Container.h"

#include "../Interfaces/IUpdateable.h"
#include "../Physics/DPhysics.h"

class CPhysicsEngine : public IUpdateable
{
public:
	CPhysicsEngine(CTile_Container* pTile_Container,
	               CRoom_Container* pRoom_Container,
	               CUnit_Container* pUnit_Container);
	~CPhysicsEngine();

	// * updates all of the tiles, rooms, and units
	// * ONLY DOES POSITION UPDATES no state/image/other types of updating things
	void update();

private:
	// main data structure/algorithm used to reduce collision detection
	CQuadTree* m_pQuadTree;

	// pointer to the object maintainers
	CTile_Container* m_pTile_Container;
	CRoom_Container* m_pRoom_Container;
	CUnit_Container* m_pUnit_Container;

	// 2 different collision detection algorithums
	void quadTree_collision(); // quad tree data structure to reduce worst case
	void n2_collision(); // fast and easy O(n^2) collision detection

	// * internal collision resolution methods
	// * a potential collision has been found between these two given pointers by
	//		the calling function, it is resolved here
	// * naming scheme is in "this collides with that" (room -> tile == room_tile)
	// * returns true if can step normally, false if collision was resolved
	bool room_tile(CRoom* pRoom, CTile* pTile);
	bool room_room(CRoom* pFrom, CRoom* pTo);
	bool room_unit(CRoom* pRoom, CUnit* pUnit);
	bool unit_tile(CUnit* pUnit, CTile* pTile);
	bool unit_room(CUnit* pUnit, CRoom* pRoom);

	// * applies physics to the vertical movement of the given object
	// * contains the mathematical expression to determine velocity
	void applyPhysics(DPhysics* pObject);

	// calls update normally on all in the list
	void applyStepNormally(std::list<DPhysics*>* pList);
};

#endif /* CPHYSICSENGINE_H_ */
