#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "score.h"



/*
 * Function Name : GetScore
 *
 * Function Description :
 * ��� ���ھ �Է¹����� User������ �Է¹޴´�.
 * �Է��� ������ �������� ���������� �����ص�
 * (����: ����ü�� �ִ� �迭�� �ش���ġ�� �����̵��ؼ� ���Ҹ� �ٲ���ߵ�)
 * 
 * Input : int user_score
 * Output : void
 * Version : 0.1
 */
/*
void GetScore(int user_score)
{
	char user_name[10];

	while (1) 
	{
		printf("USER Name�� �Է��ϼ���:   ");
		scanf("%s", user_name);
		if (strlen(user_name) == 3)
		{
			break;
		}
		else if(user_name == NULL || strlen(user_name) != 3)
		{
			printf("�̸��� 3���ڷ� �Է����ּ���!! \n");
		}

	}


	strcpy(UserResult.user, user_name);
	UserResult.score = user_score;
}
*/




/*
 * Function Name : SaveScore
 *
 * Function Description :
 * ������ ������ ���ھ ��ŷ���忡 ������Ʈ�� ����
 *
 * Input : void
 * Output : void
 * Version : 0.0 �̿ϼ���
 */
 /*
void SaveScore(void)
{
	FILE* file = fopen("ranking_table.txt", "r");
	userInfo temp_info;
	userInfo resultTable[5];
	char each_score[100];
	bool save_flag = true;
	
	int result_idx = 0;

	//���Ͽ��� ���پ� �б�
	while (fgets(each_score,
		sizeof(each_score) / sizeof(each_score[0]),
		file) != NULL)
	{
		strcpy(temp_info.user, strtok(NULL, ","));
		temp_info.score = atoi(strtok(NULL, ","));

		if (save_flag && (UserResult.score > temp_info.score))
		{
			resultTable[result_idx] = UserResult;
			save_flag = false;
			result_idx += 1;
			resultTable[result_idx] = temp_info;
			result_idx += 1;
		}
		else
		{
			resultTable[result_idx] = temp_info;
			result_idx += 1;
		}

		if (result_idx >= MAX_USER_NUMBER) break;
	}
	
	//�����̹����� ���� ������ߵ�
	file = fopen("ranking_table.txt", "w");
	for (int i = 0; i < MAX_USER_NUMBER; i++) {
		fprintf(file, "%s,%d \n", resultTable[i].user, resultTable[i].score);
	}
	fclose(file);
	
}
 */

/*
 * Function Name : ShowScore
 *
 * Function Description :
 * ���� �����Ҷ� ������ ��ϵ� ���ھ�带 �ҷ���
 *
 * Input : void
 * Output : void
 * Version : 0.0 �̿ϼ���
 */
void ShowScore(userInfo* scoreBoard)
{
	FILE* file = fopen("ranking_table.txt", "r");
	char each_score[100];

	int result_idx = 0;

	//���Ͽ��� ���پ� �б�
	while(fgets(each_score,
		sizeof(each_score) / sizeof(each_score[0]),
		file) != NULL)
	{
		strcpy(scoreBoard[result_idx].user, strtok(each_score, ","));
		scoreBoard[result_idx].score = atoi(strtok(NULL, ","));
		result_idx += 1;
	}
}