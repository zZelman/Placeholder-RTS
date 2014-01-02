/*
 * IGetRenderData.h
 *
 *  Created on: Jan 1, 2014
 *      Author: zZelman
 */

#ifndef IGETRENDERDATA_H_
#define IGETRENDERDATA_H_

#include "../include_sfml.h"
#include "../Abstracts/ARender.h"
#include <list>

class IGetRenderData
{
public:
	virtual ~IGetRenderData();

	// fills the list with objects that need to be rendered
	virtual void getRenderData(std::list<ARender*>* pList) = 0;
};

#endif /* IGETRENDERDATA_H_ */
