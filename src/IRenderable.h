/*
 * IRenderable.h
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

// Interface base class holding the "render()" method
class IRenderable
{
public:
	virtual ~IRenderable();
	virtual void render() = 0;
};


#endif /* IRENDERABLE_H_ */
