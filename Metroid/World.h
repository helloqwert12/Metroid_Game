#pragma once
#ifndef _WORLD_H_
#define _WORLD_H_

#include <d3dx9.h>
#include "Samus.h"
#include "Parameters.h"
#include "Bedgehog.h"
#include "Block.h"
/*
	Class này chứa tất cả những thứ trong Game
	Các class khác chứa con trỏ đến class này để thao tác với các đối tượng trong class này
*/

class Metroid;

class World
{
public:
	Metroid * metroid;
	Samus * samus;

	LPD3DXSPRITE spriteHandler;

	QNode * rootQNode;
	GroupObject * quadtreeGroup;

	Bedgehog * hog;

	Block * block;

	BulletManager * bullets;

	GroupObject * collisionGroup;	//Group chứa các gameobject có khả năng va chạm với nhau
	GroupObject * enemyGroup;

	World();
	World(LPD3DXSPRITE spriteHandler, Metroid * metroid);
	~World();

	//void Init();
	void Update(float t);
	void Render();
	//void Destroy();

};

#endif // !_WORLD_H_

