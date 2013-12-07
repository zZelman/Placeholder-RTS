/*
 * CUnit.h
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#ifndef CUNIT_H_
#define CUNIT_H_

#include "IRenderable.h"
#include "IUpdateable.h"
#include "CSprite.h"
#include "include_sfml.h"
#include "CGrid.h"
#include "Utills.h"

class CUnit: public IUpdateable, public IRenderable
{
public:
	struct SPhysics m_sPhysics;

	CUnit(sf::RenderWindow* pWindow, 			// rendering window
	      CGrid* pGrid,
	      CTexture* pTexture, 				// texture that this sprite will render with
	      const sf::Vector2<int>& currSub);	// LENGTH current sub image being rendered
	~CUnit();

	CSprite* const getSprite();

	void update();
	void render();

private:
	CSprite* m_pSprite;
	CGrid* m_pGrid;

	// * Controls how the sprite is moving during the update phase
	// * these flags are set elsewhere, then passively acted on as they precist
	struct SDirections m_sMovement;

	bool m_isFirstUpdate;

	// collision detection between
	bool canMove_vertical();
	bool canMove_horizontal();
};

#endif /* CUNIT_H_ */
