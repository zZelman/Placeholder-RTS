/*
 * CRoom_Container.h
 *
 *  Created on: Dec 10, 2013
 *      Author: zZelman
 */

#ifndef CROOM_CONTAINER_H_
#define CROOM_CONTAINER_H_

#include "IUpdateable.h"
#include "AUserInput.h"
#include "IRenderable.h"
#include "include_sfml.h"
#include "CRoom.h"
#include "CTile_Container.h"
#include <vector>
#include "IGetCollisionData.h"
#include <list>

class CRoom_Container: public IUpdateable, public IRenderable, public IGetCollisionData, public AUserInput
{
public:
	CRoom_Container(sf::RenderWindow* pWindow,
	                CTile_Container* pGrid);
	~CRoom_Container();

	void update();
	void render();

	void getCollisiondata(std::list<ARender*>* pList);

	bool userInput_keyPress(sf::Event* pEvent);
	bool userInput_keyRelease(sf::Event* pEvent);

	bool userInput_mousePress(sf::Event* pEvent);
	bool userInput_mouseRelease(sf::Event* pEvent);

	bool isCollision(const sf::Rect<float>& rect, CRoom*& pRoom);


private:
	sf::RenderWindow* m_pWindow;
	CTile_Container* m_pGrid;

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
