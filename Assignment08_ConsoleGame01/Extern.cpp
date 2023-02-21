#include "Extern.h"
#include "Console.h"
#include <iostream>

bool g_exit = false;
int32 g_iX = 0;
int32 g_Stage = 0;
int32 g_Scene = 0;
int32 g_finalStage;

char rootData[] = ".\\Data\\RootData.txt";
char playData[] = ".\\Data\\PlayData.txt";
char playFinalData[] = ".\\Data\\PlayFinalData.txt";
char sceneFileRoot[END][ROOT_LEN] = { '\0', };

void SetExitTrue(const char func[], const int line)
{
	printf("%s, line %d: \n", func, line);
	g_exit = true;
}