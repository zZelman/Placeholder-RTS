/*
 * CTile.cpp
 *
 *  Created on: Dec 3, 2013
 *      Author: zZelman
 */

#include "CTile.h"
#include "CSprite.h"


CTile::CTile(CSprite* pSprite)
{
	m_pSprite = pSprite;
}


CTile::~CTile()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


CSprite* const CTile::getSprite()
{
	return m_pSprite;
}


void CTile::render()
{
	m_pSprite->render();
}


void CTile::update()
{
}
