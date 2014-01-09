/*
 * CUnit.h
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#ifndef CUNIT_H_
#define CUNIT_H_

#include "../Abstracts/ARenderable.h"
#include "../Abstracts/AUpdate.h"
#include "../Graphics/CSprite.h"
#include "../include_sfml.h"
#include "../Tiles/CTile_Container.h"
#include "../Physics/DPhysics.h"

class CUnit: public AUpdate, public ARenderable, public DPhysics
{
public:
	CUnit(CTile_Container* pGrid,
	      CTexture* pTexture, 				// texture that this sprite will render with
	      const sf::Vector2<int>& currSub);	// LENGTH current sub image being rendered
	~CUnit();

	void update();
	void stepNormally();

private:
	CTile_Container* m_pGrid;

	// collision detection between
	bool canMove_vertical();
	bool canMove_horizontal();
};

#endif /* CUNIT_H_ */
