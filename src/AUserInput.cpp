/*
 * IUserInput.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: zZelman
 */

#include "AUserInput.h"

AUserInput::AUserInput()
{
	m_sKeys.nullStates();

	m_isMousePressed = false;
}


AUserInput::~AUserInput()
{
	// TODO Auto-generated destructor stub
}

void AUserInput::SKeyStates::nullStates()
{
	isUp 		= false;
	isDown 		= false;
	isRight 	= false;
	isLeft 		= false;
}
