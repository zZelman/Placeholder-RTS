/*
 * CUI.h
 *
 *  Created on: Jan 2, 2014
 *      Author: zZelman
 */

#ifndef CUI_H_
#define CUI_H_

#include "../Abstracts/AUserInput.h"
#include "../Templates/SRoomBookkeeping.h"
#include "../Templates/SSpawnInfo.h"
#include "../include_sfml.h"
#include "../Spawner/CSpawner.h"
#include "../Interfaces/IUpdateable.h"
#include "../Tiles/CTile_Container.h"
#include "../Rooms/CRoom_Container.h"



/**
 * 'Parses' user events, as well as keeps
 * Bookkeeping information on several user states.
 *
 * Keeps bookkeeping information for the states
 * of keys that are bound to spawn Rooms/Units
 *
 * Tells the 'Spawner' module to spawn specific
 * objects based on current values of the key states
 *
 * Uses a finite state machine to determine how
 * user events are interpreted (menu vs. game-play)
 */
class CUI: public AUserInput, public IUpdateable
{
public:
	CUI(CTile_Container* pTile_Container,
	    CRoom_Container* pRoom_Container,
	    CSpawner* pSpawner);
	~CUI();

	void update();

	bool userInput_keyPress(sf::Event* pEvent);
	bool userInput_keyRelease(sf::Event* pEvent);

	bool userInput_mousePress(sf::Event* pEvent);
	bool userInput_mouseRelease(sf::Event* pEvent);


private:
	CTile_Container* m_pTile_Container;
	CRoom_Container* m_pRoom_Container;
	CSpawner* m_pSpawner;

	/**
	 * Room Bookkeeping for key types that spawn rooms
	 */
	SRoomBookkeeping<sf::Keyboard::Key> m_room_spawnKeys;
	/**
	 * Room Bookkeeping the states of the key types that spanw rooms
	 */
	SRoomBookkeeping<bool> m_room_keyStates;

	/**
	 * Data struct whos values are set with current information
	 * user-state to determine what is updated/spawned.
	 */
	SSpawnInfo<CSpawner> m_sSpawnInfo;

	/**
	 * Iterates through each room-set function to set relevant
	 * information about user-state then calls a function that
	 * determines whether to update user-state, or spawn a room.
	 */
	bool roomSwitchBoard();

	/**
	 * Utility function only used by the constructor to set what key
	 * presses are acceptable to spawn a room.
	 */
	void setRoomKeybinds();

	// fills in the specific values of m_sSpawnInfo for the specific room
	void setInfo_warehouse();
	void setInfo_kitchen();
	void setInfo_smithy();
	void setInfo_powerPlant();
	void setInfo_warSpawner();
	void setInfo_researchSpawner();
	void setInfo_supportSpawner();

	/**
	 * Does 1 of two things: (1) updates user-state for rooms; (2) tells
	 * the spawner module to spawn a specific room by using a function pointer
	 */
	bool canSpawnRoom();

	/**
	 * Translates screen coords into grid coords.
	 */
	void normalizeToGrid(int* x, int* y);

	/**
	 * DEBUG (forwards to CRoom_Container::deleteRoom() ).
	 *
	 * Deletes a room at mouse coords (x,y) if there exists one
	 */
	bool deleteRoom(int x, int y);

};

#endif /* CUI_H_ */
