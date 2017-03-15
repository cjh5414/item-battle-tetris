/*Name : keyCurControl.c
* Content : Ŀ��, Ű���� ��Ʈ�� �Լ����� ����
* Implementation : CJH, SYB
* Last modified 20014/12/01
*/

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "point.h"
#include "blockStageControl.h"
#include "item.h"
#include "blockInfo.h"
#include "color.h"
#include "scoreLevelControl.h"
#include "startMenu.h"
#include "basicHeader.h"

#define KEY_SENSITIVE 300
#define SYS_DELAY 5

int LEFT[3] = {75, 100, 75};
int RIGHT[3] = {77, 103, 77};
int UP[3] = {72, 114, 72};
int DOWN[3] = {80, 102, 80};
int SPACE[3] = {32, 119, 46};
int HOLD[3] = {100, 113, 44};
int ITEMUSEME[3] = {0, 49, 59}; //         / 1 / ;  
int ITEMUSEYOU[3] = {0, 50, 108}; //      / 2 / l
int ITEMREMOVE[3] = {0, 96, 107}; //      / ` / k
int ESC = 27;
int ENTER = 13;

static int keyDelayRate;	// ���� Ŭ���� �ӵ� ����

/* ��	�� : void CursorSetting(void)
* ��	�� : ���� �Ÿ��� Ŀ���� ���� : 0�̸� ����, 1�̸� ����
* ��	ȯ : void
*
*/
void CursorSetting(int set)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible=set;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

/* ��	�� : point GetCurrentCursorPos(void)
* ��	�� : ���� Ŀ�� ��ġ ������ ���� ����ü ���� ��ȯ
* ��	ȯ : ���� Ŀ���� ��ȯ
*
*/
point GetCurrentCursorPos(void)
{
	point curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

/* ��	�� : void SetCurrentCursorPos(int x, int t)
* ��	�� : Ŀ�� ��ġ�� ����
* ��	ȯ : void
*
*/
void SetCurrentCursorPos(int x, int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* ��  �� : int PauseMenu(int mode)
*  ��  �� : ������ �Ͻ������ϰ� Pause �޴��� ���.
*  ��  ȯ : ������ �޴��� ������ ��ȯ
*
*/
int PauseMenu(int mode)
{
   int startX, startY;
   int curX, curY;
   char ch;

   if(mode) {
      startX = GBOARD_ORIGIN_X_2P_1 + 22;
      startY = GBOARD_ORIGIN_Y_2P_1 + 9;
   }
   else {
      startX = GBOARD_ORIGIN_X_1P + 4;
      startY = GBOARD_ORIGIN_Y_1P + 9;
   }

   curX = startX;
   curY = startY;

   SetColor(-1);
   SetCurrentCursorPos(startX - 2, startY - 3);
   printf("��������������������");
   SetCurrentCursorPos(startX - 2, startY - 2);
   printf("��   Pause Menu   ��");
   SetCurrentCursorPos(startX - 2, startY - 1);
   printf("��                ��");
   SetCurrentCursorPos(startX - 2, startY);
   printf("����Continue      ��");
   SetCurrentCursorPos(startX - 2, startY + 1);
   printf("��  Restart       ��");
   SetCurrentCursorPos(startX - 2, startY + 2);
   printf("��  Return to menu��");
   SetCurrentCursorPos(startX - 2, startY + 3);
   printf("��  Exit          ��");
   SetCurrentCursorPos(startX - 2, startY + 4);
   printf("��������������������");

   while(1) {
      SetCurrentCursorPos(curX, curY);
      printf("��");
      ch = getch();
      SetCurrentCursorPos(curX, curY);
      printf("  ");
      
      if(ch == MENUUP)
         curY--;
      else if(ch == MENUDOWN)
         curY++;
      else if(ch == ENTER) {
         if(curY == startY) {
            for(curX = 1; curX <11; curX++) {
               for(curY = 0; curY < 8; curY++) {
                  SetCurrentCursorPos(startX - 4 + 2 * curX, startY - 3 + curY);
                  printf("  ");
               }
            }
            DrawGameBoard(mode);
            DrawSolidBlocks(mode);
            SetCurrentCursorPos(curPosX[mode], curPosY[mode]);
            ShowBlock(blockModel[GetCurrentBlockIdx(mode)]);
            if(mode) {
               DrawSolidBlocks(2);
               SetCurrentCursorPos(curPosX[2], curPosY[2]);
               ShowBlock(blockModel[GetCurrentBlockIdx(2)]);
            }
            return 0;
         }
         else if(curY == startY + 1)
            return 2;
         else if(curY == startY + 2)
            return 3;
         else if(curY == startY + 3)
            Exit();
      }
      if(curY < startY)
         curY = startY + 3;
      else if(curY > startY + 3)
         curY = startY;
   }
}

/* ��	�� : int ProcessKeyInput(void)
* ��	�� : Ű �Է� ó��
* ��	ȯ : SPACE, HOLD ���� �� 1, ������ 0
*
*/
int ProcessKeyInput(int mode) {
   int i, key, isFloor[2]= {0,0}, pMenu;
   int floorDelay=0; // ���ҽ�Ű�� ������ ����

   /* �ٴڿ� ������ ������ ����( ���� �ʿ� 1. �ٴڿ��� �����, 2. ������ ���������� ����) */
   if(!DetectCollision(curPosX[mode], curPosY[mode] + 1, blockModel[GetCurrentBlockIdx(mode)], mode))
      isFloor[mode]=1;
   if( mode == 1 ) {
      if(!DetectCollision(curPosX[2], curPosY[2] + 1, blockModel[GetCurrentBlockIdx(2)], 2))
         isFloor[1]=1;
   }

   for(i = 0; i < KEY_SENSITIVE; i++) {
      if(isFloor[mode]){
         if(!floorDelay) { Sleep(1); floorDelay = 10; }
         else { floorDelay--; }
      }
      if(_kbhit() != 0) {
         key = _getch();
         SetCurrentCursorPos(curPosX[mode], curPosY[mode]);
         if( key == LEFT[mode] )
            ShiftLeft(mode);
         else if( key == RIGHT[mode] )   
            ShiftRight(mode);
         else if( key == UP[mode] )   
            RotateBlock(mode);
         else if( key == DOWN[mode] )   
            BlockDown(mode);
         else if( key == HOLD[mode] )   {
            if(isHoldMode)
               if(!BlockHold(mode)) {
                  ChooseBlock(mode);
                  if( !mode )
                     InitNewBlockPos(START_CURPOS_X_1P, START_CURPOS_Y_1P,0);
                  else
                     InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1,1);
               }
         }
         else if ( key == SPACE[mode] ) { 
            SolidCurrentBlock(mode); 
            if( !mode ) 
               InitNewBlockPos(START_CURPOS_X_1P, START_CURPOS_Y_1P,0);
            else
               InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1,1);
         }
         else if( key == ITEMREMOVE[1] ) 
            ItemUse(mode, 0);
         else if( key == ITEMUSEME[1] )
            ItemUse(mode, 1);
         else if( key == ITEMUSEYOU[1] )
            ItemUse(mode, 2);
         else if( key == ESC ) {
            if(pMenu = PauseMenu(mode))
               return pMenu;
         }
         if ( mode == 1 ) {
            SetCurrentCursorPos(curPosX[2], curPosY[2]);
            if( key == LEFT[2] )
               ShiftLeft(2);
            else if( key == RIGHT[2] )   
               ShiftRight(2);
            else if( key == UP[2] )   
               RotateBlock(2);
            else if( key == DOWN[2] )   
               BlockDown(2);
            else if( key == HOLD[2] )   { 
               if(isHoldMode)
                  if(!BlockHold(2)) {
                     ChooseBlock(2);
                     InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2,2);
                  }
            }
            else if ( key == SPACE[2] ) { 
               SolidCurrentBlock(2); 
               InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2,2);
            }
            else if( key == ITEMREMOVE[2] ) 
               ItemUse(2, 0);
            else if( key == ITEMUSEME[2] )
               ItemUse(2, 1);
            else if( key == ITEMUSEYOU[2] )
               ItemUse(2, 2);
         }
      }
      if(IsGameOver(0) || IsGameOver(1) || IsGameOver(2))
         break;
      if(i % keyDelayRate == 0)
         Sleep(SYS_DELAY);
   }
   return 0;   // �����̽� ��, Ȧ�� Ű �̿��� Ű�� �ԷµǾ��� �� ��ȯ
}

/* ��	�� : void InitKeyDelayRate(int rate)
* ��	�� : �ӵ� ����, ���� Ŭ���� �ӵ� ����
* ��	ȯ : void
*
*/
void InitKeyDelayRate(int rate) {
	if(rate < 1)
		return;
	keyDelayRate = rate;
}

/* ��	�� : void KeyDelaySpeedCtl(int addSpeed)
* ��	�� : �ӵ��� ��ȭ��Ų�� +�� ����, -�� ����
* ��	ȯ : void
*
*/
void KeyDelaySpeedCtl(int addSpeed) {
	keyDelayRate += addSpeed;
}

/* end of file */