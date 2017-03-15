#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "blockStageControl.h"
#include "keyCurControl.h"

static int Map[4];

void MapTree(void) {
	int i, x;
	for( i=0; i<3; i++) {
		for(x=1; x<10; x++) {
			gameBoardInfo[i][19][x] = 6;
			gameBoardInfo[i][18][x] = 6;
		}
		for(x=2; x<9; x++) {
			gameBoardInfo[i][17][x] = 6;
			gameBoardInfo[i][16][x] = 6;
		}
		for(x=3; x<8; x++) {	
			gameBoardInfo[i][15][x] = 6;
			gameBoardInfo[i][14][x] = 6;
		}
		for(x=4; x<7; x++) {
			gameBoardInfo[i][13][x] = 6;
		}
		gameBoardInfo[i][12][5] = 5;
		gameBoardInfo[i][11][4] = 5;
		gameBoardInfo[i][11][5] = 'Y';
		gameBoardInfo[i][11][6] = 5;
		gameBoardInfo[i][10][4] = 5;
		gameBoardInfo[i][10][5] = 'Z';
		gameBoardInfo[i][10][6] = 5;
		gameBoardInfo[i][9][5] = 5;	
		
		gameBoardInfo[i][19][3] = 'C';
		gameBoardInfo[i][18][2] = 'Y';
		gameBoardInfo[i][18][7] = 'A';
		gameBoardInfo[i][17][5] = 'X';
		gameBoardInfo[i][16][4] = 'E';
		gameBoardInfo[i][15][7] = 'Z';
		gameBoardInfo[i][14][5] = 'B';
		gameBoardInfo[i][13][4] = 'A';
		
	}
}

void MapStep(void) {
	int y, x, i;
	for(i=0; i<3; i++) {
	for( y=1; y<10; y++) {
		for( x=2; x<=y; x++ ) 
			gameBoardInfo[i][y+10][x] = y%7+1;
		gameBoardInfo[i][y+10][1] = 'A';
	}
	}
}

void MapHeart(void) {
	int i;
	for( i=0; i<3; i++) {
		gameBoardInfo[i][19][5] = 'A';
		gameBoardInfo[i][19][6] = 'A';
		gameBoardInfo[i][18][4] = 8;
		gameBoardInfo[i][18][7] = 8;
		gameBoardInfo[i][17][3] = 8;
		gameBoardInfo[i][17][8] = 8;
		gameBoardInfo[i][16][2] = 8;
		gameBoardInfo[i][16][9] = 8;
		gameBoardInfo[i][15][2] = 8;
		gameBoardInfo[i][15][9] = 8;
		gameBoardInfo[i][15][5] = 8;
		gameBoardInfo[i][15][6] = 8;
		gameBoardInfo[i][14][3] = 8;
		gameBoardInfo[i][14][4] = 8;
		gameBoardInfo[i][14][7] = 8;
		gameBoardInfo[i][14][8] = 8;
	}
}

void MapKey(void) {
	int y, i;
	for( i=0; i<3; i++ ) {
		for( y=19; y>9; y-- ) {
			gameBoardInfo[i][y][5] = 5;
			gameBoardInfo[i][y][6] = 5;
		}
		gameBoardInfo[i][y-1][5] = 5;
		gameBoardInfo[i][y-1][6] = 5;
		for( y=12; y>7; y-- ) {
			gameBoardInfo[i][y][3] = 5;
			gameBoardInfo[i][y][4] = 5;
			gameBoardInfo[i][y][7] = 5;
			gameBoardInfo[i][y][8] = 5;
		}
		for( y=11; y>8; y-- ) {
			gameBoardInfo[i][y][2] = 5;
			gameBoardInfo[i][y][9] = 5;	
		}
		gameBoardInfo[i][18][4] = 'Z';
		gameBoardInfo[i][15][3] = 'Y';
		gameBoardInfo[i][15][4] = 'X';
	}
}

void MapClear(void) {
	int x, y, i;
	for(i = 0; i < 3; i++) {
		for(x = 1; x < 11; x++) {
			for(y = 0; y < 20; y++)
				gameBoardInfo[i][y][x] = 0;
		}
	}
}

void MapChoice(void) {
	char input, mapIdx = 0;

	DrawGameWall(GBOARD_ORIGIN_X_1P, GBOARD_ORIGIN_Y_1P);
	SetCurrentCursorPos(GBOARD_ORIGIN_X_1P - 10, GBOARD_ORIGIN_Y_1P + 6);
	printf("<<--");
	SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 28, GBOARD_ORIGIN_Y_1P + 6);
	printf("-->>");
	SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 6, GBOARD_ORIGIN_Y_1P + 21);
	printf("이동 : ← →");
	SetCurrentCursorPos(GBOARD_ORIGIN_X_1P + 6, GBOARD_ORIGIN_Y_1P + 22);
	printf("선택 : Enter");
	while(1) {
		input = _getch();
		if(input == LEFT[2]) {
			mapIdx--;
			if(mapIdx < 0)
				mapIdx = 4;
		}
		else if(input == RIGHT[2]) {
			mapIdx++;
			if(mapIdx > 4)
				mapIdx = 0;
		}
		else if(input == 13) {
			system("cls");
			DrawSolidBlocks(1);
			DrawSolidBlocks(2);
			return;
		}
		MapClear();
		if(mapIdx == 1)
			MapStep();
		else if(mapIdx == 2)
			MapHeart();
		else if(mapIdx == 3)
			MapKey();
		else if(mapIdx == 4)
			MapTree();
		DrawSolidBlocks(0);
	}
}