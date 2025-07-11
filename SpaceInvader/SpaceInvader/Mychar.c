#include "main.h"

MYSHIP  myship;
BULLET myship_bullet[MAXMY_BULLET];

char myship_shape[10] = "ui^iu";
char PowerAttack[5][6] = {
	{"T_T_T"},
	{"_T_T_"},
	{" TTT "},
	{" III "},
	{"  I  "}
};


/**
 * Function Name : InitMyship
 *
 * Function Description :
 * 내 캐릭터를 초화함, myship.flag를 True로 하여 생존처리를하고
 * 초기화 위치로 이동함
 *
 * Input : void,
 * Output : void
 * Version : 0.0
 */
void InitMyship()
{
	myship.flag = TRUE;
	myship.pos.x = MYSHIP_BASE_POSX;
	myship.pos.y = MYSHIP_BASE_POSY;
}


/**
 * Function Name : InitMyBullet
 *
 * Function Description :
 * 화면상에 생성된 내 캐릭터의 총알을 삭제함
 *
 * Input : void,
 * Output : void
 * Version : 0.0
 */
void InitMyBullet()
{
	int i;
	UPOINT current_pos;

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		if (myship_bullet[i].flag == TRUE)
		{

			current_pos.x = myship_bullet[i].pos.x;
			current_pos.y = myship_bullet[i].pos.y;
			myship_bullet[i].flag = FALSE;
			gotoxy(current_pos);
			printf("  ");
		}
	}
}

/**
 * Function Name : DrawMyship
 *
 * Function Description :
 * 캐릭터를 입력한 위치로 이동시킴, 캐릭터를 옮기고,
 * 기존위치에서는 공백표시함
 *
 * Input : UPOINT *pt, UPOINT *oldpt
 * Output : void
 * Version : 1.0
 *  변경사항 1.0 ---> 캐릭터의 잔상이 사라지는것을 삭제
 */
void DrawMyship(UPOINT* pt, UPOINT* oldpt)
{
	UPOINT temp_pt = *oldpt;
	temp_pt.x -= 2;
	temp_pt.y += 1;
	for (int i=0; i < 3; i++)
	{
		gotoxy(temp_pt);
		printf("       ");
		temp_pt.y -= 1;
	}
	gotoxy(*pt);
	printf("%s", myship_shape);
}

/**
 * Function Name : DrawMyBullet
 *
 * Function Description :
 * 총알을 그려줌,
 * 총알은 최대로 설정된 값만큼만 그릴수 있음
 *
 * Input : UPOINT *pt, UPOINT *oldpt
 * Output : void
 * Version : 0.0
 */
void DrawMyBullet()
{
	int i;
	UPOINT ptpos, oldpos;

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		if (myship_bullet[i].flag == TRUE)
		{
			if (myship_bullet[i].pos.y < 1)
			{
				myship_bullet[i].flag = FALSE;
				oldpos.x = myship_bullet[i].pos.x;
				oldpos.y = myship_bullet[i].pos.y;
				gotoxy(oldpos);
				printf(" ");
				break;
			}

			oldpos.x = myship_bullet[i].pos.x;
			oldpos.y = myship_bullet[i].pos.y;
			--myship_bullet[i].pos.y; // 좌측상단이 0,0 이니깐 -1 을 해줘야 커서가 북쪽으로 움직임
			ptpos.x = myship_bullet[i].pos.x;
			ptpos.y = myship_bullet[i].pos.y;
			gotoxy(oldpos);
			printf(" ");
			gotoxy(ptpos);
			printf("!");
		}
	}
}

/**
 * Function Name : MyBulletshot
 *
 * Function Description :
 * 총알을 그려줌, 총알은 MAXMY_BULLET 만큼만 그릴 수 있음
 * 총알 발사 유무는 flag로 확인이 가능함
 *
 * Input : UPOINT *pt, UPOINT *oldpt
 * Output : void
 * Version : 0.0
 */
void MyBulletshot(UPOINT ptthisMypos)
{
	int i;

	for (i = 0; i < MAXMY_BULLET; i++)
	{
		if (myship_bullet[i].flag == FALSE)
		{
			myship_bullet[i].flag = TRUE;
			myship_bullet[i].pos.x = ptthisMypos.x + 2;
			myship_bullet[i].pos.y = ptthisMypos.y - 1;
			break;
		}
	}
}

/**
 * Function Name : CheckMybullet
 *
 * Function Description :
 * 적 총알이랑 겹쳤을때 대응하는 함수
 *
 * Input : UPOINT *pt, UPOINT *oldpt
 * Output : void
 * Version : 0.0
 */
int CheckMybullet(UPOINT ptthisMypos)
{
	int i, flag;

	flag = FALSE;

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		if (enemy_bullet[i].flag == TRUE)
		{
			if (ptthisMypos.x <= enemy_bullet[i].pos.x &&
				(enemy_bullet[i].pos.x <= ptthisMypos.x + 4) &&
				enemy_bullet[i].pos.y == ptthisMypos.y)
			{
				flag = TRUE;
				break;
			}
		}
	}

	if (flag == TRUE)
		return 0;
	else
		return 1;
}



void MyBoomshot(UPOINT ptthisMypos)
{
	myship_boom.flag[0] = TRUE;
	myship_boom.pos[0].x = ptthisMypos.x + 2;
	myship_boom.pos[0].y = ptthisMypos.y - 1;
	for (int i = 1; i < 5; i++)
	{
		myship_boom.pos[i].x = myship_boom.pos[0].x;
		myship_boom.pos[i].y = myship_boom.pos[0].y - i;
	}
}

/**
 * Function Name : DrawBoom
 *
 * Function Description :
 * 필살기 폭탄을 연출 해줌
 *
 * Input : void
 * Output : void
 * Version : 현재 미완성
 */
void DrawBoom()
{
	int i;
	UPOINT ptpos, oldpos;


	if (myship_boom.flag[0] == TRUE)
	{
		//캐릭터의 위치와 ship의 위치에 따라서 빔형상 계산
		for (int i = 0; i < 5; i++) 
		{
			if (myship_boom.pos[i].y < 1)
			{
				myship_boom.flag[i] = TRUE;
			}
			else
			{
				myship_boom.flag[i] = FALSE;
			}

		}

		for (int i = 0; i < 5; i++)
		{
			if (myship_boom.flag[i] == TRUE)
			{
				oldpos.x = myship_boom.pos[i].x;
				oldpos.y = myship_boom.pos[i].y;
				myship_boom.pos[i].y -= 1;
				ptpos.x = myship_boom.pos[i].x;
				ptpos.y = myship_boom.pos[i].y;
				gotoxy(oldpos);
				printf("    \n");
				gotoxy(ptpos);
				printf("%s", PowerAttack[i]);
			}
		}
	}
}