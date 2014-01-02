/*
 * CRenderEngine.cpp
 *
 *  Created on: Jan 1, 2014
 *      Author: zZelman
 */

#include "CRenderEngine.h"
#include <sstream>

CRenderEngine::CRenderEngine(sf::RenderWindow* pWindow,
                             CRoom_Container* pRoom_Container,
                             CUnit_Container* pUnit_Container,
                             CTile_Container* pTile_Container,
                             CHUD* pHUD)
{
	m_pWindow			= pWindow;
	m_pRoom_Container	= pRoom_Container;
	m_pUnit_Container	= pUnit_Container;
	m_pTile_Container	= pTile_Container;
	m_pHUD				= pHUD;

	m_pSprite = NULL;
}


CRenderEngine::~CRenderEngine()
{
}


void CRenderEngine::render()
{
	// fill lists with respective data
	getData();

	// * render each type in a specific order
	// * remember: law of super-position - things rendered
	//		later will be on top
	// * each individually determines whether or not the object
	//		can be seen by calling canBeSeen(...);
	render_tiles();
	render_rooms();
	render_units();
	render_UI();
	render_HUD();
	render_menu();
}


void CRenderEngine::getData()
{
	m_pRoom_Container->getRenderData(&m_rooms);
}


bool CRenderEngine::canBeSeen(ARender* pRender)
{
	// retrieve data
	m_view = m_pWindow->getView();

	m_viewTopLeft.x = m_view.getCenter().x - (m_view.getSize().x) / 2;
	m_viewTopLeft.y = m_view.getCenter().y - (m_view.getSize().y) / 2;

	m_viewSize = m_view.getSize();

	m_screenRect.left 	= m_viewTopLeft.x;
	m_screenRect.top 	= m_viewTopLeft.y;
	m_screenRect.width	= m_viewSize.x;
	m_screenRect.height	= m_viewSize.y;

	// test to see if the object is within the current window view
	if (pRender->getGlobalBounds().intersects(m_screenRect) == true)
	{
		return true;
	}

	// object cannot be seen
	return false;
}


void CRenderEngine::render_tiles()
{
}


void CRenderEngine::render_rooms()
{
	for (std::list<ARender*>::iterator itr = m_rooms.begin();
	        itr != m_rooms.end();
	        ++itr)
	{
		if (canBeSeen(*itr))
		{
			m_pSprite = (*itr)->getSprite_API();
			m_pWindow->draw(*m_pSprite);
		}
	}
}


void CRenderEngine::render_units()
{
}


void CRenderEngine::render_UI()
{
}


void CRenderEngine::render_HUD()
{
}


void CRenderEngine::render_menu()
{
}
