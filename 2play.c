/* Name : 2play.c
* Content : main �Լ��� ����
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

/* ���� ���� �� �Լ� */
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

	/*������ ���� �ʱ�ȭ*/
	InitItemBucket();

	/*���� ���ھ�, ����, �޺� �ʱ�ȭ*/
	InitGameState();
	isItemMode = optionItemMode;

	/* ���� ���� ��� ���� �ʱ�ȭ */
	InitGameBoardInfo();

	/* ���� �ӵ� ���� */
	InitKeyDelayRate(curGameLevel);

	/* Ŀ�� ������ ���� */
	CursorSetting(0);

	/*�� ����*/
	MapChoice();

	/* player�� ID ǥ�� */
	ShowID(1);
	ShowID(2);

	/* ���� ���� �׸��� */
	DrawGameBoard(1);

	/* ���� ����, ���� ǥ�� */
	ShowCurrentScoreAndLevel(mode);

	/* �� �ʱⰪ �����ϰ� ���� */
	InitRandomBlock();

	/* �ʱ�� ����*/
	ChooseBlock(1);
	ChooseBlock(2);

	/* �� �ʱ� ���� ��ġ ����*/
	InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1,1);
	InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2,2);

	/* �ݺ������� ���ο� ����� ���� */
	while(1) {
		/* ���� ���� Ȯ�� */
		if( IsGameOver(1) ) {
			loser = 1;
			break;
		}
		else if( IsGameOver(2) ) {
			loser = 2;
			break;
		}
		/* ������ �۾� ���� */
		while(1) {
			/* ����� �Ʒ��� �� ĭ �̵�*/
			if( !BlockDown(1) ) {	// ��� �̵����� ��
				InitNewBlockPos(START_CURPOS_X_2P_1, START_CURPOS_Y_2P_1,1);
				break;
			}

			if( !BlockDown(2) ) {	// ��� �̵����� ��
				InitNewBlockPos(START_CURPOS_X_2P_2, START_CURPOS_Y_2P_2,2);
				break;
			}
			/* ���̸� Ű �Է� ó�� */
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