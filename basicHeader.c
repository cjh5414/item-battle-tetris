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
	printf("����  ����  ����  ����    ����   ����");
	SetCurrentCursorPos(LOGOX, LOGOY+2);
	printf("  ��    ��        ��    ��   ��     ��    ��");
	SetCurrentCursorPos(LOGOX, LOGOY+3);
	printf("  ��    ����    ��    ����      ��     ����");
	SetCurrentCursorPos(LOGOX, LOGOY+4);
	printf("  ��    ��        ��    ��   ��     ��          ��");
	SetCurrentCursorPos(LOGOX, LOGOY+5);
	printf("  ��    ����    ��    ��    ��  ����   ����");

}

void Exit() {
	int x = 38;
	int y = STARTY;

	system("cls");

	Logo();

	Sleep(350);
	SetCurrentCursorPos(x, y);
	printf("Made by ��������");

	Sleep(350);
	SetCurrentCursorPos(x, y+2);
	printf(" 1192043 ������");

	Sleep(350);
	SetCurrentCursorPos(x, y+4);
	printf(" 1192024 �ɿ���");

	Sleep(350);
	SetCurrentCursorPos(x, y+6);
	printf(" 1392029 �̼Ҷ�");

	Sleep(350);
	SetCurrentCursorPos(x, y+8);
	printf(" 1092065 �̱���");

	SetCurrentCursorPos(x-7, y+12);
	Sleep(700);
	exit(0);
}