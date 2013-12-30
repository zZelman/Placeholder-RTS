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
#include "CRoom_warehouse.h"
#include "CRoom_kitchen.h"
#include "CTile_Container.h"
#include "IGetCollisionData.h"
#include <list>

class CRoom_Container: public IUpdateable, public IRenderable, public IGetCollisionData,
	public AUserInput
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

	// container for all units
	std::list<CRoom*> m_rooms;

	// Unit texture filepaths
	CTexture* m_pDebugTexture;
	CTexture* m_pWarehouseTexture;
	CTexture* m_pKitchenTexture;

	// encapsilation of the new'ing of the CTexture's for each room
	void init_RoomTextures();
	void delete_RoomTextures();

	struct SRoomSpawnKeys
	{
		sf::Keyboard::Key warehouse;
		sf::Keyboard::Key kitchen;

	} m_sRoomSpawnKeys;

	struct SNumRooms
	{
		int warehouse;
		int kitchen;

		void nullAll();
	} m_sNumRooms;

	struct SRoomSpawnKeyStates
	{
		bool warehouse;
		bool kitchen;

		void nullAll();
	} m_sRoomSpawnKeyStates;

	// * Encapsulation of the ability to spawn the specific room
	// * keyPressState is whether or not the key was pressed (true) or released (false)
	// * bool isMouse true if event came from mouse, false if it came from the keyboard
	// * returns true if the function was able to do something (weather spawn a room,
	//		or change the states of flags that controll spawning)
	bool canSpawnRoom_room(bool keyPressState, bool isMouse, sf::Event* pEvent);
	bool canSpawnRoom_warehouse(bool keyPressState, bool isMouse, sf::Event* pEvent);
	bool canSpawnRoom_kitchen(bool keyPressState, bool isMouse, sf::Event* pEvent);

	// makes the given x,y coords into the (left,top) coords used by
	//		sfml to create a room that is grid-aligned
	void normalizeToGrid(int* x, int* y);

	// creates a new room
	void spawnRoom_room(int x, int y);
	void spawnRoom_warehouse(int x, int y);
	void spawnRoom_kitchen(int x, int y);

	// deletes a room
	bool deleteRoom(int x, int y);

//	void applyPhysics(CRoom* pRoom);
};

#endif /* CROOM_CONTAINER_H_ */
