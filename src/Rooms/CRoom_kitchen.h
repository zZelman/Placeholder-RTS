/*
 * CRoom_kitchen.h
 *
 *  Created on: Dec 30, 2013
 *      Author: zZelman
 */

#ifndef CROOM_KITCHEN_H_
#define CROOM_KITCHEN_H_

#include "CRoom.h"

class CRoom_kitchen: public CRoom
{
public:
	CRoom_kitchen(sf::RenderWindow* pWindow,
	              CTexture* pTexture,
	              const sf::Vector2<int>& currSub);
	~CRoom_kitchen();

	void update();
};

#endif /* CROOM_KITCHEN_H_ */
