#pragma once

//////////////////////////////////////////////////////////////
// Windows �� �ܼ� ȭ�鿡�� Ŀ�� ����.							//
//////////////////////////////////////////////////////////////

#ifndef __CONSOLE__
#define __CONSOLE__
#define dfSCREEN_WIDTH		81		// �ܼ� ���� 80ĭ + NULL
#define dfSCREEN_HEIGHT		24		// �ܼ� ���� 24ĭ

#include "Types.h"

void cs_Initial(void);
void cs_MoveCursor(int32 iPosX, int32 iPosY);
void cs_ClearScreen(void);


#endif

