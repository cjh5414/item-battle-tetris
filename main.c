#include <stdio.h>

#include "startMenu.h"
#include "Login.h"
#include "playMenu.h"
#include "signup.h"
#include "scoreSave.h"
#include "scoreSave2.h"
#include "Windows.h"
#include "basicHeader.h"
#include "keyCurControl.h"

extern int playernum;
extern char RESULT_ID[30];
int LoginCheckNum;
int ranknum;

int main () {
	int n;
	int PM;
	char Sys[50];
	system("color 80");
	sprintf(Sys, "MODE CON:COLS=96 LINES=40");
	system(Sys);

	ReadRankFile();
	ReadTwoRankFile();
	// MENUESC������ ���� �ݺ���
	while(1) {
		system("cls");
		PlaySound(TEXT("bgm-��Ʈ����.wav"),
			NULL, SND_FILENAME| SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		LoginCheckNum = FAIL;
		// start menu
		n = menu();
		switch(n) {
		case 1:
			// MENUESC������ ���� �ݺ���
			while(1) {
				// play �ο� ����
				player_num();
				if(playernum != 0) {
					system("cls");
					Logo();

					// �α��� ȭ��
					Login(playernum);

					// play menu
					if(LoginCheckNum == SUCCESS) {
						PM = Play_menu();
						// Logout

						if(PM == 5){
							playernum = 0;
							break;
						}
					}
				}
				else if(playernum == 0)
					break;
			}
			break;


		case 2:
			//ranking
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

		case 3:
			//ȸ������
			CursorSetting(1);
			system("cls");
			Init();     // �ʱ�ȭ
			LoadFile();
			AddNode();     // ȸ�� ����
			LoadFile();  // txt������ �о� ������ �ۼ� 
			break;

		case 4:
			Exit();
			break;
		}
	}
}