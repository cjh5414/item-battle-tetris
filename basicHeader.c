#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <mmsystem.h>

#include "color.h"
#include "keyCurControl.h"
#include "point.h"
#include "basicHeader.h"

int playernum;
int ranknum;
int LoginCheckNum;
char ID_1p[30];
char ID_2p[30];

void Logo() {
	SetCurrentCursorPos(LOGOX+20, LOGOY);
	printf("                with you and I");

	SetCurrentCursorPos(LOGOX, LOGOY+1);
	printf("■■■  ■■■  ■■■  ■■■    ■■■   ■■■");
	SetCurrentCursorPos(LOGOX, LOGOY+2);
	printf("  ■    ■        ■    ■   ■     ■    ■");
	SetCurrentCursorPos(LOGOX, LOGOY+3);
	printf("  ■    ■■■    ■    ■■■      ■     ■■■");
	SetCurrentCursorPos(LOGOX, LOGOY+4);
	printf("  ■    ■        ■    ■   ■     ■          ■");
	SetCurrentCursorPos(LOGOX, LOGOY+5);
	printf("  ■    ■■■    ■    ■    ■  ■■■   ■■■");

}

void Exit() {
	int x = 38;
	int y = STARTY;

	system("cls");

	Logo();

	Sleep(350);
	SetCurrentCursorPos(x, y);
	printf("Made by 한잔하조");

	Sleep(350);
	SetCurrentCursorPos(x, y+2);
	printf(" 1192043 최지훈");

	Sleep(350);
	SetCurrentCursorPos(x, y+4);
	printf(" 1192024 심영보");

	Sleep(350);
	SetCurrentCursorPos(x, y+6);
	printf(" 1392029 이소라");

	Sleep(350);
	SetCurrentCursorPos(x, y+8);
	printf(" 1092065 이기은");

	SetCurrentCursorPos(x-7, y+12);
	Sleep(700);
	exit(0);
}