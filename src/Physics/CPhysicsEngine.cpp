/*
 * CPhysicsEngine.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#include "CPhysicsEngine.h"

CPhysicsEngine::CPhysicsEngine(CTile_Container* pTile_Container,
                               CRoom_Container* pRoom_Container,
                               CUnit_Container* pUnit_Container)
{
	m_pTile_Container = pTile_Container;
	m_pRoom_Container = pRoom_Container;
	m_pUnit_Container = pUnit_Container;

	// work toward finding the whole world width/height
	sf::Vector2<int> gridSize = m_pTile_Container->getGridSize();
	sf::Vector2<int> gridSubSize = m_pTile_Container->getGridSubSize();

	int width = gridSize.x * gridSubSize.x;
	int height = gridSize.y * gridSubSize.y;

	sf::IntRect worldSpace(0, 0, width, height);

	m_pQuadTree = new CQuadTree(0, &worldSpace);
}


CPhysicsEngine::~CPhysicsEngine()
{
	delete m_pQuadTree;
}


void CPhysicsEngine::update()
{
//	 choice of collision detection
//	quadTree_collision();
	n2_collision();
}


void CPhysicsEngine::quadTree_collision()
{
	// retrieve all collidable objects
	std::list<ARender*> totalObjects;
	m_pTile_Container->getCollisiondata(&totalObjects);
	m_pRoom_Container->getCollisiondata(&totalObjects);
	m_pUnit_Container->getCollisiondata(&totalObjects);

	// add all objects to the quad tree
	m_pQuadTree->clear();
	for (std::list<ARender*>::iterator itr = totalObjects.begin();
	        itr != totalObjects.end();
	        ++itr)
	{
		m_pQuadTree->insert(*itr);
	}


	//------------------------------------
	// Collision detection happens (below)
	//------------------------------------


	// casting pointers to try and find which object in "totalObjects" (inAll) and
	//		"returnedObjects" (inCollis) are
	// they are allocated here because it is more efficient
	CRoom* pRoom_inAll = NULL;
	CUnit* pUnit_inAll = NULL;
	CTile* pTile_inCollis = NULL;
	CRoom* pRoom_inCollis = NULL;
	CUnit* pUnit_inCollis = NULL;

	// bools to control wheather or not the obj has been touched
	//	by the collision resolution methods
	bool canStepNormally_room = true;
	bool canStepNormally_unit = true;

	// objects that the current object could collide with
	std::list<ARender*> returnedObjects;

	// list of things that will not collide with anything on their next step
	//	(can update normally)
	std::list<DPhysics*> normals;

	for (std::list<ARender*>::iterator all_itr = totalObjects.begin();
	        all_itr != totalObjects.end();
	        ++all_itr)
	{
		// the type that *all_itr is (the current pointer within returnedObjects
		//		will be non NULL, the other 2 will be NULL
		pRoom_inAll = dynamic_cast<CRoom*>(*all_itr);
		pUnit_inAll = dynamic_cast<CUnit*>(*all_itr);

		// apply physics to the velocities of the object
		if (pRoom_inAll != NULL)
		{
			applyPhysics(pRoom_inAll);
		}
		else if (pUnit_inAll != NULL)
		{
			applyPhysics(pUnit_inAll);
		}

		canStepNormally_room = true;
		canStepNormally_unit = true;

		// "returnedObjects" now represents all of the objects that could potentially
		//		collide with the current ARender*
		returnedObjects.clear();
		m_pQuadTree->retrieve(&returnedObjects, *all_itr);

		// resolve collision detection
		for (std::list<ARender*>::iterator collision_itr = returnedObjects.begin();
		        collision_itr != returnedObjects.end();
		        ++collision_itr)
		{
			// use casting to see which type the returned object is
			//		(returns NULL if cast was unsuccessful)
			pTile_inCollis = dynamic_cast<CTile*>(*collision_itr);
			pRoom_inCollis = dynamic_cast<CRoom*>(*collision_itr);
			pUnit_inCollis = dynamic_cast<CUnit*>(*collision_itr);

			// room -> tile potential collision
			if (pRoom_inAll != NULL && pTile_inCollis != NULL)
			{
				if (room_tile(pRoom_inAll, pTile_inCollis) == false)
				{
					canStepNormally_room = false;
				}
			}

			// room -> room potential collision
			else if (pRoom_inAll != NULL && pRoom_inCollis != NULL)
			{
				if (room_room(pRoom_inAll, pRoom_inCollis) == false)
				{
					canStepNormally_room = false;
				}
			}

			// room -> unit potential collision
			else if (pRoom_inAll != NULL && pUnit_inCollis != NULL)
			{

			}

			// unit -> tile potential collision
			else if (pUnit_inAll != NULL && pTile_inCollis != NULL)
			{

			}

			// unit -> room potential collision
			else if (pUnit_inAll != NULL && pRoom_inCollis != NULL)
			{

			}
		}

		// If you are working with [room/unit] and it has not been touched by
		//	the collision resolution methods, put it in the linked list that will
		//	be stepped normally at the end of this function
		if (pRoom_inAll != NULL && canStepNormally_room == true)
		{
			normals.push_front(pRoom_inAll);
		}
		if (pUnit_inAll != NULL && canStepNormally_unit == true)
		{
			normals.push_front(pUnit_inAll);
		}
	}

	// all of the things that are now in "normals" are guaranteed not to hit
	//	anything in their next step, so they can step normally
	applyStepNormally(&normals);
}


void CPhysicsEngine::n2_collision()
{
	std::list<ARender*> rooms;
	m_pRoom_Container->getCollisiondata(&rooms);

	std::list<ARender*> tiles;
	m_pTile_Container->getCollisiondata(&tiles);

	CRoom* pRoom_from = NULL;
	CRoom* pRoom_to = NULL;
	CTile* pTile = NULL;
	bool canStepNormally = true;
	std::list<DPhysics*> normals; // objects that can step normally
	for (std::list<ARender*>::iterator itr_rooms_from = rooms.begin();
	        itr_rooms_from != rooms.end();
	        ++itr_rooms_from)
	{
		pRoom_from = dynamic_cast<CRoom*>(*itr_rooms_from);
		applyPhysics(pRoom_from);

		canStepNormally = true;

		//
		// room -> tile collision detection
		//
		for (std::list<ARender*>::iterator itr_tiles = tiles.begin();
		        itr_tiles != tiles.end();
		        ++itr_tiles)
		{
			pTile = dynamic_cast<CTile*>(*itr_tiles);

			// returns false if the collision was resolved
			if (room_tile(pRoom_from, pTile) == false)
			{
				canStepNormally = false;
				break;
			}
		}

		//
		// room -> room collision detection
		//
		for (std::list<ARender*>::iterator itr_rooms_to = rooms.begin();
		        itr_rooms_to != rooms.end();
		        ++itr_rooms_to)
		{
			pRoom_to = dynamic_cast<CRoom*>(*itr_rooms_to);

			// returns false if the collision was resolved
			if (room_room(pRoom_from, pRoom_to) == false)
			{
				canStepNormally = false;
				break;
			}
		}

		if (canStepNormally == true)
		{
			normals.push_front(pRoom_from);
		}
	}

	applyStepNormally(&normals);
}


bool CPhysicsEngine::room_tile(CRoom* pRoom, CTile* pTile)
{
	// pull required data from pRoom
	sf::FloatRect futureRect = pRoom->getGlobalBounds();

	// test the future
	futureRect.top += pRoom->m_sPhysics.velosity_y;

	sf::FloatRect tileRect = pTile->getGlobalBounds();

	if (futureRect.intersects(tileRect))
	{
		int newY = tileRect.top - futureRect.height;
		pRoom->setPosition(futureRect.left, newY);

		pRoom->m_sPhysics.gravityTimer.restart();

		pRoom->m_sPhysics.isFalling = false;

		return false;
	}

	return true;
}


bool CPhysicsEngine::room_room(CRoom* pFrom, CRoom* pTo)
{
	if (pFrom != pTo)
	{
		// pull required data
		sf::FloatRect fromRect = pFrom->getGlobalBounds();
		sf::FloatRect toRect = pTo->getGlobalBounds();

		// test the future
		fromRect.top += pFrom->m_sPhysics.velosity_y;

		if (fromRect.intersects(toRect))
		{
			int newY = toRect.top - fromRect.height;
			pFrom->setPosition(fromRect.left, newY);

			pFrom->m_sPhysics.gravityTimer.restart();

			pFrom->m_sPhysics.isFalling = false;

			return false;
		}
	}

	return true;
}


bool CPhysicsEngine::room_unit(CRoom* pRoom, CUnit* pUnit)
{
	return true;
}


bool CPhysicsEngine::unit_tile(CUnit* pUnit, CTile* pTile)
{
	return true;
}


bool CPhysicsEngine::unit_room(CUnit* pUnit, CRoom* pRoom)
{
	return true;
}

void CPhysicsEngine::applyPhysics(DPhysics* pObject)
{
	sf::Time timer = pObject->m_sPhysics.gravityTimer.getElapsedTime();
	int elapsed = timer.asMilliseconds();
	pObject->m_sPhysics.velosity_y = (0.01) * (elapsed);
}


void CPhysicsEngine::applyStepNormally(std::list<DPhysics*>* pList)
{
	for (std::list<DPhysics*>::iterator itr = pList->begin();
	        itr != pList->end();
	        ++itr)
	{
		(*itr)->stepNormally();
	}
}
