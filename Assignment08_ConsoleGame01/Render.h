#pragma once
#include "Console.h"
#include "Types.h"
#include "Extern.h"

void rd_BufferFlip(void);
void rd_BufferClear(void);
void rd_SpriteDraw(int32 iX, int32 iY, char chSprite);
void rd_DataToBuffer(char* data, int32 size);