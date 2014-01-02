/*
 * CRoom_war.h
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#ifndef CROOM_WARSPAWNER_H_
#define CROOM_WARSPAWNER_H_

#include "CRoom.h"

class CRoom_warSpawner: public CRoom
{
public:
	CRoom_warSpawner(CTexture* pTexture,
	                 const sf::Vector2<int>& currSub);
	~CRoom_warSpawner();

	void update();
};

#endif /* CROOM_WAR_H_ */
