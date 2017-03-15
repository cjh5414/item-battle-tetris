#ifndef PM_H
#define PM_H

#define term 20
#define PMenuX 30

#include "point.h"

typedef struct rankInf {
   char IDCheck[30];
   int rank_1p;
   int best_score;
   int Hold;
   int rank_2p;
   int record;
   int win;
   int lose;
   double rate;
} rankInf;

// extern
extern int playernum;
extern int LoginCheckNum;
extern char ID_1p[30];
extern char ID_2p[30];
int BGMCheck;

extern int curGameLevel; // 게임 시작스피드
extern int isHoldMode; //1이 쓰는거 0이 안쓰느거
extern int isItemMode;

// option메뉴 위치 저장
point p;
point On;
point Off;
point Item;
point Speed;
point speedset;
point KOption;
point BGMon;
point BGMoff;

// keyset menu 위치 저장
point upPos[3];
point downPos[3];
point leftPos[3];
point rightPos[3];
point holdPos[3];
point clearPos[3];
point itemMePos[3];
point itemYouPos[3];
point itemThrowPos[3];

int Play_menu();
void make_line();
void take_rank(char ID[], int num);
void makeMenu();
int PlayMenuSel(int x, int y);
int LogoutCheck();
void LogoutCheckPrint();
void Information();
void MakeOption();
void Option();
void KeyOption();
void MakeKeyOption();
void PrintKey(point Pos, int key);
void SetKey(point Pos, int *key);


extern int optionItemMode;
extern int optionGameLevel;


#endif