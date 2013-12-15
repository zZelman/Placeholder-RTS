/*
 * CPhysicsEngine.h
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#ifndef CPHYSICSENGINE_H_
#define CPHYSICSENGINE_H_

#include "CQuadTree.h"
#include "CTile_Container.h"
#include "CRoom_Container.h"
#include "CUnit_Container.h"

#include "IUpdateable.h"

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
};

#endif /* CPHYSICSENGINE_H_ */
