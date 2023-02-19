#pragma once
#include "Types.h"
#include <stdio.h>

//pFile IO
void OpenFile(char filename[], FILE** pFile, const char* mode);
void ReadFile(FILE** pFile, int32 size, char data[]);
void WriteFile(FILE** pFile, int32 size, char data[]);
void CloseFile(FILE** pFile);
int32 GetFileSize(FILE** pFile);
