#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "score.h"



/*
 * Function Name : GetScore
 *
 * Function Description :
 * 결과 스코어를 입력받으면 User네임을 입력받는다.
 * 입려된 정보를 바탕으로 유저정보를 저장해둠
 * (참고: 구조체에 있는 배열은 해당위치로 직접이동해서 원소를 바꿔줘야됨)
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
		printf("USER Name을 입력하세요:   ");
		scanf("%s", user_name);
		if (strlen(user_name) == 3)
		{
			break;
		}
		else if(user_name == NULL || strlen(user_name) != 3)
		{
			printf("이름은 3글자로 입력해주세요!! \n");
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
 * 게임이 끝나고 스코어를 랭킹보드에 업데이트를 해줌
 *
 * Input : void
 * Output : void
 * Version : 0.0 미완성임
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

	//파일에서 한줄씩 읽기
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
	
	//최종이미지를 저장 시켜줘야됨
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
 * 게임 시작할때 기존에 기록된 스코어보드를 불러옴
 *
 * Input : void
 * Output : void
 * Version : 0.0 미완성임
 */
void ShowScore(userInfo* scoreBoard)
{
	FILE* file = fopen("ranking_table.txt", "r");
	char each_score[100];

	int result_idx = 0;

	//파일에서 한줄씩 읽기
	while(fgets(each_score,
		sizeof(each_score) / sizeof(each_score[0]),
		file) != NULL)
	{
		strcpy(scoreBoard[result_idx].user, strtok(each_score, ","));
		scoreBoard[result_idx].score = atoi(strtok(NULL, ","));
		result_idx += 1;
	}
}