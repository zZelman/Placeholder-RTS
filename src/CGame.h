/*
 * CGame.h
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#ifndef CGAME_H_
#define CGAME_H_

#include "Graphics/include_sfml.h"
#include "Graphics/CSprite.h"
#include "Graphics/CTexture.h"
#include "Interfaces/IUpdateable.h"
#include "Tiles/CTile_Container.h"
#include "Units/CUnit_Container.h"
#include "Rooms/CRoom_Container.h"
#include "Physics/CPhysicsEngine.h"
#include "HUD/CHUD.h"

class CGame : public IUpdateable
{
public:
	CGame();
	~CGame();

	sf::RenderWindow* getGameWindow();

	bool getIsRunning();
	bool getIsPaused();

	void startGame();
	void stopGame();

private:
	sf::RenderWindow* m_pWindow;
	CTile_Container* m_pTile_Container;
	CUnit_Container* m_pUnit_Container;
	CRoom_Container* m_pRoom_Container;
	CPhysicsEngine* m_pPhysicsEngine;
	CHUD* m_pHUD;

	bool isRunning;
	bool isPaused;

	void initWindow();

	void gameLoop();

	bool input_user(sf::Event* pEvent);
	bool input_gameSystem(sf::Event* pEvent);
	void update();
	void render();
};

#endif /* CGAME_H_ */
