/*
 * CRoom_Warehouse.h
 *
 *  Created on: Dec 30, 2013
 *      Author: zZelman
 */

#ifndef CROOM_WAREHOUSE_H_
#define CROOM_WAREHOUSE_H_

#include "CRoom.h"
#include "../Graphics/CTexture.h"
#include "../include_sfml.h"

class CRoom_warehouse: public CRoom
{
public:
	CRoom_warehouse(CTexture* pTexture,
	                const sf::Vector2<int>& currSub);
	~CRoom_warehouse();

	void update();
};

#endif /* CROOM_WAREHOUSE_H_ */
