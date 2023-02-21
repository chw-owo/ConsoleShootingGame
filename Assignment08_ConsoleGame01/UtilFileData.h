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

void SetStageData(const int32 &stage);
void LoadOriginData(const char* fileName, void* output, int32& resultSize);
void LoadTokenedData(const char* fileName, void* output, int32& resultSize, const LOAD_FLAG& flag, const int32& idx = 0);

void TokenizeRootAll(char* fileData, const char* sep, int32& fileNum, char output[][ROOT_LEN]);
void TokenizeRootOne(char* fileData, const char* sep, const int32& idx, char output[]);
void TokenizeGameData(char* fileData, const char* sep, int32& fileNum, char output[][ROOT_CNT][ROOT_LEN]);

void TokenizeEnemyData(char* fileData, const char* sep, EnemyData* output);
void TokenizePlayerData(char* fileData, const char* sep, Player* output);
void TokenizeBulletData(char* fileData, const char* sep, Bullet* output);