#pragma once
#define MAX_USER_NUMBER 5//�ִ� ���� ��    

typedef struct {
	char user[3];
	int score;
}userInfo;

userInfo scoreBoard[5];
userInfo UserResult;


void GetScore(char user_name, int user_score);
void ShowScore(userInfo* scoreBoard);

