#include "Scenes.h"
#include "Extern.h"
#include "UtilFileData.h"
#include <stdlib.h>

void InitialSceneData()
{
	int32 tmpSize;
	LoadTokenedData(rootData, sceneFileRoot, tmpSize, GET_ROOT_ALL);
}

void InitialStageData()
{
	int32 tmpSize;

	char curStage[NUM_SIZE] = { '\0', };
	LoadOriginData(playData, curStage, tmpSize);
	g_Stage = atoi(curStage);

	char finalStageTmp[NUM_SIZE] = { '\0', };
	LoadOriginData(playFinalData, finalStageTmp, tmpSize);
	g_finalStage = atoi(finalStageTmp);
}




