#include "UtilFileData.h"
#include "FileFunction.h"
#include <iostream>

#define SEP_LEN 16
char seps[][SEP_LEN] =
{
	"\n",
	"\n",
	"\n",
	"\n",
	"\n",
	"\n",
};


void SetStageData(int32 stage)
{
	g_Stage = stage;

	FILE* pFile;
	char data[NUM_SIZE] = { 0, };
	sprintf_s(data, NUM_SIZE, "%d", g_Stage);
	OpenFile(playData, &pFile, "w");
	WriteFile(&pFile, 1, data);
	CloseFile(&pFile);
}

void LoadOriginData(char* fileName, void* output, int32& resultSize)
{
	FILE* pFile;
	OpenFile(fileName, &pFile, "r");
	resultSize = GetFileSize(&pFile);
	ReadFile(&pFile, resultSize, static_cast<char*>(output));
	CloseFile(&pFile);
	return;

}
void LoadTokenedData(char* fileName, void* output, int32& resultSize, 
							 LOAD_FLAG flag, int32 idx)
{
	FILE* pFile;
	char* fileData;

	OpenFile(fileName, &pFile, "r");
	resultSize = GetFileSize(&pFile);
	fileData = static_cast<char*>(calloc(resultSize, sizeof(char)));
	ReadFile(&pFile, resultSize, fileData);
	CloseFile(&pFile);

	switch (flag)
	{
		case GET_ROOT_ALL:
			TokenizeRootAll(fileData, seps[flag], resultSize, 
								static_cast<char(*)[ROOT_LEN]>(output));
			break;

		case GET_ROOT_ONE:
			TokenizeRootOne(fileData, seps[flag], idx, 
								static_cast<char*>(output));
			break;

		case GET_GAMEDATA:
			TokenizeGameData(fileData, seps[flag], resultSize,
				static_cast<char(*)[ROOT_CNT][ROOT_LEN]>(output));
			break;

		case GET_DATA_ENEMY:
			TokenizeEnemyData(fileData, seps[flag], static_cast<EnemyData*>(output));
			break;

		case GET_DATA_PLAYER:
			TokenizePlayerData(fileData, seps[flag], static_cast<Player*>(output));
			break;

		case GET_DATA_BULLET:
			TokenizeBulletData(fileData, seps[flag], static_cast<Bullet*>(output));
			break;
		

		default:
			break;
	}

	free(fileData);
}

void TokenizeGameData(char* fileData, char sep[], int32& fileNum, char output[][ROOT_CNT][ROOT_LEN])
{
	int32 idx1 = 0;
	int32 idx2 = 0;
	char* tok = NULL;
	char* next = NULL;

	tok = strtok_s(fileData, sep, &next);
	while (tok != NULL)
	{
		if (strcmp(tok, "POSITION") == 0)
		{
			idx1 = DATA_POS;
			idx2 = 0;
		}
		else if (strcmp(tok, "PLAYER") == 0)
		{
			idx1 = DATA_PLAYER;
			idx2 = 0;
		}
		else if (strcmp(tok, "BULLET") == 0)
		{
			idx1 = DATA_BULLET;
			idx2 = 0;
		}
		else if (strcmp(tok, "ENEMY") == 0)
		{
			idx1 = DATA_ENEMY;
			idx2 = 0;
		}
		else if (strcmp(tok, "ENEMYNUM") == 0)
		{
			idx1 = DATA_ENEMY_NUM;
			idx2 = 0;
		}
		else
		{
			strcpy_s(output[idx1][idx2], ROOT_LEN, tok);
			idx2++;
		}
		
		tok = strtok_s(NULL, sep, &next);
	}

	fileNum = idx2;
}

void TokenizeRootOne(char* fileData, char sep[], int32 idx, char* output)
{
	int32 cnt = 0;
	char* tok = NULL;
	char* next = NULL;
	
	tok = strtok_s(fileData, sep, &next);
	while (cnt < idx && tok != NULL)
	{
		tok = strtok_s(NULL, sep, &next);
		cnt++;
	}
	strcpy_s(output, ROOT_LEN, tok);
}

void TokenizeRootAll(char* fileData, char sep[], int32& fileNum, char output[][ROOT_LEN])
{
	int32 idx = 0;
	char* tok = NULL;
	char* next = NULL;

	tok = strtok_s(fileData, sep, &next);
	while (tok != NULL)
	{
		strcpy_s(output[idx], ROOT_LEN, tok);
		tok = strtok_s(NULL, sep, &next);
		idx++;
	}
	fileNum = idx;
}


void TokenizeEnemyData(char* fileData, char sep[], EnemyData* output)
{
	int32 idx = 0;
	char* tok = NULL;
	char* next = NULL;

	tok = strtok_s(fileData, sep, &next);
	strcpy_s(output->name, NAME_SIZE, tok);

	tok = strtok_s(NULL, sep, &next);
	strcpy_s(output->icon, ICON_SIZE, tok);

	tok = strtok_s(NULL, sep, &next);
	output-> totalHp = atoi(tok);
	output-> cnt = 0;
}

void TokenizePlayerData(char* fileData, char sep[], Player* output)
{
	int32 idx = 0;
	char* tok = NULL;
	char* next = NULL;

	tok = strtok_s(fileData, sep, &next);
	strcpy_s(output->icon, ICON_SIZE, tok);

	tok = strtok_s(NULL, sep, &next);
	output->iTotalHp = atoi(tok);
	output->iHp = atoi(tok);
}

void TokenizeBulletData(char* fileData, char sep[], Bullet* output)
{
	int32 idx = 0;
	char* tok = NULL;
	char* next = NULL;

	tok = strtok_s(fileData, sep, &next);

	for(int i = 0; i < BULLET_CNT; i++)
		strcpy_s((output + i)->icon, ICON_SIZE, tok);

	tok = strtok_s(NULL, sep, &next);
	for (int i = 0; i < BULLET_CNT; i++)
		(output + i)->iAttack = atoi(tok);

	tok = strtok_s(NULL, sep, &next);
	for (int i = 0; i < BULLET_CNT; i++)
		(output + i)->iSpeed = atof(tok);
}