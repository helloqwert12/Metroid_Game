#include "Sentry.h"
#include "World.h"
#include "GroupObject.h"

Sentry::Sentry()
{
}

Sentry::Sentry(LPD3DXSPRITE spriteHandler, World * manager, SENTRY_TYPE sentry_type) : Enemy(spriteHandler, manager)
{
	this->sentry_type = sentry_type;
	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();

	//--TO DO: Khởi tạo collider cho Sentry
	collider = new Collider();
	collider->SetCollider(0, 0, -SENTRY_HEIGHT, SENTRY_WIDTH);
}


Sentry::~Sentry()
{
	delete(a1);
	delete(a2);
	delete(a3);
	delete(a4);
	delete(a5);
	//delete(top);
	//delete(top_right);
	//delete(right);
	//delete(bottom_right);
	//delete(bottom);
	//delete(bottom_left);
	//delete(left);
	//delete(top_left);
}


void Sentry::InitSprites()
{

	char *top_path = NULL, *top_right_path = NULL, *right_path = NULL, *bottom_right_path = NULL;
	char *bottom_path = NULL, *bottom_left_path = NULL, *left_path = NULL, *top_left_path = NULL;
	switch (sentry_type)
	{
	case SENTRY_LEFT:
		top_path = SENTRY_TOP_PATH;
		top_right_path = SENTRY_TOP_RIGHT_PATH;
		right_path = SENTRY_RIGHT_PATH;
		bottom_right_path = SENTRY_BOTTOM_RIGHT_PATH;
		bottom_path = SENTRY_BOTTOM_PATH;

		a1 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, top_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a2 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, top_right_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a3 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, right_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a4 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_right_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a5 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		break;
	case SENTRY_RIGHT:
		top_path = SENTRY_TOP_PATH;
		top_left_path = SENTRY_TOP_LEFT_PATH;
		left_path = SENTRY_LEFT_PATH;
		bottom_left_path = SENTRY_BOTTOM_LEFT_PATH;
		bottom_path = SENTRY_BOTTOM_PATH;

		a1 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, top_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a2 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, top_left_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a3 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, left_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a4 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_left_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a5 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		break;
	case SENTRY_TOP:;
		left_path = SENTRY_LEFT_PATH;
		bottom_left_path = SENTRY_BOTTOM_LEFT_PATH;
		bottom_path = SENTRY_BOTTOM_PATH;
		bottom_right_path = SENTRY_BOTTOM_RIGHT_PATH;
		right_path = SENTRY_RIGHT_PATH;

		a1 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, left_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a2 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_left_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a3 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a4 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_right_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		a5 = new Sprite(spriteHandler, BOSS_SPRITE_PATH, right_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
		break;
	}

	//// Khởi tạo sprite
	//top = new Sprite(spriteHandler, BOSS_SPRITE_PATH, top_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
	//top_right = new Sprite(spriteHandler, BOSS_SPRITE_PATH, top_right_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
	//right = new Sprite(spriteHandler, BOSS_SPRITE_PATH, right_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
	//bottom_right = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_right_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
	//bottom = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
	//bottom_left = new Sprite(spriteHandler, BOSS_SPRITE_PATH, bottom_left_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
	//left = new Sprite(spriteHandler, BOSS_SPRITE_PATH, left_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);
	//top_left = new Sprite(spriteHandler, BOSS_SPRITE_PATH, top_left_path, SENTRY_WIDTH, SENTRY_HEIGHT, SENTRY_SPRITE_COUNT, 1);

}

void Sentry::Update(int t)
{
	if (!isActive) return;

	// Nếu không nằm trong Camera thì unactive
	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

	//vy += -FALLDOWN_VELOCITY_DECREASE;

	//Kiểm tra va chạm
	//for (int i = 0; i < manager->quadtreeGroup->size; i++)
	//{
	//	switch (manager->quadtreeGroup->objects[i]->GetType())
	//	{
	//	case BRICK:
	//		float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
	//		if (timeScale < 1.0f)
	//		{
	//			
	//			pos_x += vx * timeScale;
	//			pos_y += vy * timeScale;

	//			//Push
	//			float magnitude = sqrt((vx * vx + vy * vy)) * (1.0f - timeScale);
	//			float dotprod = vx * normaly + vy * normalx;
	//			if (dotprod > 0.0f)
	//				dotprod = 1.0f;
	//			else if (dotprod < 0.0f)
	//				dotprod = -1.0f;
	//			vx = dotprod * normaly * magnitude;
	//			vy = dotprod * normalx * magnitude;

	//		}
	//		break;
	//	}
	//}

	pos_x += vx * t;
	pos_y += vy * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case ON_SENTRY_A1:
			a1->Next();
			break;
		case ON_SENTRY_A2:
			a2->Next();
			break;
		case ON_SENTRY_A3:
			a3->Next();
			break;
		case ON_SENTRY_A4:
			a4->Next();
			break;
		case ON_SENTRY_A5:
			a5->Next();
			break;

		/*case ON_SENTRY_TOP:
			top->Next();
			break;
		case ON_SENTRY_TOP_RIGHT:
			top_right->Next();
			break;
		case ON_SENTRY_RIGHT:
			right->Next();
			break;
		case ON_SENTRY_BOTTOM_RIGHT:
			bottom_right->Next();
			break;
		case ON_SENTRY_BOTTOM:
			bottom->Next();
			break;
		case ON_SENTRY_BOTTOM_LEFT:
			bottom_left->Next();
			break;
		case ON_SENTRY_LEFT:
			left->Next();
			break;
		case ON_SENTRY_TOP_LEFT:
			top_left->Next();
			break;*/
		}
		last_time = now;
	}

	// --TO DO: Xử lý va chạm
	// ...
	// Khi cần xử lý va chạm, gọi groupCollision ở world
	//	
}

void Sentry::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (state)
	{
	case ON_SENTRY_A1:
		a1->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_A2:
		a2->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_A3:
		a3->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_A4:
		a4->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_A5:
		a5->Render(pos_x, pos_y);
		break;
	/*case ON_SENTRY_TOP:
		top->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_TOP_RIGHT:
		top_right->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_RIGHT:
		right->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_BOTTOM_RIGHT:
		bottom_right->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_BOTTOM:
		bottom->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_BOTTOM_LEFT:
		bottom_left->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_LEFT:
		left->Render(pos_x, pos_y);
		break;
	case ON_SENTRY_TOP_LEFT:
		top_left->Render(pos_x, pos_y);
		break;*/
	}
	spriteHandler->End();
}
