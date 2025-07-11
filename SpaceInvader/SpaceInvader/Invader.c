#include "main.h"
#include "score.h"

UPOINT     ptthisMypos;
BOOM       myship_boom;
int    timeflag = FALSE;
int    score, hiscore = 2000, killnum;
char* Aboom[8];

void DrawBox(UPOINT* score_position, userInfo* scoreBoard);

//���� �÷��̸� ������ �����ϴ� �Լ�
void main(void)
{
	UPOINT        ptend;
	int	loop = 1;

	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = "(* *)";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";
	ptend.x = 36;
	ptend.y = 12;
	while (loop)
	{
		DWORD         thisTickCount =  GetTickCount64();
		DWORD         bcount = thisTickCount;
		int           bp = 0;

		play();

		for (;;)
		{
			if (timeflag == FALSE)
			{
				thisTickCount = GetTickCount64();

				if (thisTickCount - bcount > 100)
				{
					gotoxy(ptthisMypos);
					printf("%s", Aboom[bp]);
					bp++;
					if (bp > 7)
						break;
					bcount = thisTickCount;
				}
			}
			else
				break;
		}

		ClearScreen();
		gotoxy(ptend);
		GetScore(score);
		Sleep(3000);
		SaveScore();

		ptend.y += 1;


		gotoxy(ptend);
		printf("����� ������ �ı��Ǿ����ϴ�.");
		ptend.y += 1;
		gotoxy(ptend);
		printf("�ٽ� �ұ��? (y/n)\n");

		if (_getch() == 'y')
		{
			ClearScreen();
			InitBullet();
			InitMyBullet();
			bp = 0;
			killnum = 0;
			timeflag = 0;
			ptend.y = 12;
			loop = 1;
			score = 0;
		}
		else
			loop = 0;
	}
}

/**
 * Function Name : play
 *
 * Function Description :
 * ���� �÷���
 *
 * Input : void
 * Output : void
 * Version : 2.0
 * ���� ��
 *    --> 1.0 �����¿� ����� �߰���
 *    --> 2.0 ��ź��� �߰�
 */
void  play()
{
	static UPOINT ptMyoldpos;
	DWORD         gthisTickCount = GetTickCount64();
	DWORD         gCount = gthisTickCount;
	DWORD         Count = gthisTickCount;
	DWORD         bulletcount = gthisTickCount;
	DWORD         boomcount = gthisTickCount;
	UPOINT        ptscore, pthi;
	UPOINT        ptdashboard;
	int           juckspeed = 500;
	userInfo      scoreboard[5];

	InitConsole();
	InitMyship();
	Initenemyship();
	
	myship_boom.flag[0] = FALSE;
	ptthisMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
	ptthisMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;

	ptscore.x = 68;
	ptscore.y = 1;

	ptdashboard.x = 85;
	ptdashboard.y = 2;

	pthi.x = 2;
	pthi.y = 1;

	ShowScore(scoreboard);
	DrawBox(&ptdashboard,scoreboard);

	while (TRUE)
	{
		gthisTickCount = GetTickCount64();

		// 1. Ű���� �Է¹ޱ�
		if (_kbhit())
		{

			switch (_getch())
			{
			// �Ѿ� ���
			case 'a':
				if (gthisTickCount - bulletcount > 300)
				{
					MyBulletshot(ptthisMypos);
					bulletcount = gthisTickCount;
				}
				break;
			// ��ź ���
			case 's':
				MyBoomshot(ptthisMypos);
				break;
			// ������ �̵�
			case 'j':
				ptMyoldpos.x = ptthisMypos.x;
				if (--ptthisMypos.x < 1)ptthisMypos.x = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			// ���� �̵�
			case 'l':
				ptMyoldpos.x = ptthisMypos.x;
				if (++ptthisMypos.x > 75)ptthisMypos.x = 75;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			//���� �̵�
			case 'i':
				ptMyoldpos.y = ptthisMypos.y;
				if (--ptthisMypos.y < 1)ptthisMypos.y = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			//�Ʒ��� �̵�
			case 'k':
				ptMyoldpos.y = ptthisMypos.y;
				if (++ptthisMypos.y > 23)ptthisMypos.y = 23;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			}
		}

		// 2. ���ھ� ���� �� ĳ���� �����ϱ� 
		if (gthisTickCount - Count > 150)
		{

			if (CheckMybullet(ptthisMypos) == 0)
			{
				if (score > 2000)
					hiscore = score;
				break;
			}
			CheckenemyBullet(enemyship);
			DrawMyBullet();
			DrawBoom();
			DrawMyship(&ptthisMypos, &ptMyoldpos);
			gotoxy(ptscore);

			if (killnum < 40)
			{
				printf("���� : %d", score);
			}

			else
			{
				timeflag = TRUE;
				break;
			}
			

			if (killnum > 20)
				juckspeed = 150;

			gotoxy(pthi);

			Count = gthisTickCount;
		}

		// 3. �� ĳ���� �����ϱ�  
		if (gthisTickCount - gCount > juckspeed)
		{
			Bulletshot();
			DrawBullet();
			CalenemyshipPos();
			Drawenemyship();
			if (Checkenemypos() == 1)
				break;
			gCount = gthisTickCount;
		}
	}

}

void DrawBox(UPOINT *score_position, userInfo *scoreBoard) {
	UPOINT temppostion = *score_position;
	char ranking[][10] = {"1st","2nd","3rd", "4th", "5th"};

	gotoxy(temppostion);
	printf("  Player Ranking  ");
	temppostion.y += 1;
	gotoxy(temppostion);
	printf("������������������\n");   
	temppostion.y += 1;
	gotoxy(temppostion);

	for (int idx = 0; idx < 5; idx++)
	{
		printf("%5s : %5s / %6d \n", ranking[idx], scoreBoard[idx].user, scoreBoard[idx].score);
		temppostion.y += 1;
		gotoxy(temppostion);
	}

	printf("��������������������");
}