#include "FileFunction.h"
#include "Extern.h"

// File IO
void OpenFile(char filename[], FILE** pFile, const char* mode)
{
	errno_t ret = fopen_s(pFile, filename, mode);

	if (ret != 0)
	{
		printf("Fail to open %s\n", filename);
		printf("errno_t : %d\n", ret);
		SetExitTrue(__FUNCTION__, __LINE__);
	}
}

void CloseFile(FILE** pFile)
{
	errno_t ret = fclose(*pFile);
	if (ret != 0)
	{
		printf("Fail to close pFile : %d\n", ret);
		SetExitTrue(__FUNCTION__, __LINE__);
	}

}

void ReadFile(FILE** pFile, int32 size, char data[])
{
	fread(data, 1, size, *pFile);
	errno_t ret = ferror(*pFile);
	if (ret != 0)
	{
		printf("Fail to read data : %d\n", ret);
		SetExitTrue(__FUNCTION__, __LINE__);
	}

}

void WriteFile(FILE** pFile, int32 size, char data[])
{
	fwrite(data, size, 1, *pFile);
	errno_t ret = ferror(*pFile);

	if (ret != 0)
	{
		printf("Fail to write data : %d\n", ret);
		SetExitTrue(__FUNCTION__, __LINE__);
	}

}

int32 GetFileSize(FILE** pFile)
{
	fseek(*pFile, 0, SEEK_END);
	int32 size = ftell(*pFile);
	rewind(*pFile);

	if (size == -1)
	{
		printf("Fail to get file size\n");
		SetExitTrue(__FUNCTION__, __LINE__);
	}

	return size;
}

