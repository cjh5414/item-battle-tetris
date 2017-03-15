/*Name : blockStageControl.c
* Content : ��ϰ��� �Լ��� ����
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
char itemBucket[3][11] = {"", "", ""}; // ������10�� + '\0' = 11
int gameBoardInfo[3][GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { {0},0 };
int specialBlock[3] = {0};
int currentBlockModel[3];
int useHold[3] = {0, 0, 0};
int holdBlockModel[3] = {-1, -1, -1};
int rotateSte[3];

static int nextBlockModel[3];
static int nextnextBlockModel[3];

/* ��	�� : void InitRandomBlock(void)
* ��	�� : ����, �ٴ��� ����� �����ϰ� �ʱ�ȭ.
* ��	ȯ : void
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

/* ��	�� : void ShowBlock(char blockInfo[][4]) 
* ��	�� : ���� ����� ȭ�鿡 �׸�.
* ��	ȯ : void
*
*/
void ShowBlock(char blockInfo[][4]) {
	int y, x;
	point curPos = GetCurrentCursorPos();

	for(y = 0; y < 4; y++) {
		for(x = 0; x < 4; x++) {
			/*10t ���ΰ��  */
			if(blockInfo[y][x] == 10) {
				SetColor(10);
				SetCurrentCursorPos(curPos.x + (x*2), curPos.y + y);
				printf(" |��");
				SetCurrentCursorPos(curPos.x + (x*2), curPos.y + y + 1);
				printf(" |��");
				SetCurrentCursorPos(curPos.x, curPos.y);
				return;
			}
			else if(blockInfo[y][x] >= 1) {
				SetCurrentCursorPos(curPos.x + (x*2), curPos.y + y);
				SetColor(blockInfo[y][x]);
				printf("��");
			}
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);
}

/* ��	�� : void InitNewBlockPos(int x, int y, int player)
* ��	�� : ����� ��ġ�� x,y�� �ű�� ����� �׸�.
* ��	ȯ : void
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

/* ��	�� : void DeleteBlock(char blockInfo[][4])
* ��	�� : ���� ����� ����.
* ��	ȯ : void
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

/* ��	�� : void ChooseBlock(int player)
* ��	�� : ����, �ٴ��� ����� ����
* ��	ȯ : void
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

		if(specialBlock[1] == 3) // ����� ��� ó�� ������.
			nextBlockModel[1] = ((rand() % 10)+8) * 4;
		else // ����� ��� �ι�°���� �׹�°���� �̰ų� ���� ���� ���
			nextBlockModel[1] = nextnextBlockModel[1];
		ShowBlock(blockModel[nextBlockModel[1]]);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1 - 12, GBOARD_ORIGIN_Y_2P_1 + 6);
		DeleteBlock(blockModel[nextnextBlockModel[1]]);

		if( specialBlock[1] ) // ����� ��� ����
			nextnextBlockModel[1] = ((rand() % 10)+8) * 4;
		else // ���� ��� ����
			nextnextBlockModel[1] = (rand() % 7) * 4;
		ShowBlock(blockModel[nextnextBlockModel[1]]);
	}

	else {
		if(specialBlock[2] != 3)
			currentBlockModel[2] = nextBlockModel[2];
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 + 28, GBOARD_ORIGIN_Y_2P_2);
		DeleteBlock(blockModel[nextBlockModel[2]]);

		if(specialBlock[2] == 3) // ����� ��� ó�� ������.
			nextBlockModel[2] = ((rand() % 10)+8) * 4;
		else // ����� ��� �ι�°���� �׹�°���� �̰ų� ���� ���� ���
			nextBlockModel[2] = nextnextBlockModel[2];
		ShowBlock(blockModel[nextBlockModel[2]]);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 + 28, GBOARD_ORIGIN_Y_2P_2 + 6);
		DeleteBlock(blockModel[nextnextBlockModel[2]]);

		if( specialBlock[2] ) // ����� ��� ����
			nextnextBlockModel[2] = ((rand() % 10)+8) * 4;
		else // ���� ��� ����
			nextnextBlockModel[2] = (rand() % 7) * 4;
		ShowBlock(blockModel[nextnextBlockModel[2]]);
	}
	if(specialBlock[player]!=0)
		specialBlock[player]--;

	SetCurrentCursorPos(curPos.x, curPos.y);
}

/* ��	�� : int GetCurrentBlockIdx(void)
* ��	�� : ���� ����ؾ� �ϴ� ����� intdex ���� ��ȯ
* ��	ȯ : ���� ��� Index���� ��ȯ
*
*/
int GetCurrentBlockIdx(int player) {
	return currentBlockModel[player] + rotateSte[player];
}

/* ��	�� : int DetectCollision(int posX, int posY, char blockModel[][4])
* ��	�� : ����� �̵� �� ȸ�� ���� ���� �Ǵ�
* ��	ȯ : �̵� �� ȸ�� ���� �� 1 ��ȯ
*
*/
int DetectCollision(int posX, int posY, char blockModel[][4], int player) {
	int x, y, arrX, arrY;

	/* gameBoardInfo �迭�� ��ǥ�� ���� */
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
	/* �浹 �˻� */
	for(x = 0; x < 4; x++) {
		for(y = 0; y < 4; y++) {
			if(arrY + y < 0) continue;
			/* Short Circuit Evaluation�� ���� �迭 �Ϻθ� �˻� */
			if(blockModel[y][x] >= 1 && gameBoardInfo[player][arrY + y][arrX + x] >= 1)
				return 0;
		}
	}
	return 1;
}

/* ��	�� : void ShiftLeft(void)
* ��	�� : ����� �������� �� ĭ �̵�
* ��	ȯ : void
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

/* ��	�� : void ShiftRight(void)
* ��	�� : ����� ���������� �� ĭ �̵�
* ��	ȯ : void
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

/* ��	�� : void RotateBlock(void)
* ��	�� : ����� 90�� ȸ��
* ��	ȯ : void
*
*/
void RotateBlock(int player) {
	int nextRotSte;
	int beforeRotSte = rotateSte[player];
	int x, y, arrX, arrY;

	/* gameBoardInfo �迭�� ��ǥ�� ���� */
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

	/* �浹 �˻� */
	for(x = 0; x < 2; x++) {
		for(y = 0; y < 4; y++) {
			if(arrY + y < 0)
				continue;
			if(blockModel[GetCurrentBlockIdx(player)][y][x] >= 1 && gameBoardInfo[player][arrY + y][arrX + x] >= 1) {
				if(DetectCollision(curPosX[player]+2, curPosY[player], blockModel[GetCurrentBlockIdx(player)], player))
					InitNewBlockPos(curPosX[player]+2,curPosY[player],player);   // ���� ���� �浹�ϸ� ��� ���������� ��ĭ �̵�
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
					InitNewBlockPos(curPosX[player]-2,curPosY[player],player);   // ������ ���� �浹�ϸ� ��� �������� ��ĭ �̵�
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

/* ��	�� : int BlockHold(void)
* ��	�� : ����� Hold ������ ����
* ��	ȯ : int
*
*/

int BlockHold(int player) {
	int tmp;

	if(useHold[player] == 1)
		return 1;
	else {
		useHold[player] = 1;
		/* ���� ����� holdâ�� ���*/
		DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);
		rotateSte[player]=0; // ���������� Hold��� ������ �� �⺻ ��� �������� ����
		switch(player) {
		case 0: SetCurrentCursorPos(GBOARD_ORIGIN_X_1P - 12, GBOARD_ORIGIN_Y_1P); break;
		case 1: SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1 - 12, GBOARD_ORIGIN_Y_2P_1+14); break;
		case 2: SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 + 28 , GBOARD_ORIGIN_Y_2P_2+14); break;
		}
		DeleteBlock(blockModel[holdBlockModel[player]]);
		ShowBlock(blockModel[currentBlockModel[player]]);

		if( holdBlockModel[player]==-1 ) { // Ȧ��Ű�� ó�� ����ϸ� 0����
			holdBlockModel[player] = currentBlockModel[player]; 
			return 0;
		}
		else { // ���� ��ϰ� hold ����� �ٲ�
			tmp = currentBlockModel[player]; 
			currentBlockModel[player] = holdBlockModel[player];
			holdBlockModel[player] = tmp;
			// Hold ����� ���������� ���������� ��ǥ ����
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

/* ��	�� : void DrawItemBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* ��	�� : ������ â�� �׸�
* ��	ȯ : void
*
*/
void DrawItemBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {
	int x, y;   

	SetCurrentCursorPos(GBOARD_ORIGIN_X + 2, GBOARD_ORIGIN_Y + 24);
	printf("��");
	/* ������ ��� â ��� */
	for(x = 0; x < 12; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + 21);
		if(x == 0) printf("��");
		else printf("��");
	}
	for(y = 0; y < 3; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 21 + y);
		if(y == 0) printf("��");
		else printf("��");
	}
	for(x = 1; x < 12; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + 23);
		if(x == 11) printf("��");
		else printf("��");
	}
	for(y = 1; y < 3; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + 21 + y);
		if(y == 2) printf("��");
		else printf("��");
	}
}

/* ��	�� : void DrawShieldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* ��	�� : ���� â�� �׸�
* ��	ȯ : void
*
*/
void DrawShieldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {

	SetCurrentCursorPos(GBOARD_ORIGIN_X - 5 * 2, GBOARD_ORIGIN_Y + 24);
	printf("Shield");
	SetCurrentCursorPos(GBOARD_ORIGIN_X - 5 * 2, GBOARD_ORIGIN_Y + 21);
	printf("������");
	SetCurrentCursorPos(GBOARD_ORIGIN_X - 5 * 2, GBOARD_ORIGIN_Y + 22);
	printf("��  ��");
	SetCurrentCursorPos(GBOARD_ORIGIN_X - 5 * 2, GBOARD_ORIGIN_Y + 23);
	printf("������");
}

/* ��	�� : void DrawHoldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* ��	�� : Ȧ�� â�� �׸�
* ��	ȯ : void
*
*/
void DrawHoldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {
	int x, y;   
	/* Hold ��� */
	if( !isHoldMode ) { // Ȧ�� ��� ���ϴ� ���
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 11, GBOARD_ORIGIN_Y + 1);
		printf("No Use");
	}

	SetCurrentCursorPos(GBOARD_ORIGIN_X - 10, GBOARD_ORIGIN_Y - 2);
	printf("Hold");

	/* Ȧ�� ��� â ��� */
	for(x = 0; x < 5; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 14 + x * 2, GBOARD_ORIGIN_Y - 1);
		if(x == 0) printf("��");
		else printf("��");
	}
	for(y = 0; y < 5; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 4, GBOARD_ORIGIN_Y - 1 + y);
		if(y == 0) printf("��");
		else printf("��");
	}
	for(x = 1; x < 6; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 14 + x * 2, GBOARD_ORIGIN_Y + 4);
		if(x == 5) printf("��");
		else printf("��");
	}
	for(y = 1; y < 6; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X - 14, GBOARD_ORIGIN_Y - 1 + y);
		if(y == 5) printf("��");
		else printf("��");
	}
}

/* ��	�� : void DrawNextBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* ��	�� : ����, �ٴ��� ��� â�� �׸�.
* ��	ȯ : void
*
*/
void DrawNextBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {
	int x, y;
	/* Next ��� */
	SetCurrentCursorPos(GBOARD_ORIGIN_X + 30, GBOARD_ORIGIN_Y - 2);
	printf("Next");

	/* ���� ��� â ��� */
	for(x = 0; x < 5; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26 + x * 2, GBOARD_ORIGIN_Y - 1);
		if(x == 0) printf("��");
		else printf("��");
	}
	for(y = 0; y < 5; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 36, GBOARD_ORIGIN_Y - 1 + y);
		if(y == 0) printf("��");
		else printf("��");
	}
	for(x = 1; x < 6; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26 + x * 2, GBOARD_ORIGIN_Y + 4);
		if(x == 5) printf("��");
		else printf("��");
	}
	for(y = 1; y < 6; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26, GBOARD_ORIGIN_Y - 1 + y);
		if(y == 5) printf("��");
		else printf("��");
	}

	/*�ٴ��� ��� â ���*/
	for(x = 0; x < 5; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26 + x * 2, GBOARD_ORIGIN_Y + 5);
		if(x == 0) printf("��");
		else printf("��");
	}
	for(y = 0; y < 5; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 36, GBOARD_ORIGIN_Y + 5 + y);
		if(y == 0) printf("��");
		else printf("��");
	}
	for(x = 1; x < 6; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26 + x * 2, GBOARD_ORIGIN_Y + 10);
		if(x == 5) printf("��");
		else printf("��");
	}
	for(y = 1; y < 6; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 26, GBOARD_ORIGIN_Y + 5 + y);
		if(y == 5) printf("��");
		else printf("��");
	}
}

/* ��	�� : void DrawNextBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y)
* ��	�� : ���� ���� �׸�.
* ��	ȯ : void
*
*/
void DrawGameWall(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y) {
	int x, y;
	/* �ð����� �κ� ó�� */
	SetColor(-1);
	for(y = 0; y <= GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);

		if(y == GBOARD_HEIGHT) printf("��");
		else printf("��");
	}

	for(y = 0; y <= GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(
			GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2,
			GBOARD_ORIGIN_Y + y);

		if(y == GBOARD_HEIGHT) printf("��");
		else printf("��");
	}

	for(x = 1; x < GBOARD_WIDTH + 1; x++) {
		SetCurrentCursorPos(
			GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("��");
	}
}

/* ��	�� : void DrawGameBoard(void)
* ��	�� : ��ü���� ���� ���� ��� ���� �׸���.
* ��	ȯ : void
*
*/
void DrawGameBoard(int player) {
	int x, y, z;
	SetColor(-1); // ���������� ����

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
	/* ������ �κ� ó�� */
	for(z = 0; z < 3; z++) {
		for(y = 0; y < GBOARD_HEIGHT; y++) {
			gameBoardInfo[z][y][0] = 1;
			gameBoardInfo[z][y][GBOARD_WIDTH + 1] = 1;
		}
		for(x = 0; x < GBOARD_WIDTH + 2; x++) 
			gameBoardInfo[z][GBOARD_HEIGHT][x] = 1;
	}
}

/* ��	�� : void AddCurrentBlockInfoToBoard(void)
* ��	�� : �迭�� ���� ����� ������ �߰��Ѵ�.
* ��	ȯ : void
*
*/
void AddCurrentBlockInfoToBoard(char blockInfo[][4], int player) {
	int x, y;

	int arrCurX;
	int arrCurY;

	for(y = 0; y < 4; y++) {
		for(x = 0; x < 4; x++) {
			/* Ŀ�� ��ġ ������ �迭 index ������ ���� */
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

/* ��	�� : int IsGameOver(void)
* ��	�� : ������ ����Ǿ����� Ȯ���ϴ� �Լ�
* ��	ȯ : ���� ���� �� 1 ��ȯ
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

/* ��	�� : void ShowLoser(int loser)
* ��	�� : ����, ���� ǥ��
* ��	ȯ : void
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

/* ��	�� : void DrawSolidBlocks(int player)
* ��	�� : ���� �ǿ� ������ ����� �׸���.
* ��	ȯ : void
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
				printf("��");
			}
			else {
				SetColor(-1);
				printf("  ");
			}
		}
	}
}

/* ��	�� : void DrawItemBucket(int player)
* ��	�� : player�� ������ â���� �׸���.
* ��	ȯ : void
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

/* ��	�� : void ShowID(int player)
* ��	�� : player�� ���̵� �����ش�
* ��	ȯ : void
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

/* ��	�� : void AddLine(int player, int lineNum)
* ��	�� : �ش� �÷��̾�� lineNum ��ŭ �߰��Ѵ�
* ��	ȯ : void
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

/* ��	�� : void SubLine(int player, int lineNum)
* ��	�� : �ش� �÷��̾�� lineNum ��ŭ �����Ѵ�
* ��	ȯ : void
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

/* ��	�� : void RemoveFillUpLine(void)
* ��	�� : �� ������ ä���� ����� �����Ѵ�.
* ��	ȯ : void
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

		if(x == (GBOARD_WIDTH + 1))	{	// ������ �� ä�����ٸ�

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
			y++;	// �迭 ������ �Ʒ��� �� ĭ�� �̵������Ƿ�

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

	// ��Ʈ������ �� ��� ���ĳ��ٰ� �ֽ��ϴ� ���
	if(lineCount == 4 && BGMCheck == 1) {
		PlaySound(TEXT("���� ���ٰ� �ֽ��ϴ�.wav"),
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

/* ��	�� : int BlockDown(void)
* ��	�� : ����Ϳ� �׷��� ����� �Ʒ��� �� ĭ ����
* ��	ȯ : ���� �� 1, ���� �� 0
*
*/
int BlockDown(int player) {
	int y, x;
	if(!DetectCollision(curPosX[player], curPosY[player] + 1, blockModel[GetCurrentBlockIdx(player)], player)) {

		if(BGMCheck == 1){
			PlaySound(TEXT("����.wav"),
				NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT | SND_NOSTOP);
		}

		/*10t ���ΰ��  */
		if(currentBlockModel[player]>27 && currentBlockModel[player] < 32) { // 10t ����̸�
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
				printf(" |��");
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_1, y+GBOARD_ORIGIN_Y_2P_1-1);
				printf(" |��");
				Sleep(100);
				SetColor(-1);
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_1, y+GBOARD_ORIGIN_Y_2P_1-2);
				printf("    ");
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_1, y+GBOARD_ORIGIN_Y_2P_1-1);
				printf("    ");
			}
			else if( player == 2) {
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_2, y+GBOARD_ORIGIN_Y_2P_2-2);
				printf(" |��");
				SetCurrentCursorPos(x*2+GBOARD_ORIGIN_X_2P_2, y+GBOARD_ORIGIN_Y_2P_2-1);
				printf(" |��");
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

		/* �� ������ ä���� ��� ���� �˻� */
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

/* ��   �� : void InitGameBoardInfo()
* ��   �� : ���� ���� ����� ���¸� 0���� �ʱ�ȭ �Ѵ�.
* ��   ȯ : void
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

/* ��	�� : void InitItemBucket(void)
* ��	�� : ������ ������ �ʱ�ȭ�Ѵ�.
* ��	ȯ : void
*
*/
void InitItemBucket(void) {
	int i;
	for(i = 0; i < 11; i++) {
		itemBucket[1][i] = '\0';
		itemBucket[2][i] = '\0';
	}
}

/* ��	�� : void SolidCurrentBlock(void)
* ��	�� : ������ ����� �ٴ����� �̵����� ������.
* ��	ȯ : void
*
*/
void SolidCurrentBlock(int player) {
	while(BlockDown(player));
}

/* end of file */