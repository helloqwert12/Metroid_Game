#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "BulletObject.h"
#include "Sprite.h"
#include "Parameters.h"


class Bullet : public BulletObject
{
protected:
	Sprite * bullet;
	
public:

	Bullet(World * manager);
	Bullet(World * manager, int x_holder, int y_holder);
	~Bullet();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Render();
	void Update(float t);
	
};

#endif // !_BULLET_H
