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

	// Collision detection happens here
	std::list<ARender*> returnedObjects;
	for (std::list<ARender*>::iterator all_itr = totalObjects.begin();
	        all_itr != totalObjects.end();
	        ++all_itr)
	{
		returnedObjects.clear();

		// "returnedObjects" now represents all of the objects that could potentially
		//		collide with the current ARender*
		m_pQuadTree->retrieve(&returnedObjects, *all_itr);

		for (std::list<ARender*>::iterator collision_itr = returnedObjects.begin();
		        collision_itr != returnedObjects.end();
		        ++collision_itr)
		{
			std::cout << "collision" << std::endl;
		}
		std::cout << std::endl;
	}
}
