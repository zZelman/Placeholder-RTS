/*
 * CRenderEngine.h
 *
 *  Created on: Jan 1, 2014
 *      Author: zZelman
 */

#ifndef CRENDERENGINE_H_
#define CRENDERENGINE_H_

#include "../include_sfml.h"
#include "../Rooms/include_rooms.h"
#include "../Units/include_units.h"
#include "../Tiles/include_tiles.h"
#include "../HUD/CHUD.h"

#include <list>

class CRenderEngine
{
public:
	CRenderEngine(sf::RenderWindow* pWindow,
	              CRoom_Container* pRoom_Container,
	              CUnit_Container* pUnit_Container,
	              CTile_Container* pTile_Container,
	              CHUD* pHUD);
	~CRenderEngine();

	// priority in the rendering:
	//		([top] menu, HUD, UI, Units, Rooms, Tiles [bottom])
	// NOTE: rendered in reverse order (bottom first) because of
	//		super-position
	void render();

private:
	sf::RenderWindow* m_pWindow;

	// used to fill the data lists (below)
	CRoom_Container* m_pRoom_Container;
	CUnit_Container* m_pUnit_Container;
	CTile_Container* m_pTile_Container;
	CHUD* m_pHUD;

	// Note that the individual data groups is kept separate
	//		(and not in one massive ARenderable list) because
	//		there is a priority in the rendering:
	//		([top] menu, HUD, UI, Units, Rooms, Tiles [bottom])
	std::list<ARenderable*> m_rooms;
	std::list<ARenderable*> m_units;
	std::list<ARenderable*> m_tiles;

	// * the current sprite being rendered
	// * allocated here because it is common to all of the render functions
	sf::Sprite* m_pSprite;

	// * data fields used by canBeSeen()
	// * allocated here because canBeSeen is called ALOT, so it is more
	//		efficient here, rather than on the stack
	sf::View m_view;
	sf::Vector2f m_viewSize;
	sf::Vector2f m_viewTopLeft;
	sf::FloatRect m_screenRect;


	// fills the std::list with the ARenderable data
	void getData();

	// * determines whether or not the thing is within the window
	//		subsection of the overall world (able to be seen)
	// * true = render the thing (done in calling function)
	// * false = dont render because it would be a waste because it cant be seen
	bool canBeSeen(ARenderable* pRender);

	// individual rendering functions
	void render_obj(std::list<ARenderable*>* pList); // takes care of Tile, Unit, and Room
	void render_UI();
	void render_HUD();
	void render_menu();

};

#endif /* CRENDERENGINE_H_ */
