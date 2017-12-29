#pragma once
#ifndef _BEDGEHOG_H_
#define _BEDGEHOG_H_

#include "Enemy.h"
#include "Parameters.h"

enum BEDGEHOG_STATE
{
	ON_BEDGEHOG_UP,
	ON_BEDGEHOG_BOTTOM,
	ON_BEDGEHOG_LEFT,
	ON_BEDGEHOG_RIGHT,
	ON_BEDGEHOG_PINK_UP,
	ON_BEDGEHOG_PINK_BOTTOM,
	ON_BEDGEHOG_PINK_LEFT,
	ON_BEDGEHOG_PINK_RIGHT
};
enum eDirection
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};
class Bedgehog: public Enemy
{
protected:
	BEDGEHOG_STATE state;
	Sprite * up;
	Sprite * bottom;
	Sprite * left;
	Sprite * right;
	Sprite * up_pink;
	Sprite * bottom_pink;
	Sprite * left_pink;
	Sprite * right_pink;

	eDirection preDirection;

	GameObject * Temp;
	bool isMoving = false;

public:
	Bedgehog();
	Bedgehog(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type);
	~Bedgehog();

	void InitSprites();
	void ResponseGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	void ChangeDirection(GameObject *target);
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(int t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
};

#endif // !_BEDGEHOG_H_
