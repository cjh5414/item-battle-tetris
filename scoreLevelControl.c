/*Name : scoreLevelControl.c
* Content : ���� ���ھ�(����) ���� �� ���� ���� �Լ����� ����
* Implementation : CJH, SYB
* Last modified 20014/12/01
*/
#include <stdio.h>
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "playMenu.h"

#define LEVEL_DIFF 1	// �ܰ躰 �ӵ� ���� ����

static int LEVEL_UP_SCORE_DIFF = 20; 	// ������ �����ϴ� ���ھ� ���� ����
static int curGameScore = 0;
static int curGameCombo[3] = {-1,-1,-1};

int curGameLevel = 1;

/* ��	�� : void ShowCurrentScoreAndLevel(int mode)
* ��	�� : ������ ���� ���� ���
* ��	ȯ : void
*
*/
void ShowCurrentScoreAndLevel(int mode) {
	if(mode == 0) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 26
			, GBOARD_ORIGIN_Y_1P + 12);
		printf("�� ���� ���� : %10d ��", curGameLevel);

		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 26
			, GBOARD_ORIGIN_Y_1P + 18);
		printf("�� ���� ���� : %10d ��", curGameLevel *LEVEL_UP_SCORE_DIFF);

		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 26
			, GBOARD_ORIGIN_Y_1P + 16);
		printf("�� ���� ���� : %10d ��", curGameScore);
	}
	else {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 - 8, GBOARD_ORIGIN_Y_2P_2 + 2);
		printf("Level");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 - 8, GBOARD_ORIGIN_Y_2P_2 + 4);
		printf("%3d", curGameLevel);
	}
}

/* ��	�� : void ShowCurrentCombo(void)
* ��	�� : �޺� ���� ���
* ��	ȯ : void
*
*/
void ShowCurrentCombo(int player) {
	switch(player) {
	case 0:
		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 26	, GBOARD_ORIGIN_Y_1P + 14);
		if(curGameCombo[player] == -1)
			printf("�� ���� �޺� : %10d ��", curGameCombo[player] + 1);
		else
			printf("�� ���� �޺� : %10d ��", curGameCombo[player]);
		break;
	case 1:
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1 - 14, GBOARD_ORIGIN_Y_1P + 20);
		if(curGameCombo[player] <= 0)
			printf("             ");
		else
			printf(" %2d Combo! ", curGameCombo[player]);
		break;
	case 2:
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 + 26, GBOARD_ORIGIN_Y_1P + 20);
		if(curGameCombo[player] <= 0)
			printf("             ");
		else
			printf(" %2d Combo! ", curGameCombo[player]);
		break;
	}
}

/* ��	�� : void GameLevelUp(void)
* ��	�� : ���� ���� ���
* ��	ȯ : void
*
*/
void GameLevelUp(void) {
	curGameLevel++;
	LEVEL_UP_SCORE_DIFF *= 2;
	KeyDelaySpeedCtl(LEVEL_DIFF);
}

/* ��	�� : void GameComboChange(int num)
* ��	�� : ���� �޺� ����
* ��	ȯ : void
*
*/
void GameComboChange(int num, int player) {
	if(num == 1)
		curGameCombo[player]++;
	else
		curGameCombo[player] = -1;
}

/* ��	�� : void AddGameScore(int score)
* ��	�� : ���� ���� ���
* ��	ȯ : void
*
*/
void AddGameScore(int score) {
	if(score < 1)
		return;

	curGameScore += score;

	/* ���� ��� Ȯ�� �� ���� UP! */
	if(curGameScore >= curGameLevel *LEVEL_UP_SCORE_DIFF)
		GameLevelUp();
}

/* ��	�� : int getGameCombo(void)
* ��	�� : ���� �޺� ��ȯ
* ��	ȯ : player�� �޺� ���� ��ȯ
*
*/
int getGameCombo(int player) {
	return curGameCombo[player];
}

/* ��	�� : int getGameLevel(void)
* ��	�� : ���� ���� ��ȯ
* ��	ȯ : ���� ���� ������ ��ȯ
*
*/
int getGameLevel(void) {
	return curGameLevel;
}

/* ��   �� : int getGameScore(void)
* ��   �� : ���� ���ھ� ��ȯ
* ��   ȯ : ���� ���� ���ھ ��ȯ
*
*/
int getGameScore(void)
{
   return curGameScore;
}

/* ��	�� : void InitGameState(void)
* ��	�� : ���� ����, ����, �޺� �ʱ�ȭ
* ��	ȯ : void
*
*/
void InitGameState(void) {
	int i;
	for(i=0; i<3; i++) {
		curGameCombo[i] = -1;
		holdBlockModel[i] = -1;
		useHold[i] = 0;
		rotateSte[i] = 0;
	}
	curGameScore = 0;
	LEVEL_UP_SCORE_DIFF=20;
	curGameLevel = optionGameLevel;
}