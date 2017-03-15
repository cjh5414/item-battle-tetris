#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include "Login.h"
#include "basicHeader.h"
#include "signup.h"
#include "color.h"
#include "point.h"
#include "keyCurControl.h"

typedef struct data {
	char ID[30];   // ����� ID
	char EMAIL[30]; // ����� ����
	char PASS[30]; // ����� ��й�ȣ
	struct data *next;     // ���� ���
}DATA;
DATA *head=NULL;//����� ����

void Save_File() {
	FILE* fp=fopen("information.txt", "w");
	DATA* temp=head;

	while(temp!=NULL) {
		fprintf(fp, "%s %s %s\n", temp->ID, temp->EMAIL, temp->PASS);
		temp=temp->next;
	}
	fclose(fp);
}

void Reset_pw() {
	int x = menuX_1p-3;
	int y = STARTY+1;

	char ID[30];
	char EMAIL[30];
	char PASS[30];
	char inputID[30];
	char inputMail[30];
	char inputPW[30], Re_Pass[30];
	DATA* temp;
	FILE* fp = fopen("information.txt", "r");
	char ch = 0;
	int i= 0;
	point p;

	if (fp == NULL)	{
		printf("File Open FAIL!\n");
		return;
	}

	while (fscanf(fp, "%s %s %s", ID, EMAIL, PASS) != EOF) 	{
		DATA* NewNode = (DATA*)malloc(sizeof(DATA));
		strcpy(NewNode->ID, ID);
		strcpy(NewNode->EMAIL, EMAIL);
		strcpy(NewNode->PASS, PASS);
		NewNode->next = NULL;

		if (head == NULL)
			head = NewNode;
		else {
			temp = head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = NewNode;
		}
	}

	system("cls");
	Logo();
	SetCurrentCursorPos(x+6,y-2);
	printf("��й�ȣ �缳��");

	fflush(stdin);
	SetCurrentCursorPos(x,y);
	printf("ID : ");
	gets(inputID);
	fflush(stdin);
	SetCurrentCursorPos(x,y+1);
	printf("E-mail : ");
	gets(inputMail);

	temp = head;

	while (temp->next != NULL)
	{
		if (strcmp(temp->ID, inputID) == 0)
		{
			if (strcmp(temp->EMAIL, inputMail) == 0)
			{
				memset(inputPW, 0,sizeof(char)*30);
				i=ch=0;
				fflush(stdin);
				SetCurrentCursorPos(x,y+2);
				printf("Password : ");
				while (1)
				{
					ch = getch();
					if (ch == '\r')
						break;

					else if(ch == MENUBSPACE) {
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

					inputPW[i++] = ch;
					putch('*');
				}
				puts("");
				memset(Re_Pass, 0,sizeof(char)*30);
				i=ch=0;
				fflush(stdin);
				SetCurrentCursorPos(x,y+3);
				printf("Password recheck : ");
				while (1) {
					ch = getch();
					if (ch == '\r')
						break;
					else if(ch == MENUBSPACE) {
						i--;
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						printf(" ");
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						continue;
					}

					else if(i==0 && ch == MENUBSPACE) {
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x, p.y);
						continue;
					}
					Re_Pass[i++] = ch;
					putch('*');
				}
				puts("");
				if(strcmp(inputPW, Re_Pass)==0) {
					strcpy(temp->PASS, inputPW);SetCurrentCursorPos(x,y-1);
					printf("��й�ȣ ���� ����\n");
					Save_File();
					return ;
				}
				else {
					SetCurrentCursorPos(x,y-1);
					SetColor(7);
					printf("��й�ȣ�� ���� Ʋ���ϴ�.\n");
					SetColor(-1);
					return ;
				}
			}
			else {
				printf("�̸��� ���� ����!\n");
				getch();
				return;
			}
		}
		temp = temp ->next;
	}
	SetCurrentCursorPos(x,y-1);
	SetColor(7);
	printf("�ش� ���̵� �������� �ʽ��ϴ�.\n");
	SetColor(-1);
	getch();
}

void Find_id() { // ���̵� ã�� �Լ�
	char ID[30];
	char EMAIL[30];
	char inputMail[30];
	FILE* fp = fopen("information.txt", "r");

	int x = menuX_1p-3;
	int y = STARTY+1;

	if (fp == NULL) {
		printf("File Open FAIL!\n");
		return;
	}

	Logo();
	SetCurrentCursorPos(x+10,y-2);
	printf("ID ã�� ");
	SetCurrentCursorPos(x,y);
	printf(" E-mail [                       ]");
	fflush(stdin);
	SetCurrentCursorPos(x+9,y);
	scanf("%s", inputMail);

	while (fscanf(fp, "%s %s %*s", ID, EMAIL) != EOF) {
		if (strcmp(inputMail, EMAIL) == 0) {
			SetColor(7);
			SetCurrentCursorPos(x+5,y-1);
			printf("ID : %s\n", ID);
			SetColor(-1);
			getch();
			return;
		}
	}

	SetCurrentCursorPos(x+2,y-1);
	SetColor(7);
	printf("���̵� ã�� ���Ͽ����ϴ�.");
	SetColor(-1);
	getch();
}

void LoginMenu_1p() {
	SetCurrentCursorPos(menuX_1p, STARTY);
	printf("1P");

	SetCurrentCursorPos(menuX_1p, STARTY+1);
	printf("ID [               ]");

	SetCurrentCursorPos(menuX_1p, STARTY+2);
	printf("PW [               ]");

	SetCurrentCursorPos(menuX_1p+8, STARTY+3);
	printf("Log In");

	SetCurrentCursorPos(menuX_1p-6, STARTY+4);
	printf("Sign Up      ID find      PW reset");
}

void LoginMenu_2p() {
	SetCurrentCursorPos(menuX_2p, STARTY);
	printf(" 1p\t\t\t   2p");

	SetCurrentCursorPos(menuX_2p, STARTY+1);
	printf("ID [               ]");

	SetCurrentCursorPos(menuX_2p+25, STARTY+1);
	printf("ID [               ]");

	SetCurrentCursorPos(menuX_2p, STARTY+2);
	printf("PW [               ]");

	SetCurrentCursorPos(menuX_2p+25, STARTY+2);
	printf("PW [               ]");

	SetCurrentCursorPos(menuX_1p+8, STARTY+3);
	printf("Log In");

	SetCurrentCursorPos(menuX_1p-6, STARTY+4);
	printf("Sign Up       ID find        PW reset");
}

// 1�ο� �α��� ȭ�鿡�� �޴����� �Լ�
void LoginMenuSel_1p() {
	point p;

	char temp;
	int x = menuX_1p-3;
	int y = STARTY+1;

	char ID_input[30];
	char PW_input[30];

	char CharCheck;
	char temp2;

	while(1) {
		SetCurrentCursorPos(x, y);
		printf("��");

		temp = getch();

		SetCurrentCursorPos(x, y);
		printf("  ");

		switch(temp) {
		case MENUUP:
			x = menuX_1p-3;
			y--;
			break;
		case MENUDOWN :
			x = menuX_1p-3;
			y++;
			break;
		case MENUESC:
			return;
		case MENUENTER :
			// 1�ο� ID �Է�
			if(y==STARTY+1) {
				int count=0;

				SetCurrentCursorPos(x+7, y);
				printf("               ");

				SetCurrentCursorPos(x+7, y);
				CursorSetting(1);

				while(count>=0 &&count<15) {
					CharCheck = getch();

					// Ư��Ű�� ��
					if(CharCheck == -32 || CharCheck == 0) {
						temp2 = getch();
						continue;
					}
					else if(CharCheck == MENUENTER) {
						ID_input[count] = '\0';
						break;
					}
					else if( count>0 && CharCheck==MENUBSPACE) {
						count--;

						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						printf(" ");
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);

						continue;
					}
					else if( count == 0 && CharCheck == MENUBSPACE) {
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x, p.y);
						continue;
					}
					else if(isalpha(CharCheck)!=0 || isdigit(CharCheck)!=0) {

						ID_input[count] = CharCheck;
						putchar(CharCheck);
					}
					else
						continue;

					count++;
				}

				fflush(stdin);
				CursorSetting(0);
			}

			// 1�ο� PW�Է�
			else if(y==STARTY+2) {
				int count=0;

				SetCurrentCursorPos(x+7, y);
				printf("               ");

				SetCurrentCursorPos(x+7, y);
				CursorSetting(1);

				while(count>=0 && count<15){
					CharCheck = getch();

					// Ư��Ű�̸� �׳� ������!
					if(CharCheck==-32 || CharCheck==0) {
						temp2 = getch();
						continue;
					}

					else if(CharCheck == MENUENTER){
						PW_input[count] = '\0';
						break;
					}

					else if(count>0 && CharCheck == MENUBSPACE) {
						count--;

						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						printf(" ");
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						continue;
					}

					else if(count==0 && CharCheck == MENUBSPACE) {
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x, p.y);
						continue;
					}

					else if(isalpha(CharCheck)!=0 || isdigit(CharCheck)!=0) {
						PW_input[count] = CharCheck;
						putchar('*');
					}
					else 
						continue;

					count++;
				}
				fflush(stdin);
				CursorSetting(0);
			}

			// 1�ο� Login
			else if(y==STARTY+3) {
				switch(LoginCheck(ID_input, PW_input)){
				case 1: 
					SetCurrentCursorPos(menuX_1p, STARTY-1);
					printf("                     ");
					SetCurrentCursorPos(menuX_1p, STARTY-1);
					SetColor(7);
					printf("   PW  is diffrent!");
					SetColor(-1);
					break;
				case 2:
					SetCurrentCursorPos(menuX_1p, STARTY-1);
					SetColor(7);
					printf("Can not find your ID!");
					SetColor(-1);
					break;
				case 3: 
					LoginCheckNum = SUCCESS;
					strcpy(ID_1p, ID_input);
					return;
				}
			}
		}

		if(y<STARTY+1)
			y++;

		else if(y>STARTY+4)
			y--;

		else if(y==STARTY+4){
			SetCurrentCursorPos(x, y-1);
			printf("  ");
			etcSel(&temp, &x, &y);
		}

		else if(y==STARTY+3)
			x = menuX_1p+5;

		// �Ʒ� �޴����� ESC�� ������ ��
		if(temp == MENUESC)
			return;

		fflush(stdin);
	}
	fflush(stdin);
}

// 2�ο� �α��� ȭ�鿡�� �޴����� �Լ�
void LoginMenuSel_2p(){
	point p;

	char temp;      // ��ɼ�����
	int x = menuX_2p-3;
	int y = STARTY+1;
	int term = 25;

	int save_x = x;

	char ID_input1[30];
	char ID_input2[30];
	char PW_input1[30];
	char PW_input2[30];

	char CharCheck;   // �Է�Ȯ�ο�
	char temp2;      // ID/PW Ư��Ű �Է¹�����

	do{
		SetCurrentCursorPos(x, y);
		printf("��");

		temp = getch();

		SetCurrentCursorPos(x, y);
		printf("  ");

		switch(temp) {
		case MENUUP :
			x = save_x; 
			y--;
			break;
		case MENUDOWN:
			x = save_x;
			y++;
			break;
		case MENULEFT:
			x -= term;
			break;
		case MENURIGHT:
			x += term;
			break;

		case MENUENTER:
			if(y==STARTY+1 && x==menuX_2p-3) {
				int count=0;

				SetCurrentCursorPos(x+7, y);
				printf("               ");

				SetCurrentCursorPos(x+7, y);
				CursorSetting(1);

				while(count>=0 &&count<15) {
					CharCheck = getch();

					if(CharCheck == 0 || CharCheck == -32) {
						temp2 = getch();
						continue;
					}

					else if(CharCheck == MENUENTER){ 
						ID_input1[count] = '\0';
						break;
					}
					else if( count>0 && CharCheck == MENUBSPACE) {
						count--;

						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						printf(" ");
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						continue;
					}
					else if( count == 0 && CharCheck == MENUBSPACE) {
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x, p.y);
						continue;
					}
					else if(isalpha(CharCheck)!=0 || isdigit(CharCheck)!=0) {
						ID_input1[count] = CharCheck;
						putchar(CharCheck);
					}
					else continue;
					count++;
				}

				fflush(stdin);
				CursorSetting(0);
			}

			// 2�ο� 2p ID�Է�
			else if(y==STARTY+1 && x==menuX_2p-3+term) {
				int count=0;

				SetCurrentCursorPos(x+7, y);
				printf("               ");

				SetCurrentCursorPos(x+7, y);
				CursorSetting(1);

				while(count>=0 &&count<15) {
					CharCheck = getch();
					if(CharCheck == -32 || CharCheck ==0) {
						temp2 = getch();
						continue;
					}
					else if(CharCheck == MENUENTER){
						ID_input2[count] ='\0';
						break;
					}
					else if( count>0 && CharCheck == MENUBSPACE) {
						count--;

						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						printf(" ");
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						continue;
					}
					else if( count == 0 && CharCheck == MENUBSPACE){
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x, p.y);
						continue;
					}

					else if(isalpha(CharCheck)!=0 || isdigit(CharCheck)!=0){
						ID_input2[count] = CharCheck;
						putchar(CharCheck);
					}

					else continue;
					count++;
				}
				fflush(stdin);
				CursorSetting(0);
			}

			// 2�ο� 1p PW�Է�
			else if(y==STARTY+2 && x==menuX_2p-3) {
				int count=0;

				SetCurrentCursorPos(x+7, y);
				printf("               ");

				SetCurrentCursorPos(x+7, y);
				CursorSetting(1);

				while(count>=0 && count<15) {
					CharCheck = getch();

					if(CharCheck == -32 || CharCheck == 0){
						temp2 = getch();
						continue;
					}
					else if(CharCheck == MENUENTER) { 
						PW_input1[count] = '\0';
						break;
					}
					if(count>0 && CharCheck == MENUBSPACE) {
						count--;

						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						printf(" ");
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						fflush(stdin);
						continue;
					}
					else if(count==0 && CharCheck == MENUBSPACE) {
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x, p.y);
						continue;
					}
					else if(isalpha(CharCheck)!=0 || isdigit(CharCheck)!=0) {
						PW_input1[count] = CharCheck;
						putchar('*');
					}
					else continue;
					count++;
				}
				fflush(stdin);
				CursorSetting(0);
			}

			// 2�ο� 2p PW�Է�
			else if(y==STARTY+2 && x==menuX_2p-3+term) {
				int count=0;

				SetCurrentCursorPos(x+7, y);
				printf("               ");

				SetCurrentCursorPos(x+7, y);
				CursorSetting(1);

				while(count>=0 && count<15) {
					CharCheck = getch();

					if(CharCheck == -32 || CharCheck == 0){
						temp2 = getch();
						continue;
					}
					else if(CharCheck == MENUENTER){
						PW_input2[count] = '\0';
						break;
					}
					if(count>0 && CharCheck == MENUBSPACE) {
						count--;

						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						printf(" ");
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x-1, p.y);
						continue;
					}
					else if(count==0 && CharCheck == MENUBSPACE) {
						p = GetCurrentCursorPos();
						SetCurrentCursorPos(p.x, p.y);
						continue;
					}
					else if(isalpha(CharCheck)!=0 || isdigit(CharCheck)!=0) {
						PW_input2[count] = CharCheck;
						putchar('*');
					}
					count++;
				}
				fflush(stdin);
				CursorSetting(0);
			}

			// 2�ο� Login
			else if(y==STARTY+3) {
				SetCurrentCursorPos(menuX_1p-3, STARTY-1);
				printf("                            ");
				if(strcmp(ID_input1, ID_input2)==0){
					SetCurrentCursorPos(menuX_1p-3, STARTY-1);
					SetColor(7);
					printf("1p's ID and 2p's ID is same!");
					SetColor(-1);
					break;
				}
				switch(LoginCheck(ID_input1, PW_input1)) {

				case 1: 
					SetCurrentCursorPos(menuX_1p+1, STARTY-1);
					SetColor(7);
					printf("1P's PW  is diffrent!");
					SetColor(-1);
					break;
				case 2:
					SetCurrentCursorPos(menuX_1p+1, STARTY-1);
					SetColor(7);
					printf("Can not find 1p's ID!");
					SetColor(-1);
					break;
				case 3:
					switch(LoginCheck(ID_input2, PW_input2)) {
					case 1:
						SetCurrentCursorPos(menuX_1p+1, STARTY-1);
						SetColor(7);
						printf("2P's PW  is diffrent!");
						SetColor(-1);
						break;
					case 2:
						SetCurrentCursorPos(menuX_1p+1, STARTY-1);
						SetColor(7);
						printf("Can not find 2p's ID!");
						SetColor(-1);
						break;
					case 3:
						LoginCheckNum = SUCCESS;
						strcpy(ID_1p, ID_input1);
						strcpy(ID_2p, ID_input2);
						return;
					}
				}
			}
			break;
		case MENUESC:
			return;
		default :
			continue;
		}

		// ���� ����ġ�� �ʵ���
		if(y<STARTY+1)
			y++;
		else if(y>STARTY+4)
			y--;
		if(x <menuX_2p-3)
			x += term;
		else if(x>menuX_2p + term)
			x -= term;

		// y��ǥ�� �´� x��ǥ �缳��
		if(y==STARTY+3)
			x = menuX_1p+5;
		else if(y==STARTY+4)
			etcSel(&temp, &x, &y);
		else
			save_x = x;
		fflush(stdin);
	}while(1);

	fflush(stdin);
}

void etcSel(char *tmp, int *x, int *y) {
	char temp;
	int etcx = menuX_1p-9;
	int term = 13;

	while(1) {
		system("cls");
		Logo();

		if(playernum==1)
			LoginMenu_1p();
		else if(playernum==2)
			LoginMenu_2p();
		fflush(stdin);
		SetCurrentCursorPos(etcx, *y);
		printf("��");

		temp = getch();

		SetCurrentCursorPos(etcx, *y);
		printf("  ");

		switch(temp) {
		case MENULEFT :
			etcx -= term;
			break;
		case MENURIGHT :
			etcx += term;
			break;
		case MENUUP:
			*x = menuX_1p+5;
			--(*y);
			return;
		case MENUENTER:
			if(etcx == menuX_1p-9) {
				//ȸ������
				CursorSetting(1);
				//int MenuP();     // �޴���°� ���Ϸε�
				system("cls");
				Init();     // �ʱ�ȭ
				AddNode();     // ȸ�� ����
				//   Printlist(); // ȸ�� ��� ���
				LoadFile();  // txt������ �о� ������ �ۼ� 
				//   SaveFile();  // �����͸� txt���Ͽ� ����;
			}
			else if(etcx == menuX_1p-9+term) {
				system("cls");
				CursorSetting(1);
				Find_id();
				CursorSetting(0);
			}
			else if(etcx == menuX_1p-9+2*term) {
				system("cls");
				CursorSetting(1);
				Reset_pw();
				CursorSetting(0);
				getch();
			}
			break;

		case MENUESC :
			*tmp = MENUESC;
			return;
		}

		if(etcx < menuX_1p-9)
			etcx += term;

		else if(etcx > menuX_1p-9 + (2*term))
			etcx -= term;
	}
}


void Login(int playernum){
	system("cls");
	Logo();

	//1�ο��� �������� ���
	if(playernum == 1) {
		LoginMenu_1p();
		LoginMenuSel_1p();
	}

	//2�ο��� �������� ���
	else{
		LoginMenu_2p();
		LoginMenuSel_2p();
	}
}

// �α��� Ȯ��
// return 1 �̸� -> PW ����
// return 2 �̸� -> ID ����
int LoginCheck(char ID_input[], char PW_input[]) {
	FILE *fp;
	char ID_check[30];
	char PW_check[30];

	fp = (FILE *)fopen("information.txt","r");

	if(fp == NULL)
		exit(0);

	SetCurrentCursorPos(menuX_1p, STARTY-1);
	printf("                    ");

	// ���� ���� open
	while(feof(fp) == 0) {
		fscanf(fp, "%s %*s %s", ID_check, PW_check);

		if(strcmp(ID_check, ID_input)==0) {
			if(strcmp(PW_check, PW_input)==0)
				return 3;
			else {
				fclose(fp);
				return 1;
			}

		}
	}
	fclose(fp);
	return 2;
}