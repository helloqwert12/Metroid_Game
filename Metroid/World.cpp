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

	bullets = new BulletManager(this, STANDARD);
	bullets->InitPosition(samus->GetPosX(), samus->GetPosY());
	missiles = new BulletManager(this, MISSILE);
	missiles->InitPosition(samus->GetPosX(), samus->GetPosY());
	sentrybullets = new BulletManager(this, SENTRY);

	collisionGroup = new GroupObject(this);

	enemyGroup = new GroupObject(this);

	hog_yellow = new Bedgehog(spriteHandler, this, BEDGEHOG_YELLOW);
	hog_pink = new Bedgehog(spriteHandler, this, BEDGEHOG_PINK);
	bird = new Bird(spriteHandler, this, BIRD);
	block = new Block(spriteHandler, this, BLOCK);

	sentry = new Sentry(spriteHandler, this, SENTRY_LEFT);
	enemyGroup->AddGameObject(hog_yellow);
	enemyGroup->AddGameObject(hog_pink);
	enemyGroup->AddGameObject(bird);
	enemyGroup->AddGameObject(block);
	enemyGroup->AddGameObject(sentry);
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

	bullets->Update(t);
	missiles->Update(t);
	sentrybullets->Update(t);

	quadtreeGroup->GetCollisionObjectQTree();
	// Cập nhật các đối tượng có khả năng va chạm trong frame này
	collisionGroup->GetCollisionObjects();

	collisionGroup->Update(t);

	hog_yellow->Update(t);
	hog_pink->Update(t);
	block->Update(t);
	bird->Update(t);
	sentry->Update(t);
}

void World::Render()
{
	samus->Render();
	//zoomer->Render();
	bullets->Render();
	missiles->Render();
	sentrybullets->Render();
	quadtreeGroup->Render();
	hog_yellow->Render();
	hog_pink->Render();
	block->Render();
	bird->Render();
	sentry->Render();
	collisionGroup->Render();
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	samus->InitSprites(d3ddv);
	bullets->InitSprites(d3ddv);
	missiles->InitSprites(d3ddv);
	sentrybullets->InitSprites(d3ddv);
}
