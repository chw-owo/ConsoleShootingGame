#pragma once

//////////////////////////////////////////////////////////////
// Windows 의 콘솔 화면에서 커서 제어.							//
//////////////////////////////////////////////////////////////

#ifndef __CONSOLE__
#define __CONSOLE__
#define dfSCREEN_WIDTH		81		// 콘솔 가로 80칸 + NULL
#define dfSCREEN_HEIGHT		24		// 콘솔 세로 24칸

#include "Types.h"

void cs_Initial(void);
void cs_MoveCursor(const int32& iPosX, const int32& iPosY);
void cs_ClearScreen(void);


#endif

