/*
 * CUnitContainer.h
 *
 *  Created on: Dec 7, 2013
 *      Author: zZelman
 */

#ifndef CUNIT_CONTAINER_H_
#define CUNIT_CONTAINER_H_

#include "../Interfaces/IUpdateable.h"
#include "../Abstracts/AUserInput.h"
#include "../Interfaces/IRenderable.h"
#include "../Graphics/include_sfml.h"
#include "CUnit.h"
#include "../Tiles/CTile_Container.h"
#include <vector>
#include "../Interfaces/IGetCollisionData.h"
#include <list>

class CUnit_Container: public IUpdateable, public IRenderable, public IGetCollisionData, public AUserInput
{
public:
	CUnit_Container(sf::RenderWindow* pWindow,
	                CTile_Container* pGrid);
	~CUnit_Container();

	void update();
	void render();

	void getCollisiondata(std::list<ARender*>* pList);

	bool userInput_keyPress(sf::Event* pEvent);
	bool userInput_keyRelease(sf::Event* pEvent);

	bool userInput_mousePress(sf::Event* pEvent);
	bool userInput_mouseRelease(sf::Event* pEvent);


private:
	sf::RenderWindow* m_pWindow;
	CTile_Container* m_pGrid;

	// Unit texture filepaths
	std::string m_debugTexture_path;
	CTexture* m_pDebugTexture;

	// container for all units
	std::vector<CUnit*> m_units;

	// creates a new unit into m_units
	void initUnit(int x, int y);

	void applyPhysics(CUnit* pUnit);

};

#endif /* CUNIT_CONTAINER_H_ */
