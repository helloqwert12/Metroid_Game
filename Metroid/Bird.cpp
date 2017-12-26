#include "Bird.h"

Bird::Bird()
{
}

Bird::Bird(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->enemy_type = enemy_type;
	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();

	//--TO DO: Khởi tạo collider cho Block (Khang)
	collider = new Collider();
	collider->SetCollider(0, 0, -BLOCK_HEIGHT, BLOCK_WIDTH);
}


Bird::~Bird()
{
	delete(idle);
	delete(fly);
}

ENEMY_TYPE Bird::GetEnemyType()
{
	return enemy_type;
}

void Bird::InitSprites()
{
	char  *idle_path = NULL, *fly_path = NULL;
	switch (enemy_type)
	{
	case BIRD:
		idle_path = BIRD_IDLE;
		fly_path = BIRD_FLY;
		break;
	}

	// Khởi tạo sprite
	idle = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, idle_path, BIRD_WIDTH, BIRD_HEIGHT, BIRD_IDLE_SPRITE_COUNT, 1);
	fly = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, fly_path, BIRD_WIDTH, BIRD_HEIGHT, BIRD_FLY_SPRITE_COUNT, 1);
}

void Bird::Update(int t)
{
	if (!isActive) return;

	// Nếu không nằm trong Camera thì unactive
	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

	pos_x += vx * t;
	pos_y += vx * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case ON_BIRD_IDLE:
			idle->Next();
			break;
		case ON_BIRD_FLY:
			fly->Next();
			break;
		}
		last_time = now;
	}

	// --TO DO: Xử lý va chạm
	// ...
	// Khi cần xử lý va chạm, gọi groupCollision ở world
	//	
}

void Bird::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (state)
	{
	case ON_BIRD_IDLE:
		idle->Render(pos_x, pos_y);
		break;
	case ON_BIRD_FLY:
		fly->Render(pos_x, pos_y);
		break;
	}
	spriteHandler->End();
}
