#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

#include "basicHeader.h"
#include "startMenu.h"
#include "keyCurControl.h"
#include "color.h"
#include "signup.h"

#pragma warning(disable:4996)

typedef struct data {
	char ID[30];   // 사용자 ID
	char EMAIL[30]; // 사용자 메일
	char PASS[30]; // 사용자 비밀번호
	struct data *next;     // 다음 노드
} DATA;

DATA *head; //헤더와 테일

void Init()
{
	head = NULL;        // 초기화
	//head = (DATA*)malloc(sizeof(DATA));
}

DATA* Create_Node(char* ID, char* EMAIL, char* PASS)
{
	DATA* NewNode = (DATA*)malloc(sizeof(DATA));

	strcpy(NewNode->ID, ID);
	strcpy(NewNode->EMAIL, EMAIL);
	strcpy(NewNode->PASS, PASS);
	NewNode->next = NULL;

	return NewNode;

}

void LoadFile()
{
	char  ID[30];              // 사용자 ID
	char  EMAIL[30];          // 사용자 이메일
	char  PASS[30];           // 사용자 비밀번호
	FILE *file = fopen("information.txt", "rt");
	DATA* RoopData;
	if(NULL != file)
	{
		while(fscanf(file, "%s %s %s", ID, EMAIL, PASS)!=EOF)
		{


			if(head == NULL){      // 로드시 아무 리스트도 없는 경우
				head = Create_Node(ID, EMAIL, PASS);   // head와 tail을 NULL로 잡는다
			}
			else            //첫 노드의 다음 노드들을 연결
			{
				RoopData = head;
				while(RoopData ->next != NULL)
				{
					RoopData = RoopData->next;
				}
				RoopData->next = Create_Node(ID, EMAIL, PASS);
			}
		}                     //while문의 끝
		fclose(file);              //파일닫기
	}
	//free(temp);  //반환
}


void AddNode()
{
	FILE * fp;
	DATA *newdata;      // 새로운 데이터
	DATA *temp = head;
	int cnt=0, i=0;         // 아이디 발견시 ++변수
	char         ID[30];   // 사용자 ID
	char         EMAIL[30]; // 사용자 이메일
	char         PASS[30]; // 사용자 비밀번호
	char         RE_PASS[30];
	char  ch = 0;
	int count = 0;
	char tmp;
	point p;
	//int i;  

	newdata = (DATA*)malloc(sizeof(DATA)); // 공간할당
	newdata->next = NULL;               // 다음노드 NULL
	SetCurrentCursorPos(menuX-11, STARTY-1);
	printf("***너와 나의 TETRIS 회원 가입!***");

	Logo();

	while(1)
	{
		fflush(stdin);
		SetCurrentCursorPos(menuX-5, STARTY+1);
		printf("ID : ");
		//////
		//gets(ID);

		while(count>=0 &&count<=15) {
			tmp= getch();

			// 특수키일 때
			if(tmp == -32 || tmp == 0) {
				tmp = getch();
				continue;
			}

			else if (tmp == MENUESC)
				return;

			else if(tmp == MENUENTER) {
				ID[count] = '\0';
				break;
			}
			else if( count>0 && tmp==MENUBSPACE) {
				count--;

				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x-1, p.y);
				printf(" ");
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x-1, p.y);

				continue;
			}
			else if( count == 0 && tmp == MENUBSPACE) {
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x, p.y);
				continue;
			}
			else if(isalpha(tmp)!=0 || isdigit(tmp)!=0) {

				ID[count] = tmp;
				putchar(tmp);
			}
			else
				continue;

			count++;
		}

		//////////
		if(strlen(ID)<4 || strlen(ID)>15)
		{
			SetCurrentCursorPos(menuX-14, STARTY);
			printf("                                                            ");
			SetCurrentCursorPos(menuX-14, STARTY);
			SetColor(7);
			printf("최소 4자이상 최대15자이내로 입력해주세요.");
			SetColor(-1);
			continue;
		}
		for (i = 0; i < strlen(ID); i++)
		{
			if (!((ID[i] >= 'a' && ID[i] <= 'z') || (ID[i] >= 'A' && ID[i] <= 'Z')) && (!(ID[i]>='0' && ID[i]<='9')))
			{
				SetCurrentCursorPos(menuX-10, STARTY);
				printf("                                            ");
				SetCurrentCursorPos(menuX-10, STARTY);
				SetColor(7);
				printf("영어로만 입력해주세요.");
				SetColor(-1);
				break;
			}
		}
		if (!((ID[i] >= 'a' && ID[i] <= 'z') || (ID[i] >= 'A' && ID[i] <= 'Z')) && (!(ID[i] >= '0' && ID[i] <= '9')))
		{
			if (i != strlen(ID))
				continue;
		}

		while (temp != NULL)
		{
			if (strcmp(ID, temp->ID) == 0)
			{
				SetCurrentCursorPos(menuX-14, STARTY);
				printf("                                            ");
				SetCurrentCursorPos(menuX-14, STARTY);
				SetColor(7);
				printf("         중복되는 ID입니다.");
				SetColor(-1);
				break;
			}
			temp = temp->next;
		}

		if (temp != NULL)
		{
			if (strcmp(ID, temp->ID) == 0)
				continue;
		}

		if (strlen(ID) == 0)
		{
			SetCurrentCursorPos(menuX-14, STARTY);
			printf("                                            ");
			SetCurrentCursorPos(menuX-14, STARTY);
			SetColor(7);
			printf("필수입력 사항이므로 다시 입력해주세요.");
			SetColor(-1);
			continue;
		}
		SetCurrentCursorPos(menuX-14, STARTY);
		printf("                                            ");
		SetCurrentCursorPos(menuX-14, STARTY);
		SetColor(7);
		printf("         사용 가능한 ID입니다.");
		SetColor(-1);
		break;
	}


	while (1)
	{
		fflush(stdin);
		SetCurrentCursorPos(menuX-8, STARTY+2);
		printf("EMAIL : ");
		gets(EMAIL);

		if (strlen(EMAIL) == 0)
		{
			SetCurrentCursorPos(menuX-14, STARTY);
			printf("                                            ");
			SetCurrentCursorPos(menuX-14, STARTY);
			SetColor(7);
			printf("필수입력 사항이므로 다시 입력해주세요.");
			SetColor(-1);
			continue;
		}

		for (i = 0; i < strlen(EMAIL); i++)
		{
			if (EMAIL[i] == '@')
			{
				if ((isalpha(EMAIL[i-1]) || isdigit(EMAIL[i-1])) && (isalpha(EMAIL[i+1]) || isdigit(EMAIL[i+1])))
					break;
			}
		}

		if (EMAIL[i] == '@')
			break;
		else
		{
			SetCurrentCursorPos(menuX-14, STARTY);
			printf("                                            ");
			SetCurrentCursorPos(menuX-14, STARTY);
			SetColor(7);
			printf("            이메일 형식이 아닙니다.");
			SetColor(-1);
			continue;
		}
	}

	ch = i = 0;
	while (1)
	{   
		fflush(stdin);
		SetCurrentCursorPos(menuX-5, STARTY+3);
		printf("PW : ");
		memset(PASS, 0, sizeof(char)*30);
		ch = i = 0;
		while (1)
		{
			ch = getch();

			if(ch == -32){
				fflush(stdin);
				continue;
			}

			else if (ch == '\r'){
				PASS[i] = '\0';
				break;
			}

			else if( ch  == MENUESC)
				return;


			else if(ch == MENUBSPACE){

				i--;
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x-1, p.y);
				printf(" ");
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x-1, p.y);
				continue;

			}

			else if(i==0 && ch == MENUBSPACE){
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x, p.y);
				continue;
			}

			else{
				PASS[i++] = ch;
				putch('*');
			}
		}
		PASS[i] = '\0';

		if (strlen(PASS)<4 || strlen(PASS) >15)
		{
			SetCurrentCursorPos(menuX-14, STARTY);
			printf("                                            ");
			SetCurrentCursorPos(menuX-14, STARTY);
			SetColor(7);
			printf("최소 4자 이상 최대 15자 이내로 입력해주세요.\n");
			SetColor(-1);
			continue;
		}

		ch = i = 0;
		memset(RE_PASS, 0, sizeof(char)*30);
		fflush(stdin);
		SetCurrentCursorPos(menuX-13, STARTY+4);
		printf("PW recheck : ");
		while (1)
		{
			ch = getch();
			if (ch == '\r')
				break;

			else if(ch == MENUBSPACE){

				i--;
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x-1, p.y);
				printf(" ");
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x-1, p.y);
				continue;

			}

			else if(i==0 && ch == MENUBSPACE){
				p = GetCurrentCursorPos();
				SetCurrentCursorPos(p.x, p.y);
				continue;
			}

			else if(ch == MENUESC)
				return;

			RE_PASS[i++] = ch;
			putch('*');
		}
		RE_PASS[i] = '\0';
		printf("\n");

		if (strcmp(PASS, RE_PASS) != 0)
		{
			SetCurrentCursorPos(menuX-14, STARTY);
			printf("                                            ");
			SetCurrentCursorPos(menuX-14, STARTY);
			SetColor(7);
			printf("         비밀번호가 같지 않습니다.");
			SetColor(-1);
			continue;
		}

		break;
	}

	strcpy(newdata->ID, ID);
	strcpy(newdata->EMAIL, EMAIL);
	strcpy(newdata->PASS, PASS);

	if(head == NULL)   // 연결된 노드가 없을 경우(처음으로 노드를 생성하여 연결할 경우)
	{
		head = newdata;   // head를 새로운 노드에 연결
	}
	else            // 연결된 노드가 있을 경우
	{
		DATA* roopData = head;
		while(roopData != NULL)
			roopData = roopData->next;
		roopData = temp;
	}
	fflush(stdin);

	fp = fopen("information.txt", "a+");
	fprintf(fp, "%s %s %s \n", ID, EMAIL, PASS);
	fclose(fp);

	printf("                              ***너와나의 TETRIS에 오신걸 환영합니다.***\n\n");
	getch();

	newdata = temp = NULL;   // newdata, temp 노드를 비운다
	free(newdata);         // 반환
	free(temp);            // 반환
}