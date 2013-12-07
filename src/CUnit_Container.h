/*
 * CUnitContainer.h
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#ifndef CUNIT_CONTAINER_H_
#define CUNIT_CONTAINER_H_

#include "IRenderable.h"
#include "IUpdateable.h"
#include "IUserInput.h"
#include "include_sfml.h"
#include "CUnit.h"
#include "Utills.h"
#include <vector>

class CUnit_Container: public IUpdateable, public IRenderable, public IUserInput
{
public:
	CUnit_Container(sf::RenderWindow* pWindow);
	~CUnit_Container();

	void update();
	void render();

	bool userInput_keyPress(sf::Event* pEvent);
	bool userInput_keyRelease(sf::Event* pEvent);

	bool userInput_mousePress(sf::Event* pEvent);
	bool userInput_mouseRelease(sf::Event* pEvent);


private:
	sf::RenderWindow* m_pWindow;

	// keeps track of what arbitrary keys representing directions are pressed
	struct SDirections m_sKeyPress;

	// acceptable keys for user input (init'ed in constructor)
	struct SAcceptableKeys m_sKeys;

	bool m_isMousePressed;

	// Unit texture filepaths
	std::string m_debugTexture_path;
	CTexture* m_pDebugTexture;

	// container for all units
	std::vector<CUnit*> m_units;


	// creates a new unit into m_units
	void initUnit(int x, int y);

};

#endif /* CUNIT_CONTAINER_H_ */
