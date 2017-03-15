/*Name : item.c
* Content : item �Լ� ����
* Implementation : CJH, SYB
* Last modified 20014/12/01
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "blockInfo.h"
#include "color.h"
#include "item.h"
#include "blockStageControl.h"
#include "keyCurControl.h"

#define SWAP(x,y,z) ((z) = (x), (x) = (y), (y) = (z))

static int sheild[3] = {0};
extern int BGMCheck;

/* ��	�� : char* GetItemShape(char item)
* ��	�� : �ش� �������� ��� ��ȯ
* ��	ȯ : char*
*
*/
char* GetItemShape(char item) {
	switch(item) {
	case 'A':
		return "+1";
	case 'B':
		return "��";
	case 'C':
		return "��";
	case 'D':
		return "��";
	case 'E':
		return "��";
	case 'F':
		return "+2";

	case 'Z':
		return "-1";
	case 'Y':
		return "��";
	case 'X':
		return "��";
	case 'W':
		return "-2";

	default :
		return "  ";
	}
}

/* ��   �� : void ItemInfo(int player, char item)
* ��   �� : ���� ��밡���� ������ ����
* ��   ȯ : void
*
*/
void ItemInfo(int player, char item) {
	if( player == 1)
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1 + 4, GBOARD_ORIGIN_Y_2P_1 + 24);
	else
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2 + 4, GBOARD_ORIGIN_Y_2P_2 + 24);
	SetColor(-1);
	switch(item) {
	case 'A':
		printf(" One Line Up    ");
		break;
	case 'B':
		printf(" Special Block  ");
		break;
	case 'C':
		printf(" Twisit Map     ");
		break;
	case 'D':
		printf(" Switch Map     ");
		break;
	case 'E':
		printf(" Still Item     ");
		break;
	case 'F':
		printf(" Two Line Up    ");
		break;

	case 'Z':
		printf(" One Line Down  ");
		break;
	case 'Y':
		printf(" 10t Block      ");
		break;
	case 'X':
		printf(" Shield         ");
		break;
	case 'W':
		printf(" Two Line Down  ");
		break;
	default :
		printf("                ");
	}
}

/* ��	�� : void ItemFly(int player, char itemShape)
* ��	�� : �������� ���󰡴� ���� ������
* ��	ȯ : void
*
*/
void ItemFly(int player, char *itemShape) {
	int x, y;
	
	if(BGMCheck == 1){
	PlaySound(TEXT("������.wav"),
		NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT  | SND_NOSTOP);
	}
	for( x=0, y=0; x<5; y++, x++ ) {
		if(player == 1) 
			SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+12*2+x*2, GBOARD_ORIGIN_Y_2P_1+22-y);
		else if( player == 2) 
			SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-1*2-x*2, GBOARD_ORIGIN_Y_2P_2+22-y);
		printf("%s",itemShape);
		if(x % 2 == 1)
			Sleep(10);
	}
	if(player == 1) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+12*2+x*2, GBOARD_ORIGIN_Y_2P_1+23-y);
		printf("%s",itemShape);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+11*2+x*2, GBOARD_ORIGIN_Y_2P_1+22-y);
		printf("%s",itemShape);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+12*2+x*2, GBOARD_ORIGIN_Y_2P_1+21-y);
		printf("%s",itemShape);
		Sleep(10);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+11*2+x*2, GBOARD_ORIGIN_Y_2P_1+24-y);
		printf("%s",itemShape);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+11*2+x*2, GBOARD_ORIGIN_Y_2P_1+20-y);
		printf("%s",itemShape);
	}
	else if( player == 2) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-1*2-x*2, GBOARD_ORIGIN_Y_2P_2+23-y);
		printf("%s",itemShape);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-1*2-x*2, GBOARD_ORIGIN_Y_2P_2+21-y);
		printf("%s",itemShape);
		Sleep(10);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-x*2, GBOARD_ORIGIN_Y_2P_2+20-y);
		printf("%s",itemShape);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-x*2, GBOARD_ORIGIN_Y_2P_2+22-y);
		printf("%s",itemShape);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-x*2, GBOARD_ORIGIN_Y_2P_2+24-y);
		printf("%s",itemShape);
	}
	Sleep(1);
	SetColor(9);
	for( x=0, y=0; x<5; y++, x++ ) {
		if(player == 1) 
			SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+12*2+x*2, GBOARD_ORIGIN_Y_2P_1+22-y);
		else if( player == 2) 
			SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-1*2-x*2, GBOARD_ORIGIN_Y_2P_2+22-y);
		printf("  ");
		if(x % 2 == 1)
			Sleep(10);
	}

	if( player == 1){
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+12*2+x*2, GBOARD_ORIGIN_Y_2P_1+23-y);
		printf("  ");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+11*2+x*2, GBOARD_ORIGIN_Y_2P_1+22-y);
		printf("  ");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+12*2+x*2, GBOARD_ORIGIN_Y_2P_1+21-y);
		printf("  ");
		Sleep(10);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+11*2+x*2, GBOARD_ORIGIN_Y_2P_1+24-y);
		printf("  ");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1+11*2+x*2, GBOARD_ORIGIN_Y_2P_1+20-y);
		printf("  ");
	}
	else if( player == 2 ) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-1*2-x*2, GBOARD_ORIGIN_Y_2P_2+23-y);
		printf("  ");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-1*2-x*2, GBOARD_ORIGIN_Y_2P_2+21-y);
		printf("  ");
		Sleep(10);
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-x*2, GBOARD_ORIGIN_Y_2P_2+20-y);
		printf("  ");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-x*2, GBOARD_ORIGIN_Y_2P_2+22-y);
		printf("  ");
		SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2-x*2, GBOARD_ORIGIN_Y_2P_2+24-y);
		printf("  ");
	}
}

/* ��	�� : void ChoiceBlock(int player, int itemInfo)
* ��	�� : ������ ���� ������ ����
* ��	ȯ : void
*
*/
void ChoiceBlock(int player, int itemInfo) {
	int x, y, blockCount = 0, itemBlock;
	for(y = 0; y < GBOARD_HEIGHT; y++) {
		for(x = 1; x < GBOARD_WIDTH + 1; x++) {
			if(gameBoardInfo[player][y][x] > 0) blockCount++;
		}
	}
	if(blockCount == 0)
		return;
	itemBlock = rand() % blockCount + 1;
	for(y = 0; y < GBOARD_HEIGHT; y++) {
		for(x = 1; x < GBOARD_WIDTH + 1; x++) {
			if(gameBoardInfo[player][y][x] > 0) itemBlock--;
			if(!itemBlock){
				if(isalpha(gameBoardInfo[player][y][x]))
					return;
				gameBoardInfo[player][y][x] = itemInfo;
				DrawSolidBlocks(player);
				return;
			}
		}
	}
}

/* ��	�� : void MakeItem(int player, int itemInfo)
* ��	�� : ������ ���θ� �Ǵ��Ͽ� ������ ���� ����
* ��	ȯ : void
*
*/
void MakeItem(int player, int itemInfo) {
	switch(itemInfo) {
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':

	case 'Z':
	case 'Y':
	case 'X':
	case 'W':
		ChoiceBlock(player, itemInfo);
		break;
	default:
		return;
	}
}

/* ��   �� : void Item10t(int player)
* ��   �� : 10t��� �����ϴ� ������
* ��   ȯ : void
*
*/
void Item10t(int player) {
	SetCurrentCursorPos(curPosX[player], curPosY[player]);   
	DeleteBlock(blockModel[GetCurrentBlockIdx(player)]);
	currentBlockModel[player] = 7*4;
	if( player==1 ) 
		InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1,player);
	else if( player == 2 )
		InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2,player);
}

/* ��   �� : void ItemSpecial(int player)
* ��   �� : Ư������� 4�� �����ϴ� ������
* ��   ȯ : void
*
*/
void ItemSpecial(int player) {
	specialBlock[player] = 3;
	ChooseBlock(player);
}

/* ��	�� : void ItemTwist(int player)
* ��	�� : ��ϵ��� ��ġ�� �������� �����Ѵ�.
* ��	ȯ : void
*
*/
void ItemTwist(int player) {
	int y, randNum1, randNum2, i, temp;

	for(y = 0; y < 20; y++) {
		for(i = 0; i < 10; i++) {
			randNum1 = rand() % 10 + 1;
			randNum2 = rand() % 10 + 1;
			SWAP(gameBoardInfo[player][y][randNum1], gameBoardInfo[player][y][randNum2]
			, temp);
		}
	}
	DrawSolidBlocks(player);
}

/* ��	�� : void ItemSteal(int player)
* ��	�� : ��ϵ��� ��ġ�� �������� �����Ѵ�.
* ��	ȯ : void
*
*/
void ItemSteal(int user, int dest) {

	if(user == dest)
		return;
	itemBucket[user][strlen(itemBucket[user])] = itemBucket[dest][strlen(itemBucket[dest])-1];
	itemBucket[dest][strlen(itemBucket[dest])-1] = '\0';	
	DrawItemBucket(user);
	DrawItemBucket(dest);
}

/* ��	�� : void ItemSteal(int player)
* ��	�� : ������ �������� 1ȸ ������ִ� ���� ���¸� �����Ѵ�.
* ��	ȯ : void
*
*/
void ItemShield(int player, int num) {
	if(num == 1) {
		if(player == 1)
			SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1-8, GBOARD_ORIGIN_Y_2P_1+22);
		else
			SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2+30, GBOARD_ORIGIN_Y_2P_2+22);
		SetColor('X');
		printf("��");
		SetColor(-1);
	}
	else {
		if(player == 1)
			SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_1-8, GBOARD_ORIGIN_Y_2P_1+22);
		else
			SetCurrentCursorPos(GBOARD_ORIGIN_X_2P_2+30, GBOARD_ORIGIN_Y_2P_2+22);
		SetColor(-1);
		printf("  ");
	}
	sheild[player] = num;
}

/* ��	�� : int IsSheild(int player)
* ��	�� : ������ �������� 1ȸ ������ִ� ���带 �Ҵ�.
* ��	ȯ : void
*
*/
int IsShield(int player) {
	return sheild[player];
}

/* ��	�� : void ItemChangeMap(int user, int dest)
* ��	�� : �������� ���� ������� ���� �ٲ۴�.
* ��	ȯ : void
*
*/
void ItemChangeMap(int user, int dest) {
	int x, y;
	int temp[GBOARD_WIDTH];
	if(user == dest)
		return;
	SetCurrentCursorPos(curPosX[user], curPosY[user]);
	DeleteBlock(blockModel[GetCurrentBlockIdx(user)]);
	SetCurrentCursorPos(curPosX[user], curPosY[dest]);
	DeleteBlock(blockModel[GetCurrentBlockIdx(dest)]);
	for(y = 0; y < 6; y++) {
		for(x = 1; x < 11; x++) {
			gameBoardInfo[user][y][x] = 0;
			gameBoardInfo[dest][y][x] = 0;
		}
	}
	for(y = 6; y < 20; y++) {
		memcpy(temp, &gameBoardInfo[user][y][1], GBOARD_WIDTH * sizeof(int));
		memcpy(&gameBoardInfo[user][y][1], &gameBoardInfo[dest][y][1], GBOARD_WIDTH * sizeof(int));
		memcpy(&gameBoardInfo[dest][y][1], temp, GBOARD_WIDTH * sizeof(int));
	}
	DrawSolidBlocks(user);
	DrawSolidBlocks(dest);
	ChooseBlock(user);
	ChooseBlock(dest);
	InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1, 1);
	InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2, 2);
	Sleep(100);
}

/* ��	�� : void ItemUse(int player, int useMode)
* ��	�� : ������ ���, ����
* ��	ȯ : void
*
*/
void ItemUse(int player, int useMode) {
	char item;
	int dest = (player + useMode) % 2 + 1;	// ������ ���� ������

	if( !itemBucket[player][0] )
		return;
	item = itemBucket[player][0];
	strcpy(itemBucket[player], (itemBucket[player]+1));
	DrawItemBucket(player);
	if( !useMode ) return;

	else if(dest != player) {
		SetColor(item); // ������ ������ ���� �ش� ������ ����
		ItemFly(player, GetItemShape(item));
	}

	switch(item) {	// ���� ���� �˻�
	case 'A':
		if(IsShield(dest)) {
			ItemShield(dest, 0);
			break;
		}
		AddLine(dest, 1);
		break;
	case 'B':
		if(IsShield(dest)) {
			ItemShield(dest, 0);
			break;
		}
		ItemSpecial(dest);
		break;
	case 'C':
		if(IsShield(dest)) {
			ItemShield(dest, 0);
			break;
		}
		ItemTwist(dest);
		break;
	case 'D':
		if(IsShield(dest)) {
			ItemShield(dest, 0);
			break;
		}
		ItemChangeMap(player, dest);
		break;
	case 'E':
		if(IsShield(dest)) {
			ItemShield(dest, 0);
			break;
		}
		ItemSteal(player, dest);
		break;
	case 'F':
		if(IsShield(dest)) {
			ItemShield(dest, 0);
			break;
		}
		AddLine(dest, 2);
		break;

	case 'Z':
		SubLine(dest, 1);
		break;
	case 'Y':
		Item10t(dest);
		break;
	case 'X':
		ItemShield(dest, 1);
		break;
	case 'W':
		SubLine(dest,2);
		break;
	}
}