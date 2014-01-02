/*
 * CRoom_powerPlant.h
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#ifndef CROOM_POWERPLANT_H_
#define CROOM_POWERPLANT_H_

#include "CRoom.h"

class CRoom_powerPlant: public CRoom
{
public:
	CRoom_powerPlant(CTexture* pTexture,
	                 const sf::Vector2<int>& currSub);
	~CRoom_powerPlant();

	void update();
};

#endif /* CROOM_POWERPLANT_H_ */
