#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include "basicHeader.h"
#include "startMenu.h"
#include "keyCurControl.h"
#include "startMenu.h"

// start menu
int menu(){

	char temp;
	int x = menuX;
	int y = STARTY;

	Logo();
	CursorSetting(0);

	SetCurrentCursorPos(x, y);
	printf("1. Log In\n");

	SetCurrentCursorPos(x, y+1); 
	printf("2. Ranking\n");

	SetCurrentCursorPos(x, y+2);
	printf("3. Sign Up\n");

	SetCurrentCursorPos(x, y+3);
	printf("4. Exit\n");

	//////////////
	while(1){

		SetCurrentCursorPos(arrX, y);
		printf("☞");

		temp = getch();

		SetCurrentCursorPos(arrX, y);
		printf("  ");

		switch(temp){

		case MENUUP:
			y--;
			break;

		case MENUDOWN :
			y++;
			break;

		case MENUENTER :
			return y-STARTY+1;
			break;
		}

		// y가 범위 밖으로 나가면 이동 안함
		if(y<STARTY){
			y++;
			continue;
		}

		else if(y>STARTY+3){
			y--;
			continue;
		}

	}

	fflush(stdin);
}

// player 인원 선택
void player_num(){

	char temp;
	int y = STARTY+2;
	int x = menuX;

	system("cls");

	Logo();
	CursorSetting(0);

	SetCurrentCursorPos(x, STARTY);
	printf("1P or 2P ?");

	SetCurrentCursorPos(x+3, y);
	printf("1P\n");

	SetCurrentCursorPos(x+3, y+1); 
	printf("2P\n");

	while(1){

		SetCurrentCursorPos(arrX, y);
		printf("☞");

		temp = getch();

		SetCurrentCursorPos(arrX, y);
		printf("  ");

		switch(temp){

		case MENUUP:
			y--;
			break;

		case MENUDOWN:
			y++;
			break;

		case MENUENTER:
			playernum = y-STARTY-1;
			return;

		case MENUESC:
			playernum = 0;
			return;
		}

		if(y < STARTY+2){
			y++;
			continue;
		}

		else if(y > STARTY+3){
			y--;
			continue;
		}

		fflush(stdin);
	}

	fflush(stdin);
}


//랭킹 조회 1인용 or 2인용 선택
void Rank_num(void) {

	char temp;
	int y = STARTY+2;
	int x = menuX;

	system("cls");

	Logo();
	CursorSetting(0);

	SetCurrentCursorPos(x-3,  STARTY);
	printf("1P Rank or 2P Rank ?");

	SetCurrentCursorPos(x+5, y);

	printf("1P\n");

	SetCurrentCursorPos(x+5, y+1); 
	printf("2P\n");

	while(1){

		SetCurrentCursorPos(arrX+3, y);
		printf("☞");

		temp = getch();

		SetCurrentCursorPos(arrX+3, y);
		printf("  ");

		switch(temp){

		case MENUUP:
			y--;
			break;

		case MENUDOWN:
			y++;
			break;

		case MENUENTER:
			if( y == STARTY + 2 ){
				ranknum = 1;
			}
			else
				ranknum = 2;
			return;

		case MENUESC:
			ranknum = 0;
			return;
		}

		if(y < STARTY+2){
			y++;
			continue;
		}

		else if(y > STARTY+3){
			y--;
			continue;
		}

		fflush(stdin);
	}
	fflush(stdin);
}