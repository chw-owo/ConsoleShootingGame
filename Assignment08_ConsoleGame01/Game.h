#pragma once
#include "Extern.h"
#include "Render.h"

#define BULLET_CNT 32

enum GAMEDATA
{
	DATA_POS,
	DATA_PLAYER,
	DATA_BULLET,
	DATA_ENEMY,
	DATA_ENEMY_NUM,
	DATA_END
};

struct Player
{
	bool bDead = false;
	char icon[ICON_SIZE];
	int32 iX = dfSCREEN_WIDTH / 2;
	int32 iY = (dfSCREEN_HEIGHT / 4) * 3;
	int32 iTotalHp;
	int32 iHp;
};

struct Bullet
{
	bool bDead = false;
	char icon[ICON_SIZE];
	int32 iX = -1;
	int32 iY = -1;
	int32 iAttack;
	float iSpeed;

};

struct Enemy
{
	bool bDead = false;
	int32 iX;
	int32 iY;
	int32 hp;
};

struct EnemyData
{
	char name[NAME_SIZE];
	char icon[ICON_SIZE];
	Enemy* enemies;
	int32 totalHp;
	int32 max;
	int32 cnt;
};

extern Player player;
extern Bullet bullets[BULLET_CNT];
extern char posData[DATA_SIZE];
extern EnemyData* enemyData;

extern int32 csSize;
extern int32 enemyDataCnt;
extern char strStage[INFO_SIZE];

// Main
void UpdateGame();

// Get Input
void GetKeyGame();

// Update
void UpdateBullet();
void UpdateEnemy();
void UpdatePlayer();

// Render
void GameDataToBuffer();

// Scene Change
void FreeHeapData();
void GameClear();
void GameOver();
