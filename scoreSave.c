#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#include "keyCurControl.h"
#include "basicHeader.h"
#include "startMenu.h"
#include "scoreSave.h"
#include "scoreSave2.h"
#include "color.h"
#include "playMenu.h"

Node* Head = NULL;

/* 1인용 랭킹파일 Read */
void ReadRankFile(){
	FILE* fp;
	int score, HoldFlag, rank;
	char ID[30];
	fp = fopen("ranking.txt", "r");
	if(fp==NULL)
		return;
	while (fscanf(fp, "%d %s %d %d", &rank, ID, &score, &HoldFlag) != EOF){
		AppendNode(&Head, Create_RankNode(rank, score, ID, HoldFlag));
	}
	fclose(fp);
}

/* 랭킹파일 Save */
void SaveRankFile(){
	FILE* fp;
	int i = 1;
	Node* Temp;
	fp = fopen("ranking.txt", "w");
	if(fp==NULL)
		return;
	Temp = Head;
	while (Temp != NULL){
		fprintf(fp, "%d %s %d %d\n", i, Temp->ID, Temp->score, Temp->HoldFlag);
		Temp->rank = i;
		Temp = Temp->Next;
		i++;
	}
	fclose(fp);
}

Node* Create_RankNode(int rank, int score, char* ID, int HoldFlag){
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->rank = rank;
	NewNode->score = score;
	strcpy(NewNode->ID, ID);
	NewNode->HoldFlag = HoldFlag;
	NewNode->Next = NULL;

	return NewNode;
}

/* 랭킹 노드 추가, 게임끝난 후 1p추가  */
void AppendNode(Node** Head, Node* NewNode){
	Node* pre = *Head;
	if (*Head == NULL){
		*Head = NewNode;
		(*Head)->Next = NULL;
	}
	else if(pre->Next == NULL) {
		if(pre->score < NewNode->score) {
			NewNode->Next = pre;
			*Head = NewNode;
		}
		else {
			pre->Next = NewNode;
		}
	}
	else{
		Node *Temp = pre->Next;
		if(pre->score < NewNode->score) {
			NewNode->Next = pre;
			*Head = NewNode;
		}
		else {
			while (Temp != NULL){
				if (Temp->score < NewNode->score){
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

/* 랭킹파일 Display */
void DisplayRank() {
	Node* Temp;
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
		Temp = Head;
		i = 0;
		SetCurrentCursorPos(menuX, STARTY-8);
		printf("\n\t\t\t\t\t1인용 RANKING\n");
		printf("\t\t------------------------------------------------------------------\n");
		printf("\t\t\t순위\t\t아이디\t\t점수\t\tHOLD\n");
		printf("\t\t------------------------------------------------------------------\n");
		while (Temp != NULL && i<10){
			printf("\t\t\t%d\t\t%s\t\t%d\t\t", Temp->rank, Temp->ID, Temp->score);
			if (Temp->HoldFlag)
				printf("%s\n", "ON  ");
			else
				printf("%s\n", "OFF");
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
	} while(RankSearch(ID));
}

/* 나의 랭킹 조회 */
int RankSearch(char* ID){
	Node* Temp = Head;
	Node* Result;
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
	printf("\n\t\t\t\t\t1인용 RANKING\n");
	printf("\t\t------------------------------------------------------------------\n");
	printf("\t\t\t순위\t\t아이디\t\t점수\t\tHOLD\n");
	printf("\t\t------------------------------------------------------------------\n");
	Result=Temp;
	Temp = Head;
	while (Temp != NULL && flag){
		if (j >= i - 4 && j < i + 6){
			if(j==i)
				SetColor(1);
			printf("\t\t\t%d\t\t%s\t\t%d\t\t", Temp->rank, Temp->ID, Temp->score);
			if (Temp->HoldFlag)
				printf("%s\n", "ON  ");
			else
				printf("%s\n", "OFF");
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
		printf("\t\t\t%d\t\t%s\t\t%d\t\t", Temp->rank, Temp->ID, Temp->score);
		if (Temp->HoldFlag)
			printf("%s\n", "ON");
		else
			printf("%s\n", "OFF");
		Temp = Temp->Next;
	}

	printf("\n");
	return 1;
}

Node *SearchID(char *ID) {
	Node *temp = Head;
	while(temp != NULL) {
		if(strcmp(temp->ID, ID) == 0)
			break;
		temp = temp->Next;
	}
	return temp;
}

void SortGameResult(int GameScore, char *ID_1p, int isHoldMode) {
	Node *temp, *pre = Head;

	temp = SearchID(ID_1p);
	if(temp == NULL) {
		temp = Create_RankNode(0, GameScore, ID_1p, isHoldMode);
	}
	else {
		if(temp->score < GameScore) {
			if(temp->rank != 1) {
				while(pre != NULL) {
					if(strcmp(pre->Next->ID,temp->ID) == 0)
						break;
					pre = pre->Next;
				}
			}
			temp->score = GameScore;
			temp->HoldFlag = isHoldMode;
			if(temp->rank == 1)
				return;
			pre->Next = temp->Next;
			temp->Next = NULL;
		}
		else
			return;
	}
	if(Head->score < temp->score) {
		temp->Next = Head;
		Head = temp;
		return;
	}
	for(pre = Head; pre->Next != NULL; pre = pre->Next) {
		if(pre->Next->score < temp->score) {
			temp->Next = pre->Next;
			pre->Next = temp;
			return;
		}
	}
	pre->Next = temp;
}
