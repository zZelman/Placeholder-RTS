/*
 * CHUD.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#include "CHUD.h"
#include <string>
#include <sstream>

CHUD::CHUD(sf::RenderWindow* pWindow, CGameLogic* pGameLogic)
{
	m_pWindow = pWindow;
	m_pGameLogic = pGameLogic;

	m_font.loadFromFile("res/Fonts/Luxi-Mono/luximb.ttf");

	m_fontColor = sf::Color::Red;

	m_text.setFont(m_font);
	m_text.setCharacterSize(m_fontSize);
	m_text.setColor(m_fontColor);
}

CHUD::~CHUD()
{
}


void CHUD::render()
{
	m_pWindow->draw(m_text);
}


void CHUD::update()
{
	std::string total("Total resource cap: ");

	std::stringstream ss;
	ss << m_pGameLogic->getResources()->storage_cap;

	total += ss.str();

	m_text.setPosition(0, 0);
	m_text.setString(total);
}


bool CHUD::userInput_keyPress(sf::Event* pEvent)
{
	return false;
}


bool CHUD::userInput_keyRelease(sf::Event* pEvent)
{
	return false;
}


bool CHUD::userInput_mousePress(sf::Event* pEvent)
{
	return false;
}


bool CHUD::userInput_mouseRelease(sf::Event* pEvent)
{
	return false;
}
