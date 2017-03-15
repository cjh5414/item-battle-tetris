#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#include "keyCurControl.h"
#include "playMenu.h"
#include "basicHeader.h"
#include "color.h"
#include "point.h"
#include "play.h"
#include "scoreSave.h"
#include "scoreSave2.h"
#include "startMenu.h"

int playernum;
int LoginCheckNum;
char ID_1p[30];
char ID_2p[30];
int BGMCheck = 1;
int optionGameLevel = 1;
int optionItemMode = 1;

extern int LEFT[3];
extern int RIGHT[3];
extern int UP[3];
extern int DOWN[3];
extern int SPACE[3];
extern int HOLD[3];
extern int ITEMUSEME[3];
extern int ITEMUSEYOU[3];
extern int ITEMREMOVE[3];


int Play_menu() {
	int sel, temp;
	point menupoint;

	menupoint.x = PMenuX-3;
	menupoint.y = STARTY+2;

	makeMenu();
	PlaySound(TEXT("내 솜씨를 제대로보여줄시간이군.wav"),
		NULL, SND_ASYNC);

	while(1) {
		// 
		make_line();
		Logo();

		take_rank(ID_1p, 1);

		if(playernum==2)
			take_rank(ID_2p, 2);

		makeMenu();

		sel = PlayMenuSel(menupoint.x, menupoint.y);

		switch(sel){
		case 1:
			if(playernum == 1) {
				do {
					system("cls");
					SetColor(9);
					temp = oneplay(playernum-1);
					if(temp == 3) 
						break;
				}while(temp);
			}
			else if(playernum == 2) {
				do {
					system("cls");
					SetColor(9);
					temp = twoplay(playernum-1);
					if(temp == 3) 
						break;
				}while(temp);
			}

			menupoint.x = PMenuX-3;
			menupoint.y = STARTY+2;
			SetColor(-1);
			break;

		case 2 :
			//ranking
			make_line();

			take_rank(ID_1p, 1);

			if(playernum==2)
				take_rank(ID_2p, 2);

			Rank_num();
			system("cls");

			switch(ranknum){
			case 1:
				DisplayRank();
				system("cls");
				break;

			case 2:
				DisplayTwoRank();
				break;
			}

			break;

		case 3 :
			Option();
			menupoint.x = PMenuX-3;
			menupoint.y = STARTY+3;
			break;

		case 4 :
			Information();
			menupoint.x = PMenuX-3+term;
			menupoint.y = STARTY+3;
			break;

		case 5 : 
			LogoutCheckPrint();
			if(LogoutCheck() == 1)
				return sel;

			//false 이면 다시 Playmenu
			else{
				menupoint.y = STARTY+4;
				break;
			}

		case 6 :
			Exit();
		}
	}
}

void make_line(void){


	int i, j;
	int x = 10;
	int y = 1;
	point p;

	SetCurrentCursorPos(0,0);
	system("cls");

	// 맨 윗줄
	p = GetCurrentCursorPos();
	SetCurrentCursorPos(p.x+8, p.y);
	printf("┌");

	for(i=0;i<8;i++)
		printf("─");
	printf("┬");

	for(i=0;i<3;i++)
		printf("─");
	printf("┬");


	for(i=0;i<8;i++)
		printf("─");
	printf("┬");

	for(i=0;i<3;i++)
		printf("─");
	printf("┬");

	for(i=0;i<12;i++)
		printf("─");


	printf("┐\n");

	for(j=0; j<=playernum; j++){
		p = GetCurrentCursorPos();
		SetCurrentCursorPos(p.x+8, p.y);
		// 정보 탭이름 입력칸
		printf("│                ");   // ID 입력칸 16
		printf("│      ");            // Rank 입력칸 6
		printf("│                ");   // 최고점수 입력칸 16
		printf("│      ");            // hold 입력칸 4
		printf("│                        │\n"); // 2인용 전적 나머지

		if(j==playernum)
			break;

		// 구분선
		p = GetCurrentCursorPos();
		SetCurrentCursorPos(p.x+8, p.y);
		printf("├");

		for(i=0;i<8;i++)
			printf("─");
		printf("┼");

		for(i=0;i<3;i++)
			printf("─");
		printf("┼");


		for(i=0;i<8;i++)
			printf("─");
		printf("┼");

		for(i=0;i<3;i++)
			printf("─");
		printf("┼");

		for(i=0;i<12;i++)
			printf("─");


		printf("┤\n");

	}

	//맨 아랫줄
	p = GetCurrentCursorPos();
	SetCurrentCursorPos(p.x+8, p.y);
	printf("└");

	for(i=0;i<8;i++)
		printf("─");
	printf("┴");

	for(i=0;i<3;i++)
		printf("─");
	printf("┴");

	for(i=0;i<8;i++)
		printf("─");
	printf("┴");

	for(i=0;i<3;i++)
		printf("─");
	printf("┴");

	for(i=0;i<12;i++)
		printf("─");

	printf("┘\n");


	SetCurrentCursorPos(x+7, y);
	printf("ID");
	SetCurrentCursorPos(x+19, y);
	printf("RANK");      
	SetCurrentCursorPos(x+30, y);
	printf("BEST SCORE");
	SetCurrentCursorPos(x+45, y);
	printf("HOLD");
	SetCurrentCursorPos(x+58, y);
	printf("2PLAY SCORE");


}

void take_rank(char ID[], int num){

	rankInf rank;

	FILE *fp;
	FILE *fp2;
	int y = 1+(2*num);
	int x = 10;
	int fend1=0, fend2=0;


	fp = (FILE *)fopen("ranking.txt","r");
	fp2 = (FILE *)fopen("ranking2.txt","r");

	if(fp == NULL || fp2 == NULL)
		exit(0);

	while(1) {
		fend1=fscanf(fp, "%d %s %d %d",&rank.rank_1p, rank.IDCheck, 
			&rank.best_score, &rank.Hold);
		if(strcmp(rank.IDCheck, ID)==0) {

			SetCurrentCursorPos(x+1, y);
			printf("%s", ID);

			SetCurrentCursorPos(x+19, y);
			printf("%d", rank.rank_1p);

			SetCurrentCursorPos(x+27, y);
			printf("%d", rank.best_score);

			SetCurrentCursorPos(x+46, y);
			if(rank.Hold) 
				printf("ON");
			else
				printf("OFF");

			break;
		}

		if(fend1 == -1 ) {
			SetCurrentCursorPos(x+1, y);
			printf("%s", ID);

			SetCurrentCursorPos(x+27, y);
			printf("정보 없음");
			break;
		}

	}


	while(1) {      
		fend2=fscanf(fp2, "%d %s %*d %*d %*d %lf",
			&rank.rank_2p, rank.IDCheck, &rank.rate);
		if(strcmp(rank.IDCheck, ID)==0) {
			SetCurrentCursorPos(64, y);
			printf("no.%d", rank.rank_2p);
			SetCurrentCursorPos(79, y);
			printf("%5.1lf%%", rank.rate);
			break;
		}

		if(fend2 == -1) {
			SetCurrentCursorPos(64, y);
			printf("정보 없음");
			break;
		}
	}

	fclose(fp);
}

void makeMenu(){

	int x = PMenuX;
	int y = STARTY+2;

	SetCurrentCursorPos(x, y);
	printf("Game Start");

	SetCurrentCursorPos(x+term, y);
	printf("  Ranking");

	SetCurrentCursorPos(x, y+1);
	printf("  Option");

	SetCurrentCursorPos(x+term, y+1);
	printf("Information");

	SetCurrentCursorPos(x, y+2);
	printf("  LogOut");

	SetCurrentCursorPos(x+term, y+2);
	printf("   Exit");

}

int PlayMenuSel(int x, int y){

	char temp;

	while(1){
		SetCurrentCursorPos(x, y);
		printf("☞");
		fflush(stdin);
		temp = getch();

		SetCurrentCursorPos(x, y);
		printf("  ");

		switch(temp){

		case MENUUP:
			y--;
			break;

		case MENUDOWN:
			y++;
			break;

		case MENULEFT:
			x-=term;
			break;

		case MENURIGHT:
			x+=term;
			break;

		case MENUENTER:

			// game start
			if(x==PMenuX-3 && y==STARTY+2)
				return 1;

			// ranking
			else if(x==PMenuX-3+term && y==STARTY+2)
				return 2;

			// option
			else if(x==PMenuX-3 && y==STARTY+3)
				return 3;

			// information
			else if(x==PMenuX-3+term && y==STARTY+3)
				return 4;

			// Logout
			else if(x==PMenuX-3 && y==STARTY+4)
				return 5;

			// Exit
			else if(x==PMenuX-3+term && y==STARTY+4)
				Exit();

		}

		if(y>STARTY+4)
			y--;

		else if(y<STARTY+2)
			y++;


		if(x<PMenuX-3)
			x+=term;

		else if(x>PMenuX-3+term)
			x-=term;

		//fflush(stdin);
	}

	fflush(stdin);
}

void LogoutCheckPrint(){


	int x = 35;
	int y = STARTY-3;
	int i;


	SetCurrentCursorPos(x, y);
	// 맨 윗줄
	printf("┌");

	for(i=0;i<10;i++)
		printf("─");

	printf("┐");

	SetCurrentCursorPos(x, ++y);
	printf("│ Are You Sure you   │");

	SetCurrentCursorPos(x, ++y);
	printf("│   want to Log Out? │");

	SetCurrentCursorPos(x, ++y);
	printf("│                    │");

	SetCurrentCursorPos(x, ++y);
	printf("│          /         │");


	SetCurrentCursorPos(x, ++y);
	printf("└");

	for(i=0;i<10;i++)
		printf("─");

	printf("┘");


}

int LogoutCheck() {

	point Yes, No;
	int check=1;
	char temp;


	Yes.y = No.y = STARTY+1;
	Yes.x = 41;
	No.x = 51;

	SetCurrentCursorPos(Yes.x, Yes.y);
	SetColor(9);
	printf("Yes");

	SetCurrentCursorPos(No.x, No.y);
	SetColor(-1);
	printf("No");

	while(1){

		temp = getch();

		switch(temp){

		case MENURIGHT : 
			SetCurrentCursorPos(Yes.x, Yes.y);
			printf("Yes");

			SetCurrentCursorPos(No.x, No.y);
			SetColor(9);
			printf("No");

			SetColor(-1);

			check = 0;

			break;


		case MENULEFT :  
			SetCurrentCursorPos(Yes.x, Yes.y);
			SetColor(9);
			printf("Yes");

			SetCurrentCursorPos(No.x, No.y);
			SetColor(-1);
			printf("No");

			check = 1;
			break;

		case MENUENTER :
			SetColor(-1);
			return check;

		}

	}
}

void Information() {
	int x = PMenuX;
	int y = STARTY;
	char temp;

	SetCurrentCursorPos(x+9, y);
	printf(" * Information * ");



	SetCurrentCursorPos(x, y+2);
	printf("  Offensive");

	SetCurrentCursorPos(x, y+3);
	printf("           ");

	SetCurrentCursorPos(x, y+4);
	printf("+1 Line up");

	SetCurrentCursorPos(x, y+5);
	printf("※ Special block");

	SetCurrentCursorPos(x, y+6);
	printf("§ Earthquake");

	SetCurrentCursorPos(x, y+7);
	printf("↔ Exchange");

	SetCurrentCursorPos(x, y+8);
	printf("☜ Steal");




	SetCurrentCursorPos(x+term, y+2);
	printf("  Defensive");

	SetCurrentCursorPos(x+term, y+3);
	printf("           ");

	SetCurrentCursorPos(x+term, y+4);
	printf("-1 Line down");

	SetCurrentCursorPos(x+term, y+5);
	printf("⑩ 10t block");

	SetCurrentCursorPos(x+term, y+6);
	printf("▣ Shield");


	while(1){
		temp = getch();

		if(temp == MENUESC)
			return;
	}
}

void MakeOption(){

	int x = PMenuX+5;
	int y = STARTY;

	system("cls");
	Logo();

	SetCurrentCursorPos(x+3, y);
	printf(" *    Option    * ");

	SetCurrentCursorPos(x, y+2);

	if(isHoldMode == 1){
		printf("Hold :   ");
		On = GetCurrentCursorPos(); 
		SetColor(9);
		printf("On");
		SetColor(-1);
		printf("   /   ");
		Off = GetCurrentCursorPos();
		printf("OFF");
	}

	else if(isHoldMode == 0){
		printf("Hold :   ");
		On = GetCurrentCursorPos();
		printf("On");
		printf("   /   ");
		Off = GetCurrentCursorPos();
		SetColor(9);
		printf("OFF");
		SetColor(-1);


	}

	SetCurrentCursorPos(x, y+3);

	if(playernum == 1){
		printf("Mode :  ");

		Item = GetCurrentCursorPos();
		printf("Item");
		printf("  /  ");

		Speed = GetCurrentCursorPos();
		printf("Speed");
	}

	else if(playernum == 2){

		if(optionItemMode == 1){
			printf("Mode :  ");
			Item = GetCurrentCursorPos();
			SetColor(9);
			printf("Item");
			SetColor(-1);
			printf("  /  ");
			Speed = GetCurrentCursorPos();
			printf("Speed");
		}

		else if(optionItemMode == 0){

			printf("Mode :   ");
			BGMon = GetCurrentCursorPos();
			SetColor(-1);
			printf("On");
			SetColor(9);
			printf("   /   ");

			BGMoff = GetCurrentCursorPos();
			printf("OFF");

		}
	}

	SetCurrentCursorPos(x-1, y+4);
	printf("Speed :      ");
	speedset = GetCurrentCursorPos();
	SetColor(9);
	printf("%2d", curGameLevel);
	SetColor(-1);

	if(BGMCheck == 1){
		SetCurrentCursorPos(x, y+5);
		printf(" BGM :   ");
		BGMon = GetCurrentCursorPos(); 
		SetColor(9);
		printf("On");
		SetColor(-1);
		printf("   /   ");
		BGMoff = GetCurrentCursorPos();
		printf("OFF");

	}

	else if(BGMCheck == 0){
		SetCurrentCursorPos(x, y+5);
		printf(" BGM :   ");
		BGMon = GetCurrentCursorPos(); 
		SetColor(9);
		printf("On");
		SetColor(-1);
		printf("   /   ");
		BGMoff = GetCurrentCursorPos();
		printf("OFF");

	}


	SetCurrentCursorPos(x+3, y+6);
	KOption = GetCurrentCursorPos();
	printf("Go to KeySettings");

}

void Option(){

	int x = PMenuX;
	int y = STARTY+2;
	char temp;

	MakeOption();

	while(1){
		SetCurrentCursorPos(x, y);
		printf("☞");

		temp = getch();

		SetCurrentCursorPos(x, y);
		printf("  ");

		p = GetCurrentCursorPos();

		switch(temp){

		case MENUDOWN :
			if(p.y !=STARTY+6){
				if(p.y == STARTY+2 && playernum == 1)
					SetCurrentCursorPos(x, y +=2);

				else SetCurrentCursorPos(x, ++y);

			}
			break;

		case MENUUP :
			if(p.y !=STARTY+2){
				if(p.y == STARTY+4 && playernum == 1)
					SetCurrentCursorPos(x, y-=2);

				else SetCurrentCursorPos(x, --y);
			}

			break;

		case MENUENTER :
			if(p.y == STARTY+2){
				if(isHoldMode == 1){

					isHoldMode = 0;
					SetCurrentCursorPos(On.x, On.y);
					SetColor(-1);
					printf("On");

					SetCurrentCursorPos(Off.x, Off.y);
					SetColor(9);
					printf("Off");

					SetColor(-1);
				}

				else if(isHoldMode == 0){

					isHoldMode = 1;
					SetCurrentCursorPos(On.x, On.y);
					SetColor(9);
					printf("On");

					SetCurrentCursorPos(Off.x, Off.y);
					SetColor(-1);
					printf("Off");

				}

			}

			else if(p.y == STARTY+3){
				if(optionItemMode == 1){

					optionItemMode = 0;
					SetCurrentCursorPos(Item.x, Item.y);
					SetColor(-1);
					printf("Item");

					SetCurrentCursorPos(Speed.x, Speed.y);
					SetColor(9);
					printf("Speed");

					SetColor(-1);
				}

				else if(optionItemMode == 0){


					optionItemMode = 1;
					SetCurrentCursorPos(Item.x, Item.y);
					SetColor(9);
					printf("Item");

					SetCurrentCursorPos(Speed.x, Speed.y);
					SetColor(-1);
					printf("Speed");

				}

			}

			else if(p.y == STARTY+4){

				if(optionGameLevel == 10)
					optionGameLevel = 1;

				else
					optionGameLevel++;

				SetCurrentCursorPos(speedset.x, speedset.y);
				SetColor(9);
				printf("%2d", optionGameLevel);
				SetColor(-1);
			}

			else if(p.y == STARTY+5){
				if(BGMCheck == 1){

					BGMCheck = 0;

					SetCurrentCursorPos(BGMon.x, BGMon.y);
					SetColor(-1);
					printf("On");

					SetColor(9);
					SetCurrentCursorPos(BGMoff.x, BGMoff.y);
					printf("OFF");

					SetColor(-1);
				}

				else if(BGMCheck == 0){

					BGMCheck = 1;

					SetCurrentCursorPos(BGMon.x, BGMon.y);
					SetColor(9);
					printf("On");

					SetColor(-1);
					SetCurrentCursorPos(BGMoff.x, BGMoff.y);
					printf("OFF");

				}

			}

			else if(p.y == STARTY+6){
				KeyOption();
				MakeOption();
			}
			break;

		case MENUESC:
			return;
		}

	}

}


void KeyOption(){

	int x = PMenuX;
	int y = STARTY+2;

	int index;
	char temp;

	MakeKeyOption();

	if(playernum == 1){

		while(1){
			SetCurrentCursorPos(x, y);
			printf("☞");

			temp = getch();

			SetCurrentCursorPos(x, y);
			printf("  ");

			switch(temp){
			case MENUUP:
				if(y != STARTY +2)
					y--;
				break;

			case MENUDOWN:
				if(y != STARTY+7)
					y++;
				break;

			case MENUENTER:
				index = 0;

				switch(y){
				case (STARTY+2):
					SetKey(holdPos[index], &HOLD[index]);
					break;

				case (STARTY+3) :
					SetKey(clearPos[index], &SPACE[index]);
					break;

				case (STARTY+4) :
					SetKey(upPos[index], &UP[index]);
					break;

				case (STARTY+5) :
					SetKey(downPos[index], &DOWN[index]);
					break;

				case (STARTY+6) :
					SetKey(leftPos[index], &LEFT[index]);
					break;

				case (STARTY+7) :
					SetKey(rightPos[index], &RIGHT[index]);
					break;
				}

				break;

			case MENUESC :
				return;
			}
		}
	}

	else if(playernum == 2){
		int xxxxx = PMenuX;

		x -= 5;
		y++;

		while(1){

			SetCurrentCursorPos(x, y);
			printf("☞");

			temp = getch();

			SetCurrentCursorPos(x, y);
			printf("  ");

			switch(temp){
			case MENUUP:
				if(y != STARTY +3)
					y--;
				break;

			case MENUDOWN:
				if(y != STARTY+11)
					y++;
				break;

			case MENULEFT:
				if(x != PMenuX-2)
					x -= term;
				break;

			case MENURIGHT:
				if(x != PMenuX+term-2)
					x += term;
				break;

			case MENUENTER:
				// 좌표설정
				if(x == PMenuX-5){


					index = 1;

					switch(y){
					case (STARTY+3):
						SetKey(holdPos[index], &HOLD[index]);
						break;

					case (STARTY+4) :
						SetKey(clearPos[index], &SPACE[index]);
						break;

					case (STARTY+5) :
						SetKey(itemYouPos[index], &ITEMUSEYOU[index]);
						break;

					case (STARTY+6) :
						SetKey(itemMePos[index], &ITEMUSEME[index]);
						break;

					case (STARTY+7) :
						SetKey(itemThrowPos[index], &ITEMREMOVE[index]);
						break;

					case (STARTY+8) :
						SetKey(upPos[index], &UP[index]);
						break;

					case (STARTY+9) :
						SetKey(downPos[index], &DOWN[index]);
						break;

					case (STARTY+10) :
						SetKey(leftPos[index], &LEFT[index]);
						break;

					case (STARTY+11) :
						SetKey(rightPos[index], &RIGHT[index]);
						break;
					}
				}

				else if(x == PMenuX - 5 +term){
					index = 2;


					switch(y){
					case (STARTY+3):
						SetKey(holdPos[index], &HOLD[index]);
						break;

					case (STARTY+4) :
						SetKey(clearPos[index], &SPACE[index]);
						break;

					case (STARTY+5) :
						SetKey(itemYouPos[index], &ITEMUSEYOU[index]);
						break;

					case (STARTY+6) :
						SetKey(itemMePos[index], &ITEMUSEME[index]);
						break;

					case (STARTY+7) :
						SetKey(itemThrowPos[index], &ITEMREMOVE[index]);
						break;

					case (STARTY+8) :
						SetKey(upPos[index], &UP[index]);
						break;

					case (STARTY+9) :
						SetKey(downPos[index], &DOWN[index]);
						break;

					case (STARTY+10) :
						SetKey(leftPos[index], &LEFT[index]);
						break;

					case (STARTY+11) :
						SetKey(rightPos[index], &RIGHT[index]);
						break;
					}

					break;

			case MENUESC :
				return;
				}
			}
		}
	}

}
void SetKey(point Pos, int *key){

	char temp, temp2;

	SetCurrentCursorPos(Pos.x, Pos.y);

	temp = getch();

	if(temp == MENUENTER || temp == 0)
		return;

	else if(temp == -32){
		temp2 = getch();

		switch(temp2){

		case MENULEFT:
		case MENURIGHT:
		case MENUUP:
		case MENUDOWN:
		case 82: // Insert
		case 71: // Home
		case 73: // PageUp
		case 83: // Delete
		case 79: // End
		case 81: // PageDown
			*key = temp2;
			PrintKey(Pos, *key);
		default : return;

		}
	}

	else if(temp >= 65 && temp <= 90){
		return;
	}

	else if(isprint(temp)){

		*key = temp;
		PrintKey(Pos, *key);
	}

}
void PrintKey(point Pos, int key){

	int temp = key;


	SetCurrentCursorPos(Pos.x, Pos.y);
	printf("        ");

	SetCurrentCursorPos(Pos.x, Pos.y);

	if( key>= 65 && key<= 90 ){

		if(temp == MENULEFT) printf("←");
		else if(temp == MENURIGHT) printf("→");
		else if(temp == MENUUP) printf("↑");
		else if(temp == MENUDOWN) printf("↓");
		else if(temp == 82) printf("Insert");
		else if(temp == 71) printf("Home");
		else if(temp == 73) printf("PageUp");
		else if(temp == 83) printf("Delete");
		else if(temp == 79) printf("End");
		else if(temp == 81) printf("PageDown");

	}

	else if(temp == MENUBSPACE) printf("Bspace");
	else if(temp == MENUENTER) printf("Enter");
	else if(temp == MENUSPACE) printf("Spacebar");
	else printf("%c", temp);

}

void MakeKeyOption(){

	int y = STARTY;
	int index = 0;

	system("cls");
	Logo();

	SetCurrentCursorPos(PMenuX+5, y);
	printf(" *    Key Setting    * ");


	if(playernum == 1){
		int x = PMenuX+5;


		SetCurrentCursorPos(x, y+2);
		printf(" Hold :     ");
		holdPos[index] = GetCurrentCursorPos();
		PrintKey(holdPos[index], HOLD[index]);

		SetCurrentCursorPos(x, y+3);
		printf(" Drop :     ");
		clearPos[index] = GetCurrentCursorPos();
		PrintKey(clearPos[index], SPACE[index]);


		SetCurrentCursorPos(x, y+4);
		printf("   UP :     ");
		upPos[index] = GetCurrentCursorPos();
		PrintKey(upPos[index], UP[index]);

		SetCurrentCursorPos(x, y+5);
		printf(" Down :     ");
		downPos[index] = GetCurrentCursorPos();
		PrintKey(downPos[index], DOWN[index]);

		SetCurrentCursorPos(x, y+6);
		printf(" Left :     ");
		leftPos[index] = GetCurrentCursorPos();
		PrintKey(leftPos[index], LEFT[index]);

		SetCurrentCursorPos(x, y+7);
		printf("Right :     ");
		rightPos[index] = GetCurrentCursorPos();
		PrintKey(rightPos[index], RIGHT[index]);

	}

	else if(playernum == 2){

		int x = PMenuX+1;
		int index;

		SetCurrentCursorPos(x+3, y+2);
		printf("1P");

		SetCurrentCursorPos(x+3+term, y+2);
		printf("2P");

		for(index = 1; index <=2; index++){

			SetCurrentCursorPos(x, y+3);
			printf(" Hold : ");
			holdPos[index] = GetCurrentCursorPos();
			PrintKey(holdPos[index], HOLD[index]);

			SetCurrentCursorPos(x, y+4);
			printf(" Drop : ");
			clearPos[index] = GetCurrentCursorPos();
			PrintKey(clearPos[index], SPACE[index]);

			SetCurrentCursorPos(x-4, y+5);
			printf("ItemToYou : ");
			itemYouPos[index] = GetCurrentCursorPos();
			PrintKey(itemYouPos[index], ITEMUSEYOU[index]);

			SetCurrentCursorPos(x-3, y+6);
			printf("ItemToMe : ");
			itemMePos[index] = GetCurrentCursorPos();
			PrintKey(itemMePos[index], ITEMUSEME[index]);

			SetCurrentCursorPos(x-4, y+7);
			printf("ItemThrow : ");
			itemThrowPos[index] = GetCurrentCursorPos();
			PrintKey(itemThrowPos[index], ITEMREMOVE[index]);

			SetCurrentCursorPos(x, y+8);
			printf("   Up : ");
			upPos[index] = GetCurrentCursorPos();
			PrintKey(upPos[index], UP[index]);

			SetCurrentCursorPos(x, y+9);
			printf(" Down : ");
			downPos[index] = GetCurrentCursorPos();
			PrintKey(downPos[index], DOWN[index]);

			SetCurrentCursorPos(x, y+10);
			printf(" Left : ");
			leftPos[index] = GetCurrentCursorPos();
			PrintKey(leftPos[index], LEFT[index]);

			SetCurrentCursorPos(x, y+11);
			printf("Right : ");
			rightPos[index] = GetCurrentCursorPos();
			PrintKey(rightPos[index], RIGHT[index]);

			x += (term+1);

		}
	}
}