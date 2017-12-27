#include "Gate.h"
#include "Game.h"
#include <vector>
#include "GroupObject.h"
#include "World.h"
#include <time.h>

void Gate::Render()
{
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	switch (state)
	{
	case CLOSE:
		left_gate->Render(pos_x, pos_y); //Kiểm tra State là Close thì sẽ Render Gate
		break;
	}
	spriteHandler->End();
}

void Gate::Destroy()
{
	//Ngưng active
	isActive = false;

	//--TO DO: Đưa Gate ra khỏi viewport
}

Gate::Gate()
{
}

Gate::Gate(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	left_gate = NULL;

	//Set type
	this->type = GATE;  //Type of GameObject :GATE
	width = 32;
	height = 96;
	state = CLOSE;

	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();
	//Collider
	this->collider = new Collider();
	this->collider->SetCollider(0, 0, -this->height, this->width);
	this->SetHealth(-10); //Khởi tạo Health cua Gate = 10 (Gate Open) , nếu Health của Gate <= 0 (Gate Close)

}

Gate::~Gate()
{
	delete(left_gate);
}

void Gate::InitSprites()
{
	//Create instance of sprites
	left_gate = new Sprite(spriteHandler, GATE_SPRITES_PATH, GATE_LEFT, GATE_WIDTH, GATE_HEIGHT, 1, 1);
}

void Gate::InitPostition()
{
	//--TO DO: This code will be edited soon
	pos_x = 2496;   //Khoi tao vi tri x,y cua Gate
	pos_y = 288;

	//Init state of Gate
	state = CLOSE;

}

GATE_STATE Gate::GetState()
{
	return state;
}

void Gate::SetState(GATE_STATE value)
{
	state = value;
}
void Gate::Update(int t)
{
	if (!isActive) return;

	//Xử lí khi bắn đạn thì Health của Gate giảm đến <=0

	if (this->GetHealth() <= 0)  //Neu Health cua Gate <= 0 thi khong render Gate ,state tu Close sang Open
	{
		state = OPEN;
		this->isActive = false;
		this->SetHealth(10);  //Set lai Health nhu luc dau
	}

	//LƯU Ý:Mở comment lệnh If dưới đây khi cần chuyển trạng thái từ cửa Mở sang Đóng sau 1 khoảng thời gian 

	//if (state == OPEN)
	//{
	//	if ((double)(clock() - last_time) / CLOCKS_PER_SEC >=5) 	//Sau một khoảng thời gian cửa Mở thì sẽ đưa sang cửa Đóng ,
	//	{															
	//		state = CLOSE;										
	//		this->isActive = true;
	//	}
	//}
}