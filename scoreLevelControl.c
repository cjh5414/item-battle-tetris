/*Name : scoreLevelControl.c
* Content : 게임 스코어(점수) 관리 및 레벨 관리 함수들의 정의
* Implementation : CJH, SYB
* Last modified 20014/12/01
*/
#include <stdio.h>
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "playMenu.h"

#define LEVEL_DIFF 1	// 단계별 속도 증가 정보

static int LEVEL_UP_SCORE_DIFF = 20; 	// 레벨이 증가하는 스코어 간격 정보
static int curGameScore = 0;
static int curGameCombo[3] = {-1,-1,-1};

int curGameLevel = 1;

/* 함	수 : void ShowCurrentScoreAndLevel(int mode)
* 기	능 : 점수와 레벨 정보 출력
* 반	환 : void
*
*/
void ShowCurrentScoreAndLevel(int mode) {
	if(mode == 0) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 26
			, GBOARD_ORIGIN_Y_1P + 12);
		printf("§ 현재 레벨 : %10d §", curGameLevel);

		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 26
			, GBOARD_ORIGIN_Y_1P + 18);
		printf("§ 다음 레벨 : %10d §", curGameLevel *LEVEL_UP_SCORE_DIFF);

		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 26
			, GBOARD_ORIGIN_Y_1P + 16);
		printf("§ 현재 점수 : %10d §", curGameScore);
	}
	else {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 - 8, GBOARD_ORIGIN_Y_2P_2 + 2);
		printf("Level");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 - 8, GBOARD_ORIGIN_Y_2P_2 + 4);
		printf("%3d", curGameLevel);
	}
}

/* 함	수 : void ShowCurrentCombo(void)
* 기	능 : 콤보 정보 출력
* 반	환 : void
*
*/
void ShowCurrentCombo(int player) {
	switch(player) {
	case 0:
		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 26	, GBOARD_ORIGIN_Y_1P + 14);
		if(curGameCombo[player] == -1)
			printf("§ 현재 콤보 : %10d §", curGameCombo[player] + 1);
		else
			printf("§ 현재 콤보 : %10d §", curGameCombo[player]);
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

/* 함	수 : void GameLevelUp(void)
* 기	능 : 게임 레벨 향상
* 반	환 : void
*
*/
void GameLevelUp(void) {
	curGameLevel++;
	LEVEL_UP_SCORE_DIFF *= 2;
	KeyDelaySpeedCtl(LEVEL_DIFF);
}

/* 함	수 : void GameComboChange(int num)
* 기	능 : 게임 콤보 변경
* 반	환 : void
*
*/
void GameComboChange(int num, int player) {
	if(num == 1)
		curGameCombo[player]++;
	else
		curGameCombo[player] = -1;
}

/* 함	수 : void AddGameScore(int score)
* 기	능 : 게임 레벨 향상
* 반	환 : void
*
*/
void AddGameScore(int score) {
	if(score < 1)
		return;

	curGameScore += score;

	/* 레벨 상승 확인 후 레벨 UP! */
	if(curGameScore >= curGameLevel *LEVEL_UP_SCORE_DIFF)
		GameLevelUp();
}

/* 함	수 : int getGameCombo(void)
* 기	능 : 게임 콤보 반환
* 반	환 : player의 콤보 수를 반환
*
*/
int getGameCombo(int player) {
	return curGameCombo[player];
}

/* 함	수 : int getGameLevel(void)
* 기	능 : 게임 레벨 반환
* 반	환 : 현재 게임 레벨을 반환
*
*/
int getGameLevel(void) {
	return curGameLevel;
}

/* 함   수 : int getGameScore(void)
* 기   능 : 게임 스코어 반환
* 반   환 : 현재 게임 스코어를 반환
*
*/
int getGameScore(void)
{
   return curGameScore;
}

/* 함	수 : void InitGameState(void)
* 기	능 : 게임 레벨, 점수, 콤보 초기화
* 반	환 : void
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