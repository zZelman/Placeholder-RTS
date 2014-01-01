/*
 * CGameLogic.cpp
 *
 *  Created on: Jan 1, 2014
 *      Author: zZelman
 */

#include "CGameLogic.h"


void SResources::sumUse()
{
	storage_use = power_use + metal_use + food_use;
}


void SResources::nullAll()
{
	power_use = 0;
	power_cap = 0;

	metal_use = 0;
	metal_cap = 0;

	food_use = 0;
	food_cap = 0;

	storage_use = 0;
	storage_cap = 0;
}


CGameLogic::CGameLogic(CRoom_Container* pRoom_Container) : AUpdate()
{
	m_psNumRooms = pRoom_Container->getNumRooms();

	m_resources.nullAll();
}


CGameLogic::~CGameLogic()
{
}


const SResources* CGameLogic::getResources() const
{
	return &m_resources;
}


void CGameLogic::update()
{
	if (m_isFirstUpdate)
	{
		m_resourceClock.restart();
		m_isFirstUpdate = false;
	}

	update_resourceCaps();
}


void CGameLogic::update_resourceCaps()
{
	int numWarehouses = m_psNumRooms->warehouse;

	m_resources.storage_cap = numWarehouses * m_warehouseCapIncrease;
}

