#include <stdio.h>
#include <string.h>
#include "score.h"



/*
 * Function Name : GetScore
 *
 * Function Description :
 * ��� ���ھ �Է¹����� User������ �Է¹޴´�.
 * �Է��� ������ �������� ���������� �����ص�
 *
 * Input : int user_score
 * Output : void
 * Version : 0.0
 */
void GetScore(int user_score)
{
	FILE* file = fopen("ranking_table.txt", "r");
	userInfo guest_info;
	char each_score[100];
	char user_name[10];

	while (1) 
	{
		printf("USER Name�� �Է��ϼ���:   ");
		scanf("%s", &user_name);
		if (strlen(user_name) == 3)
		{
			break;
		}
		else
		{
			printf("�̸��� 3���ڷ� �Է����ּ���!! \n");
		}
	}

	UserResult.user = *user_name;
	UserResult.score = user_score;
}

/*
 * Function Name : GetScore
 *
 * Function Description :
 * ���ھ� ���� ���� ����ü ���·� ��ȯ�� ����
 *
 * Input : userInfo* scoreBoard
 * Output : void
 * Version : 0.0 �̿ϼ���
 */
void ShowScore(userInfo* scoreBoard)
{
	FILE* file = fopen("ranking_table.txt", "r");
	userInfo guest_info;
	char each_score[100];

	//���Ͽ��� ���پ� �б�
	while (fgets(each_score,
		sizeof(each_score) / sizeof(each_score[0]),
		file) != NULL)
	{

	}
}