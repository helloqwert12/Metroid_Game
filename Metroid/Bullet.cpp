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

