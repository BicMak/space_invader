#include "main.h"

char  enemyship_shape[5] = "^V^";

ENEMYSHIP enemyship[MAX_ENEMY];
UPOINT ptOld[MAX_ENEMY];
BULLET enemy_bullet[MAXENEMY_BULLET];
short flag;

/**
 * Function Name : Initenemyship
 *
 * Function Description :
 * �� �Լ��� �ʱ�ȭ ������
 * MAXENEMY_BASE_ROW * MAXENEMY_BASE_COL ������ŭ ������ ����
 *
 * Input : void
 * Output : void
 * Version : 0.0
 */
void Initenemyship()
{
	int i, j, k;
	k = 0;

	for (i = 0; i < MAXENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAXENEMY_BASE_COL; j++)
		{
			enemyship[k].flag = TRUE;
			enemyship[k].pos.x = ENEMYSHIP_BASE_POSX + j * 4;
			enemyship[k].pos.y = ENEMYSHIP_BASE_POSY + i * 2;
			ptOld[k].x = ENEMYSHIP_BASE_POSX + j * 4;
			ptOld[k].y = ENEMYSHIP_BASE_POSY + i * 2;
			k++;
		}
	}
	InitBullet();
}

/**
 * Function Name : CalenemyshipPos
 *
 * Function Description :
 * ������ �����̴� ��ǥ�� ������� x�� 1��ŭ���ְ� flag�� ������ -1��ŭ
 * y�� �ٲ𶧸��� �÷��װ� ����
 *
 * Input : void
 * Output : void
 * Version : 0.0
 */
void CalenemyshipPos()
{
	int i, j, k, XAdd, YAdd;

	k = 0;

	YAdd = Calflag();
	if (flag == FALSE)
		XAdd = 1;
	else
		XAdd = -1;

	for (i = 0; i < MAXENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAXENEMY_BASE_COL; j++)
		{
			ptOld[k].x = enemyship[k].pos.x;
			ptOld[k].y = enemyship[k].pos.y;
			enemyship[k].pos.x += XAdd;
			enemyship[k].pos.y += YAdd;
			k++;

		}
	}
}

/**
 * Function Name : CalenemyshipPos
 *
 * Function Description :
 * enermyship[0]�� �������� x������ 40�̻� �̵��ϸ� flag�� �÷��ְ�
 * 1�� ��ȯ����
 *
 * Input : void
 * Output : int add
 * Version : 0.0
 */
int Calflag()
{
	int add;

	if (enemyship[0].pos.x < 1 || enemyship[0].pos.x > 40)
	{
		if (flag == TRUE)
			flag = FALSE;
		else
			flag = TRUE;
		add = 1;
	}
	else
		add = 0;
	return add;
}


/**
 * Function Name : Drawenemyship
 *
 * Function Description :
 * ���� ���� ������ ��ǥ�� ����ؼ� ��ĳ���͸� �׷���
 *
 * Input : void
 * Output : void
 * Version : 0.0
 */
void Drawenemyship()
{
	UPOINT pos, posOld;
	int i;

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if (enemyship[i].flag == TRUE)
		{
			posOld.x = ptOld[i].x;
			posOld.y = ptOld[i].y;

			pos.x = enemyship[i].pos.x;
			pos.y = enemyship[i].pos.y;

			gotoxy(posOld);
			printf("       ");

			gotoxy(pos);
			printf("%s", enemyship_shape);
		}
	}
}

/**
 * Function Name : BulletNum
 *
 * Function Description :
 * �Ѿ˰����� ����� ������ �����ؼ� �ش� �ε����� �谡 ���������
 * �ش� �谡 ���� ��°ɷ� ������
 *
 * Input : void
 * Output : int num
 * Version : 0.0
 */
int BulletNum()
{
	int num;
	while (1)
	{
		num = rand() % 40;
		if (enemyship[num].flag == FALSE)
			continue;
		break;
	}
	return num;
}

/**
 * Function Name : InitBullet
 *
 * Function Description :
 * ���Լ��� ���� �Ѿ��� ���� �ʱ�ȭ ��Ŵ
 *
 * Input : void
 * Output : void
 * Version : 0.0
 */
void InitBullet()
{
	int i;

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		enemy_bullet[i].flag = FALSE;
		enemy_bullet[i].pos.x = 0;
		enemy_bullet[i].pos.y = 0;
	}
}

/**
 * Function Name : Bulletshot
 *
 * Function Description :
 * �� �Ѹ��� �����ؼ� �Ѿ��� �Ƚ�� �ִٸ� �Ѿ��� �����
 * �ִ� ���������� �Ѿ˰����� �Ѿ��� �ֿܼ� ǥ�� �� �� ����
 *
 * Input : void
 * Output : void
 * Version : 0.0
 */
void Bulletshot()
{
	int i, num;
	num = BulletNum();

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		if (enemy_bullet[i].flag == FALSE)
		{
			enemy_bullet[i].flag = TRUE;
			enemy_bullet[i].pos.x = enemyship[num].pos.x;
			enemy_bullet[i].pos.y = enemyship[num].pos.y;
			break;
		}
	}
}

/**
 * Function Name : DrawBullet
 *
 * Function Description :
 * ���� �Ѿ��� �׸��� ���� �Ѿ��� "|" ���� ǥ����
 * Y��ǥ�� 23���� Ŀ���ٸ� �ش� �Ѿ��� �����ȴ�.
 *
 * Input : void
 * Output : void
 * Version : 0.0
 */
void DrawBullet()
{
	int i;
	UPOINT ptpos, oldpos;

	for (i = 0; i < MAXENEMY_BULLET; i++)
	{
		if (enemy_bullet[i].flag == TRUE)
		{
			if (enemy_bullet[i].pos.y > 23)
			{
				enemy_bullet[i].flag = FALSE;
				oldpos.x = enemy_bullet[i].pos.x;
				oldpos.y = enemy_bullet[i].pos.y;
				gotoxy(oldpos);
				printf(" ");
				break;
			}
			oldpos.x = enemy_bullet[i].pos.x;
			oldpos.y = enemy_bullet[i].pos.y;
			++enemy_bullet[i].pos.y;
			ptpos.x = enemy_bullet[i].pos.x;
			ptpos.y = enemy_bullet[i].pos.y;
			gotoxy(oldpos);
			printf(" ");
			gotoxy(ptpos);
			printf("|");
		}
	}
}

/**
 * Function Name : Checkenemypos
 *
 * Function Description :
 * ���� ��ġ�� y��������� 23���� Ŀ���� flag�� ON ���� �ٲ۴�.
 *
 * Input : void
 * Output : int flag
 * Version : 0.0
 */
int Checkenemypos()
{
	int flag = FALSE, i;

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if (enemyship[i].flag == TRUE && enemyship[i].pos.y == 23)
		{
			flag = TRUE;
			break;
		}
	}

	return flag;
}


/**
 * Function Name : CheckenemyBullet
 *
 * Function Description :
 * ���� ��ġ�� y��������� 23���� Ŀ���� �� �Ѿ��� flag�� ON ���� �ٲ۴�.
 * �׸��� ���� �Ѿ˿� �´� ��� ��������� �÷��׸� ������
 * ��������Ʈ�� off ��Ŵ
 *
 * Input : ENEMYSHIP *enemyship
 * Output : void
 * Version : 0.0
 */
void CheckenemyBullet(ENEMYSHIP* enemyship)
{
	int i, j;
	static BULLET boompos[MAXMY_BULLET];
	static int flag;

	for (i = 0; i < 5; i++)
	{
		if (myship_boom.flag[i] == TRUE)
		{
			for (int j = 0; j < MAX_ENEMY; j++)
			{
				if (enemyship[j].flag == TRUE)
				{
					if ((enemyship[j].pos.x >= myship_boom.pos[i].x - 2 &&
						myship_bullet[i].pos.x -2  >= enemyship[j].pos.x )  &&
						(enemyship[j].pos.y == myship_boom.pos[i].y))
					{
						enemyship[j].flag = FALSE;
						gotoxy(enemyship[j].pos);
						printf(" *** ");
						score += 100;
						killnum++;
					}
				}
			}
		}
	}

	for (i = 0; i < MAXMY_BULLET; i++)
	{
		if (myship_bullet[i].flag == TRUE)
		{
			for (j = 0; j < MAX_ENEMY; j++)
			{
				if (enemyship[j].flag == TRUE)
				{
					if (enemyship[j].pos.x <= myship_bullet[i].pos.x &&
						myship_bullet[i].pos.x <= (enemyship[j].pos.x + 2) &&
						(enemyship[j].pos.y == myship_bullet[i].pos.y))
					{
						enemyship[j].flag = FALSE;
						gotoxy(enemyship[j].pos);
						printf(" *** ");
						myship_bullet[i].flag = FALSE;
						score += 100;
						killnum++;
						boompos[i].pos = enemyship[j].pos;
						boompos[i].flag = TRUE;
					}
				}
			}
		}
	}


}


