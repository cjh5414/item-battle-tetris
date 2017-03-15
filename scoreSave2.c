#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#include "keyCurControl.h"
#include "basicHeader.h"
#include "startMenu.h"
#include "scoreSave2.h"
#include "scoreSave.h"
#include "color.h"
#include "playMenu.h"

NodeTwo* HeadTwo = NULL;

/* 2인용 랭킹파일 Read */
void ReadTwoRankFile(){
	FILE* fp;
	int record, rank, win, lose;
	double rate;
	char ID[30];
	fp = fopen("ranking2.txt", "r");
	if(fp==NULL)
		return;
	while (fscanf(fp, "%d %s %d %d %d %lf", &rank, ID, &record, &win, &lose, &rate) != EOF)   {
		AppendNodeTwo(&HeadTwo, Create_RankNodeTwo(rank, record, ID, win, lose, rate));
	}
	fclose(fp);
}
/* 2인용 랭킹파일 Save */
void SaveTwoRankFile(){
	FILE* fp;
	int i = 1;
	NodeTwo* Temp;
	fp = fopen("ranking2.txt", "w");
	if(fp==NULL)
		return;
	Temp = HeadTwo;
	while (Temp != NULL){
		fprintf(fp, "%d %s %d %d %d %.1lf\n", i, Temp->ID, Temp->record, Temp->win, Temp->lose, Temp->rate);
		Temp->rank = i;
		Temp = Temp->Next;
		i++;
	}
	fclose(fp);
}

NodeTwo* Create_RankNodeTwo(int rank, int record, char* ID, int win, int lose, double rate){

	NodeTwo* NewNode = (NodeTwo*)malloc(sizeof(NodeTwo));

	NewNode->rank = rank;
	NewNode->record = record;
	NewNode->rate = rate;
	NewNode->win=win;
	NewNode->lose=lose; 
	strcpy(NewNode->ID, ID);
	NewNode->Next = NULL;
	return NewNode;
}
void AppendNodeTwo(NodeTwo** Head, NodeTwo* NewNode){
	NodeTwo* pre = *Head;
	if (*Head == NULL){
		*Head = NewNode;
		(*Head)->Next = NULL;
	}
	else if(pre->Next == NULL) {
		if(pre->win < NewNode->win) {
			NewNode->Next = pre;
			*Head = NewNode;
		}
		else {
			pre->Next = NewNode;
		}
	}
	else{
		NodeTwo *Temp = pre->Next;
		if(pre->win < NewNode->win) {
			NewNode->Next = pre;
			*Head = NewNode;
		}
		else {
			while (Temp != NULL){
				if (Temp->win < NewNode->win){
					NewNode->Next = Temp;
					pre->Next = NewNode;
					return;
				}
				Temp = Temp->Next;
				pre = pre->Next;
			}
			pre->Next = NewNode;
		}
	}
}

/* 2인용 랭킹파일 Display */
void DisplayTwoRank(){
	NodeTwo* Temp;
	int count = 0;
	int i;
	point p;
	char temp;
	char ID[30];

	if(playernum != 0) {
		make_line();
		take_rank(ID_1p, 1);
		if(playernum==2)
			take_rank(ID_2p, 2);
	}

	do{
		i = 0;
		Temp =  HeadTwo;
		SetCurrentCursorPos(menuX, STARTY-8);
		printf("\n\t\t\t\t\t2인용 RANKING\n");
		printf("\t\t------------------------------------------------------------------------\n");
		printf("\t\t\t순위\t    아이디\t\t전적\t\t승률\n");
		printf("\t\t------------------------------------------------------------------------\n");
		while (Temp != NULL && i<10){
			printf("\t\t\t%3d\t    %s\t   %3d전 %3d승 %3d패\t%5.1lf\n", Temp->rank, Temp->ID, Temp->record, Temp->win, Temp->lose, Temp->rate);
			Temp = Temp->Next;
			i++;
		}
		SetCurrentCursorPos(menuX, STARTY+12);
		printf("ID : ");
		SetCurrentCursorPos(menuX+21, STARTY+12);
		printf("\t검색");
		SetCurrentCursorPos(menuX + 5, STARTY + 12);
		printf("                  ");
		SetCurrentCursorPos(menuX + 5, STARTY + 12);
		CursorSetting(1);
		count = 0;

		while(1) {
			temp = getch();

			if(temp == -32 || temp == 0 ){ 
				temp= getch();
				continue;
			}

			else if (temp == MENUESC) {
				CursorSetting(0);
				return ;
			}
			else if(temp == MENUENTER) { 
				ID[count] = '\0';
				break;
			}

			else if(count > 15)
				continue;

			else if(count>0 && temp == MENUBSPACE) {
				count--;

				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x-1, p.y);
				printf(" ");
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x-1, p.y);
				fflush(stdin);
				continue;
			}

			else if(count==0 && temp == MENUBSPACE) {
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x, p.y);
				continue;
			}

			else if(isalpha(temp)!=0 || isdigit(temp)!=0 ) {
				ID[count] = temp;
				putchar(temp);                  
			}

			else continue;
			count++;
		}
		CursorSetting(0);
	}while(RankSearchTwo(ID));
}

int RankSearchTwo(char* ID){
	NodeTwo* Temp = HeadTwo;
	NodeTwo* Result;
	int i=0, j=0, flag=FALSE;
	while (Temp != NULL){
		if (strcmp(ID, Temp->ID) == 0){
			system("cls");
			flag = TRUE;
			break;
		}
		i++;
		Temp = Temp->Next;
	}
	if(playernum != 0) {
		make_line();
		take_rank(ID_1p, 1);
		if(playernum==2)
			take_rank(ID_2p, 2);
	}
	if(Temp == NULL)
		return 1;
	SetCurrentCursorPos(menuX + 5, STARTY + 12);
	printf("                  ");
	SetCurrentCursorPos(menuX, STARTY-8);
	printf("\n\t\t\t\t\t2인용 RANKING\n");
	printf("\t\t------------------------------------------------------------------------\n");
	printf("\t\t\t순위\t    아이디\t\t전적\t\t승률\n");
	printf("\t\t------------------------------------------------------------------------\n");
	Result=Temp;
	Temp = HeadTwo;
	while (Temp != NULL && flag){
		if (j >= i - 4 && j < i + 6){
			if(j==i)
				SetColor(1);
			printf("\t\t\t%3d\t    %s\t   %3d전 %3d승 %3d패\t%5.1lf\n", Temp->rank, Temp->ID, Temp->record, Temp->win, Temp->lose, Temp->rate);
			if(j==i)
				SetColor(11);
		}
		if(j == i + 6)
			break;
		Temp = Temp->Next;
		j++;
	}
	for(j = 5 - Result->rank; j > 0; j--) {
		if(Temp == NULL)
			break;
		printf("\t\t\t%3d\t    %s\t   %3d전 %3d승 %3d패\t%5.1lf\n", Temp->rank, Temp->ID, Temp->record, Temp->win, Temp->lose, Temp->rate);
		Temp = Temp->Next;
	}

	printf("\n");
	return 1;
}

NodeTwo* SearchNode(char* ID) {
	NodeTwo* temp = HeadTwo;
	while(temp!=NULL) {
		if(strcmp(temp->ID, ID) == 0)
			break;
		temp = temp->Next;
	}
	return temp;
}

void SortGameResultTwo(char *winner, char *loser) {
	NodeTwo *temp, *lose, *pre = HeadTwo;

	lose = SearchNode(loser);
	if(lose == NULL) {
		lose = Create_RankNodeTwo(0, 1, loser, 0, 1, 0);
		temp = HeadTwo;
		if(temp == NULL)
			temp = lose;
		else {
			while(temp->Next != NULL)
				temp = temp->Next;
			temp->Next = lose;
		}
	}
	else {
		lose->record++;
		lose->lose++;
		lose->rate = ((double)lose->win / lose->record) * 100;
	}

	temp = SearchNode(winner);
	if(temp == NULL) {
		temp = Create_RankNodeTwo(0, 1, winner, 1, 0, 100.0);
	}
	else {
		if(temp->rank != 1) {
			while(pre != NULL) {
				if(strcmp(pre->Next->ID,temp->ID) == 0)
					break;
				pre = pre->Next;
			}
		}
		temp->win++;
		temp->record++;
		temp->rate = ((double)temp->win / temp->record) * 100;
		if(temp->rank == 1)
			return;
		pre->Next = temp->Next;
		temp->Next = NULL;
	}
	if(HeadTwo->win < temp->win) {
		temp->Next = HeadTwo;
		HeadTwo = temp;
		return;
	}
	for(pre = HeadTwo; pre->Next != NULL; pre = pre->Next) {
		if(pre->Next->win < temp->win) {
			temp->Next = pre->Next;
			pre->Next = temp;
			return;
		}
	}
	pre->Next = temp;
}
