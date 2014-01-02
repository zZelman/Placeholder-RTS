/*
 * CTIle.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#include "CTile.h"

CTile::CTile(CTexture* pTexture,
             const sf::Vector2<int>& currSub)
	: ARenderable(pTexture, currSub), AUpdate()
{
}

CTile::CTile(CSprite* pSprite)
	: ARenderable(pSprite), AUpdate()
{
}

CTile::~CTile()
{
}

void CTile::update()
{
}
