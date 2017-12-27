#pragma once
#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_
#include "Bullet.h"
#include "Missile.h"
#include "Parameters.h"
#define BULLET_COUNT 5

class BulletManager
{
private:
	World * manager;
	BulletObject ** bullet_list;
	int pos_x_holder;
	int pos_y_holder;
	int _Index;
	DWORD now_shoot;
	DWORD start_shoot;
	DWORD tick_per_frame;
	int frame_rate;
	
public:
	//BulletManager();
	BulletManager(World * manager, BULLET_TYPE bullet_type);
	//BulletManager(int posX, int posY);
	~BulletManager();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void InitPosition(int posX, int posY);
	void ResetAll();
	void Next(BULLET_DIRECTION dir);
	void Update(int t, int posX, int posY);
	void Render();
	void Shoot(BULLET_DIRECTION dir);
	
};

#endif // !_BULLETMANAGER_H_



