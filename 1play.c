/* Name : 1play.c
* Content : main 함수의 정의
* Implementation : CJH, SYB
*
* Last modified 2014/11/10
*/

#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "keyCurControl.h"
#include "blockStageControl.h"
#include "scoreLevelControl.h"
#include "color.h"
#include "basicHeader.h"
#include "scoreSave.h"

int oneplay(int mode) {
	int temp;

	/*게임 스코어, 레벨, 콤보 초기화*/
	InitGameState();

	/* 게임 보드 블록 정보 초기화 */
	InitGameBoardInfo();

	/* No item으로 설정 */
	isItemMode = 0;

	/* 게임 속도 설정 */
	InitKeyDelayRate(curGameLevel);

	/* 커서 깜박임 제거 */
	CursorSetting(0);

	/* player의 ID 표시 */
	ShowID(0);

	/* 게임 보드 그리기 */
	DrawGameBoard(0);

	/* 현재 점수, 레벨 표시 */
	ShowCurrentScoreAndLevel(mode);

	/* 현재 콤보 표시 */
	ShowCurrentCombo(0);

	/* 블럭 초기값 랜덤하게 설정 */
	InitRandomBlock();

	/* 초기블럭 설정*/
	/* 0: 1P, 1: 2p_1, 2: 2P_2*/
	ChooseBlock(0);

	/* 블럭 초기 생성 위치 설정*/
	/* 1인용 2인용에 관계없이 3번째 매개변수가 1이면 player1, 2이면 player2 */
	InitNewBlockPos(START_CURPOS_X_1P, START_CURPOS_Y_1P,0);

	/* 반복적으로 새로운 블록의 등장 */
	while(1) {
		/* 게임 종료 확인 */
		if(IsGameOver(0))  {
			SortGameResult(getGameScore(), ID_1p, isHoldMode);
			SaveRankFile();
			break;
		}
		/* 내리는 작업 시작 */
		while(1) {
			/* 블록을 아래로 한 칸 이동*/
			if(!BlockDown(0)) { // 블록 이동실패 시
				InitNewBlockPos(START_CURPOS_X_1P, START_CURPOS_Y_1P,0);
				break;
			}
			/* 게이머 키 입력 처리 */
			if(temp = ProcessKeyInput(0))
				return temp;
		}
	}
	SetColor(-1); // 텍스트 출력인 기본 색으로 설정
	SetCurrentCursorPos(GBOARD_ORIGIN_X_1P+6, GBOARD_ORIGIN_Y_1P+10);
	printf("  Game Over!  ");
	Sleep(1000);
	SetCurrentCursorPos(GBOARD_ORIGIN_X_1P, GBOARD_ORIGIN_Y_1P+22);
	printf("Press any key to return to menu");
	fflush(stdin);
	getch();
	fflush(stdin);

	return 0;
}

/* end of file */



