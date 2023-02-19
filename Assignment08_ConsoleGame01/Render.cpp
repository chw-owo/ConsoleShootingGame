#include "Render.h"
#include <stdio.h>
#include <memory.h>

char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

// ������ ������ ȭ������ ����ִ� �Լ�.
// ����,�Ʊ�,�Ѿ� ���� szScreenBuffer �� �־��ְ�, 
// �� �������� ������ �������� �� �Լ��� ȣ���Ͽ� ���� -> ȭ�� ���� �׸���.
void rd_BufferFlip(void)
{
	int32 iCnt;
	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(szScreenBuffer[iCnt]);
	}
}

// ȭ�� ���۸� �����ִ� �Լ�
// �� ������ �׸��� �׸��� ������ ���۸� ���� �ش�. 
void rd_BufferClear(void)
{
	int32 iCnt;
	memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0';
	}
}

// ������ Ư�� ��ġ�� ���ϴ� ���ڸ� ���.
// �Է� ���� X,Y ��ǥ�� �ƽ�Ű�ڵ� �ϳ��� ����Ѵ�. (���ۿ� �׸�)
void rd_SpriteDraw(int32 iX, int32 iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	szScreenBuffer[iY][iX] = chSprite;
}

void rd_DataToBuffer(char* data, int32 size)
{
	int32 iX = 0;
	int32 iY = 0;

	for (int i = 0; i < size; i++)
	{
		if (*(data + i) == ' ')
		{
			iX++;
		}
		else if (*(data + i) == '\n')
		{
			iY++;
			iX = 0;
		}
		else
		{
			iX++;
			rd_SpriteDraw(iX, iY, *(data + i));
		}
	}
}