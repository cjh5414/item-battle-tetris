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
	char ID[30];   // ����� ID
	char EMAIL[30]; // ����� ����
	char PASS[30]; // ����� ��й�ȣ
	struct data *next;     // ���� ���
} DATA;

DATA *head; //����� ����

void Init()
{
	head = NULL;        // �ʱ�ȭ
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
	char  ID[30];              // ����� ID
	char  EMAIL[30];          // ����� �̸���
	char  PASS[30];           // ����� ��й�ȣ
	FILE *file = fopen("information.txt", "rt");
	DATA* RoopData;
	if(NULL != file)
	{
		while(fscanf(file, "%s %s %s", ID, EMAIL, PASS)!=EOF)
		{


			if(head == NULL){      // �ε�� �ƹ� ����Ʈ�� ���� ���
				head = Create_Node(ID, EMAIL, PASS);   // head�� tail�� NULL�� ��´�
			}
			else            //ù ����� ���� ������ ����
			{
				RoopData = head;
				while(RoopData ->next != NULL)
				{
					RoopData = RoopData->next;
				}
				RoopData->next = Create_Node(ID, EMAIL, PASS);
			}
		}                     //while���� ��
		fclose(file);              //���ϴݱ�
	}
	//free(temp);  //��ȯ
}


void AddNode()
{
	FILE * fp;
	DATA *newdata;      // ���ο� ������
	DATA *temp = head;
	int cnt=0, i=0;         // ���̵� �߽߰� ++����
	char         ID[30];   // ����� ID
	char         EMAIL[30]; // ����� �̸���
	char         PASS[30]; // ����� ��й�ȣ
	char         RE_PASS[30];
	char  ch = 0;
	int count = 0;
	char tmp;
	point p;
	//int i;  

	newdata = (DATA*)malloc(sizeof(DATA)); // �����Ҵ�
	newdata->next = NULL;               // ������� NULL
	SetCurrentCursorPos(menuX-11, STARTY-1);
	printf("***�ʿ� ���� TETRIS ȸ�� ����!***");

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

			// Ư��Ű�� ��
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
			printf("�ּ� 4���̻� �ִ�15���̳��� �Է����ּ���.");
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
				printf("����θ� �Է����ּ���.");
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
				printf("         �ߺ��Ǵ� ID�Դϴ�.");
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
			printf("�ʼ��Է� �����̹Ƿ� �ٽ� �Է����ּ���.");
			SetColor(-1);
			continue;
		}
		SetCurrentCursorPos(menuX-14, STARTY);
		printf("                                            ");
		SetCurrentCursorPos(menuX-14, STARTY);
		SetColor(7);
		printf("         ��� ������ ID�Դϴ�.");
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
			printf("�ʼ��Է� �����̹Ƿ� �ٽ� �Է����ּ���.");
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
			printf("            �̸��� ������ �ƴմϴ�.");
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
			printf("�ּ� 4�� �̻� �ִ� 15�� �̳��� �Է����ּ���.\n");
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
			printf("         ��й�ȣ�� ���� �ʽ��ϴ�.");
			SetColor(-1);
			continue;
		}

		break;
	}

	strcpy(newdata->ID, ID);
	strcpy(newdata->EMAIL, EMAIL);
	strcpy(newdata->PASS, PASS);

	if(head == NULL)   // ����� ��尡 ���� ���(ó������ ��带 �����Ͽ� ������ ���)
	{
		head = newdata;   // head�� ���ο� ��忡 ����
	}
	else            // ����� ��尡 ���� ���
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

	printf("                              ***�ʿͳ��� TETRIS�� ���Ű� ȯ���մϴ�.***\n\n");
	getch();

	newdata = temp = NULL;   // newdata, temp ��带 ����
	free(newdata);         // ��ȯ
	free(temp);            // ��ȯ
}