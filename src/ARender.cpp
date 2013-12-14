/*
 * IRenderable.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: zZelman
 */

#include "ARender.h"
#include "include_sfml.h"
#include "CTexture.h"
#include "CSprite.h"

ARender::ARender(sf::RenderWindow* pWindow,
                 CTexture* pTexture,
                 const sf::Vector2<int>& currSub)
{
	m_pSprite = new CSprite(pWindow, pTexture, currSub);
}


ARender::ARender(CSprite* pSprite)
{
	m_pSprite = pSprite;
}


ARender::~ARender()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


CSprite* const ARender::getSprite()
{
	return m_pSprite;
}

sf::Sprite* const ARender::getSprite_API()
{
	return m_pSprite;
}

void ARender::render()
{
	m_pSprite->render();
}
