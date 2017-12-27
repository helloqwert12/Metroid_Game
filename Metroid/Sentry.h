#pragma once
#ifndef _SENTRY_H_
#define _SENTRY_H_

#include "Enemy.h"
#include "Parameters.h"

enum SENTRY_STATE
{
	ON_SENTRY_A1,
	ON_SENTRY_A2,
	ON_SENTRY_A3,
	ON_SENTRY_A4,
	ON_SENTRY_A5,

	//ON_SENTRY_TOP,
	//ON_SENTRY_TOP_RIGHT,
	//ON_SENTRY_RIGHT,
	//ON_SENTRY_BOTTOM_RIGHT,
	//ON_SENTRY_BOTTOM,
	//ON_SENTRY_BOTTOM_LEFT,
	//ON_SENTRY_LEFT,
	//ON_SENTRY_TOP_LEFT,
};

class Sentry : public Enemy
{
protected:
	SENTRY_STATE state;
	Sprite * a1;
	Sprite * a2;
	Sprite * a3;
	Sprite * a4;
	Sprite * a5;
	//Sprite * top;
	//Sprite * top_right;
	//Sprite * right;
	//Sprite * bottom_right;
	//Sprite * bottom;
	//Sprite * bottom_left;
	//Sprite * left;
	//Sprite * top_left;

public:
	Sentry();
	Sentry(LPD3DXSPRITE spriteHandler, World * manager, SENTRY_TYPE sentry_type);
	~Sentry();

	void InitSprites();
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(int t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
};

#endif // !_SENTRY_H_
