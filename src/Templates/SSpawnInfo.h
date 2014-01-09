/*
 * SSpawnInfo.h
 *
 *  Created on: Jan 3, 2014
 *      Author: zZelman
 */

#ifndef SSPAWNINFO_H_
#define SSPAWNINFO_H_

#include "../include_sfml.h"

/**
 * Bookkeeping struct passed between functions to determine what the user intended to spawn
 *
 * ALL are intended to be temporary
 * @param T object name that the spawn function exists within
 */
template <typename T>
struct SSpawnInfo
{
	/**
	 * Determines whether the mouse was pressed or a keyboard key.
	 *
	 * true = mouse, false = keyboard
	 */
	bool isMouse;

	/**
	 * State of an arbitrary key.
	 *
	 * true = pressed, false = released
	 */
	bool keyPressState;

	/**
	 * Pointer to actual event that occurred
	 */
	sf::Event* pEvent;

	/**
	 * The key (if pressed) will cause a spawn event to occur
	 */
	sf::Keyboard::Key* spawnKey;

	/**
	 * State of the spawnKey variable
	 *
	 * true = pressed, false = released
	 */
	bool* spawnKeyState;			// state of ^ key, true = pressed; false = !pressed

	/**
	 * Function pointer called if a spawn event has been detected, verified, and then initiated
	 *
	 * @param T it is assumed that the spawn function exists within an object, this is that
	 */
	void (T::*spawnFunction)(int, int);

	void nullAll();
};

#endif /* SSPAWNINFO_H_ */
