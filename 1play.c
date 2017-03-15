/* Name : 1play.c
* Content : main �Լ��� ����
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

	/*���� ���ھ�, ����, �޺� �ʱ�ȭ*/
	InitGameState();

	/* ���� ���� ��� ���� �ʱ�ȭ */
	InitGameBoardInfo();

	/* No item���� ���� */
	isItemMode = 0;

	/* ���� �ӵ� ���� */
	InitKeyDelayRate(curGameLevel);

	/* Ŀ�� ������ ���� */
	CursorSetting(0);

	/* player�� ID ǥ�� */
	ShowID(0);

	/* ���� ���� �׸��� */
	DrawGameBoard(0);

	/* ���� ����, ���� ǥ�� */
	ShowCurrentScoreAndLevel(mode);

	/* ���� �޺� ǥ�� */
	ShowCurrentCombo(0);

	/* �� �ʱⰪ �����ϰ� ���� */
	InitRandomBlock();

	/* �ʱ�� ����*/
	/* 0: 1P, 1: 2p_1, 2: 2P_2*/
	ChooseBlock(0);

	/* �� �ʱ� ���� ��ġ ����*/
	/* 1�ο� 2�ο뿡 ������� 3��° �Ű������� 1�̸� player1, 2�̸� player2 */
	InitNewBlockPos(START_CURPOS_X_1P, START_CURPOS_Y_1P,0);

	/* �ݺ������� ���ο� ����� ���� */
	while(1) {
		/* ���� ���� Ȯ�� */
		if(IsGameOver(0))  {
			SortGameResult(getGameScore(), ID_1p, isHoldMode);
			SaveRankFile();
			break;
		}
		/* ������ �۾� ���� */
		while(1) {
			/* ����� �Ʒ��� �� ĭ �̵�*/
			if(!BlockDown(0)) { // ��� �̵����� ��
				InitNewBlockPos(START_CURPOS_X_1P, START_CURPOS_Y_1P,0);
				break;
			}
			/* ���̸� Ű �Է� ó�� */
			if(temp = ProcessKeyInput(0))
				return temp;
		}
	}
	SetColor(-1); // �ؽ�Ʈ ����� �⺻ ������ ����
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



