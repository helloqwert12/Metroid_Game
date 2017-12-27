#pragma once
class Bullet;
class BulletManager;
class World;
class Collider;
class Metroid;
class Sprite;
class Samus;
class GameObject;
class GroupObject;
class Enemy;
class QNode;
class Loader;
class Brick;
class Bedgehog;
class Block;

//================ SCREEN RESOLUTION ================
#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12
//================ END RESOLUTION ====================

//================ FACTOR OF QUADTREE NODE ===========
#define NODE_FACTOR 8;

//================== SAMUS ===================
#define SHOOTING_SPEED 15
#define SAMUS_SPEED 0.25f
//#define SAMUS_SPEED 0.05f

#define SAMUS_SPRITES_PATH L"sprites\\samus\\samus_sprites.png"

#define APPEARING "sprites\\samus\\APPEARING.txt"
#define RUNNING_LEFT "sprites\\samus\\RUNNING_LEFT.txt"
#define RUNNING_RIGHT "sprites\\samus\\RUNNING_RIGHT.txt"
#define JUMP_LEFT "sprites\\samus\\JUMP_LEFT.txt"
#define JUMP_RIGHT "sprites\\samus\\JUMP_RIGHT.txt"
#define RUN_SHOOTING_LEFT "sprites\\samus\\RUN_SHOOTING_LEFT.txt"
#define RUN_SHOOTING_RIGHT "sprites\\samus\\RUN_SHOOTING_RIGHT.txt"
#define RUN_AIM_UP_LEFT "sprites\\samus\\RUN_AIM_UP_LEFT.txt"
#define RUN_AIM_UP_RIGHT "sprites\\samus\\RUN_AIM_UP_RIGHT.txt"
#define IDLE_AIM_UP_LEFT "sprites\\samus\\IDLE_AIM_UP_LEFT.txt"
#define IDLE_AIM_UP_RIGHT "sprites\\samus\\IDLE_AIM_UP_RIGHT.txt"
#define STANDING_LEFT "sprites\\samus\\STANDING_LEFT.txt"
#define STANDING_RIGHT "sprites\\samus\\STANDING_RIGHT.txt"
#define MORPH_BALL_LEFT "sprites\\samus\\MORPH_BALL_LEFT.txt"
#define MORPH_BALL_RIGHT "sprites\\samus\\MORPH_BALL_RIGHT.txt"
#define SOMERSAULT_LEFT "sprites\\samus\\SOMERSAULT_LEFT.txt"
#define SOMERSAULT_RIGHT "sprites\\samus\\SOMERSAULT_RIGHT.txt"
#define JUMPING_SHOOTING_LEFT "sprites\\samus\\JUMP_SHOOTING_LEFT.txt"
#define JUMPING_SHOOTING_RIGHT "sprites\\samus\\JUMP_SHOOTING_RIGHT.txt"
#define JUMP_AIM_UP_LEFT "sprites\\samus\\JUMP_AIM_UP_LEFT.txt"
#define JUMP_AIM_UP_RIGHT "sprites\\samus\\JUMP_AIM_UP_RIGHT.txt"
#define STAND_SHOOTING_LEFT "sprites\\samus\\STAND_SHOOTING_LEFT.txt"
#define STAND_SHOOTING_RIGHT "sprites\\samus\\STAND_SHOOTING_RIGHT.txt"
#define STAND_SHOOTING_UP_LEFT "sprites\\samus\\STAND_SHOOTING_UP_LEFT.txt"
#define STAND_SHOOTING_UP_RIGHT "sprites\\samus\\STAND_SHOOTING_UP_RIGHT.txt"
#define JUMP_SHOOTING_UP_LEFT "sprites\\samus\\JUMP_SHOOTING_UP_LEFT.txt"
#define JUMP_SHOOTING_UP_RIGHT "sprites\\samus\\JUMP_SHOOTING_UP_RIGHT.txt"

#define APPEARING_WIDTH 32
#define APPEARING_HEIGHT 64
#define RUNNING_WIDTH 40
#define RUNNING_HEIGHT 64
#define JUMP_WIDTH 36
#define JUMP_HEIGHT 50
#define RUN_SHOOTING_WIDTH 50
#define RUN_SHOOTING_HEIGHT 62
#define RUN_AIM_UP_WIDTH 36
#define RUN_AIM_UP_HEIGHT 76
#define IDLE_AIM_UP_WIDTH 29
#define IDLE_AIM_UP_HEIGHT 77
#define STANDING_WIDTH 42
#define STANDING_HEIGHT 64
#define MORPH_BALL_WIDTH 24
#define MORPH_BALL_HEIGHT 26
#define RUN_SHOOTING_WIDTH 44
#define RUN_SHOOTING_HEIGHT 62
#define SOMERSAULT_WIDTH 38
#define SOMERSAULT_HEIGHT 46
#define JUMPING_SHOOTING_WIDTH 46
#define JUMPING_SHOOTING_HEIGHT 50
#define JUMP_AIM_UP_WIDTH 37
#define JUMP_AIM_UP_HEIGHT 64
#define STANDING_SHOOTING_WIDTH 38
#define STANDING_SHOOTING_HEIGHT 64
#define STANDING_SHOOTING_UP_WIDTH 29
#define STANDING_SHOOTING_UP_HEIGHT 72
#define JUMP_SHOOTING_UP_WIDTH 37
#define JUMP_SHOOTING_UP_HEIGHT 60

#define APPEARING_COUNT 5
#define RUNNING_COUNT 3
#define JUMP_COUNT 1
#define RUN_SHOOTING_COUNT 3
#define RUN_AIM_UP_COUNT 3
#define IDLE_AIM_UP_COUNT 1
#define STANDING_COUNT 1
#define MORPH_BALL_COUNT 4
#define RUN_SHOOTING_COUNT 3
#define SPRITE_PER_ROW 1
#define SOMERSAULT_COUNT 4
#define JUMPING_SHOOTING_COUNT 1
#define JUMP_AIM_UP_COUNT 1
#define STAND_SHOOTING_COUNT 1
#define STAND_SHOOTING_UP_COUNT 1
#define JUMP_SHOOTING_UP_COUNT 1

#define ANIMATE_RATE 15

#define JUMP_VELOCITY_BOOST 0.05f
#define JUMP_VELOCITY_BOOST_FIRST 0.6f
#define FALLDOWN_VELOCITY_DECREASE 0.07f
//================== END SAMUS ====================

//================== ENEMY =====================
//================== BEDGEHOG =====================
#define ENEMY_SPRITE_PATH L"sprites\\enemy\\metroid_enemies_sheet.png"
#define BEDGEHOG_WIDTH 36
#define BEDGEHOG_HEIGHT 32
#define BEDGEHOG_SPRITE_COUNT 2
#define BEDGEHOG_SPEED 0.05f;

//--YElLOW
#define BEDGEHOG_YELLOW_UP "sprites\\enemy\\BEDGEHOG_YELLOW_UP.txt"
#define BEDGEHOG_YELLOW_BOTTOM "sprites\\enemy\\BEDGEHOG_YELLOW_BOTTOM.txt"
#define BEDGEHOG_YELLOW_LEFT "sprites\\enemy\\BEDGEHOG_YELLOW_LEFT.txt"
#define BEDGEHOG_YELLOW_RIGHT "sprites\\enemy\\BEDGEHOG_YELLOW_RIGHT.txt"

//PINK
#define BEDGEHOG_PINK_UP "sprites\\enemy\\BEDGEHOG_PINK_UP.txt"
#define BEDGEHOG_PINK_BOTTOM "sprites\\enemy\\BEDGEHOG_PINK_BOTTOM.txt"
#define BEDGEHOG_PINK_LEFT "sprites\\enemy\\BEDGEHOG_PINK_LEFT.txt"
#define BEDGEHOG_PINK_RIGHT "sprites\\enemy\\BEDGEHOG_PINK_RIGHT.txt"
//================== END BEDGEHOG =================

//================== BIRD  =====================

#define BIRD_WIDTH 36
#define BIRD_HEIGHT 52

#define BIRD_FLY_SPRITE_COUNT 2

#define BIRD_FLY "sprites\\enemy\\BIRD_FLY.txt"

#define BIRD_STANDARD_ANIMATE_RATE 7
#define BIRD_BOOST_ANIMATE_RATE 20
//================== END BIRD =================

//================== BLOCK =====================

#define BLOCK_WIDTH 36
#define BLOCK_HEIGHT 20
#define BLOCK_SPRITE_COUNT 1
#define BLOCK_SPEED 0.0001f

//--YElLOW
#define BLOCK_LEFT "sprites\\enemy\\BLOCK_LEFT.txt"
#define BLOCK_RIGHT "sprites\\enemy\\BLOCK_RIGHT.txt"
//================== END BLOCK =================

//================== END ENEMY =================

//================= BRICK ====================
#define BRICK_1_PATH L"map\\brick_blue.png"
#define BRICK_1_WIDTH_COUNT 5
#define BRICK_1_HEIGHT_COUNT 4
#define BRICK_WIDTH 32
#define BRICK_HEIGHT 32

enum BRICK_TYPE
{
	BLUE = 1
};
//================ END BRICK ==================

//================ BOSS =======================

//=========== MOTHER BRAIN
enum MOTHERBRAIN_STATE
{
	UNBROKEN,
	BROKEN
};

//================ END BOSS ===================

//================ BULLET TYPE ================
enum BULLET_TYPE
{
	STANDARD,
	MISSILE
};
//================ END BULLET TYPE ============


//================ BULLET ===============
enum BULLET_DIRECTION
{
	NONE,
	ON_LEFT,
	ON_RIGHT,
	ON_UP,
	ON_BOTTOM,
	ON_TOPLEFT,
	ON_TOPRIGHT,
	ON_BOTTOMLEFT,
	ON_BOTTOMRIGHT
};
//================= END BULLET ===========

//================= OBJECT TYPE ================
enum OBJECT_TYPE
{
	SAMUS = 1,
	ENEMY = 2,
	BRICK = 3,
	PROJECTILE = 4
};
//================= END OBJECT TYPE ============

//================= ENEMY TYPE =================
enum ENEMY_TYPE
{
	//--TO DO: Bổ sung các type enemy
	BEDGEHOG_YELLOW,
	BEDGEHOG_PINK,
	BIRD,
	BLOCK
};
//================= END ENEMY TYPE =============

//================= EFFECT TYPE =============
#define EXPLOSION_SPRITE_PATH L"sprites\\enemy\\explosion.png"

#define EXPLOSION_WIDTH 64
#define EXPLOSION_HEIGHT 64

#define EXPLOSION_SPRITE_COUNT 3
//================= END ENEMY TYPE =============

//================= BOSSES =================
#define BOSS_SPRITE_PATH L"sprites\\bosses\\NES - Metroid - Bosses.png"

//================= MOTHER_BRAIN =================
#define MOTHER_BRAIN_WIDTH 160
#define MOTHER_BRAIN_HEIGHT 128
#define MOTHER_BRAIN_SPRITE_COUNT 8

#define MOTHER_BRAIN_HIT_WIDTH 96
#define MOTHER_BRAIN_HIT_HEIGHT 128
#define MOTHER_BRAIN_HIT_SPRITE_COUNT 2

//================= SENTRY =================
//================= SENTRY TYPE =================
enum SENTRY_TYPE
{
	SENTRY_LEFT,
	SENTRY_TOP,
	SENTRY_RIGHT
};
//================= END SENTRY TYPE =============

#define SENTRY_WIDTH 42
#define SENTRY_HEIGHT 42
#define SENTRY_SPRITE_COUNT 1

#define SENTRY_TOP_PATH "sprites\\bosses\\SENTRY_TOP.txt"
#define SENTRY_TOP_RIGHT_PATH "sprites\\bosses\\SENTRY_TOP_RIGHT.txt"
#define SENTRY_RIGHT_PATH "sprites\\bosses\\SENTRY_RIGHT.txt"
#define SENTRY_BOTTOM_RIGHT_PATH "sprites\\bosses\\SENTRY_BOTTOM_RIGHT.txt"
#define SENTRY_BOTTOM_PATH "sprites\\bosses\\SENTRY_BOTTOM.txt"
#define SENTRY_BOTTOM_LEFT_PATH "sprites\\bosses\\SENTRY_BOTTOM_LEFT.txt"
#define SENTRY_LEFT_PATH "sprites\\bosses\\SENTRY_LEFT.txt"
#define SENTRY_TOP_LEFT_PATH "sprites\\bosses\\SENTRY_TOP_LEFT.txt"

//================= SENTRY BULLET =================
#define SENTRY_BULLET_WIDTH 16
#define SENTRY_BULLET_HEIGHT 16
#define SENTRY_SPRITE_COUNT 1

#define SENTRY_BULLET_TOP_PATH "sprites\\bosses\\SENTRY_BULLET_TOP.txt"
#define SENTRY_BULLET_TOP_RIGHT_PATH "sprites\\bosses\\SENTRY_BULLET_TOP_RIGHT.txt"
#define SENTRY_BULLET_RIGHT_PATH "sprites\\bosses\\SENTRY_BULLET_RIGHT.txt"
#define SENTRY_BULLET_BOTTOM_RIGHT_PATH "sprites\\bosses\\SENTRY_BULLET_BOTTOM_RIGHT.txt"
#define SENTRY_BULLET_BOTTOM_PATH "sprites\\bosses\\SENTRY_BULLET_BOTTOM.txt"
#define SENTRY_BULLET_BOTTOM_LEFT_PATH "sprites\\bosses\\SENTRY_BULLET_BOTTOM_LEFT.txt"
#define SENTRY_BULLET_LEFT_PATH "sprites\\bosses\\SENTRY_BULLET_LEFT.txt"
#define SENTRY_BULLET_TOP_LEFT_PATH "sprites\\bosses\\SENTRY_BULLET_TOP_LEFT.txt"

//================= END SENTRY BULLET =============
#define SENTRY_BULLET_SPRITE_COUNT 1
#define SENTRY_BULLET_SPIRTE_PATH L"sprites\\bosses\\boss_sprtesheet.png"

#define SENTRY_BULLET_UP ""
#define SENTRY_BULLET_LEFT ""
#define SENTRY_BULLET_RIGHT ""
#define SENTRY_BULLET_BOTTOM ""
#define SENTRY_BULLET_TOPLEFT ""
#define SENTRY_BULLET_TOPRIGHT ""
#define SENTRY_BULLET_BOTTOMLEFT ""
#define SENTRY_BULLET_BOTTOMRIGHT ""
//================= END BULLET =============

//================= END SENTRY =============

//================= END MOTHER_BRAIN =============



//================= END BOSSES =============