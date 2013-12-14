/*
 * CTIle.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#include "CTile.h"

CTile::CTile(sf::RenderWindow* pWindow,
             CTexture* pTexture,
             const sf::Vector2<int>& currSub)
	: ARender(pWindow, pTexture, currSub), AUpdate()
{
}

CTile::CTile(CSprite* pSprite)
	: ARender(pSprite), AUpdate()
{
}

CTile::~CTile()
{
}

void CTile::update()
{
}
