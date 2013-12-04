/*
 * CTile.h
 *
 *  Created on: Dec 3, 2013
 *      Author: zZelman
 */

#ifndef CTILE_H_
#define CTILE_H_

#include "IRenderable.h"
#include "IUpdateable.h"
#include "include_sfml.h"
#include "CTexture.h"
#include "CSprite.h"

class CTile: public IRenderable, public IUpdateable
{
public:
	// * the CSprite has been allocated on the heap then given to this object
	// * this object assumes responsibility for CSprite given (delete will be happen here)
	CTile(CSprite* pSprite);
	~CTile();

	void render();
	void update();


private:
	CSprite* m_pSprite;
};

#endif /* CTILE_H_ */
