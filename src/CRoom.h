/*
 * CRoom.h
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#ifndef CROOM_H_
#define CROOM_H_

#include "ARender.h"
#include "AUpdate.h"
#include "CSprite.h"
#include "CTexture.h"
#include "include_sfml.h"
#include "DPhysics.h"

// forward declare to prevent circular includes
class CRoom_Container;

class CRoom: public ARender, public AUpdate, public DPhysics
{
public:
	CRoom(sf::RenderWindow* pWindow,
	      CTexture* pTexture,
	      const sf::Vector2<int>& currSub);
	virtual ~CRoom();

	virtual void update();
	void stepNormally();

//private:
//	CTile_Container* m_pGrid;
//	CRoom_Container* m_pRoom_Container;

//	bool canMove_vertical();
};

#endif /* CROOM_H_ */
