#ifndef LOGIN_H
#define LOGIN_H

#define menuX_1p 36
#define menuX_2p 25

extern int playernum;
extern int LoginCheckNum;
extern char ID_1p[30];
extern char ID_2p[30];

void Reset_pw();
void Find_id(); // 아이디 찾는 함수
void Login(int plyernum);
void LoginMenu_1p();
void LoginMenu_2p();
void LoginMenuSel_1p();
void LoginMenuSel_2p();
int LoginCheck(char ID_input[], char PW_input[]);

void etcSel(char* temp, int* x, int* y);

#endif