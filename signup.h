#ifndef SIGNUP_H
#define SIGNUP_H

char ID[30];
char EMAIL[30];
char PASS[30];

//ȸ������
void Init();     // �ʱ�ȭ
void AddNode();     // ȸ�� ����
void LoadFile();  // txt������ �о� ������ �ۼ� 
void etcSel(char* temp, int* x, int* y);

#endif