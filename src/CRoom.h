/*
 * CRoom.h
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#ifndef CROOM_H_
#define CROOM_H_

#include "IRenderable.h"
#include "IUpdateable.h"
#include "CSprite.h"
#include "Utills.h"
#include "include_sfml.h"
#include "CGrid.h"

// forward declare to prevent circular includes
class CRoom_Container;

class CRoom: public IRenderable, public IUpdateable
{
public:
	struct SPhysics m_sPhysics;

	CRoom(sf::RenderWindow* pWindow,
	      CGrid* pGrid, CRoom_Container* pRoom_Container,
	      CTexture* pTexture,
	      const sf::Vector2<int>& currSub);
	~CRoom();

	CSprite* const getSprite();

	void update();
	void render();

private:
	CSprite* m_pSprite;
	CGrid* m_pGrid;
	CRoom_Container* m_pRoom_Container;

	bool m_isFalling;
	bool m_isFirstUpdate;

	bool canMove_vertical();
};

#endif /* CROOM_H_ */