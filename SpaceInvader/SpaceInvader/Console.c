#include <stdio.h>
#include "console.h"

HANDLE hout;

/*
 * Function Name : ClearScreen()
 *
 * Function Description : 해당 좌표주변의 영역의 아스키문자를 삭제함
 *
 * Input : void
 * Output : void
 * Version : 0.0
 */
 
void ClearScreen()
{
	int i, j;
	UPOINT pos;

	for (i = 1; i < 25; i++)
	{
		for (j = 1; j < 80; j++)
		{
			pos.x = j;
			pos.y = i;
			gotoxy(pos);
			printf(" ");
		}
	}
}


/* Function Name : InitConsole()
 *
 * Function Description : 커서를 초기화함
 *  초기화는 bVisible은 투명하게, 사이즈는 1로 초기화
 * 표준 출력 핸들을 가져와서 (GetStdHandle)
 * 커서 정보를 저장함 (SetConsoleCursorInfo)
 *
 * 참고로 CMD 화면 자체를 콘솔이라고 부름
 *
 * Input : void
 * Output : void
 * Version : 0.0
 */

void InitConsole()
{
	CONSOLE_CURSOR_INFO coninfo;

	coninfo.bVisible = FALSE;
	coninfo.dwSize = 1;

	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorInfo(hout, &coninfo);
}

/*
 * Function Name : gotoxy
 *
 * Function Description :
 *  입력으로 들어온 콘솔 포지션으로 커서를 옮긴다.
 *
 * 참고로 CMD 화면 텍스트를 입력하기 위한 깜박이는 막대기를 커서라고 함
 *
 * Input : UPOINT pt,
 * Output : void
 * Version : 0.0
 */
void gotoxy(UPOINT pt)
{
	COORD pos;

	pos.X = pt.x;
	pos.Y = pt.y;

	SetConsoleCursorPosition(hout, pos);
}
