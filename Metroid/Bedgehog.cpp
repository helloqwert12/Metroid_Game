#include "Bedgehog.h"
#include "World.h"
#include "GroupObject.h"

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

	//Set vận tốc
	gravity = FALLDOWN_VELOCITY_DECREASE;
	vx = BEDGEHOG_SPEED;
}


Bedgehog::~Bedgehog()
{
	delete(up);
	delete(bottom);
	delete(left);
	delete(right);
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

	//if (onGround)
	//	vy -= FALLDOWN_VELOCITY_DECREASE;
	vy -= gravity;

	//Kiểm tra va chạm
	for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
			if (timeScale < 1.0f)
			{
				ResponseGround(manager->quadtreeGroup->objects[i], t, timeScale);
			}
			else
			{
				//ChangeDirection(manager->quadtreeGroup->objects[i]);
			}
			break;
		}
	}

	pos_x += vx*t;
	pos_y += vy*t;

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
	}
	spriteHandler->End();
}

// Phản xạ khi va chạm với ground
void Bedgehog::ResponseGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{
	//ResponseFrom(target, _DeltaTime, collisionTimeScale);
	// lỡ đụng 2,3 ground mà chạy cái này nhiều lần sẽ rất sai
	// "góc lag" sẽ làm đi luôn vào trong tường


	if (normalx > 0.1f)	// tông bên phải gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetRight() - this->collider->GetLeft()) + 0.1f;
		pos_x -= vx*DeltaTime;

		vy = BEDGEHOG_SPEED;
		state = ON_BEDGEHOG_RIGHT;
		this->preDirection = RIGHT;
	}
	else if (normalx < -0.1f)// tông bên trái gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetLeft() - this->collider->GetRight()) - 0.1f;
		pos_x -= vx*DeltaTime;

		//vx *= (-1);
		vy = BEDGEHOG_SPEED;
		state = ON_BEDGEHOG_LEFT;
		this->preDirection = LEFT;
		gravity = 0.0f;
	}
	else if (normaly > 0.1f) // trên xuống (không vào normaly được)
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
		pos_y -= vy*DeltaTime;

		
		vy = -0.01f;
		state = ON_BEDGEHOG_UP;
		this->preDirection = TOP;
	}
	else if (normaly < -0.1f)	// tông ở dưới lên
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetTop() - this->collider->GetBottom()) - 0.1f;
		pos_y -= vy*DeltaTime;
		
		vx *= (-1);
		vy = 0.0f;
		state = ON_BEDGEHOG_BOTTOM;
		this->preDirection = BOTTOM;
	}
	if (vx != 0 || vy != 0)
	{
		this->isMoving = true;
	}
	Temp = target;
}

void Bedgehog::ChangeDirection(GameObject * target)
{
	if (this->Temp == target && isMoving == true)
	{
		if (this->preDirection == TOP )
		{
			this->vx = -0.05f;
			//vx = 0.0f;
			this->vy = -BEDGEHOG_SPEED;
			gravity = 0.0f;
		}
		else if (this->preDirection == RIGHT)
		{
			this->vx = BEDGEHOG_SPEED;
			this->vy = 0.01f;
			gravity = 0.0f;

		}
		else if (this->preDirection == BOTTOM )
		{
			this->vx = 0.01f;
			this->vy = BEDGEHOG_SPEED;
		}
		else if (this->preDirection == LEFT)
		{
			this->vx = BEDGEHOG_SPEED;
			this->vy = -0.01f;
		}
		this->isMoving = false;
	}
}

//----------------------------------