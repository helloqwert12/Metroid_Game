#include "BulletManager.h"
#include "World.h"
#include "Metroid.h"
#include "Bullet.h"
#include "SentryBullet.h"

BulletManager::BulletManager(World * manager, BULLET_TYPE bullet_type)
{
	this->manager = manager;
	//Create instance bullet_list
	bullet_list = new BulletObject*[BULLET_COUNT];
	switch (bullet_type)
	{
	case STANDARD:
		for (int i = 0; i < BULLET_COUNT; i++)
		{
			bullet_list[i] = new Bullet(manager);
		}
		break;
	case MISSILE:
		for (int i = 0; i < BULLET_COUNT; i++)
		{
			bullet_list[i] = new Missile(manager);
		}
		break;
	case SENTRY:
		for (int i = 0; i < BULLET_COUNT; i++)
		{
			bullet_list[i] = new SentryBullet(manager);
		}
	// ...
	}
	
	_Index = 0;
	this->start_shoot = 0;
	//this->tick_per_frame = manager->metroid->GetTickPerFrame();
	this->frame_rate = manager->metroid->FrameRate;
	this->tick_per_frame = 1000 / 80;
}

//BulletManager::BulletManager(int posX, int posY)
//{
//	BulletManager();
//	this->pos_x_holder = posX;
//	this->pos_y_holder = posY;
//}


BulletManager::~BulletManager()
{
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		delete(bullet_list[i]);
	}
	delete(bullet_list);
}

void BulletManager::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i]->InitSprites(d3ddv);
	}
}

void BulletManager::InitPosition(int posX, int posY)
{
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i]->InitPosition(pos_x_holder, pos_y_holder);
	}
}

void BulletManager::ResetAll()
{
	_Index = 0;
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i]->Reset();
	}
}

//void BulletManager::Next(BULLET_DIRECTION dir)
//{
//	bullet_list[_Index]->Shoot(dir);
//	_Index = (_Index + BULLET_COUNT - 1) % BULLET_COUNT;
//}

void BulletManager::Next(BULLET_DIRECTION dir, float posX, float posY)
{
	bullet_list[_Index]->Shoot(dir, posX, posY);
	_Index = (_Index + BULLET_COUNT - 1) % BULLET_COUNT;
}

void BulletManager::Update(int t)
{
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i]->Update(t);
	}

}

void BulletManager::Render()
{
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i]->Render();
	}
}

// Cái này chưa dùng được bị sai
//void BulletManager::Shoot(BULLET_DIRECTION dir)
//{
//	now_shoot = GetTickCount();
//	if (start_shoot <= 0) //if shooting is active
//	{
//		start_shoot = GetTickCount();
//		this->Next(dir);
//	}
//	else if ((now_shoot - start_shoot) > 1000);
//	{
//		//Reset start_shoot
//		start_shoot = 0;
//	}
//}

