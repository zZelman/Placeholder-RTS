/*
 * CRoom_researchSpawner.h
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#ifndef CROOM_RESEARCHSPAWNER_H_
#define CROOM_RESEARCHSPAWNER_H_

#include "CRoom.h"

class CRoom_researchSpawner: public CRoom
{
public:
	CRoom_researchSpawner(CTexture* pTexture,
	                      const sf::Vector2<int>& currSub);
	~CRoom_researchSpawner();

	void update();
};

#endif /* CROOM_RESEARCHSPAWNER_H_ */
