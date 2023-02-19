#pragma once
#include "Extern.h"
#include "Types.h"
#include "Game.h"

enum LOAD_FLAG {

	GET_ROOT_ALL,
	GET_ROOT_ONE,
	GET_GAMEDATA,
	GET_DATA_ENEMY,
	GET_DATA_PLAYER,
	GET_DATA_BULLET
};

void SetStageData(int32 stage);
void LoadOriginData(char* fileName, void* output, int32& resultSize);
void LoadTokenedData(char* fileName, void* output, int32& resultSize, LOAD_FLAG flag, int32 idx = 0);

void TokenizeRootAll(char* fileData, char sep[], int32& fileNum, char output[][ROOT_LEN]);
void TokenizeRootOne(char* fileData, char sep[], int32 idx, char* output);
void TokenizeGameData(char* fileData, char sep[], int32& fileNum, char output[][ROOT_CNT][ROOT_LEN]);

void TokenizeEnemyData(char* fileData, char sep[], EnemyData* output);
void TokenizePlayerData(char* fileData, char sep[], Player* output);
void TokenizeBulletData(char* fileData, char sep[], Bullet* output);