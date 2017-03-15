#ifndef SIGNUP_H
#define SIGNUP_H

char ID[30];
char EMAIL[30];
char PASS[30];

//회원가입
void Init();     // 초기화
void AddNode();     // 회원 가입
void LoadFile();  // txt파일을 읽어 데이터 작성 
void etcSel(char* temp, int* x, int* y);

#endif