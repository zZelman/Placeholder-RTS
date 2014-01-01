/*
 * CRoom_supportSpawner.h
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#ifndef CROOM_SUPPORTSPAWNER_H_
#define CROOM_SUPPORTSPAWNER_H_

#include "CRoom.h"

class CRoom_supportSpawner: public CRoom
{
public:
	CRoom_supportSpawner(sf::RenderWindow* pWindow,
	                     CTexture* pTexture,
	                     const sf::Vector2<int>& currSub);
	~CRoom_supportSpawner();

	void update();
};

#endif /* CROOM_SUPPORTSPAWNER_H_ */
