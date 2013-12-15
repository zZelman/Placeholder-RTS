/*
 * CGame.h
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#ifndef CGAME_H_
#define CGAME_H_

#include "include_sfml.h"
#include "CSprite.h"
#include "CTexture.h"
#include "IUpdateable.h"
#include "CTile_Container.h"
#include "CUnit_Container.h"
#include "CRoom_Container.h"
#include "CPhysicsEngine.h"

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
