#include <stdio.h>
#include <string.h>
#include "score.h"



/*
 * Function Name : GetScore
 *
 * Function Description :
 * 결과 스코어를 입력받으면 User네임을 입력받는다.
 * 입려된 정보를 바탕으로 유저정보를 저장해둠
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
		printf("USER Name을 입력하세요:   ");
		scanf("%s", &user_name);
		if (strlen(user_name) == 3)
		{
			break;
		}
		else
		{
			printf("이름은 3글자로 입력해주세요!! \n");
		}
	}

	UserResult.user = *user_name;
	UserResult.score = user_score;
}

/*
 * Function Name : GetScore
 *
 * Function Description :
 * 스코어 보드 값을 구조체 형태로 반환을 해줌
 *
 * Input : userInfo* scoreBoard
 * Output : void
 * Version : 0.0 미완성임
 */
void ShowScore(userInfo* scoreBoard)
{
	FILE* file = fopen("ranking_table.txt", "r");
	userInfo guest_info;
	char each_score[100];

	//파일에서 한줄씩 읽기
	while (fgets(each_score,
		sizeof(each_score) / sizeof(each_score[0]),
		file) != NULL)
	{

	}
}