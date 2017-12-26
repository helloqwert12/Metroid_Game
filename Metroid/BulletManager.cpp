#include "BulletManager.h"
#include "World.h"
#include "Metroid.h"
BulletManager::BulletManager()
{
	//Create instance bullet_list
	bullet_list = new Bullet*[BULLET_COUNT];
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i] = new Bullet(manager);
	}
	_Index = 0;
	this->start_shoot = 0;
	this->tick_per_frame = manager->metroid->GetTickPerFrame();
}

BulletManager::BulletManager(World * manager)
{
	this->manager = manager;
	//Create instance bullet_list
	bullet_list = new Bullet*[BULLET_COUNT];
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i] = new Bullet(manager);
	}
	_Index = 0;
	this->start_shoot = 0;
	this->tick_per_frame = manager->metroid->GetTickPerFrame();
}

BulletManager::BulletManager(int posX, int posY)
{
	BulletManager();
	this->pos_x_holder = posX;
	this->pos_y_holder = posY;
}


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

void BulletManager::Next(BULLET_DIRECTION dir)
{
	bullet_list[_Index]->Shoot(dir);
	_Index = (_Index + BULLET_COUNT - 1) % BULLET_COUNT;
}

void BulletManager::Update(int t, int posX, int posY)
{
	pos_x_holder = posX;
	pos_y_holder = posY;

	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i]->Update(t, posX, posY);
	}

}

void BulletManager::Render()
{
	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullet_list[i]->Render();
	}
}

void BulletManager::Shoot(BULLET_DIRECTION dir)
{
	now_shoot = GetTickCount();
	if (start_shoot <= 0) //if shooting is active
	{
		start_shoot = GetTickCount();
		this->Next(dir);
	}
	else if ((now_shoot - start_shoot) > SHOOTING_SPEED * manager->metroid->GetTickPerFrame());
	{
		//Reset start_shoot
		start_shoot = 0;
	}
}
