#include "Block.h"

Block::Block()
{
}

Block::Block(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->enemy_type = enemy_type;
	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();

	//--TO DO: Khởi tạo collider cho Block (Khang)
	collider = new Collider();
	collider->SetCollider(0, 0, -BLOCK_HEIGHT, BLOCK_WIDTH);
}


Block::~Block()
{
	delete(left);
	delete(right);
}

ENEMY_TYPE Block::GetEnemyType()
{
	return enemy_type;
}

void Block::InitSprites()
{

	char  *left_path = NULL, *right_path = NULL;
	switch (enemy_type)
	{
	case BLOCK:
		left_path = BLOCK_LEFT;
		right_path = BLOCK_RIGHT;
		break;
	}

	// Khởi tạo sprite
	left = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, left_path, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_SPRITE_COUNT, 1);
	right = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, right_path, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_SPRITE_COUNT, 1);
}

void Block::Update(int t)
{
	if (!isActive) return;

	// Nếu không nằm trong Camera thì unactive
	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

	pos_x += vx*t;
	pos_y += vx*t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case ON_BLOCK_LEFT:
			left->Next();
			break;
		case ON_BLOCK_RIGHT:
			right->Next();
			break;
		}
		last_time = now;
	}

	// --TO DO: Xử lý va chạm
	// ...
	// Khi cần xử lý va chạm, gọi groupCollision ở world
	//	
}

void Block::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (state)
	{
	case ON_BLOCK_LEFT:
		left->Render(pos_x, pos_y);
		break;
	case ON_BLOCK_RIGHT:
		right->Render(pos_x, pos_y);
		break;
	}
	spriteHandler->End();
}
