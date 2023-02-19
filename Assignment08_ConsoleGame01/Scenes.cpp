#include "Scenes.h"
#include "Extern.h"
#include "UtilFileData.h"
#include <stdlib.h>

void InitialSceneData()
{
	int32 resultSize = 0;
	LoadTokenedData(rootData, sceneFileRoot, resultSize, GET_ROOT_ALL);
}

void InitialStageData()
{
	int32 resultSize = 0;

	char curStage[NUM_SIZE] = { '\0', };
	LoadOriginData(playData, curStage, resultSize);
	g_Stage = atoi(curStage);

	char finalStageTmp[NUM_SIZE] = { '\0', };
	LoadOriginData(playFinalData, finalStageTmp, resultSize);
	g_finalStage = atoi(finalStageTmp);
}

