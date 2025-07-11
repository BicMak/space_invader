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
 * 적 함선을 초기화 시켜줌
 * MAXENEMY_BASE_ROW * MAXENEMY_BASE_COL 개수만큼 적함이 생김
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
 * 적함을 움직이는 좌표를 계산해줌 x는 1만큼해주고 flag가 켜지면 -1만큼
 * y가 바뀔때마다 플래그가 켜짐
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
 * enermyship[0]을 기준으로 x축으로 40이상 이동하면 flag를 올려주고
 * 1을 반환해줌
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
 * 위에 계산된 정보로 좌표를 계산해서 적캐릭터를 그려줌
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
 * 총알개수를 계산함 난수를 생성해서 해당 인덱스에 배가 살아있으면
 * 해당 배가 총을 쏘는걸로 간주함
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
 * 적함선의 배의 총알을 전부 초기화 시킴
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
 * 적 한명을 지정해서 총알을 안쏘고 있다면 총알을 쏘게함
 * 최대 생성가능한 총알개수로 총알을 콘솔에 표현 할 수 있음
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
 * 적의 총알을 그린다 적의 총알은 "|" 으로 표현됨
 * Y좌표가 23보다 커진다면 해당 총알은 삭제된다.
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
 * 적의 위치가 y축기준으로 23보다 커지면 flag를 ON 으로 바꾼다.
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
 * 적의 위치가 y축기준으로 23보다 커지면 내 총알의 flag를 ON 으로 바꾼다.
 * 그리고 적이 총알에 맞는 경우 적비행기의 플래그를 내리고
 * 폭팔이펙트와 off 시킴
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


