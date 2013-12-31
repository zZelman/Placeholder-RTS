/*
 * CRoom_Container.h
 *
 *  Created on: Dec 10, 2013
 *      Author: zZelman
 */

#ifndef CROOM_CONTAINER_H_
#define CROOM_CONTAINER_H_

#include "IUpdateable.h"
#include "IRenderable.h"
#include "IGetCollisionData.h"

#include "AUserInput.h"

#include "include_sfml.h"
#include "include_rooms.h"

#include "CTile_Container.h"

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

	// Encapsulation of the room textures
	struct SRoomTextures
	{
		CTexture* debug;
		CTexture* warehouse;
		CTexture* kitchen;
		CTexture* smithy;
		CTexture* powerPlant;

		void init_RoomTextures();
		void delete_RoomTextures();
	} m_sRoomTextures;

	struct SRoomSpawnKeys
	{
		sf::Keyboard::Key warehouse;
		sf::Keyboard::Key kitchen;
		sf::Keyboard::Key smithy;
		sf::Keyboard::Key powerPlant;

	} m_sRoomSpawnKeys;

	struct SNumRooms
	{
		int warehouse;
		int kitchen;
		int smithy;
		int powerPlant;

		void nullAll();
	} m_sNumRooms;

	struct SRoomSpawnKeyStates
	{
		bool warehouse;
		bool kitchen;
		bool smithy;
		bool powerPlant;

		void nullAll();
	} m_sRoomSpawnKeyStates;

	struct SSpawnInfo
	{
		// generic (individual function wide) information
		bool isMouse;		// true = mouse; false = keyboard
		bool keyPressState; // true = pressed; false = released
		sf::Event* pEvent;	// pointer to actual event

		// * specific room information
		// * point to the data structs above (SRoomSpawnKeys SRoomSpawnKeyStates)
		sf::Keyboard::Key* spawnKey;	// key (when pressed) that allows for spawning
		bool* spawnKeyState;			// state of ^ key, true = pressed; false = !pressed
		void (CRoom_Container::*spawnFunction)(int, int) = NULL; // function ptr to the appropriate room spawner function
	} m_sSpawnInfo;

	// uses the values within m_sSpawnInfo to deduce whether or not that specific room
	//		can be spawned
	bool canSpawnRoom();

	// fills in the specific values of m_sSpawnInfo for the specific room
	void setInfo_warehouse();
	void setInfo_kitchen();
	void setInfo_smithy();
	void setInfo_powerPlant();

	// * Encapsulation of the ability to spawn the specific room
	// * keyPressState is whether or not the key was pressed (true) or released (false)
	// * bool isMouse true if event came from mouse, false if it came from the keyboard
	// * returns true if the function was able to do something (weather spawn a room,
	//		or change the states of flags that controll spawning)
	bool canSpawnRoom_debug(bool keyPressState, bool isMouse, sf::Event* pEvent);

	// * checks whether or not ANY room can be spawned @ the current mouse x,y
	// * x,y have NOT been normalized to the grid (normalizeToGrid is not used)
	// * returns false if cannot spawn
	// * current spawn conditions:
	//		- not within a current room
	//		- not below a current room (must fall onto the top of the building)
	bool canSpawn(int x, int y);

	// makes the given x,y coords into the (left,top) coords used by
	//		sfml to create a room that is grid-aligned
	void normalizeToGrid(int* x, int* y);

	// creates a new room
	void spawnRoom_debug(int x, int y);
	void spawnRoom_warehouse(int x, int y);
	void spawnRoom_kitchen(int x, int y);
	void spawnRoom_smithy(int x, int y);
	void spawnRoom_powerPlant(int x, int y);

	// deletes a room
	bool deleteRoom(int x, int y);

//	void applyPhysics(CRoom* pRoom);
};

#endif /* CROOM_CONTAINER_H_ */
