#include "Metroid.h"
#include <time.h>
#include "trace.h"
#include "utils.h"
#include "Collision.h"
#include "BulletManager.h"
void Metroid::_InitBackground()
{
}

void Metroid::_InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	world->samus->InitSprites(d3ddv);
	//tiles->InitSprites(d3ddv);
	
	//tiles->InitSprites(d3ddv);
	world->bullets->InitSprites(d3ddv);
}

void Metroid::_InitPositions()
{
	world->samus->InitPostition();
	world->hog->InitPostition(1600, 90);
	//bulletManager->InitPosition(world->samus->GetPosX(), world->samus->GetPosY());
}


void Metroid::_Shoot(BULLET_DIRECTION dir)
{
	now_shoot = GetTickCount();
	if (start_shoot <= 0) //if shooting is active
	{
		start_shoot = GetTickCount();
		world->bullets->Next(dir);
	}
	else if ((now_shoot - start_shoot) > SHOOTING_SPEED * tick_per_frame)
	{
		//Reset start_shoot
		start_shoot = 0;
	}
}

Metroid::Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate):Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	//tiles = new Tiles();
	tick_per_frame = 1000 / _FrameRate;
	start_shoot = 0;

	//bulletManager = new BulletManager();
}


Metroid::~Metroid()
{
	//delete(tiles);
	
	//delete(bulletManager);

	delete(first_room);
}

void Metroid::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	//---------Khởi tạo spriteHandler---------------
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	//-----------------------
	world = new World(spriteHandler, this);
	srand((unsigned)time(NULL));
	_InitSprites(d3ddv);
	_InitPositions();

	first_room = new Loader(spriteHandler, 1, world);
	first_room->Load();
	Game::gameSound->playSoundLoop(BACKGROUND_INTRO);
}

void Metroid::Update(float Delta)
{
	switch (screenMode)
	{
		// intro
	case GAMEMODE_INTRO:
		UpdateIntro(_DeltaTime);
		break;
		// start screen
	case GAMEMODE_START:
		break;
		// game running
	case GAMEMODE_GAMERUN:
		UpdateFrame(_DeltaTime);
		break;
	default:
		break;
	}
}

void Metroid::UpdateIntro(float Delta)
{
	//DWORD now = GetTickCount();
	//if (now - Delta > 1000 / ANIMATE_RATE)
	//{
	//	intro->Next();
	//	Delta = now;
	//}
}

void Metroid::UpdateFrame(float Delta)
{
	world->Update(Delta);
	//bulletManager->Update(Delta, world->samus->GetPosX(), world->samus->GetPosY());
}

void Metroid::Render(LPDIRECT3DDEVICE9 d3ddv)
{
	switch (screenMode)
	{
		// intro
	case GAMEMODE_INTRO:
		RenderIntro(d3ddv);
		break;
		// start screen
	case GAMEMODE_START:
		RenderStartScreen(d3ddv);
		break;
		// game running
	case GAMEMODE_GAMERUN:
		RenderFrame(d3ddv);	
		break;
	default:
		break;
	}
}

void Metroid::RenderStartScreen(LPDIRECT3DDEVICE9 d3ddv) 
{
	// Background
	d3ddv->StretchRect(
		startscreen,			// from 
		NULL,				// which portion?
		_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	startscreen = CreateSurfaceFromFile(_d3ddv, STARTSCREEN_FILE);
}

void Metroid::RenderIntro(LPDIRECT3DDEVICE9 d3ddv)
{
	//spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//intro = new Sprite(spriteHandler, INTRO_FILE, INTRO, 640, 372, 1, 154);
	//spriteHandler->End();
}

void Metroid::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)
{		
	world->Render();
	//first_room->TestRenderMapGO();
	//bulletManager->Render();
	//tiles->_Render(xc, world->samus->GetPosX());
	
}

void Metroid::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	
	if (IsKeyDown(DIK_RIGHT))
	{
		world->samus->setNormalx(1.0f);
		world->samus->setgravity(FALLDOWN_VELOCITY_DECREASE);
		world->samus->SetVelocityXLast(world->samus->GetVelocityX());
		world->samus->SetVelocityX(SAMUS_SPEED);	
		if (world->samus->GetState() != ON_MORPH_LEFT && world->samus->GetState() != ON_MORPH_RIGHT
			&& world->samus->GetState() != ON_JUMP_LEFT && world->samus->GetState() != ON_JUMP_RIGHT
			&& world->samus->GetState() != ON_JUMPING_SHOOTING_LEFT && world->samus->GetState() != ON_JUMPING_SHOOTING_RIGHT
			&& world->samus->GetState() != ON_SOMERSAULT_LEFT /*&& samus->GetState() != ON_SOMERSAULT_RIGHT*/)
		{
			if (IsKeyDown(DIK_X))
			{
				Game::gameSound->playSound(JUMP);
				world->samus->setNormaly(1.0f);
				if (world->samus->GetState() != ON_SOMERSAULT_RIGHT /*&& samus->GetState() != ON_JUMP_AIM_UP_RIGHT*/)
				{
					start_jump = GetTickCount();
					now_jump = GetTickCount();
					world->samus->SetState(ON_SOMERSAULT_RIGHT);
					world->samus->SetVelocityY(world->samus->GetVelocityY() + JUMP_VELOCITY_BOOST_FIRST);
				}
				else
				{
					now_jump = GetTickCount();
					if ((now_jump - start_jump) <= 20 * tick_per_frame)
					{
						world->samus->SetVelocityY(world->samus->GetVelocityY() + JUMP_VELOCITY_BOOST);
					}
				}
			}
			else if (world->samus->GetState() != ON_SOMERSAULT_RIGHT)
				world->samus->SetState(RIGHTING);
		}
	}
	else if (IsKeyDown(DIK_LEFT))
	{
		world->samus->setgravity(FALLDOWN_VELOCITY_DECREASE);
		world->samus->setNormalx(-1.0f);
		world->samus->SetVelocityXLast(world->samus->GetVelocityX());
		world->samus->SetVelocityX(-SAMUS_SPEED);
		if (world->samus->GetState() != ON_MORPH_LEFT && world->samus->GetState() != ON_MORPH_RIGHT
			&& world->samus->GetState() != ON_JUMP_LEFT && world->samus->GetState() != ON_JUMP_RIGHT
			&& world->samus->GetState() != ON_JUMPING_SHOOTING_LEFT && world->samus->GetState() != ON_JUMPING_SHOOTING_RIGHT
			/*&& samus->GetState() != ON_SOMERSAULT_LEFT*/ && world->samus->GetState() != ON_SOMERSAULT_RIGHT)
		{
			if (IsKeyDown(DIK_X))
			{
				Game::gameSound->playSound(JUMP);
				world->samus->setNormaly(1.0f);
				if (world->samus->GetState() != ON_SOMERSAULT_LEFT /*&& samus->GetState() != ON_JUMP_AIM_UP_LEFT*/)
				{
					start_jump = GetTickCount();
					now_jump = GetTickCount();
					world->samus->SetState(ON_SOMERSAULT_LEFT);
					world->samus->SetVelocityY(world->samus->GetVelocityY() + JUMP_VELOCITY_BOOST_FIRST);
				}
				else
				{
					now_jump = GetTickCount();
					if ((now_jump - start_jump) <= 20 * tick_per_frame)
					{
						world->samus->SetVelocityY(world->samus->GetVelocityY() + JUMP_VELOCITY_BOOST);
					}
				}
			}
			else if (world->samus->GetState() != ON_SOMERSAULT_LEFT)
				world->samus->SetState(LEFTING);
		}
	}
	else if (IsKeyDown(DIK_X))
	{
		Game::gameSound->playSound(JUMP);
		world->samus->setgravity(FALLDOWN_VELOCITY_DECREASE);
		world->samus->setNormaly(1.0f);
		if (world->samus->GetVelocityXLast() < 0)
		{
			if (world->samus->GetState() != ON_JUMP_LEFT && world->samus->GetState() != ON_SOMERSAULT_LEFT 
				&& world->samus->GetState() != ON_JUMPING_SHOOTING_LEFT && world->samus->GetState() != ON_JUMP_AIM_UP_LEFT)
			{
				start_jump = GetTickCount();
				now_jump = GetTickCount();
				if (world->samus->GetState() == IDLING_AIM_UP_LEFT)
					world->samus->SetState(ON_JUMP_AIM_UP_LEFT);
				else
					world->samus->SetState(ON_JUMP_LEFT);
				world->samus->SetVelocityY(world->samus->GetVelocityY() + JUMP_VELOCITY_BOOST_FIRST);
			}
			else
			{
				now_jump = GetTickCount();
				if ((now_jump - start_jump) <= 20 * tick_per_frame)
				{
					world->samus->SetVelocityY(world->samus->GetVelocityY() + JUMP_VELOCITY_BOOST);
				}
			}
		}
		if (world->samus->GetVelocityXLast() > 0)
		{
			if (world->samus->GetState() != ON_JUMP_RIGHT  && world->samus->GetState() != ON_SOMERSAULT_RIGHT 
				&& world->samus->GetState() != ON_JUMPING_SHOOTING_RIGHT && world->samus->GetState() != ON_JUMP_AIM_UP_RIGHT)
			{
				start_jump = GetTickCount();
				now_jump = GetTickCount();
				if (world->samus->GetState() == IDLING_AIM_UP_RIGHT)
					world->samus->SetState(ON_JUMP_AIM_UP_RIGHT);
				else
					world->samus->SetState(ON_JUMP_RIGHT);
				world->samus->SetVelocityY(world->samus->GetVelocityY() + JUMP_VELOCITY_BOOST_FIRST);
			}
			else
			{
				now_jump = GetTickCount();
				if ((now_jump - start_jump) <= 20 * tick_per_frame)
				{
					world->samus->SetVelocityY(world->samus->GetVelocityY() + JUMP_VELOCITY_BOOST);
					
				}
			}
		}
	}
	else
	{
		world->samus->SetVelocityX(0);
		
		if (world->samus->GetVelocityXLast() < 0)
		{
			if (world->samus->GetState() != ON_MORPH_LEFT && world->samus->GetState() != ON_JUMP_LEFT && world->samus->GetState() != ON_JUMP_RIGHT
				&& world->samus->GetState() != ON_JUMPING_SHOOTING_LEFT && world->samus->GetState() != ON_JUMPING_SHOOTING_RIGHT
				&& world->samus->GetState() != ON_SOMERSAULT_LEFT && world->samus->GetState() != ON_SOMERSAULT_RIGHT
				&& world->samus->GetState() != ON_JUMP_AIM_UP_LEFT)
			{
				world->samus->SetState(IDLE_LEFT);
				world->samus->ResetAllSprites();
			}
		}
		else
		{
			if (world->samus->GetState() != ON_MORPH_RIGHT && world->samus->GetState() != ON_JUMP_LEFT && world->samus->GetState() != ON_JUMP_RIGHT
				&& world->samus->GetState() != ON_JUMPING_SHOOTING_LEFT && world->samus->GetState() != ON_JUMPING_SHOOTING_RIGHT
				&& world->samus->GetState() != ON_SOMERSAULT_LEFT && world->samus->GetState() != ON_SOMERSAULT_RIGHT
				&& world->samus->GetState() != ON_JUMP_AIM_UP_RIGHT)
			{
				world->samus->SetState(IDLE_RIGHT);
				world->samus->ResetAllSprites();
			}
		}
	}

		if (IsKeyDown(DIK_UP))
		{
			if (world->samus->GetState() == LEFTING)
				world->samus->SetState(AIMING_UP_LEFT);
			if (world->samus->GetState() == RIGHTING)
				world->samus->SetState(AIMING_UP_RIGHT);
			if (world->samus->GetState() == IDLE_LEFT)
				world->samus->SetState(IDLING_AIM_UP_LEFT);
			if (world->samus->GetState() == IDLE_RIGHT)
				world->samus->SetState(IDLING_AIM_UP_RIGHT);
			if (world->samus->GetState() == ON_JUMP_LEFT/* || world->samus->GetState() == ON_JUMPING_SHOOTING_LEFT*/)
			{
				world->samus->SetState(ON_JUMP_AIM_UP_LEFT);
				Game::gameSound->playSound(JUMP);
			}
			if (world->samus->GetState() == ON_JUMP_RIGHT/* || world->samus->GetState() == ON_JUMPING_SHOOTING_RIGHT*/)
			{
				world->samus->SetState(ON_JUMP_AIM_UP_RIGHT);
				Game::gameSound->playSound(JUMP);
			}
			if (world->samus->GetState() == ON_MORPH_LEFT)
				world->samus->SetState(IDLE_LEFT);
			if (world->samus->GetState() == ON_MORPH_RIGHT)
				world->samus->SetState(IDLE_RIGHT);
		}

		if (IsKeyDown(DIK_Z))
		{
			//Để mặc định đạn thường trước
			Game::gameSound->playSound(SHOOT_BULLET);
			//State Đứng bắn lên
			if (world->samus->GetState() == IDLING_AIM_UP_LEFT)
			{
				world->samus->SetState(IDLING_SHOOTING_UP_LEFT);

				_Shoot(ON_UP);
			}
			if (world->samus->GetState() == IDLING_AIM_UP_RIGHT)
			{
				world->samus->SetState(IDLING_SHOOTING_UP_RIGHT);

				_Shoot(ON_UP);
			}
			//State Chạy bắn lên
			if (world->samus->GetState() == AIMING_UP_LEFT)
			{
				world->samus->SetState(AIMING_UP_LEFT);
				_Shoot(ON_UP);
			}
			if (world->samus->GetState() == AIMING_UP_RIGHT)
			{
				world->samus->SetState(AIMING_UP_RIGHT);
				_Shoot(ON_UP);
			}
			//State Nhảy bắn lên => bug
			if (world->samus->GetState() == ON_JUMP_AIM_UP_LEFT)
			{
				world->samus->SetState(ON_JUMP_SHOOTING_UP_LEFT);

				_Shoot(ON_UP);
			}
			if (world->samus->GetState() == ON_JUMP_AIM_UP_RIGHT)
			{
				world->samus->SetState(ON_JUMP_SHOOTING_UP_RIGHT);

				_Shoot(ON_UP);
			}
			//State nhảy bắn
			if (world->samus->GetState() == ON_JUMP_LEFT || world->samus->GetState() == ON_SOMERSAULT_LEFT || world->samus->GetState() == ON_JUMPING_SHOOTING_LEFT)
			{
				world->samus->SetState(ON_JUMPING_SHOOTING_LEFT);

				_Shoot(ON_LEFT);
			}
			if (world->samus->GetState() == ON_JUMP_RIGHT || world->samus->GetState() == ON_SOMERSAULT_RIGHT || world->samus->GetState() == ON_JUMPING_SHOOTING_RIGHT)
			{
				world->samus->SetState(ON_JUMPING_SHOOTING_RIGHT);

				_Shoot(ON_RIGHT);
			}
			//State chạy bắn
			if (world->samus->GetState() == LEFTING)
			{
				world->samus->SetState(ON_RUN_SHOOTING_LEFT);

				_Shoot(ON_LEFT);
			}
			if (world->samus->GetState() == RIGHTING)
			{
				world->samus->SetState(ON_RUN_SHOOTING_RIGHT);

				_Shoot(ON_RIGHT);
			}
			//State đứng bắn
			if (world->samus->GetState() == IDLE_LEFT)
			{
				world->samus->SetState(IDLING_SHOOTING_LEFT);

				_Shoot(ON_LEFT);
			}
			if (world->samus->GetState() == IDLE_RIGHT)
			{
				world->samus->SetState(IDLING_SHOOTING_RIGHT);

				_Shoot(ON_RIGHT);
			}
		}

	if (world->samus->GetVelocityY() < 0)
	{
		world->samus->setNormaly(-1.0f);
	}
}

void Metroid::OnKeyDown(int KeyCode)
{
	switch (screenMode)
	{
		// intro
	case GAMEMODE_INTRO:
	{
		if (KeyCode == DIK_RETURN)
		{
			this->screenMode = GAMEMODE_START;
		}
		break;
	}
	// start screen
	case GAMEMODE_START://------------------------------------------------
	{
		if (KeyCode == DIK_RETURN)
		{
			this->screenMode = GAMEMODE_GAMERUN;
			Game::gameSound->stopSound(BACKGROUND_INTRO);
			Game::gameSound->playSoundLoop(BACKGROUND_MAP);
		}
	}
	break;
	// game running
	case GAMEMODE_GAMERUN:// -------------------------------------------------
	{
		switch (KeyCode)
		{
		case DIK_DOWN:
			//if samus is idle then do morph
			if (world->samus->GetState() == IDLE_LEFT)
			{
				world->samus->SetVelocityX(0);
				world->samus->ResetAllSprites();
				world->samus->SetState(ON_MORPH_LEFT);
			}
			else if (world->samus->GetState() == IDLE_RIGHT)
			{
				world->samus->SetVelocityX(0);
				world->samus->ResetAllSprites();
				world->samus->SetState(ON_MORPH_RIGHT);
			}
			else if (world->samus->GetState() == ON_MORPH_LEFT) //otherwise, reset to idle (left of right)
			{
				world->samus->SetVelocityX(0);
				world->samus->ResetAllSprites();
				world->samus->SetState(IDLE_LEFT);
				//world->samus->setDirection(DirectCollision::RIGHT);
			}
			else if (world->samus->GetState() == ON_MORPH_RIGHT)
			{
				world->samus->SetVelocityX(0);
				world->samus->ResetAllSprites();
				world->samus->SetState(IDLE_RIGHT);
				//world->samus->setDirection(DirectCollision::LEFT);
			}
			break;
			//case DIK_X:
			//	//**********************************************************************************
			//	// [CAUTION!!!] Vi pos_y chua chinh theo toa do World, code duoi day chi la tam thoi,
			//	// se cap nhat lai sau
			//	if (samus->GetPosY() >= GROUND_Y)
			//	{
			//		if (samus->GetVelocityXLast() < 0)
			//		{
			//			samus->SetState(ON_JUMP_LEFT);
			//			samus->SetVelocityY(samus->GetVelocityY() - JUMP_VELOCITY_BOOST);
			//		}
			//		else if (samus->GetVelocityXLast() > 0)
			//		{
			//			samus->SetState(ON_JUMP_RIGHT);
			//			samus->SetVelocityY(samus->GetVelocityY() - JUMP_VELOCITY_BOOST);
			//		}
			//	}
			//	//***********************************************************************************
			//	break;
		case DIK_LEFT:
			/*if (samus->GetState() == ON_JUMP_RIGHT)
				samus->SetState(ON_JUMP_LEFT);*/
			if (world->samus->GetState() == ON_MORPH_RIGHT)
				world->samus->SetState(ON_MORPH_LEFT);
			/*else if (samus->GetState() != ON_MORPH_LEFT && samus->GetState() != ON_JUMP_LEFT && samus->GetState() != ON_JUMP_RIGHT
				&& samus->GetState() != ON_SOMERSAULT_RIGHT)
				samus->SetState(LEFTING);*/
			break;
		case DIK_RIGHT:
			/*if (samus->GetState() == ON_JUMP_LEFT)
				samus->SetState(ON_JUMP_RIGHT);*/
			if (world->samus->GetState() == ON_MORPH_LEFT)
				world->samus->SetState(ON_MORPH_RIGHT);
			/*else if (world->samus->GetState() != ON_MORPH_RIGHT && world->samus->GetState() != ON_JUMP_LEFT && world->samus->GetState() != ON_JUMP_RIGHT
				&& world->samus->GetState() != ON_SOMERSAULT_LEFT)
				world->samus->SetState(RIGHTING);*/
			break;
		}
	}

	}


}

DWORD Metroid::GetTickPerFrame()
{
	return tick_per_frame;
}
