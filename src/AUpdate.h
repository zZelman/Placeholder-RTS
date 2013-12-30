/*
 * AUpdate.h
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#ifndef AUPDATE_H_
#define AUPDATE_H_

#include "IUpdateable.h"

class AUpdate : public IUpdateable
{
public:
	AUpdate();
	virtual ~AUpdate();

	virtual void update() = 0;

protected:

	// * Boolean to keep track of first-time update cycles
	// * this is intended to prevent time-sensitive things from freaking out
	//		from the object init to the first update
	bool m_isFirstUpdate;
};

#endif /* AUPDATE_H_ */
