/*
 * CRoom_smithy.h
 *
 *  Created on: Dec 30, 2013
 *      Author: zZelman
 */

#ifndef CROOM_SMITHY_H_
#define CROOM_SMITHY_H_

#include "CRoom.h"

class CRoom_smithy: public CRoom {
public:
	CRoom_smithy(sf::RenderWindow* pWindow,
            CTexture* pTexture,
            const sf::Vector2<int>& currSub);
	~CRoom_smithy();

	void update();
};

#endif /* CROOM_SMITHY_H_ */
