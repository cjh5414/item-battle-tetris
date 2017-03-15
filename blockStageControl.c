/*Name : blockStageControl.c
* Content : 블록관련 함수의 정의
* Implementation : CJH, SYB
* Last modified 20014/12/01
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <Windows.h>
#include "point.h"
#include "blockInfo.h"
#include "keyCurControl.h"
#include "scoreLevelControl.h"
#include "color.h"
#include "blockStageControl.h"
#include "item.h"
#include "playMenu.h"

const int START_CURPOS_X_1P = (16*2);
const int START_CURPOS_Y_1P = (6);
const int START_CURPOS_X_2P_1 = (13*2);
const int START_CURPOS_Y_2P_1 = (6);
const int START_CURPOS_X_2P_2 = (31*2);
const int START_CURPOS_Y_2P_2 = (6);

const int GBOARD_ORIGIN_X_1P = 24;
const int GBOARD_ORIGIN_Y_1P = 7;
const int GBOARD_ORIGIN_X_2P_1 = 18;
const int GBOARD_ORIGIN_Y_2P_1 = 7;
const int GBOARD_ORIGIN_X_2P_2 = 54;
const int GBOARD_ORIGIN_Y_2P_2 = 7;

extern int BGMCheck;

int isItemMode = 1;
int isHoldMode = 1;
int curPosX[3], curPosY[3];
char itemBucket[3][11] = {"", "", ""}; // 아이템10개 + '\0' = 11
int gameBoardInfo[3][GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { {0},0 };
int specialBlock[3] = {0};
int currentBlockModel[3];
int useHold[3] = {0, 0, 0};
int holdBlockModel[3] = {-1, -1, -1};
int rotateSte[3];

static int nextBlockModel[3];
static int nextnextBlockModel[3];

/* 함	수 : void InitRandomBlock(void)
* 기	능 : 다음, 다다음 블록을 랜덤하게 초기화.
* 반	환 : void
*
*/
void InitRandomBlock(void) {
	srand((unsigned)time(NULL));
	nextBlockModel[0] = rand()%7*4;
	nextnextBlockModel[0] = rand()%7*4;
	nextBlockModel[1] = rand()%7*4;
	nextnextBlockModel[1] = rand()%7*4;
	nextBlockModel[2] = rand()%7*4;
	nextnextBlockModel[2] = rand()%7*4;
	specialBlock[1] = 0;
	specialBlock[2] = 0;
}

/* 함	수 : void ShowBlock(char blockInfo[][4]) 
* 기	능 : 현재 블록을 화면에 그림.
* 반	환 : void
*
*/
void ShowBlock(char blockInfo[][4]) {
	int y, x;
	point curPos = GetCurrentCursorPos();

	for(y = 0; y < 4; y++) {
		for(x = 0; x < 4; x++) {
			/*10t 블럭인경우  */
			if(blockInfo[y][x] == 10) {
				SetColor(10);
				SetCurrentCursorPos(curPos.x + (x*2), curPos.y + y);
				printf(" |∩");
				SetCurrentCursorPos(curPos.x + (x*2), curPos.y + y + 1);
				printf(" |∪");
				SetCurrentCursorPos(curPos.x, curPos.y);
				return;
			}
			else if(blockInfo[y][x] >= 1) {
				SetCurrentCursorPos(curPos.x + (x*2), curPos.y + y);
				SetColor(blockInfo[y][x]);
				printf("■");
			}
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);
}

/* 함	수 : void InitNewBlockPos(int x, int y, int player)
* 기	능 : 블록의 위치를 x,y로 옮기고 블록을 그림.
* 반	환 : void
*
*/
void InitNewBlockPos(int x, int y, int player) {
	if(x < 0 || y < 0)
		return;

	curPosX[player] = x;
	curPosY[player] = y;
	SetCurrentCursorPos(curPosX[player], curPosY[player]);
	ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
}

/* 함	수 : void DeleteBlock(char blockInfo[][4])
* 기	능 : 현재 블록을 지움.
* 반	환 : void
*
*/
void DeleteBlock(char blockInfo[][4]) {
	int y, x;
	point curPos = GetCurrentCursorPos();

	for(y = 0; y < 4; y++) {
		for(x = 0; x < 4; x++) {
			SetColor(-1);
			SetCurrentCursorPos(curPos.x+x *2, curPos.y+y);
			if(blockInfo[y][x] >= 1)
				printf("  ");
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);	
}

/* 함	수 : void ChooseBlock(int player)
* 기	능 : 다음, 다다음 블록을 생성
* 반	환 : void
*
*/
void ChooseBlock(int player) {
	point curPos = GetCurrentCursorPos();

	if( player==0 ){
		currentBlockModel[0] = nextBlockModel[0];
		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 28, GBOARD_ORIGIN_Y_1P);
		DeleteBlock(blockModel[nextBlockModel[0]]);
		nextBlockModel[0] = nextnextBlockModel[0];
		ShowBlock(blockModel[nextBlockModel[0]]);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 28, GBOARD_ORIGIN_Y_1P + 6);
		DeleteBlock(blockModel[nextnextBlockModel[0]]);
		nextnextBlockModel[0] = (rand() % 7) * 4;
		ShowBlock(blockModel[nextnextBlockModel[0]]);
	}
	else if( player==1 ){
		if(specialBlock[1] != 3)
			currentBlockModel[1] = nextBlockModel[1];

		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1 - 12, GBOARD_ORIGIN_Y_2P_1);
		DeleteBlock(blockModel[nextBlockModel[1]]);

		if(specialBlock[1] == 3) // 스페셜 블록 처음 생성시.
			nextBlockModel[1] = ((rand() % 10)+8) * 4;
		else // 스페셜 블록 두번째부터 네번째까지 이거나 보통 블럭일 경우
			nextBlockModel[1] = nextnextBlockModel[1];
		ShowBlock(blockModel[nextBlockModel[1]]);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1 - 12, GBOARD_ORIGIN_Y_2P_1 + 6);
		DeleteBlock(blockModel[nextnextBlockModel[1]]);

		if( specialBlock[1] ) // 스페셜 블록 생성
			nextnextBlockModel[1] = ((rand() % 10)+8) * 4;
		else // 보통 블록 생성
			nextnextBlockModel[1] = (rand() % 7) * 4;
		ShowBlock(blockModel[nextnextBlockModel[1]]);
	}

	else {
		if(specialBlock[2] != 3)
			currentBlockModel[2] = nextBlockModel[2];
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 + 28, GBOARD_ORIGIN_Y_2P_2);
		DeleteBlock(blockModel[nextBlockModel[2]]);

		if(specialBlock[2] == 3) // 스페셜 블록 처음 생성시.
			nextBlockModel[2] = ((rand() % 10)+8) * 4;
		else // 스페셜 블록 두번째부터 네번째까지 이거나 보통 블럭일 경우
			nextBlockModel[2] = nextnextBlockModel[2];
		ShowBlock(blockModel[nextBlockModel[2]]);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 + 28, GBOARD_ORIGIN_Y_2P_2 + 6);
		DeleteBlock(blockModel[nextnextBlockModel[2]]);

		if( specialBlock[2] ) // 스페셜 블록 생성
			nextnextBlockModel[2] = ((rand() % 10)+8) * 4;
		else // 보통 블록 생성
			nextnextBlockModel[2] = (rand() % 7) * 4;
		ShowBlock(blockModel[nextnextBlockModel[2]]);
	}
	if(specialBlock[player]!=0)
		specialBlock[player]--;

	SetCurrentCursorPos(curPos.x, curPos.y);
}

/* 함	수 : int GetCurrentBlockIdx(void)
* 기	능 : 현재 출력해야 하는 블록의 intdex 정보 반환
* 반	환 : 현재 블록 Index값을 반환
*
*/
int GetCurrentBlockIdx(int player) {
	return currentBlockModel[player] + rotateSte[player];
}

/* 함	수 : int DetectCollision(int posX, int posY, char blockModel[][4])
* 기	능 : 블록의 이동 및 회전 가능 여부 판단
* 반	환 : 이동 및 회전 가능 시 1 반환
*
*/
int DetectCollision(int posX, int posY, char blockModel[][4], int player) {
	int x, y, arrX, arrY;

	/* gameBoardInfo 배열의 좌표로 변경 */
	switch(player) {
	case 0:
		arrX = (posX - GBOARD_ORIGIN_X_1P) / 2;
		arrY = posY - GBOARD_ORIGIN_Y_1P;
		break;
	case 1:
		arrX = (posX - GBOARD_ORIGIN_X_2P_1) / 2;
		arrY = posY - GBOARD_ORIGIN_Y_2P_1;
		break;
	case 2:
		arrX = (posX - GBOARD_ORIGIN_X_2P_2) / 2;
		arrY = posY - GBOARD_ORIGIN_Y_2P_2;
		break;
	}
	/* 충돌 검사 */
	for(x = 0; x < 4; x++) {
		for(y = 0; y < 4; y++) {
			if(arrY + y < 0) continue;
			/* Short Circuit Evaluation에 의해 배열 일부만 검사 */
			if(blockModel[y][x] >= 1 && gameBoardInfo[player][arrY + y][arrX + x] >= 1)
				return 0;
		}
	}
	return 1;
}

/* 함	수 : void ShiftLeft(void)
* 기	능 : 블록을 왼쪽으로 한 칸 이동
* 반	환 : void
*
*/
void ShiftLeft(int player) {
	if(!DetectCollision(curPosX[player] - 2, curPosY[player] , blockModel[GetCurrentBlockIdx(player)], player))
		return ;

	DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);
	curPosX[player] -= 2;

	SetCurrentCursorPos(curPosX[player], curPosY[player]);
	ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
}

/* 함	수 : void ShiftRight(void)
* 기	능 : 블록을 오른쪽으로 한 칸 이동
* 반	환 : void
*
*/
void ShiftRight(int player) {
	if(!DetectCollision(curPosX[player] + 2, curPosY[player], blockModel[GetCurrentBlockIdx(player)],player))
		return ;

	DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);
	curPosX[player] += 2;

	SetCurrentCursorPos(curPosX[player], curPosY[player]);
	ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
}

/* 함	수 : void RotateBlock(void)
* 기	능 : 블록을 90도 회전
* 반	환 : void
*
*/
void RotateBlock(int player) {
	int nextRotSte;
	int beforeRotSte = rotateSte[player];
	int x, y, arrX, arrY;

	/* gameBoardInfo 배열의 좌표로 변경 */
	if( player==0 ) {
		arrX = (curPosX[player] - GBOARD_ORIGIN_X_1P) / 2;
		arrY = curPosY[player] - GBOARD_ORIGIN_Y_1P;
	}
	else if( player==1 ) {
		arrX = (curPosX[player] - GBOARD_ORIGIN_X_2P_1) / 2;
		arrY = curPosY[player] - GBOARD_ORIGIN_Y_2P_1;
	}
	else {
		arrX = (curPosX[player] - GBOARD_ORIGIN_X_2P_2) / 2;
		arrY = curPosY[player] - GBOARD_ORIGIN_Y_2P_2;
	}
	DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);

	nextRotSte = rotateSte[player] + 1;
	nextRotSte %= 4;
	rotateSte[player] = nextRotSte;

	/* 충돌 검사 */
	for(x = 0; x < 2; x++) {
		for(y = 0; y < 4; y++) {
			if(arrY + y < 0)
				continue;
			if(blockModel[GetCurrentBlockIdx(player)][y][x] >= 1 && gameBoardInfo[player][arrY + y][arrX + x] >= 1) {
				if(DetectCollision(curPosX[player]+2, curPosY[player], blockModel[GetCurrentBlockIdx(player)], player))
					InitNewBlockPos(curPosX[player]+2,curPosY[player],player);   // 왼쪽 벽과 충돌하면 블록 오른쪽으로 한칸 이동
				else
					rotateSte[player] = beforeRotSte;
				ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
				return;
			}
		}
	}
	for(x = 2; x < 4; x++) {
		for(y = 0; y < 4; y++) {
			if(arrY + y < 0)
				continue;
			if(blockModel[GetCurrentBlockIdx(player)][y][x] >= 1 && gameBoardInfo[0][arrY + y][arrX + x] >= 1) {
				if(DetectCollision(curPosX[player]-2, curPosY[player], blockModel[GetCurrentBlockIdx(player)], player))
					InitNewBlockPos(curPosX[player]-2,curPosY[player],player);   // 오른쪽 벽과 충돌하면 블록 왼쪽으로 한칸 이동
				else
					rotateSte[player] = beforeRotSte;
				ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
				return;
			}
		}
	}

	SetCurrentCursorPos(curPosX[player], curPosY[player]);
	ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
}

/* 함	수 : int BlockHold(void)
* 기	능 : 블록을 Hold 공간에 저장
* 반	환 : int
*
*/

int BlockHold(int player) {
	int tmp;

	if(useHold[player] == 1)
		return 1;
	else {
		useHold[player] = 1;
		/* 현재 블록을 hold창에 출력*/
		DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);
		rotateSte[player]=0; // 위에서부터 Hold블록 떨어질 때 기본 모양 나오도록 설정
		switch(player) {
		case 0: SetCurrentCursorPos(GBOARD_ORIGIN_X_1P - 12, GBOARD_ORIGIN_Y_1P); break;
		case 1: SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1 - 12, GBOARD_ORIGIN_Y_2P_1+14); break;
		case 2: SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 + 28 , GBOARD_ORIGIN_Y_2P_2+14); break;
		}
		DeleteBlock(blockModel[holdBlockModel[player]]);
		ShowBlock(blockModel[currentBlockModel[player]]);

		if( holdBlockModel[player]==-1 ) { // 홀드키를 처음 사용하면 0리턴
			holdBlockModel[player] = currentBlockModel[player]; 
			return 0;
		}
		else { // 현재 블록과 hold 블록을 바꿈
			tmp = currentBlockModel[player]; 
			currentBlockModel[player] = holdBlockModel[player];
			holdBlockModel[player] = tmp;
			// Hold 블록이 위에서부터 떨어지도록 좌표 설정
			switch(player) {
			case 0: InitNewBlockPos(START_CURPOS_X_1P, START_CURPOS_Y_1P,player); break;
			case 1: InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1,player); break;
			case 2: InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2,player); break;
			}
			ShowBlock(blockModel[currentBlockModel[player]]); 
			return 1;
		}
	}
}

/* 함	수 : void DrawItemBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* 기	능 : 아이템 창을 그림
* 반	환 : void
*
*/
void DrawItemBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {
	int x, y;   

	SetCurrentCursorPos(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y + 24);
	printf("▲");
	/* 아이템 블록 창 출력 */
	for(x = 0; x < 12; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + 21);
		if(x == 0) printf("┌");
		else printf("─");
	}
	for(y = 0; y < 3; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 21 + y);
		if(y == 0) printf("┐");
		else printf("│");
	}
	for(x = 1; x < 12; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + 23);
		if(x == 11) printf("┘");
		else printf("─");
	}
	for(y = 1; y < 3; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + 21 + y);
		if(y == 2) printf("└");
		else printf("│");
	}
}

/* 함	수 : void DrawShieldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* 기	능 : 쉴드 창을 그림
* 반	환 : void
*
*/
void DrawShieldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {

	SetCurrentCursorPos(GBOARD_ORIGIN_X - 5 * 2, GBOARD_ORIGIN_Y + 24);
	printf("Shield");
	SetCurrentCursorPos(GBOARD_ORIGIN_X - 5 * 2, GBOARD_ORIGIN_Y + 21);
	printf("┌─┐");
	SetCurrentCursorPos(GBOARD_ORIGIN_X - 5 * 2, GBOARD_ORIGIN_Y + 22);
	printf("│  │");
	SetCurrentCursorPos(GBOARD_ORIGIN_X - 5 * 2, GBOARD_ORIGIN_Y + 23);
	printf("└─┘");
}

/* 함	수 : void DrawHoldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* 기	능 : 홀드 창을 그림
* 반	환 : void
*
*/
void DrawHoldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {
	int x, y;   
	/* Hold 출력 */
	if( !isHoldMode ) { // 홀드 사용 안하는 모드
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 11, GBOARD_ORIGIN_Y + 1);
		printf("No Use");
	}

	SetCurrentCursorPos(GBOARD_ORIGIN_X - 10, GBOARD_ORIGIN_Y - 2);
	printf("Hold");

	/* 홀드 블록 창 출력 */
	for(x = 0; x < 5; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 14 + x * 2, GBOARD_ORIGIN_Y - 1);
		if(x == 0) printf("┌");
		else printf("─");
	}
	for(y = 0; y < 5; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 4, GBOARD_ORIGIN_Y - 1 + y);
		if(y == 0) printf("┐");
		else printf("│");
	}
	for(x = 1; x < 6; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 14 + x * 2, GBOARD_ORIGIN_Y + 4);
		if(x == 5) printf("┘");
		else printf("─");
	}
	for(y = 1; y < 6; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 14, GBOARD_ORIGIN_Y - 1 + y);
		if(y == 5) printf("└");
		else printf("│");
	}
}

/* 함	수 : void DrawNextBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* 기	능 : 다음, 다다음 블록 창을 그림.
* 반	환 : void
*
*/
void DrawNextBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {
	int x, y;
	/* Next 출력 */
	SetCurrentCursorPos(GBOARD_ORIGIN_X + 30, GBOARD_ORIGIN_Y - 2);
	printf("Next");

	/* 다음 블록 창 출력 */
	for(x = 0; x < 5; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26 + x * 2, GBOARD_ORIGIN_Y - 1);
		if(x == 0) printf("┌");
		else printf("─");
	}
	for(y = 0; y < 5; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 36, GBOARD_ORIGIN_Y - 1 + y);
		if(y == 0) printf("┐");
		else printf("│");
	}
	for(x = 1; x < 6; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26 + x * 2, GBOARD_ORIGIN_Y + 4);
		if(x == 5) printf("┘");
		else printf("─");
	}
	for(y = 1; y < 6; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26, GBOARD_ORIGIN_Y - 1 + y);
		if(y == 5) printf("└");
		else printf("│");
	}

	/*다다음 블록 창 출력*/
	for(x = 0; x < 5; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26 + x * 2, GBOARD_ORIGIN_Y + 5);
		if(x == 0) printf("┌");
		else printf("─");
	}
	for(y = 0; y < 5; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 36, GBOARD_ORIGIN_Y + 5 + y);
		if(y == 0) printf("┐");
		else printf("│");
	}
	for(x = 1; x < 6; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26 + x * 2, GBOARD_ORIGIN_Y + 10);
		if(x == 5) printf("┘");
		else printf("─");
	}
	for(y = 1; y < 6; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26, GBOARD_ORIGIN_Y + 5 + y);
		if(y == 5) printf("└");
		else printf("│");
	}
}

/* 함	수 : void DrawNextBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* 기	능 : 게임 벽을 그림.
* 반	환 : void
*
*/
void DrawGameWall(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {
	int x, y;
	/* 시각적인 부분 처리 */
	SetColor(-1);
	for(y = 0; y <= GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);

		if(y == GBOARD_HEIGHT) printf("└");
		else printf("│");
	}

	for(y = 0; y <= GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(
			GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2,
			GBOARD_ORIGIN_Y + y);

		if(y == GBOARD_HEIGHT) printf("┘");
		else printf("│");
	}

	for(x = 1; x < GBOARD_WIDTH + 1; x++) {
		SetCurrentCursorPos(
			GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("─");
	}
}

/* 함	수 : void DrawGameBoard(void)
* 기	능 : 전체적인 게임 판의 경계 면을 그린다.
* 반	환 : void
*
*/
void DrawGameBoard(int player) {
	int x, y, z;
	SetColor(-1); // 검은색으로 설정

	if( player == 0) {
		DrawHoldBlock(GBOARD_ORIGIN_X_1P, GBOARD_ORIGIN_Y_1P);
		DrawGameWall(GBOARD_ORIGIN_X_1P, GBOARD_ORIGIN_Y_1P);
		DrawNextBlock(GBOARD_ORIGIN_X_1P, GBOARD_ORIGIN_Y_1P);
	}
	else {
		DrawHoldBlock(GBOARD_ORIGIN_X_2P_1, GBOARD_ORIGIN_Y_2P_1+14);
		DrawGameWall(GBOARD_ORIGIN_X_2P_1, GBOARD_ORIGIN_Y_2P_1);
		DrawNextBlock(GBOARD_ORIGIN_X_2P_1-40, GBOARD_ORIGIN_Y_2P_1);
		DrawItemBlock(GBOARD_ORIGIN_X_2P_1, GBOARD_ORIGIN_Y_2P_1);
		DrawShieldBlock(GBOARD_ORIGIN_X_2P_1, GBOARD_ORIGIN_Y_2P_1);

		DrawHoldBlock(GBOARD_ORIGIN_X_2P_2+40, GBOARD_ORIGIN_Y_2P_2+14);
		DrawGameWall(GBOARD_ORIGIN_X_2P_2, GBOARD_ORIGIN_Y_2P_2);
		DrawNextBlock(GBOARD_ORIGIN_X_2P_2, GBOARD_ORIGIN_Y_2P_2);
		DrawItemBlock(GBOARD_ORIGIN_X_2P_2, GBOARD_ORIGIN_Y_2P_2);
		DrawShieldBlock(GBOARD_ORIGIN_X_2P_2 + 38, GBOARD_ORIGIN_Y_2P_2);
	}
	/* 데이터 부분 처리 */
	for(z = 0; z < 3; z++) {
		for(y = 0; y < GBOARD_HEIGHT; y++) {
			gameBoardInfo[z][y][0] = 1;
			gameBoardInfo[z][y][GBOARD_WIDTH + 1] = 1;
		}
		for(x = 0; x < GBOARD_WIDTH + 2; x++) 
			gameBoardInfo[z][GBOARD_HEIGHT][x] = 1;
	}
}

/* 함	수 : void AddCurrentBlockInfoToBoard(void)
* 기	능 : 배열에 현재 블록의 정보를 추가한다.
* 반	환 : void
*
*/
void AddCurrentBlockInfoToBoard(char blockInfo[][4], int player) {
	int x, y;

	int arrCurX;
	int arrCurY;

	for(y = 0; y < 4; y++) {
		for(x = 0; x < 4; x++) {
			/* 커서 위치 정보를 배열 index 정보로 변경 */
			switch(player) {
			case 0:
				arrCurX = (curPosX[player] - GBOARD_ORIGIN_X_1P) / 2;
				arrCurY = curPosY[player] - GBOARD_ORIGIN_Y_1P;
				break;
			case 1:
				arrCurX = (curPosX[player] - GBOARD_ORIGIN_X_2P_1) / 2;
				arrCurY = curPosY[player] - GBOARD_ORIGIN_Y_2P_1;
				break;
			case 2:
				arrCurX = (curPosX[player] - GBOARD_ORIGIN_X_2P_2) / 2;
				arrCurY = curPosY[player] - GBOARD_ORIGIN_Y_2P_2;
				break;
			}
			if(blockModel[GetCurrentBlockIdx(player)][y][x] >= 1)
				gameBoardInfo[player][arrCurY + y][arrCurX + x] = blockModel[GetCurrentBlockIdx(player)][y][x];
		}
	}
}

/* 함	수 : int IsGameOver(void)
* 기	능 : 게임이 종료되었는지 확인하는 함수
* 반	환 : 게임 종료 시 1 반환
*
*/
int IsGameOver(int player) {
	if(!DetectCollision(curPosX[player], curPosY[player], blockModel[GetCurrentBlockIdx(player)], player)) {
		if(player == 0)
			return 1;
		return player;
	}
	else
		return 0;
}

/* 함	수 : void ShowLoser(int loser)
* 기	능 : 승자, 패자 표시
* 반	환 : void
*
*/
void ShowLoser(int loser) {
	SetColor(-1);
	SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+8, GBOARD_ORIGIN_Y_2P_1+9);
	printf("          ");
	SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2+8, GBOARD_ORIGIN_Y_2P_2+9);
	printf("          ");
	if( loser==1 ) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+8, GBOARD_ORIGIN_Y_2P_1+10);
		printf("  LOSE  ");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2+8, GBOARD_ORIGIN_Y_2P_2+10);
		printf("   WIN  ");
	}
	else {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2+10, GBOARD_ORIGIN_Y_2P_2+10);
		printf("LOSE");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+10, GBOARD_ORIGIN_Y_2P_1+10);
		printf(" WIN");
	}		
	SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+8, GBOARD_ORIGIN_Y_2P_1+11);
	printf("          ");
	SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2+8, GBOARD_ORIGIN_Y_2P_2+11);
	printf("          ");
}

/* 함	수 : void DrawSolidBlocks(int player)
* 기	능 : 게임 판에 굳어진 블록을 그린다.
* 반	환 : void
*
*/
void DrawSolidBlocks(int player) {
	int x, y;
	int cursX, cursY;

	for(y = 0; y < GBOARD_HEIGHT; y++) {
		for(x = 1; x < GBOARD_WIDTH + 1; x++) {
			switch(player) {
			case 0:
				cursX = x * 2 + GBOARD_ORIGIN_X_1P;
				cursY = y + GBOARD_ORIGIN_Y_1P;
				break;
			case 1:
				cursX = x * 2 + GBOARD_ORIGIN_X_2P_1;
				cursY = y + GBOARD_ORIGIN_Y_2P_1;
				break;
			case 2:
				cursX = x * 2 + GBOARD_ORIGIN_X_2P_2;
				cursY = y + GBOARD_ORIGIN_Y_2P_2;
				break;
			}
			SetCurrentCursorPos(cursX, cursY);
			if(isalpha(gameBoardInfo[player][y][x])) {
				SetColor(gameBoardInfo[player][y][x]);
				printf("%s",GetItemShape(gameBoardInfo[player][y][x]));
			}
			else if(gameBoardInfo[player][y][x] >= 1) {
				SetColor(gameBoardInfo[player][y][x]);
				printf("■");
			}
			else {
				SetColor(-1);
				printf("  ");
			}
		}
	}
}

/* 함	수 : void DrawItemBucket(int player)
* 기	능 : player의 아이템 창들을 그린다.
* 반	환 : void
*
*/
void DrawItemBucket(int player) {
	int i;
	if(player == 1) 
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+2, GBOARD_ORIGIN_Y_2P_1+22);
	else if( player == 2) 
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2+2, GBOARD_ORIGIN_Y_2P_2+22);

	for(i=0; i<10; i++) {
		SetColor(itemBucket[player][i]);
		printf("%s",GetItemShape(itemBucket[player][i]));
	}
	ItemInfo(player, itemBucket[player][0]);
}

/* 함	수 : void ShowID(int player)
* 기	능 : player의 아이디를 보여준다
* 반	환 : void
*
*/
void ShowID(int player) {
	SetColor(-1);
	switch(player) {
	case 0: 
		SetCurrentCursorPos(GBOARD_ORIGIN_X_1P+1, GBOARD_ORIGIN_Y_1P-3);
		printf("ID: %s", ID_1p);
		break;
	case 1:
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+1, GBOARD_ORIGIN_Y_2P_1-3);
		printf("1P : %s", ID_1p);
		break;
	case 2:
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2+1, GBOARD_ORIGIN_Y_2P_2-3);
		printf("2P : %s", ID_2p);
		break;
	}
}

/* 함	수 : void AddLine(int player, int lineNum)
* 기	능 : 해당 플레이어에게 lineNum 만큼 추가한다
* 반	환 : void
*
*/
void AddLine(int player, int lineNum) {
	int i, j, line, emptyLocation = rand() % 10 + 1;
	for(i = 0; i < lineNum; i++) {
		for(line = 0; line < 19; line++) {
			memcpy(
				&gameBoardInfo[player][line][1],
				&gameBoardInfo[player][line + 1][1],
				GBOARD_WIDTH * sizeof(int)
				);
			if(!DetectCollision(curPosX[player], curPosY[player], blockModel[GetCurrentBlockIdx(player)], player)) {
				SetCurrentCursorPos(curPosX[player], curPosY[player]);
				DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);
				curPosY[player] -= 1;
				SetCurrentCursorPos(curPosX[player], curPosY[player]);
				SetColor(GetCurrentBlockIdx(player));
				ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
			}
		}
		SetColor(9);
		for(j = 1; j < 11; j++) {
			if(emptyLocation == j)
				gameBoardInfo[player][19][j] = 0;
			else
				gameBoardInfo[player][19][j] = 9;
		}
	}
	DrawSolidBlocks(player);
	useHold[player] = 0;
	SetCurrentCursorPos(curPosX[player], curPosY[player]);
	SetColor(GetCurrentBlockIdx(player));
	ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
}

/* 함	수 : void SubLine(int player, int lineNum)
* 기	능 : 해당 플레이어에게 lineNum 만큼 제거한다
* 반	환 : void
*
*/
void SubLine(int player, int lineNum) {
	int i, line;
	for(i = 0; i < lineNum; i++) {
		for(line = 18; line >= 0; line--) {
			memcpy(
				&gameBoardInfo[player][line + 1][1],
				&gameBoardInfo[player][line][1],
				GBOARD_WIDTH * sizeof(int)
				);
			if(!DetectCollision(curPosX[player], curPosY[player], blockModel[GetCurrentBlockIdx(player)], player)) {
				SetCurrentCursorPos(curPosX[player], curPosY[player]);
				DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);
				curPosY[player] -= 1;
				SetCurrentCursorPos(curPosX[player], curPosY[player]);
				SetColor(GetCurrentBlockIdx(player));
				ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
			}
		}
	}
	DrawSolidBlocks(player);
	useHold[player] = 0;
}

/* 함	수 : void RemoveFillUpLine(void)
* 기	능 : 행 단위로 채워진 블록을 삭제한다.
* 반	환 : void
*
*/
void RemoveFillUpLine(int player) {
	int x, y, i;
	int line, beforeCombo = getGameCombo(player), checkCombo = -2, lineCount = 0, itemHappen;

	for(y = GBOARD_HEIGHT - 1; y > 0; y--) {
		for(x = 1; x < GBOARD_WIDTH + 1; x++) {
			if(gameBoardInfo[player][y][x] < 1)
				break;
		}

		if(x == (GBOARD_WIDTH + 1))	{	// 라인이 다 채워졌다면

			for(i=1; i<11; i++) {
				if( isalpha(gameBoardInfo[player][y][i]) ) {
					if( strlen(itemBucket[player]) < 10 ) {
						itemBucket[player][strlen(itemBucket[player])] = gameBoardInfo[player][y][i];
						itemBucket[player][strlen(itemBucket[player])+1] = '\0';
					}
				}
			}
			for(line = 0; y - line > 0; line++) {
				memcpy(
					&gameBoardInfo[player][y - line][1],
					&gameBoardInfo[player][(y - line) - 1][1],
					GBOARD_WIDTH * sizeof(int)
					);
			}
			for(i = 1; i <= GBOARD_WIDTH; i++)
				gameBoardInfo[player][0][i] = 0;
			if( checkCombo != getGameCombo(player)) {
				GameComboChange(1,player);
				checkCombo = getGameCombo(player);
			}
			if( getGameCombo(player) > 0)
				AddGameScore(10 * getGameLevel() * getGameCombo(player));
			else
				AddGameScore(10 * getGameLevel());
			y++;	// 배열 정보가 아래로 한 칸씩 이동했으므로

			SetColor(-1);
			ShowCurrentScoreAndLevel(player);

			lineCount++;
		}
	}
	if(isItemMode) {
		for(i = 0; i < lineCount; i++) {
			itemHappen = rand() % 40 + 65;
			MakeItem(player, itemHappen);
		}
		DrawItemBucket(player);
	}

	// 테트리스를 할 경우 미쳐날뛰고 있습니다 출력
	if(lineCount == 4 && BGMCheck == 1) {
		PlaySound(TEXT("미쳐 날뛰고 있습니다.wav"),
			NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	}

	if(lineCount > 2) {
		if(player)
			AddLine((2-player)%2 + 1, lineCount - 2);
	}
	if(beforeCombo == getGameCombo(player))
		GameComboChange(0,player);
	else if(player) {
		switch(getGameCombo(player)) {
		case 3:
		case 4:
		case 5:
			AddLine((2-player)%2 + 1, 1);
			break;
		case 6:
		case 7:
			AddLine((2-player)%2 + 1, 2);
			break;
		case 8:
		case 9:
			AddLine((2-player)%2 + 1, 3);
			break;
		case 10:
		case 11:
			AddLine((2-player)%2 + 1, 4);
			break;
		case 12:
		case 13:
			AddLine((2-player)%2 + 1, 5);
			break;
		}
	}
	DrawSolidBlocks(player);
	useHold[player] = 0;
	SetColor(-1);
	ShowCurrentCombo(player);
	switch(player) {
	case 0: 
		curPosX[player] = START_CURPOS_X_1P;
		curPosY[player] = START_CURPOS_Y_1P;
		SetCurrentCursorPos(START_CURPOS_X_1P, START_CURPOS_Y_1P);
		break;
	case 1: 
		curPosX[player] = START_CURPOS_X_2P_1;
		curPosY[player] = START_CURPOS_Y_2P_1;
		SetCurrentCursorPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1);
		break;
	case 2:
		curPosX[player] = START_CURPOS_X_2P_2;
		curPosY[player] = START_CURPOS_Y_2P_2;
		SetCurrentCursorPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2); 
		break;
	}
}

/* 함	수 : int BlockDown(void)
* 기	능 : 모니터에 그려진 블록을 아래로 한 칸 내림
* 반	환 : 성공 시 1, 실패 시 0
*
*/
int BlockDown(int player) {
	int y, x;
	if(!DetectCollision(curPosX[player], curPosY[player] + 1, blockModel[GetCurrentBlockIdx(player)], player)) {

		if(BGMCheck == 1){
			PlaySound(TEXT("블럭깸.wav"),
				NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT | SND_NOSTOP);
		}

		/*10t 블럭인경우  */
		if(currentBlockModel[player]>27 && currentBlockModel[player] < 32) { // 10t 블록이면
			if( player == 1 ) { 
				x = ( curPosX[player] - GBOARD_ORIGIN_X_2P_1 + 2 ) / 2;
				y = curPosY[player] - GBOARD_ORIGIN_Y_2P_1 + 1;
			}
			else if( player == 2 ) {
				x = ( curPosX[player] - GBOARD_ORIGIN_X_2P_2 + 2) / 2;
				y = curPosY[player] - GBOARD_ORIGIN_Y_2P_2 + 1;
			}
			for( ; y<20; y++ ) {
				gameBoardInfo[player][y][x] = 0;
				gameBoardInfo[player][y][x+1] = 0;   
			}
			DrawSolidBlocks(player);
			useHold[player]  = 0;
			SetColor(10);
			if( player == 1 ) {
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_1, y+GBOARD_ORIGIN_Y_2P_1-2);
				printf(" |∩");
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_1, y+GBOARD_ORIGIN_Y_2P_1-1);
				printf(" |∪");
				Sleep(100);
				SetColor(-1);
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_1, y+GBOARD_ORIGIN_Y_2P_1-2);
				printf("    ");
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_1, y+GBOARD_ORIGIN_Y_2P_1-1);
				printf("    ");
			}
			else if( player == 2) {
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_2, y+GBOARD_ORIGIN_Y_2P_2-2);
				printf(" |∩");
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_2, y+GBOARD_ORIGIN_Y_2P_2-1);
				printf(" |∪");
				Sleep(100);
				SetColor(-1);
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_2, y+GBOARD_ORIGIN_Y_2P_2-2);
				printf("    ");
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_2, y+GBOARD_ORIGIN_Y_2P_2-1);
				printf("    ");
			}
			ChooseBlock(player);
			if( player==1 ) {
				curPosX[player] = START_CURPOS_X_2P_1;
				curPosY[player] = START_CURPOS_Y_2P_1;
				SetCurrentCursorPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1);
			}      
			else if( player==2 ) {
				curPosX[player] = START_CURPOS_X_2P_2;
				curPosY[player] = START_CURPOS_Y_2P_2;
				SetCurrentCursorPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2); 
			}   
			return 0;
		}

		/* 행 단위로 채워진 블록 정보 검사 */
		AddCurrentBlockInfoToBoard(blockModel[GetCurrentBlockIdx(player)],player);
		RemoveFillUpLine(player);
		rotateSte[player] = 0;
		ChooseBlock(player);
		return 0;
	}
	SetCurrentCursorPos(curPosX[player], curPosY[player]);

	DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);
	curPosY[player] += 1;

	SetCurrentCursorPos(curPosX[player], curPosY[player]);

	SetColor(GetCurrentBlockIdx(player));
	ShowBlock(blockModel[GetCurrentBlockIdx(player)]);
	return 1;
}

/* 함   수 : void InitGameBoardInfo()
* 기   능 : 게임 보드 블록의 상태를 0으로 초기화 한다.
* 반   환 : void
*
*/
void InitGameBoardInfo() {
	int x, y, i;
	for(i = 0; i < 3; i++) {
		for(y = 0; y < 20; y++) {
			for(x = 1; x < 11; x++) {
				gameBoardInfo[i][y][x] = 0;
			}
		}
	}
}

/* 함	수 : void InitItemBucket(void)
* 기	능 : 아이템 버켓을 초기화한다.
* 반	환 : void
*
*/
void InitItemBucket(void) {
	int i;
	for(i = 0; i < 11; i++) {
		itemBucket[1][i] = '\0';
		itemBucket[2][i] = '\0';
	}
}

/* 함	수 : void SolidCurrentBlock(void)
* 기	능 : 현재의 블록을 바닥으로 이동시켜 굳힌다.
* 반	환 : void
*
*/
void SolidCurrentBlock(int player) {
	while(BlockDown(player));
}

/* end of file */