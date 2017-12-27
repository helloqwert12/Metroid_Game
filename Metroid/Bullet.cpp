#include "Bullet.h"
#include "World.h"
#include "GroupObject.h"


void Bullet::Render()
{
	if (isActive)
	{
		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		bullet->Render(pos_x, pos_y);
		_SpriteHandler->End();
	}
}

void Bullet::Update(float t)
{
	// Xử lý va chạm
	for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
			if (timeScale < 1.0f)
			{
				Reset();
			}
			break;
		}
	}

	//
	// Update bullet status
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
	case ON_BOTTOM:
		isActive = true;
		vy = -SPEED;
		vx = 0;
		break;
	case ON_TOPLEFT:
		isActive = true;
		vy = SPEED;
		vx = -SPEED;
		break;
	case ON_TOPRIGHT:
		isActive = true;
		vy = SPEED;
		vx = SPEED;
		break;
	case ON_BOTTOMLEFT:
		isActive = true;
		vy = -SPEED;
		vx = -SPEED;
		break;
	case ON_BOTTOMRIGHT:
		isActive = true;
		vy = -SPEED;
		vx = SPEED;
		break;
	case NONE:
		isActive = false;
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
}

Bullet::Bullet(World * manager)
{
	bullet = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;
}

Bullet::Bullet(World * manager, int x_holder, int y_holder)
{
	bullet = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;
	
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

	//Set collider
	collider = new Collider(0, 0, -BULLET_HEIGHT, BULLET_WIDTH);
}

