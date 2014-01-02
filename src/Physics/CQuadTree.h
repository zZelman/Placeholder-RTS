/*
 * CQuadTree.h
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#ifndef CQUADTREE_H_
#define CQUADTREE_H_

#include "../include_sfml.h"
#include "../Abstracts/ARender.h"

#include <vector>
#include <list>

// algorithum recieved from (1 url):
// http://gamedevelopment.tutsplus.com/tutorials/
//		quick-tip-use-quadtrees-to-detect-likely-
//		collisions-in-2d-space--gamedev-374


// NOTATION of sub-trees
//
//    II    |    I
//--------------------
//    III   |    IV


// used to note that the requested object location is not within this specific node,
//		rather, it is in the parent of this node
#define IN_PARENT -1

class CQuadTree
{
public:
	CQuadTree(int level, sf::IntRect* bounds);
	~CQuadTree();

	// * Recursively removes all objects from all nodes
	// * remember that the ARender* objects are NOT created here,
	// 		so they are NOT "delete"ed here, they are maintained within their
	//		respective container.
	// * the CQuadTree's within m_nodes ARE delete'ed here because they were
	//		new'ed here
	void clear();

	// * Insert the object into the quadtree
	// * if node exceeds its compacity, it will be split and all objects will be
	//		distributed into their respective sub-nodes
	void insert(ARenderable* pObject);

	// * returns all objects in all nodes that the given pObject could potentially collide with
	// * this is the method that helps reduce the number of pairs to check collision against
	void retrieve(std::list<ARenderable*>* returnedObjects, ARenderable* pObject);


private:
	// maximum number of objects within one QuadTree
	static const int MAX_OBJECTS = 10;

	// Maximum number of sub-devides to reach the bottom of the quad-tree
	static const int MAX_LEVELS = 5;

	// the level of this current QuadTree
	int m_level;

	// Objects within this QuadTree
	std::vector<ARenderable*> m_objects;

	// Bounds of this quad tree that all m_objects are within
	sf::IntRect m_bounds;

	// a fixed size array of pointers to the sub-QuadTrees within this QuadTree node
	CQuadTree* m_nodes[4];

	// * NULLs the pointers within m_nodes
	// * DOES NOT DELETE
	void nullAll();

	// * this function splits the node into four subnodes by dividing the node into
	//		4 equal parts and initializing the four sub nodes with new bounds
	// * does NOT move this node's objects into the sub nodes
	void split();

	// * helper function
	// * determines where an object belongs in the quadtree by determining which
	//		node the object can fit into
	// * returns -1 if the given object cant fit into any of the sub-nodes of
	//		this quadtree, so it must fit into the parent of this quadtree
	int getIndex(ARenderable* pObject);
};

#endif /* CQUADTREE_H_ */
