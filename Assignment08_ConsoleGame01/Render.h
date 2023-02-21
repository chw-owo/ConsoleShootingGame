#pragma once
#include "Console.h"
#include "Types.h"
#include "Extern.h"

void rd_BufferFlip(void);
void rd_BufferClear(void);
void rd_SpriteDraw(const int32& iX, const int32& iY, const char& chSprite);
void rd_DataToBuffer(const char* data);