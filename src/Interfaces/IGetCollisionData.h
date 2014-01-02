/*
 * IGetCollisionData.h
 *
 *  Created on: Dec 14, 2013
 *      Author: zZelman
 */

#ifndef IGETCOLLISIONDATA_H_
#define IGETCOLLISIONDATA_H_

#include <list>
#include "../Abstracts/ARender.h"

class IGetCollisionData
{
public:
	IGetCollisionData();
	virtual ~IGetCollisionData();

	// All objects that implement this interface agree to allow their pointers to  Derived Classes of ARender
	//		to be placed within the given std::list so that they may be used for quad-tree collision detection
	virtual void getCollisiondata(std::list<ARenderable*>* pList) = 0;
};

#endif /* IGETCOLLISIONDATA_H_ */
