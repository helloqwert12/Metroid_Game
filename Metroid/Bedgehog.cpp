#include "Bedgehog.h"

Bedgehog::Bedgehog()
{
}

Bedgehog::Bedgehog(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->enemy_type = enemy_type;
	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();

	//--TO DO: Khởi tạo collider cho Bedgehog (Khang)
	collider = new Collider();
	collider->SetCollider(0, 0, -BEDGEHOG_HEIGHT, BEDGEHOG_WIDTH);
}


Bedgehog::~Bedgehog()
{
	delete(up);
	delete(bottom);
	delete(left);
	delete(right);
	delete(up_pink);
	delete(bottom_pink);
	delete(left_pink);
	delete(right_pink);
}

ENEMY_TYPE Bedgehog::GetEnemyType()
{
	return enemy_type;
}

void Bedgehog::InitSprites()
{

	char *up_path = NULL, *bottom_path = NULL, *left_path = NULL, *right_path = NULL;
	
	switch(enemy_type)
	{
	case BEDGEHOG_YELLOW:
		up_path = BEDGEHOG_YELLOW_UP;
		bottom_path = BEDGEHOG_YELLOW_BOTTOM;
		left_path = BEDGEHOG_YELLOW_LEFT;
		right_path = BEDGEHOG_YELLOW_RIGHT;
		break;
	case BEDGEHOG_PINK:
		up_path = BEDGEHOG_PINK_UP;
		bottom_path = BEDGEHOG_PINK_BOTTOM;
		left_path = BEDGEHOG_PINK_LEFT;
		right_path = BEDGEHOG_PINK_RIGHT;
		break;
	}

	//// Khởi tạo sprite
	up = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, up_path, BEDGEHOG_WIDTH, BEDGEHOG_HEIGHT, BEDGEHOG_SPRITE_COUNT, 1);
	bottom = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, bottom_path, BEDGEHOG_WIDTH, BEDGEHOG_HEIGHT, BEDGEHOG_SPRITE_COUNT, 1);
	left = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, left_path, BEDGEHOG_WIDTH, BEDGEHOG_HEIGHT, BEDGEHOG_SPRITE_COUNT, 1);
	right = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, right_path, BEDGEHOG_WIDTH, BEDGEHOG_HEIGHT, BEDGEHOG_SPRITE_COUNT, 1);

}

void Bedgehog::Update(int t)
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
		case ON_BEDGEHOG_UP:
			up->Next();
			break;
		case ON_BEDGEHOG_BOTTOM:
			bottom->Next();
			break;
		case ON_BEDGEHOG_LEFT:
			left->Next();
			break;
		case ON_BEDGEHOG_RIGHT:
			right->Next();
			break;
		case ON_BEDGEHOG_PINK_UP:
			up_pink->Next();
			break;
		case ON_BEDGEHOG_PINK_BOTTOM:
			bottom_pink->Next();
			break;
		case ON_BEDGEHOG_PINK_LEFT:
			left_pink->Next();
			break;
		case ON_BEDGEHOG_PINK_RIGHT:
			right_pink->Next();
			break;
		}
		last_time = now;
	}

	// --TO DO: Xử lý va chạm
	// ...
	// Khi cần xử lý va chạm, gọi groupCollision ở world
	//	
}

void Bedgehog::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (state)
	{
	case ON_BEDGEHOG_UP:
		up->Render(pos_x, pos_y);
		break;
	case ON_BEDGEHOG_BOTTOM:
		bottom->Render(pos_x, pos_y);
		break;
	case ON_BEDGEHOG_LEFT:
		left->Render(pos_x, pos_y);
		break;
	case ON_BEDGEHOG_RIGHT:
		right->Render(pos_x, pos_y);
		break;
	case ON_BEDGEHOG_PINK_UP:
		up_pink->Render(pos_x, pos_y);
		break;
	case ON_BEDGEHOG_PINK_BOTTOM:
		bottom_pink->Render(pos_x, pos_y);
		break;
	case ON_BEDGEHOG_PINK_LEFT:
		left_pink->Render(pos_x, pos_y);
		break;
	case ON_BEDGEHOG_PINK_RIGHT:
		right_pink->Render(pos_x, pos_y);
		break;
	}
	spriteHandler->End();
}
