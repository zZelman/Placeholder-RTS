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
#include "IRenderable.h"
#include "CGrid.h"
#include "CUnit_Container.h"

class CGame : public IUpdateable, public IRenderable
{
public:
	CGame();
	CGame(const CGame& other);
	~CGame();

	CGame& operator=(const CGame& other);

	sf::RenderWindow* getGameWindow();

	bool getIsRunning();
	bool getIsPaused();

	void startGame();
	void stopGame();

private:
	sf::RenderWindow* m_pWindow;
	CGrid* m_pGrid;
	CUnit_Container* m_pUnit_Container;

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
