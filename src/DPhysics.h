/*
 * DPhysics.h
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#ifndef DPHYSICS_H_
#define DPHYSICS_H_

#include "include_sfml.h"

class DPhysics
{
public:
	DPhysics();
	~DPhysics();

	// physics data
	struct SPhysics
	{
		sf::Clock gravityTimer; // used in parabolic curve modeling
		int velosity_x;
		int velosity_y;

		bool isFalling;

		void nullAll();
	} m_sPhysics;
};

#endif /* DPHYSICS_H_ */
