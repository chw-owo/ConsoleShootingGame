#include "Title.h"
#include "Extern.h"
#include "UtilFileData.h"
#include "Render.h"
#include <Windows.h>

bool titleInitFlag = false;
char titleData[DATA_SIZE];

void UpdateTitle()
{
	// input section
	GetKeyTitle();

	// logic section
	if (titleInitFlag == false)
	{
		LoadTitleData();
		titleInitFlag = true;
	}	

	// render section
	rd_BufferClear();
	rd_DataToBuffer(titleData);
	rd_BufferFlip();
}

void GetKeyTitle()
{
	// Continue Prev Play
	if (GetAsyncKeyState(VK_NUMPAD1) & 0x0001
		|| GetAsyncKeyState(0x31) & 0x0001)
	{
		g_Scene = LOAD;
	}
	// Start New Play
	else if (GetAsyncKeyState(VK_NUMPAD2) & 0x0001
		|| GetAsyncKeyState(0x32) & 0x0001)
	{
		SetStageData(0);
		g_Scene = LOAD;
	}
	// Exit
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		g_exit = true;
	}

}


void LoadTitleData()
{
	int32 tmpSize;
	LoadOriginData(sceneFileRoot[TITLE], titleData, tmpSize);
}
