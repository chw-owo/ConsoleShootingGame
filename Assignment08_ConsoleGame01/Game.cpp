#include "Game.h"
#include "UtilFileData.h"
#include <Windows.h>
#include <time.h>

enum GAMESTATE
{
	STATE_PLAY,
	STATE_CLEAR,
	STATE_OVER
};

int32 gameStageFlag = STATE_PLAY;
char strStage[INFO_SIZE];
Player player;

// About Enemy ==========================================

int32 csSize = 0;
char posData[DATA_SIZE];

int32 enemyDataCnt = 0;
EnemyData* enemyData;

// About bullet ==========================================

Bullet bullets[BULLET_CNT];
int32 bulletMax = 0;
int32 bulletCur = 0;
clock_t bulletStart = clock();
clock_t bulletEnd = clock();

// Function ==============================================

void UpdateGame()
{
	switch (gameStageFlag)
	{
	case STATE_PLAY:

		// input section
		GetKeyGame();

		// logic section
		UpdatePlayer();
		UpdateBullet();
		UpdateEnemy();

		// render section
		rd_BufferClear();
		GameDataToBuffer();
		rd_BufferFlip();

		break;

	case STATE_CLEAR:
		GameClear();
		break;

	case STATE_OVER:
		GameOver();
		break;
	}
}
 
// Get Input =================================================

void GetKeyGame()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		g_exit = true;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		if (player.iX > 0)
			player.iX--;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		if (player.iX < dfSCREEN_WIDTH - 2)
			player.iX++;
	}
}

// Update =================================================
void UpdateBullet()
{
	bulletEnd = clock();
	float time = (float)(bulletEnd - bulletStart) / CLOCKS_PER_SEC;

	if (time < bullets[bulletCur].iSpeed)
		return;

	if (bulletMax < BULLET_CNT)
		bulletMax++;

	bullets[bulletCur].iX = player.iX;
	bullets[bulletCur].iY = player.iY;

	for (int i = 0; i < bulletMax; i++)
	{
		bullets[i].iY--;
		bullets[i].bDead = false;
	}

	bulletCur++;

	if (bulletCur >= BULLET_CNT)
		bulletCur = 0;

	bulletStart = clock();
}

void UpdateEnemy()
{
	int enemyCnt = 0; 

	for (int i = 0; i < enemyDataCnt; i++)
	{
		EnemyData* tmp = enemyData + i;

		for (int j = 0; j < tmp -> max; j++)
		{
			Enemy* enemy = (tmp -> enemies) + j;

			for (int k = 0; k < bulletMax; k++)
			{
				if (bullets[k].bDead == false
					&& enemy -> bDead == false
					&& enemy -> iX == bullets[k].iX
					&& enemy -> iY == bullets[k].iY)
				{
					enemy -> hp -= bullets[k].iAttack;
					
					bullets[k].bDead = true;
					bullets[k].iX = -1;
					bullets[k].iY = -1;
				}
			}

			if (enemy->hp <= 0)
				enemy->bDead = true;
			else
				enemyCnt++;
		}
	}

	if (enemyCnt <= 0)
	{
		gameStageFlag = STATE_CLEAR;
		return;
	}

}

void UpdatePlayer()
{
	if (player.iHp <= 0)
	{
		gameStageFlag = STATE_OVER;
		return;
	}
}

// Render =================================================

void GameDataToBuffer()
{
	rd_SpriteDraw(player.iX, player.iY, player.icon[0]);

	for (int i = 0; i < bulletMax; i++)
	{
		if(bullets[i].bDead == false)
			rd_SpriteDraw(bullets[i].iX, bullets[i].iY, bullets[i].icon[0]);
	}

	Enemy* enemy;
	EnemyData* tmp;

	for (int i = 0; i < enemyDataCnt; i++)
	{
		tmp = enemyData + i;

		for (int j = 0; j < tmp -> max; j++)
		{
			enemy = tmp->enemies + j;

			if (enemy->bDead == false)
				rd_SpriteDraw(enemy->iX, enemy->iY, *tmp->icon);
		}
	}

	for (int i = 0; i < strlen(strStage); i++)
	{
		rd_SpriteDraw(i, 0, strStage[i]);
	}
}

// Change Scene =============================================

void FreeHeapData()
{
	for (int i = 0; i < enemyDataCnt; i++)
	{
		free((enemyData + i)->enemies);
	}
	free(enemyData);
}

void GameClear()
{
	FreeHeapData();
	gameStageFlag = STATE_PLAY;
	g_Scene = CLEAR;
}

void GameOver()
{
	FreeHeapData();
	gameStageFlag = STATE_PLAY;
	g_Scene = OVER;
}