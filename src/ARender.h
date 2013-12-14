/*
 * IRenderable.h
 *
 *  Created on: Oct 10, 2013
 *      Author: zZelman
 */

#ifndef ARENDER_H_
#define ARENDER_H_

#include "include_sfml.h"
#include "IRenderable.h"
#include "CTexture.h"
#include "CSprite.h"

class ARender : public IRenderable
{
public:
	ARender(sf::RenderWindow* pWindow,
	        CTexture* pTexture,
	        const sf::Vector2<int>& currSub);

	// if this constructor is used, note that this object then takes responsibility
	//		for the CSprite*
	ARender(CSprite* pSprite);
	virtual ~ARender();

	CSprite* const getSprite();
	sf::Sprite* const getSprite_API();

	virtual void render();


protected:
	CSprite* m_pSprite;
};


#endif /* IRENDERABLE_H_ */
