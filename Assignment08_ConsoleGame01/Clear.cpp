#include "Clear.h"
#include "Render.h"
#include "Extern.h"
#include "UtilFileData.h"
#include <Windows.h>

bool clearInitFlag = false;
char clearData[DATA_SIZE];
int32 clearDataSize;

void UpdateClear()
{
	// input section
	GetKeyClear();

	// logic section
	if (clearInitFlag == false)
	{
		InitialClear();
		clearInitFlag = true;
	}
		
	// render section
	rd_BufferClear();
	rd_DataToBuffer(clearData, clearDataSize);
	rd_BufferFlip();
	
}

void GetKeyClear()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		if (g_Stage >= g_finalStage)
		{
			clearInitFlag = false;
			g_Scene = TITLE;
		}
		else
		{
			clearInitFlag = false;
			SetStageData(g_Stage + 1);
			g_Scene = LOAD;
		}
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		clearInitFlag = false;
		g_exit = true;
	}
}

void InitialClear()
{
	int32 resultSize;
	char clearDataRoot[ROOT_LEN];
	LoadTokenedData(sceneFileRoot[CLEAR], clearDataRoot,
		resultSize, GET_ROOT_ONE, g_Stage);

	LoadOriginData(clearDataRoot, clearData, clearDataSize);
}
