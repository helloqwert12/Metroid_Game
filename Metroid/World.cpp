#include "World.h"
#include "GroupObject.h"
#include "Brick.h"
#include "Camera.h"
#include "BulletManager.h"

World::World()
{
}

World::World(LPD3DXSPRITE spriteHandler, Metroid * metroid)
{
	//Gán
	this->spriteHandler = spriteHandler;
	this->metroid = metroid;

	//Khởi tạo các đối tượng trong World
	samus = new Samus(spriteHandler, this);
	//brick = new Brick(spriteHandler, this, BLUE, 1, 32*3, 32*10);

	quadtreeGroup = new GroupObject(this);
	rootQNode = NULL;

	bullets = new BulletManager(this);
	bullets->InitPosition(samus->GetPosX(), samus->GetPosY());

	collisionGroup = new GroupObject(this);

	enemyGroup = new GroupObject(this);

	hog_yellow = new Bedgehog(spriteHandler, this, BEDGEHOG_YELLOW);
	hog_pink = new Bedgehog(spriteHandler, this, BEDGEHOG_PINK);
	bird = new Bird(spriteHandler, this, BIRD);
	block = new Block(spriteHandler, this, BLOCK);
	enemyGroup->AddGameObject(hog_yellow);
	enemyGroup->AddGameObject(hog_pink);
	enemyGroup->AddGameObject(bird);
	enemyGroup->AddGameObject(block);
}


World::~World()
{
	delete(samus);
}

void World::Update(float t)
{
	samus->Update(t);
	// Cập nhật các đối tượng hiển thị trong camera

	//zoomer->Update(t);

	bullets->Update(t, samus->GetPosX(), samus->GetPosY() + 11);

	quadtreeGroup->GetCollisionObjectQTree();
	// Cập nhật các đối tượng có khả năng va chạm trong frame này
	collisionGroup->GetCollisionObjects();

	collisionGroup->Update(t);

	hog_yellow->Update(t);
	hog_pink->Update(t);
	block->Update(t);
	bird->Update(t);
}

void World::Render()
{
	samus->Render();
	//zoomer->Render();
	bullets->Render();
	quadtreeGroup->Render();
	hog_yellow->Render();
	hog_pink->Render();
	block->Render();
	bird->Render();
	collisionGroup->Render();
}
