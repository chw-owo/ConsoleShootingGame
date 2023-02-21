#include "Over.h"
#include "Render.h"
#include "Extern.h"
#include "UtilFileData.h"
#include <Windows.h>

bool overInitFlag;
char overData[DATA_SIZE];

void UpdateOver()
{
	// input section
	GetKeyOver();

	// logic section
	if (overInitFlag == false)
	{
		LoadOverData();
		overInitFlag = true;
	}

	// render section
	rd_BufferClear();
	rd_DataToBuffer(overData);
	rd_BufferFlip();
}

void GetKeyOver()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		g_Scene = GAME;
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		g_exit = true;
	}
}

void LoadOverData()
{
	int32 tmpSize;
	LoadOriginData(sceneFileRoot[OVER], overData, tmpSize);
}