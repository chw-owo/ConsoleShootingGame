#pragma once
#include "Types.h"

#define ROOT_CNT 16
#define ROOT_LEN 128

#define ICON_SIZE 8
#define NUM_SIZE 8
#define NAME_SIZE 8
#define INFO_SIZE 16

#define DATA_SIZE 2048

enum SCENE
{
	TITLE,
	LOAD,
	GAME,
	CLEAR,
	OVER,
	END
};

extern bool g_exit;
extern int32 g_iX;
extern int32 g_Stage;
extern int32 g_Scene;
extern int32 g_finalStage;

extern char rootData[];
extern char playData[];
extern char playFinalData[];
extern char sceneFileRoot[END][ROOT_LEN];

void SetExitTrue(const char func[], const int line);