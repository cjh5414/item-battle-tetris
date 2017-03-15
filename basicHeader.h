#ifndef BASICHEADER_H
#define BASICHEADER_H

#pragma comment(lib,"winmm.lib") 

#define MENULEFT 75
#define MENURIGHT 77
#define MENUUP 72
#define MENUDOWN 80
#define MENUENTER 13
#define MENUESC 27
#define MENUBSPACE 8
#define MENUSPACE 32

#define LOGOX 22
#define LOGOY 9
#define STARTY 17

#define SUCCESS 1
#define FAIL 0

void Logo();
void Exit();

extern int playernum;
extern int LoginCheckNum;
extern int ranknum;
extern char ID_1p[30];
extern char ID_2p[30];

#endif