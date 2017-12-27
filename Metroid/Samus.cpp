#include "Samus.h"
#include "Game.h"
#include <vector>
#include "GroupObject.h"
#include "World.h"

void Samus::Render()
{
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	switch (state)
	{
	case RIGHTING:
		running_right->Render(pos_x, pos_y);
		break;
	case LEFTING:
		running_left->Render(pos_x, pos_y);
		break;
	case AIMING_UP_LEFT:
		run_aim_up_left->Render(pos_x, pos_y);
		break;
	case AIMING_UP_RIGHT:
		run_aim_up_right->Render(pos_x, pos_y);
		break;
	case IDLING_AIM_UP_LEFT:
		idle_aim_up_left->Render(pos_x, pos_y);
		break;
	case IDLING_AIM_UP_RIGHT:
		idle_aim_up_right-> Render(pos_x, pos_y);
		break;
	case IDLE_LEFT:
		idle_left->Render(pos_x, pos_y);
		break;
	case IDLE_RIGHT:
		idle_right->Render(pos_x, pos_y);
		break;
	case ON_MORPH_LEFT:
		morph_ball_left->Render(pos_x, pos_y);
		break;
	case ON_MORPH_RIGHT:
		morph_ball_right->Render(pos_x, pos_y);
		break;
	case ON_RUN_SHOOTING_LEFT:
		run_shooting_left->Render(pos_x, pos_y);
		break;
	case ON_RUN_SHOOTING_RIGHT:
		run_shooting_right->Render(pos_x, pos_y);
		break;
	case ON_JUMP_LEFT:
		jump_left->Render(pos_x, pos_y);
		break;
	case ON_JUMP_RIGHT:
		jump_right->Render(pos_x, pos_y);
		break;
	case ON_SOMERSAULT_LEFT:
		somersault_left->Render(pos_x, pos_y);
		break;
	case ON_SOMERSAULT_RIGHT:
		somersault_right->Render(pos_x, pos_y);
		break;
	case ON_JUMPING_SHOOTING_LEFT:
		jumping_shooting_left->Render(pos_x, pos_y);
		break;
	case ON_JUMPING_SHOOTING_RIGHT:
		jumping_shooting_right->Render(pos_x, pos_y);
		break;
	case ON_JUMP_AIM_UP_LEFT:
		jump_aim_up_left->Render(pos_x, pos_y);
		break;
	case ON_JUMP_AIM_UP_RIGHT:
		jump_aim_up_right->Render(pos_x, pos_y);
		break;
	case IDLING_SHOOTING_LEFT:
		idle_shooting_left->Render(pos_x, pos_y);
		break;
	case IDLING_SHOOTING_RIGHT:
		idle_shooting_right->Render(pos_x, pos_y);
		break;
	case IDLING_SHOOTING_UP_LEFT:
		idle_shooting_up_left->Render(pos_x, pos_y);
		break;
	case IDLING_SHOOTING_UP_RIGHT:
		idle_shooting_up_right->Render(pos_x, pos_y);
		break;
	case ON_JUMP_SHOOTING_UP_LEFT:
		jump_shooting_up_right->Render(pos_x, pos_y);
		break;
	case ON_JUMP_SHOOTING_UP_RIGHT:
		jump_shooting_up_right->Render(pos_x, pos_y);
		break;
	}

	
	spriteHandler->End();
}

void Samus::Destroy()
{
	//Ngưng active
	isActive = false;

	//--TO DO: Đưa Samus ra khỏi viewport
}

Samus::Samus()
{
	appearing = NULL;
	running_left = NULL;
	running_right = NULL;
	jump_left = NULL;
	jump_right = NULL;

	width = 40;
	height = 64;

	collider = new Collider();
	collider->SetCollider(0, 0, -this->height, this->width);
}

Samus::Samus(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	//Set type
	this->type = SAMUS;

	width = 40;
	height = 50;

	//Collider
	this->collider = new Collider();
	this->collider->SetCollider(0, 0, -this->height, this->width);

	gravity = FALLDOWN_VELOCITY_DECREASE;
}


Samus::~Samus()
{
	delete(appearing);
	delete(running_left);
	delete(running_right);
	delete(jump_left);
	delete(jump_right);
	delete(run_shooting_left);
	delete(run_shooting_right);
	delete(run_aim_up_left);
	delete(run_aim_up_right);
	delete(idle_aim_up_left);
	delete(idle_aim_up_right);
	delete(idle_left);
	delete(idle_right);
	delete(morph_ball_left);
	delete(morph_ball_right);
	delete(somersault_left);
	delete(somersault_right);
	delete(jumping_shooting_left);
	delete(jumping_shooting_right);
	delete(jump_aim_up_left);
	delete(jump_aim_up_right);
	delete(collider);
	delete(idle_shooting_left);
	delete(idle_shooting_right);
	delete(idle_shooting_up_left);
	delete(idle_shooting_up_right);
	delete(jump_shooting_up_left);
	delete(jump_shooting_up_right);
}

//DirectCollision Samus::getDirection()
//{
//	return this->direction;
//}
//void Samus::setDirection(DirectCollision direction)
//{
//	this->direction = direction;
//}


void Samus::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;

	//Create instance of sprites
	appearing = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, APPEARING, APPEARING_WIDTH, APPEARING_HEIGHT, APPEARING_COUNT, SPRITE_PER_ROW);
	running_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUNNING_LEFT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	running_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUNNING_RIGHT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	jump_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_LEFT, JUMP_WIDTH, JUMP_HEIGHT, JUMP_COUNT, SPRITE_PER_ROW);
	jump_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_RIGHT, JUMP_WIDTH, JUMP_HEIGHT, JUMP_COUNT, SPRITE_PER_ROW);
	run_shooting_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_SHOOTING_LEFT, RUN_SHOOTING_WIDTH, RUN_SHOOTING_HEIGHT, RUN_SHOOTING_COUNT, SPRITE_PER_ROW);
	run_shooting_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_SHOOTING_RIGHT, RUN_SHOOTING_WIDTH, RUN_SHOOTING_HEIGHT, RUN_SHOOTING_COUNT, SPRITE_PER_ROW);
	run_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_AIM_UP_LEFT, RUN_AIM_UP_WIDTH, RUN_AIM_UP_HEIGHT, RUN_AIM_UP_COUNT, SPRITE_PER_ROW);
	run_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_AIM_UP_RIGHT, RUN_AIM_UP_WIDTH, RUN_AIM_UP_HEIGHT, RUN_AIM_UP_COUNT, SPRITE_PER_ROW);
	idle_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, IDLE_AIM_UP_LEFT, IDLE_AIM_UP_WIDTH, IDLE_AIM_UP_HEIGHT, IDLE_AIM_UP_COUNT, SPRITE_PER_ROW);
	idle_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, IDLE_AIM_UP_RIGHT, IDLE_AIM_UP_WIDTH, IDLE_AIM_UP_HEIGHT, IDLE_AIM_UP_COUNT, SPRITE_PER_ROW);
	idle_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STANDING_LEFT, STANDING_WIDTH, STANDING_HEIGHT, STANDING_COUNT, SPRITE_PER_ROW);
	idle_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STANDING_RIGHT, STANDING_WIDTH, STANDING_HEIGHT, STANDING_COUNT, SPRITE_PER_ROW);
	morph_ball_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, MORPH_BALL_LEFT, MORPH_BALL_WIDTH, MORPH_BALL_HEIGHT, MORPH_BALL_COUNT, SPRITE_PER_ROW);
	morph_ball_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, MORPH_BALL_RIGHT, MORPH_BALL_WIDTH, MORPH_BALL_HEIGHT, MORPH_BALL_COUNT, SPRITE_PER_ROW);
	somersault_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, SOMERSAULT_LEFT, SOMERSAULT_WIDTH, SOMERSAULT_HEIGHT, SOMERSAULT_COUNT, SPRITE_PER_ROW);
	somersault_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, SOMERSAULT_RIGHT, SOMERSAULT_WIDTH, SOMERSAULT_HEIGHT, SOMERSAULT_COUNT, SPRITE_PER_ROW);
	jumping_shooting_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMPING_SHOOTING_LEFT, JUMPING_SHOOTING_WIDTH, JUMPING_SHOOTING_HEIGHT, JUMPING_SHOOTING_COUNT, SPRITE_PER_ROW);
	jumping_shooting_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMPING_SHOOTING_RIGHT, JUMPING_SHOOTING_WIDTH, JUMPING_SHOOTING_HEIGHT, JUMPING_SHOOTING_COUNT, SPRITE_PER_ROW);
	jump_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_AIM_UP_LEFT, JUMP_AIM_UP_WIDTH, JUMP_AIM_UP_HEIGHT, JUMP_AIM_UP_COUNT, SPRITE_PER_ROW);
	jump_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_AIM_UP_RIGHT, JUMP_AIM_UP_WIDTH, JUMP_AIM_UP_HEIGHT, JUMP_AIM_UP_COUNT, SPRITE_PER_ROW);
	idle_shooting_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STAND_SHOOTING_LEFT, STANDING_SHOOTING_WIDTH, STANDING_SHOOTING_HEIGHT, STAND_SHOOTING_COUNT, SPRITE_PER_ROW);
	idle_shooting_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STAND_SHOOTING_RIGHT, STANDING_SHOOTING_WIDTH, STANDING_SHOOTING_HEIGHT, STAND_SHOOTING_COUNT, SPRITE_PER_ROW);
	idle_shooting_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STAND_SHOOTING_UP_LEFT, STANDING_SHOOTING_UP_WIDTH, STANDING_SHOOTING_UP_HEIGHT, STAND_SHOOTING_UP_COUNT, SPRITE_PER_ROW);
	idle_shooting_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STAND_SHOOTING_UP_RIGHT, STANDING_SHOOTING_UP_WIDTH, STANDING_SHOOTING_UP_HEIGHT, STAND_SHOOTING_UP_COUNT, SPRITE_PER_ROW);
	jump_shooting_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_SHOOTING_UP_LEFT, JUMP_SHOOTING_UP_WIDTH, JUMP_SHOOTING_UP_HEIGHT, JUMP_SHOOTING_UP_COUNT, SPRITE_PER_ROW);
	jump_shooting_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_SHOOTING_UP_RIGHT, JUMP_SHOOTING_UP_WIDTH, JUMP_SHOOTING_UP_HEIGHT, JUMP_SHOOTING_UP_COUNT, SPRITE_PER_ROW);
}

void Samus::InitPostition()
{
	//--TO DO: This code will be edited soon
	pos_x = 50;
	pos_y = GROUND_Y;

	vx = 0;
	vx_last = 1.0f;
	vy = 0;

	//Init state of samus
	state = IDLE_RIGHT;
}

int max_camera_x = 300;
int max_camera_y = 480;

int min_camera_x = 0;
int min_camera_y = 480;


SAMUS_STATE Samus::GetState()
{
	return state;
}

void Samus::SetState(SAMUS_STATE value)
{
	state = value;
}

void Samus::ResetAllSprites()
{
	appearing->Reset();
	running_left->Reset();
	running_right->Reset();
	jump_left->Reset();
	jump_right->Reset();
	run_shooting_left->Reset();
	run_shooting_right->Reset();
	run_aim_up_left->Reset();
	run_aim_up_right->Reset();
	idle_aim_up_left->Reset();
	idle_aim_up_right->Reset();
	idle_left->Reset();
	idle_right->Reset();
	morph_ball_left->Reset();
	morph_ball_right->Reset();
	somersault_left->Reset();
	somersault_right->Reset();
	jumping_shooting_left->Reset();
	jumping_shooting_right->Reset();
	jump_aim_up_left->Reset();
	jump_aim_up_right->Reset();
	idle_shooting_left->Reset();
	idle_shooting_right->Reset();
	idle_shooting_up_left->Reset();
	idle_shooting_up_right->Reset();
	jump_shooting_up_left->Reset();
	jump_shooting_up_right->Reset();
}	


void Samus::Reset(int x, int y)
{
	// Cho samus active trở lại
	isActive = true;

	//Đặt lại vị trí
	this->pos_x = x;
	this->pos_y = y;
}

void Samus::Update(int t)
{
	//
	// Update mario status
	//
	//GameObject::Update(t);

	vy -= gravity;

	std::vector<GameObject*> list = manager->enemyGroup->GetListGO();
	for (int i = 0; i < list.size(); i++)
	{	
		float timeScale = SweptAABB(list[i], t);
		if (timeScale < 1.0f)
		{
			this->SlideFromGround(list[i], t, timeScale);
		}
	}
	
	for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
			if (timeScale < 1.0f)
			{
				SlideFromGround(manager->quadtreeGroup->objects[i], t, timeScale);
			}
			break;
		}
	}
	
	pos_x += vx*t;
	pos_y += vy*t;

	Camera::SetCameraX(pos_x);
	Camera::SetCameraY(pos_y);

	// Animate samus if he is running
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case RIGHTING:
			running_right->Next();
			break;
		case LEFTING:
			running_left->Next();
			break;
		case AIMING_UP_LEFT:
			run_aim_up_left->Next();
			break;
		case AIMING_UP_RIGHT:
			run_aim_up_right->Next();
			break;
		case IDLING_AIM_UP_LEFT:
			idle_aim_up_left->Next();
			break;
		case IDLING_AIM_UP_RIGHT:
			idle_aim_up_right->Next();
			break;
		case ON_MORPH_LEFT:
			morph_ball_left->Next();
			break;
		case ON_MORPH_RIGHT:
			morph_ball_right->Next();
			break;
		case ON_RUN_SHOOTING_LEFT:
			run_shooting_left->Next();
			break;
		case ON_RUN_SHOOTING_RIGHT:
			run_shooting_right->Next();
			break;
		case ON_JUMP_LEFT:
			jump_left->Next();
			break;
		case ON_JUMP_RIGHT:
			jump_right->Next();
			break;
		case ON_SOMERSAULT_LEFT:
			somersault_left->Next();
			break;
		case ON_SOMERSAULT_RIGHT:
			somersault_right->Next();
			break;
		case ON_JUMPING_SHOOTING_LEFT:
			jumping_shooting_left->Next();	
			break;
		case ON_JUMPING_SHOOTING_RIGHT:
			jumping_shooting_right->Next();
			break;
		case ON_JUMP_AIM_UP_LEFT:
			jump_aim_up_left->Next();
			break;
		case ON_JUMP_AIM_UP_RIGHT:
			jump_aim_up_right->Next();
			break;
		case IDLING_SHOOTING_LEFT:
			idle_shooting_left->Next();
			break;
		case IDLING_SHOOTING_RIGHT:
			idle_shooting_right->Next();
			break;
		case IDLING_SHOOTING_UP_LEFT:
			idle_shooting_up_left->Next();
			break;
		case IDLING_SHOOTING_UP_RIGHT:
			idle_shooting_up_right->Next();
			break;
		case ON_JUMP_SHOOTING_UP_LEFT:
			jump_shooting_up_left->Next();
			break;
		case ON_JUMP_SHOOTING_UP_RIGHT:
			jump_shooting_up_right->Next();
			break;

		}
		last_time = now;
	}

	//Check if samus is on ground or not
	/*if (pos_y > GROUND_Y)
	{
		vy -= gravity;
	}
	else
	{
		pos_y = GROUND_Y;
		vy = 0;
		if (state == ON_JUMP_LEFT || state == ON_JUMPING_SHOOTING_LEFT || state == ON_SOMERSAULT_LEFT || state == ON_JUMP_AIM_UP_LEFT)
		{
			state = IDLE_LEFT;
		}
		else if (state == ON_JUMP_RIGHT || state == ON_JUMPING_SHOOTING_RIGHT || state == ON_SOMERSAULT_RIGHT || state == ON_JUMP_AIM_UP_RIGHT)
		{
			state = IDLE_RIGHT;
		}
	}*/

	//Render
	Render();

}

void Samus::Response(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{
	// rồi mới bật ra
	if (normalx > 0.1f)	// tông bên phải
	{
		if (vx < -0.0f)// đang chạy qua trái => văng ngược lại
			vx *= -1;
	}
	else if (normalx < -0.1f) // tông bên trái
	{
		if (vx > 0.0f)//	đang chạy qua phải => văng ngược lại
			vx *= -1;
	}

	if (normaly > 0.1f) // tông phía trên
	{
		if (vy < -0.0f)// đang rơi xuống => văng lên trên
			vy = 0.0f;
		if (state == ON_JUMP_LEFT || state == ON_JUMPING_SHOOTING_LEFT || state == ON_SOMERSAULT_LEFT || state == ON_JUMP_AIM_UP_LEFT)
		{
			state = IDLE_LEFT;
		}
		else if (state == ON_JUMP_RIGHT || state == ON_JUMPING_SHOOTING_RIGHT || state == ON_SOMERSAULT_RIGHT || state == ON_JUMP_AIM_UP_RIGHT)
		{
			state = IDLE_RIGHT;
		}
	}
	else if (normaly < -0.1f) // tông phía dưới
	{
		if (vy > 0.0f)// đang bay lên => văng xuống
			vy *= -1;
	}

	if (normaly != 0)
	{
		pos_x += vx * (CollisionTimeScale)* DeltaTime;
		pos_y += vy * (CollisionTimeScale)* DeltaTime;
	}
}

// Phản xạ khi va chạm với ground
void Samus::SlideFromGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{
	//ResponseFrom(target, _DeltaTime, collisionTimeScale);
	// lỡ đụng 2,3 ground mà chạy cái này nhiều lần sẽ rất sai
	// "góc lag" sẽ làm đi luôn vào trong tường


	if (normalx > 0.1f)	// tông bên phải gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetRight() - this->collider->GetLeft()) + 0.1f;
		pos_x -= vx*DeltaTime;
		//vx = 0.0f;
	}

	else if (normalx < -0.1f)// tông bên trái gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetLeft() - this->collider->GetRight()) - 0.1f;
		pos_x -= vx*DeltaTime;
		//vx = 0.0f;
	}

	if (normaly > 0.1f) // trên xuống (không vào normaly được)
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
		//pos_y -= vy*DeltaTime;
		vy = 0;

		// Xử lý trạng thái cho samus
		if (state == ON_JUMP_LEFT || state == ON_JUMPING_SHOOTING_LEFT || state == ON_SOMERSAULT_LEFT || state == ON_JUMP_AIM_UP_LEFT)
		{
			state = IDLE_LEFT;
		}
		else if (state == ON_JUMP_RIGHT || state == ON_JUMPING_SHOOTING_RIGHT || state == ON_SOMERSAULT_RIGHT || state == ON_JUMP_AIM_UP_RIGHT)
		{
			state = IDLE_RIGHT;
		}

	}
	else if (normaly < -0.1f)	// tông ở dưới lên
	{
		//this->pos_y = (target->pos_y + target->collider->GetTop() - this->collider->GetBottom()) - 0.1f;
		pos_y -= vy*DeltaTime;
		vy = 0;
	}
	return;
}//----------------------------------