#include "Missile.h"


void Missile::Render()
{
	if (isActive)
	{
		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		missile_up->Render(pos_x, pos_y);
		missile_left->Render(pos_x, pos_y);
		missile_right->Render(pos_x, pos_y);
		_SpriteHandler->End();
	}
}

Missile::Missile(World * manager)
{
	missile_up = NULL;
	missile_left = NULL;
	missile_right = NULL;

	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;
}

Missile::Missile(World * manager, int x_holder, int y_holder)
{
	missile_up = NULL;
	missile_left = NULL;
	missile_right = NULL;

	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;

	pos_x_holder = x_holder;
	pos_y_holder = y_holder;
}

Missile::~Missile()
{
	delete(missile_up);
	delete(missile_left);
	delete(missile_right);
}

void Missile::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	missile_up = new Sprite(_SpriteHandler, MISSILE_SPRITE_PATH, MISSILE_UP_SPRITE, MISSILE_UP_WIDTH, MISSILE_UP_HEIGHT, MISSILE_COUNT, SPRITE_PER_ROW);
	missile_left = new Sprite(_SpriteHandler, MISSILE_SPRITE_PATH, MISSILE_LEFT_SPRITE, MISSILE_WIDTH, MISSILE_HEIGHT, MISSILE_COUNT, SPRITE_PER_ROW);
	missile_right = new Sprite(_SpriteHandler, MISSILE_SPRITE_PATH, MISSILE_RIGHT_SPRITE, MISSILE_WIDTH, MISSILE_HEIGHT, MISSILE_COUNT, SPRITE_PER_ROW);
}

void Missile::InitPosition(int posX, int posY)
{
	pos_x = posX;
	pos_y = posY;

	pos_x_holder = posX;
	pos_y_holder = posY;

	direction = NONE;

}

BULLET_DIRECTION Missile::GetDirection()
{
	return direction;
}

void Missile::SetDirection(BULLET_DIRECTION value)
{
	direction = value;
}

void Missile::Update(int t, int posX, int posY)
{
	//
	// Update Missile status
	//
	switch (direction)
	{
	case ON_LEFT:
		isActive = true;
		vx = -SPEED;
		vy = 0;
		break;
	case ON_RIGHT:
		isActive = true;
		vx = SPEED;
		vy = 0;
		break;
	case ON_UP:
		isActive = true;
		vy = SPEED;
		vx = 0;
		break;
	case NONE:
		isActive = false;
		vx = 0;
		vy = 0;
		break;
	}

	pos_x += vx * t;
	pos_y += vy * t;

	int temp_x = vx * t;
	int temp_y = vy * t;

	if (temp_x < 0)
		temp_x = -temp_x;
	if (temp_y < 0)
		temp_y = -temp_y;

	limit_dist_x += temp_x;
	limit_dist_y += temp_y;


	//Check if the Missile reach the limit
	if (limit_dist_x >= LIMIT_DISTANCE || limit_dist_y >= LIMIT_DISTANCE)
	{
		Reset();
	}

	//Update position of samus
	pos_x_holder = posX;
	pos_y_holder = posY;
}

void Missile::ResetPosition()
{
	pos_x = pos_x_holder;
	pos_y = pos_y_holder;
}

void Missile::Reset()
{
	//Ngung render
	isActive = false;

	//Reset vi tri
	ResetPosition();

	//Reset distance
	limit_dist_x = 0;
	limit_dist_y = 0;

	//Set direction to NONE
	direction = NONE;
}

void Missile::Release()
{
	delete(this);
}

void Missile::Shoot(BULLET_DIRECTION dir)
{
	direction = dir;
	pos_x = pos_x_holder;
	pos_y = pos_y_holder;
}
