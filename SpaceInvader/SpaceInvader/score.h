#pragma once
#define MAX_USER_NUMBER 5//�ִ� ���� ��    

typedef struct {
	char user[10];
	int score;
}userInfo;

userInfo scoreBoard[5];
userInfo UserResult;

void GetScore(int user_score);
void SaveScore(void);
void ShowScore(userInfo* scoreBoard);


