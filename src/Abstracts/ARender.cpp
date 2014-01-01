/*
 * IRenderable.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: zZelman
 */

#include "ARender.h"
#include "../Graphics/include_sfml.h"
#include "../Graphics/CTexture.h"
#include "../Graphics/CSprite.h"

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


sf::FloatRect ARender::getGlobalBounds()
{
	return m_pSprite->getGlobalBounds();
}

void ARender::setPosition(float x, float y)
{
	m_pSprite->setPosition(x, y);
}

void ARender::render()
{
	m_pSprite->render();
}
