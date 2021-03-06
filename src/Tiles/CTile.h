/*
 * CTIle.h
 *
 *  Created on: Dec 13, 2013
 *      Author: zZelman
 */

#ifndef CTILE_H_
#define CTILE_H_

#include "../Abstracts/ARenderable.h"
#include "../Abstracts/AUpdate.h"
#include "../Physics/DPhysics.h"
#include "../Graphics/CSprite.h"

class CTile: public ARenderable, public AUpdate
{
public:
	CTile(CTexture* pTexture,
	      const sf::Vector2<int>& currSub);

	// if this constructor is used, note that this object then takes responsibility
	//		for the CSprite*
	CTile(CSprite* pSprite);
	~CTile();

	void update();
};

#endif /* CTILE_H_ */
