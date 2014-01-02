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
#include "../include_sfml.h"
#include "CUnit.h"
#include "../Tiles/CTile_Container.h"
#include <vector>
#include "../Interfaces/IGetCollisionData.h"
#include "../Interfaces/IGetRenderData.h"
#include <list>

class CUnit_Container: public IUpdateable, public IGetRenderData, public IGetCollisionData, public AUserInput
{
public:
	CUnit_Container(CTile_Container* pGrid);
	~CUnit_Container();

	void update();

	void getCollisiondata(std::list<ARenderable*>* pList);
	void getRenderData(std::list<ARenderable*>* pList);

	bool userInput_keyPress(sf::Event* pEvent);
	bool userInput_keyRelease(sf::Event* pEvent);

	bool userInput_mousePress(sf::Event* pEvent);
	bool userInput_mouseRelease(sf::Event* pEvent);


private:
	CTile_Container* m_pGrid;

	// Unit texture filepaths
	std::string m_debugTexture_path;
	CTexture* m_pDebugTexture;

	// container for all units
	std::list<CUnit*> m_units;

	// creates a new unit into m_units
	void initUnit(int x, int y);

	void applyPhysics(CUnit* pUnit);

};

#endif /* CUNIT_CONTAINER_H_ */
