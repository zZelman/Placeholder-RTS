/*
 * IRenderable.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: zZelman
 */

#include "ARender.h"
#include "../include_sfml.h"
#include "../Graphics/CTexture.h"
#include "../Graphics/CSprite.h"

ARenderable::ARenderable(CTexture* pTexture,
                         const sf::Vector2<int>& currSub)
{
	m_pSprite = new CSprite(pTexture, currSub);
}


ARenderable::ARenderable(CSprite* pSprite)
{
	m_pSprite = pSprite;
}


ARenderable::~ARenderable()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


CSprite* const ARenderable::getSprite()
{
	return m_pSprite;
}

sf::Sprite* const ARenderable::getSprite_API()
{
	return m_pSprite;
}


sf::FloatRect ARenderable::getGlobalBounds()
{
	return m_pSprite->getGlobalBounds();
}

void ARenderable::setPosition(float x, float y)
{
	m_pSprite->setPosition(x, y);
}
