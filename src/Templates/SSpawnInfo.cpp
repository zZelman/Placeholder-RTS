/*
 * SSpawnInfo.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: zZelman
 */

#include "SSpawnInfo.h"


template<typename T>
void SSpawnInfo<T>::nullAll()
{
	isMouse 		= false;
	keyPressState 	= false;
	pEvent 			= 0;
	spawnKey 		= 0;
	spawnFunction 	= 0;
}
