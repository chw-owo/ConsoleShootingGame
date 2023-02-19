#include "Load.h"
#include "Render.h"
#include "Extern.h"
#include "UtilFileData.h"
#include "Game.h"
#include <Windows.h>
#include <iostream>

void UpdateLoad()
{
	// input section
	GetKeyLoad();

	// logic section
	//LoadLoadData();
	LoadGameData();

	// render section
	// rd_BufferClear();
	// rd_DataToBuffer();
	// rd_BufferFlip();
}

void GetKeyLoad()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		g_Scene = TITLE;
	}
}

void LoadLoadData()
{

}

void LoadGameData()
{
	int32 resultSize = 0;

	// Load Current Stage Data by StageInfo.txt
	char stageDataRoot[ROOT_LEN];
	LoadTokenedData(sceneFileRoot[GAME], stageDataRoot,
		resultSize, GET_ROOT_ONE, g_Stage);

	// Load Data Root by Stage.txt
	char gameDataRoot[DATA_END][ROOT_CNT][ROOT_LEN];
	LoadTokenedData(stageDataRoot, gameDataRoot,
		resultSize, GET_GAMEDATA);
	enemyDataCnt = resultSize;

	// Load Pos Data
	LoadOriginData(gameDataRoot[DATA_POS][0], posData, csSize);

	// Load Player Data
	LoadTokenedData(gameDataRoot[DATA_PLAYER][0], &player,
		resultSize, GET_DATA_PLAYER);

	// Load Bullet Data
	LoadTokenedData(gameDataRoot[DATA_BULLET][0], bullets,
		resultSize, GET_DATA_BULLET);

	// Load Enemy Data
	int32 dataSize = enemyDataCnt * sizeof(EnemyData);
	enemyData = static_cast<EnemyData*>(malloc(dataSize));
	memset(enemyData, 0, dataSize);

	for (int i = 0; i < enemyDataCnt; i++)
	{
		LoadTokenedData(gameDataRoot[DATA_ENEMY][i], enemyData + i,
			resultSize, GET_DATA_ENEMY);

		(enemyData + i)->max = atoi(gameDataRoot[DATA_ENEMY_NUM][i]);
	}
	
	InitialEnemy();
	ConvertStageToString();
	
	g_Scene = GAME;
}

void InitialEnemy()
{
	int32 iX = 0;
	int32 iY = 0;
	int enemyMax = 0;

	for (int i = 0; i < enemyDataCnt; i++)
	{
		enemyMax = (enemyData + i)->max;
		(enemyData + i)->enemies
			= static_cast<Enemy*>(malloc(sizeof(Enemy) * enemyMax));
	}

	EnemyData* tmp;
	Enemy* enemy;

	for (int i = 0; i < csSize; i++)
	{
		if (*(posData + i) == ' ')
		{
			iX++;
		}
		else if (*(posData + i) == '\n')
		{
			iY++;
			iX = 0;
		}
		else
		{
			iX++;

			for (int j = 0; j < enemyDataCnt; j++)
			{
				if (*(posData + i) == *(enemyData + j)->name)
				{
					tmp = enemyData + j;
					enemy = (tmp->enemies) + (tmp->cnt);

					enemy->bDead = false;
					enemy->iX = iX;
					enemy->iY = iY;
					enemy->hp = tmp->totalHp;

					tmp->cnt++;
				}
			}
		}
	}
}

void ConvertStageToString()
{
	sprintf_s(strStage, INFO_SIZE, "Stage: %d", g_Stage + 1);
}