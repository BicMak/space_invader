#include "main.h"

MYSHIP  myship;
BULLET myship_bullet[MAXMY_BULLET];

char  myship_shape[10] = "-i^i-";

/**
 * Function Name : InitMyship
 *
 * Function Description :
 * �� ĳ���͸� ��ȭ��, myship.flag�� True�� �Ͽ� ����ó�����ϰ�
 * �ʱ�ȭ ��ġ�� �̵���
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
 * Function Name : DrawMyship
 *
 * Function Description :
 * ĳ���͸� �Է��� ��ġ�� �̵���Ŵ, ĳ���͸� �ű��,
 * ������ġ������ ����ǥ����
 *
 * Input : UPOINT *pt, UPOINT *oldpt
 * Output : void
 * Version : 0.0
 */

void DrawMyship(UPOINT* pt, UPOINT* oldpt)
{
	gotoxy(*oldpt);
	printf("     ");
	gotoxy(*pt);
	printf("%s", myship_shape);
}

/**
 * Function Name : DrawMyBullet
 *
 * Function Description :
 * �Ѿ��� �׷���,
 * �Ѿ��� �ִ�� ������ ����ŭ�� �׸��� ����
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
			--myship_bullet[i].pos.y; // ��������� 0,0 �̴ϱ� -1 �� ����� Ŀ���� �������� ������
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
 * �Ѿ��� �׷���, �Ѿ��� MAXMY_BULLET ��ŭ�� �׸� �� ����
 * �Ѿ� �߻� ������ flag�� Ȯ���� ������
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
 * ??? �̰� ���� �𸣰ڴµ�
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



