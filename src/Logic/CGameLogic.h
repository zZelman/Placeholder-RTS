/*
 * CGameLogic.h
 *
 *  Created on: Jan 1, 2014
 *      Author: zZelman
 */

#ifndef CGAMELOGIC_H_
#define CGAMELOGIC_H_

#include "../Abstracts/AUpdate.h"
#include "../include_sfml.h"
#include "../Rooms/CRoom_Container.h"

struct SResources
{
	int power_use;
	int power_cap;

	int metal_use;
	int metal_cap;

	int food_use;
	int food_cap;

	int storage_use;
	int storage_cap;

	void sumUse();
	void nullAll();
};

class CGameLogic: public AUpdate
{
public:
	CGameLogic(CRoom_Container* pRoom_Container);
	~CGameLogic();

	const SResources* getResources() const;

	void update();


private:
	sf::Clock m_resourceClock;

	const SNumRooms* m_psNumRooms;

	SResources m_resources;

	static const int m_warehouseCapIncrease = 10;

	void update_resourceCaps();
};

#endif /* CGAMELOGIC_H_ */
