#include "Extern.h"
#include "UtilFileData.h"
#include "Render.h"
#include "Scenes.h"

int main()
{
	cs_Initial();
	InitialSceneData();
	InitialStageData();

	while (1)
	{	
		switch (g_Scene)
		{
		case TITLE:
			UpdateTitle();
			break;

		case LOAD:
			UpdateLoad();
			break;

		case GAME:
			UpdateGame();
			break;

		case CLEAR:
			UpdateClear();
			break;

		case OVER:
			UpdateOver();
			break;
		}

		if (g_exit == true)
			break;
	}

	return 0;
}





