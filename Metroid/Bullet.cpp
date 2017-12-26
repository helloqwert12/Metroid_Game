#include "Bullet.h"



void Bullet::Render()
{
	if (isRendering)
	{
		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		bullet->Render(pos_x, pos_y);
		_SpriteHandler->End();
	}
}

Bullet::Bullet()
{
	bullet = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isRendering = false;
}

Bullet::Bullet(int x_holder, int y_holder)
{
	Bullet();
	pos_x_holder = x_holder;
	pos_y_holder = y_holder;
}


Bullet::~Bullet()
{
	delete(bullet);
}

void Bullet::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	bullet = new Sprite(_SpriteHandler, BULLET_SPRITE_PATH, BULLET_SPRITE, BULLET_WIDTH, BULLET_HEIGHT, BULLET_COUNT, SPRITE_PER_ROW);
}

void Bullet::InitPosition(int posX, int posY)
{
	pos_x = posX;
	pos_y = posY;

	pos_x_holder = posX;
	pos_y_holder = posY;

	direction = NONE;

}

BULLET_DIRECTION Bullet::GetDirection()
{
	return direction;
}

void Bullet::SetDirection(BULLET_DIRECTION value)
{
	direction = value;
}

void Bullet::Update(int t, int posX, int posY)
{
	//
	// Update bullet status
	//
	switch (direction)
	{
	case ON_LEFT:
		isRendering = true;
		vx = -SPEED;
		vy = 0;
		break;
	case ON_RIGHT:
		isRendering = true;
		vx = SPEED;
		vy = 0;
		break;
	case ON_UP:
		isRendering = true;
		vy = SPEED;
		vx = 0;
		break;
	case NONE:
		isRendering = false;
		vx = 0;
		vy = 0;
		break;
	}
	
	pos_x += vx*t;
	pos_y += vy*t;

	int temp_x = vx*t;
	int temp_y = vy*t;

	if (temp_x < 0)
		temp_x = -temp_x;
	if (temp_y < 0)
		temp_y = -temp_y;

	limit_dist_x += temp_x;
	limit_dist_y += temp_y;


	//Check if the bullet reach the limit
	if (limit_dist_x >= LIMIT_DISTANCE || limit_dist_y >= LIMIT_DISTANCE)
	{
		Reset();
	}

	//Update position of samus
	pos_x_holder = posX;
	pos_y_holder = posY;
}

void Bullet::ResetPosition()
{
	pos_x = pos_x_holder;
	pos_y = pos_y_holder;
}

void Bullet::Reset()
{
	//Ngung render
	isRendering = false;

	//Reset vi tri
	ResetPosition();

	//Reset distance
	limit_dist_x = 0;
	limit_dist_y = 0;

	//Set direction to NONE
	direction = NONE;
}

void Bullet::Release()
{
	delete(this);
}

void Bullet::Shoot(BULLET_DIRECTION dir)
{
	direction = dir;
	pos_x = pos_x_holder;
	pos_y = pos_y_holder;
}
