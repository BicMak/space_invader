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
 * Function Name : InitMyBullet
 *
 * Function Description :
 * ȭ��� ������ �� ĳ������ �Ѿ��� ������
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
 * ĳ���͸� �Է��� ��ġ�� �̵���Ŵ, ĳ���͸� �ű��,
 * ������ġ������ ����ǥ����
 *
 * Input : UPOINT *pt, UPOINT *oldpt
 * Output : void
 * Version : 1.0
 *  ������� 1.0 ---> ĳ������ �ܻ��� ������°��� ����
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
 * �� �Ѿ��̶� �������� �����ϴ� �Լ�
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
 * �ʻ�� ��ź�� ���� ����
 *
 * Input : void
 * Output : void
 * Version : ���� �̿ϼ�
 */
void DrawBoom()
{
	int i;
	UPOINT ptpos, oldpos;


	if (myship_boom.flag[0] == TRUE)
	{
		//ĳ������ ��ġ�� ship�� ��ġ�� ���� ������ ���
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