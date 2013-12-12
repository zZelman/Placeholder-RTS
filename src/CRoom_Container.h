/*
 * CRoom_Container.h
 *
 *  Created on: Dec 10, 2013
 *      Author: zZelman
 */

#ifndef CROOM_CONTAINER_H_
#define CROOM_CONTAINER_H_

#include "IRenderable.h"
#include "IUpdateable.h"
#include "IUserInput.h"
#include "include_sfml.h"
#include "CRoom.h"
#include "Utills.h"
#include "CGrid.h"
#include <vector>

class CRoom_Container: public IUpdateable, public IRenderable, public IUserInput
{
public:
	CRoom_Container(sf::RenderWindow* pWindow,
	                CGrid* pGrid);
	~CRoom_Container();

	void update();
	void render();

	bool userInput_keyPress(sf::Event* pEvent);
	bool userInput_keyRelease(sf::Event* pEvent);

	bool userInput_mousePress(sf::Event* pEvent);
	bool userInput_mouseRelease(sf::Event* pEvent);

	bool isCollision(const sf::Rect<float>& rect, CRoom*& pRoom);


private:
	sf::RenderWindow* m_pWindow;
	CGrid* m_pGrid;

	// keeps track of what arbitrary keys representing directions are pressed
	struct SDirections m_sKeyPress;

	// acceptable keys for user input (init'ed in constructor)
	struct SAcceptableKeys m_sKeys;

	bool m_isMousePressed;

	// Unit texture filepaths
	std::string m_debugTexture_path;
	CTexture* m_pDebugTexture;

	// container for all units
	std::vector<CRoom*> m_rooms;


	// creates a new unit into m_units
	void initRoom(int x, int y);

	void applyPhysics(CRoom* pRoom);
};

#endif /* CROOM_CONTAINER_H_ */
