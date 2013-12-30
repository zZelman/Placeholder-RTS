/*
 * IUserInput.h
 *
 *  Created on: Oct 19, 2013
 *      Author: zZelman
 */

#ifndef AUSERINPUT_H_
#define AUSERINPUT_H_

#include "include_sfml.h"

class AUserInput
{
public:
	AUserInput();
	virtual ~AUserInput();

	// "pressed" or "released" is determined by the overarching game structure
	virtual bool userInput_keyPress(sf::Event* pEvent) = 0;
	virtual bool userInput_keyRelease(sf::Event* pEvent) = 0;

	virtual bool userInput_mousePress(sf::Event* pEvent) = 0;
	virtual bool userInput_mouseRelease(sf::Event* pEvent) = 0;

protected:
	struct SKeyStates
	{
		// Acceptable keys
		sf::Keyboard::Key up, down, left, right;

		// states of those keys
		bool isUp;
		bool isDown;
		bool isRight;
		bool isLeft;

		// reset states
		void nullStates();
	} m_sKeys;
};

#endif /* IUSERINPUT_H_ */
