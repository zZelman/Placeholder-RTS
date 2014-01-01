/*
 * CHUD.h
 *
 *  Created on: Dec 31, 2013
 *      Author: zZelman
 */

#ifndef CHUD_H_
#define CHUD_H_

#include "../Interfaces/IRenderable.h"

#include "../Abstracts/AUpdate.h"
#include "../Abstracts/AUserInput.h"

#include "../Rooms/CRoom_Container.h"

#include "../Logic/CGameLogic.h"

#include "../include_sfml.h"


class CHUD: public IRenderable, public AUpdate, public AUserInput
{
public:
	CHUD(sf::RenderWindow* pWindow, CGameLogic* pGameLogic);
	~CHUD();

	void render();
	void update();

	// "pressed" or "released" is determined by the overarching game structure
	bool userInput_keyPress(sf::Event* pEvent);
	bool userInput_keyRelease(sf::Event* pEvent);

	bool userInput_mousePress(sf::Event* pEvent);
	bool userInput_mouseRelease(sf::Event* pEvent);

private:
	sf::RenderWindow* m_pWindow;
	CGameLogic* m_pGameLogic;

	static const int m_fontSize = 15;
	sf::Color m_fontColor;
	sf::Font m_font;
	sf::Text m_text;
};

#endif /* CHUD_H_ */
