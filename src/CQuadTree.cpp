/*
 * CQuadTree.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#include "CQuadTree.h"
#include "ARender.h"

CQuadTree::CQuadTree(int level, sf::IntRect* bounds)
{
	m_level = level;

	m_bounds.left 		= bounds->left;
	m_bounds.top 		= bounds->top;
	m_bounds.width 		= bounds->width;
	m_bounds.height 	= bounds->height;

	nullAll();

	// preemptively re-size the objects vector to
	//		reduce overhead at the cost of memory
	// MAX_OBJECTS + 1 because you add to the m_objects before
	//		checking if it is > MAX_OBJECTS, so +1 to prevent
	//		a re-allocation when you are at MAX_OBJECTS+1
//	m_objects.resize(MAX_OBJECTS + 1, NULL);
}


CQuadTree::~CQuadTree()
{
	clear();
}


void CQuadTree::nullAll()
{
	m_nodes[0] = NULL;
	m_nodes[1] = NULL;
	m_nodes[2] = NULL;
	m_nodes[3] = NULL;
}


void CQuadTree::clear()
{
	// remove pointers from this variable field
	m_objects.clear();

	// Recursively call clear on all sub quad trees that exist
	for (int i = 0; i < 4; ++i)
	{
		if (m_nodes[i] != NULL)
		{
			m_nodes[i]->clear();

			// because all sub-QuadTree's are new'ed here, they
			//	must be delete here aswell
			delete m_nodes[i];
			m_nodes[i] = NULL;
		}
	}
}


void CQuadTree::insert(ARender* pObject)
{
	if (m_nodes[0] != NULL)
	{
		int index = getIndex(pObject);

		if (index != IN_PARENT)
		{
			m_nodes[index]->insert(pObject);
			return;
		}
	}

	m_objects.push_back(pObject);

	if (m_objects.size() > MAX_OBJECTS && m_level < MAX_LEVELS)
	{
		if (m_nodes[0] == NULL)
		{
			split();
		}

		unsigned int i = 0;
		while (i < m_objects.size())
		{
			ARender* pObjIndex = m_objects.at(i);
			int index = getIndex(pObjIndex);
			if (index != IN_PARENT)
			{
				m_nodes[index]->insert(pObjIndex);
				m_objects.erase(m_objects.begin() + i);
			}
			else
			{
				++i;
			}
		}
	}
}


void CQuadTree::retrieve(std::list<ARender*>* returnedObjects,
                         ARender* pObject)
{
	int index = getIndex(pObject);
	if (index != IN_PARENT && m_nodes[0] != NULL)
	{
		m_nodes[index]->retrieve(returnedObjects, pObject);
	}

	for (unsigned int i = 0; i < m_objects.size(); ++i)
	{
		returnedObjects->push_front(m_objects.at(i));
	}
}


void CQuadTree::split()
{
	// find sub image dimensions
	int subWidth 	= m_bounds.width / 2;
	int subHeight 	= m_bounds.height / 2;
	int x 			= m_bounds.left;
	int y 			= m_bounds.top;

	// NOTATION of sub-trees
	//
	//    II    |    I
	//--------------------
	//    III   |    IV

	// init 4 new sub quadTrees
	sf::IntRect I = sf::IntRect(x + subWidth, y, subWidth, subHeight);
	sf::IntRect II = sf::IntRect(x, y, subWidth, subHeight);
	sf::IntRect III = sf::IntRect(x, y + subHeight, subWidth, subHeight);
	sf::IntRect IV = sf::IntRect(x + subWidth, y + subHeight, subWidth, subHeight);

	m_nodes[0] = new CQuadTree(m_level + 1, &I);
	m_nodes[1] = new CQuadTree(m_level + 1, &II);
	m_nodes[2] = new CQuadTree(m_level + 1, &III);
	m_nodes[3] = new CQuadTree(m_level + 1, &IV);

	m_nodes[0]->nullAll();
	m_nodes[1]->nullAll();
	m_nodes[2]->nullAll();
	m_nodes[3]->nullAll();
}


int CQuadTree::getIndex(ARender* pObject)
{
	int index = IN_PARENT;
	double verticalMidpoint = m_bounds.left + (m_bounds.width / 2);
	double horizontalMidpoint = m_bounds.top + (m_bounds.height / 2);

	sf::FloatRect rect = pObject->getSprite_API()->getGlobalBounds();

	// pObject can completely fit within the top quadrants
	bool topQuadrant = (rect.top < horizontalMidpoint) && (rect.top +  rect.height < horizontalMidpoint);
	// pObject can completely fit within the bottom quadrents
	bool bottomQuadrant = rect.top > horizontalMidpoint;

	// pObject can completely fit within the left quadrants
	if ((rect.left < verticalMidpoint) && (rect.left + rect.width < verticalMidpoint))
	{
		if (topQuadrant)
		{
			index = 1;
		}
		else if (bottomQuadrant)
		{
			index = 2;
		}
	}
	// pObject can completely fit within the right quadrants
	else if (rect.left > verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 0;
		}
		else if (bottomQuadrant)
		{
			index = 3;
		}
	}

	return index;
}
