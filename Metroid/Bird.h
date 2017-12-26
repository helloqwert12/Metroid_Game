#pragma once
#ifndef _Bird_H_
#define _Bird_H_

#include "Enemy.h"
#include "Parameters.h"

enum BIRD_STATE
{
	ON_BIRD_IDLE,
	ON_BIRD_FLY
};

class Bird : public Enemy
{
protected:
	ENEMY_TYPE enemy_type;
	BIRD_STATE state;
	Sprite * idle;
	Sprite * fly;

public:
	Bird();
	Bird(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type);
	~Bird();

	ENEMY_TYPE GetEnemyType();
	void InitSprites();
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(int t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
};

#endif // !_Block_H_
