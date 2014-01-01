/*
 * CHUD.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#include "CHUD.h"
#include <string>
#include <sstream>

CHUD::CHUD(sf::RenderWindow* pWindow, CRoom_Container* pRoomContainer) {
	m_pWindow = pWindow;
	m_pRoomContainer = pRoomContainer;
	m_psNumRooms = pRoomContainer->getNumRooms();

	m_font.loadFromFile("res/Fonts/Luxi-Mono/luximb.ttf");

	m_text.setFont(m_font);
	m_text.setCharacterSize(18);
	m_text.setColor(sf::Color::Red);
}

CHUD::~CHUD() {
}


void CHUD::render() {
	m_pWindow->draw(m_text);
}


void CHUD::update() {
	int totalRooms = m_psNumRooms->warehouse;

	std::string total("Total rooms: ");

	std::stringstream ss;
	ss << totalRooms;

	total += ss.str();

	m_text.setPosition(0, 0);
	m_text.setString(total);
}


bool CHUD::userInput_keyPress(sf::Event* pEvent) {
	return false;
}


bool CHUD::userInput_keyRelease(sf::Event* pEvent) {
	return false;
}


bool CHUD::userInput_mousePress(sf::Event* pEvent) {
	return false;
}


bool CHUD::userInput_mouseRelease(sf::Event* pEvent) {
	return false;
}
