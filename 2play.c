/* Name : 2play.c
* Content : main 함수의 정의
* Implementation : CJH, SYB
*
* Last modified 2014/11/20
*/
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "keyCurControl.h"
#include "blockStageControl.h"
#include "scoreLevelControl.h"
#include "color.h"
#include "keyCurControl.h"
#include "map.h"
#include "basicHeader.h"
#include "scoreSave2.h"
#include "playMenu.h"

/* 게임 전적 비교 함수 */
void CompareAndSave(int winner, int loser)
{
	NodeTwo* player[2], *pre = HeadTwo;

	player[0]=player[1]=NULL;

	player[0]=SearchNode(ID_1p);
	player[1]=SearchNode(ID_2p);

	if(player[winner]!=NULL)
	{
		if(player[winner]->rank != 1) {
			while(pre != NULL) {
				if(strcmp(pre->Next->ID, player[winner]->ID) == 0)
					break;
				pre = pre->Next;
			}
		}
		player[winner]->win++;
		player[winner]->record++;
		player[winner]->rate=(double)player[winner]->win/(player[winner]->win+player[winner]->lose)*100;
		pre->Next = player[winner]->Next;
		player[winner]->Next = NULL;
	}
	else
	{
		if(winner==0)
			AppendNodeTwo(&HeadTwo, Create_RankNodeTwo(1, 1, ID_1p, 1, 0, 100.0));
		else
			AppendNodeTwo(&HeadTwo, Create_RankNodeTwo(1, 1, ID_2p, 1, 0, 100.0));
	}

	if(player[loser]!=NULL)
	{
		player[loser]->lose++;
		player[loser]->record++;
		player[loser]->rate=(double)player[loser]->win/(player[loser]->win+player[loser]->lose)*100;
	}
	else
	{
		if(loser==0)
			AppendNodeTwo(&HeadTwo, Create_RankNodeTwo(1, 1, ID_1p, 0, 1, 0.0));
		else
			AppendNodeTwo(&HeadTwo, Create_RankNodeTwo(1, 1, ID_2p, 0, 1, 0.0));
	}
	if(player[winner]->rank == 1)
		return;
	if(HeadTwo->win < player[winner]->win) {
		player[winner]->Next = HeadTwo;
		HeadTwo = player[winner];
		return;
	}
	for(pre = HeadTwo; pre->Next != NULL; pre = pre->Next) {
		if(pre->Next->win < player[winner]->win) {
			player[winner]->Next = pre->Next;
			pre->Next = player[winner];
			return;
		}
	}
	pre->Next = player[winner];
}

int twoplay(int mode) {
	int temp, loser;

	/*아이템 버켓 초기화*/
	InitItemBucket();

	/*게임 스코어, 레벨, 콤보 초기화*/
	InitGameState();
	isItemMode = optionItemMode;

	/* 게임 보드 블록 정보 초기화 */
	InitGameBoardInfo();

	/* 게임 속도 설정 */
	InitKeyDelayRate(curGameLevel);

	/* 커서 깜박임 제거 */
	CursorSetting(0);

	/*맵 선택*/
	MapChoice();

	/* player의 ID 표시 */
	ShowID(1);
	ShowID(2);

	/* 게임 보드 그리기 */
	DrawGameBoard(1);

	/* 현재 점수, 레벨 표시 */
	ShowCurrentScoreAndLevel(mode);

	/* 블럭 초기값 랜덤하게 설정 */
	InitRandomBlock();

	/* 초기블럭 설정*/
	ChooseBlock(1);
	ChooseBlock(2);

	/* 블럭 초기 생성 위치 설정*/
	InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1,1);
	InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2,2);

	/* 반복적으로 새로운 블록의 등장 */
	while(1) {
		/* 게임 종료 확인 */
		if( IsGameOver(1) ) {
			loser = 1;
			break;
		}
		else if( IsGameOver(2) ) {
			loser = 2;
			break;
		}
		/* 내리는 작업 시작 */
		while(1) {
			/* 블록을 아래로 한 칸 이동*/
			if( !BlockDown(1) ) {	// 블록 이동실패 시
				InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1,1);
				break;
			}

			if( !BlockDown(2) ) {	// 블록 이동실패 시
				InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2,2);
				break;
			}
			/* 게이머 키 입력 처리 */
			if(temp = ProcessKeyInput(1))
				return temp;
		}
	}
	if(loser == 1)
		SortGameResultTwo(ID_2p, ID_1p);
	else
		SortGameResultTwo(ID_1p, ID_2p);
	SaveTwoRankFile();
	ShowLoser(loser);
	Sleep(1000);
	SetColor(-1);
	SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+14, GBOARD_ORIGIN_Y_2P_1+27);
	printf("Press any key to return to menu");
	fflush(stdin);
	getch();
	fflush(stdin);
	return 0;
}

/* end of file */