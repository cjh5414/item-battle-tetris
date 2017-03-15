/*Name : color.c 
* Content : �� ���� ����
* Implementation : CJH, SYB
* Last modified 20014/12/01
*/

#include <Windows.h>
#include "color.h"

void SetColor(int blockIdx) {
   switch(blockIdx) {
   case 1: //�Ķ�
      SetConsoleTextAttribute(col, 137);
      break;
   case 2: //��Ȳ
      SetConsoleTextAttribute(col, 132);
      break;
   case 3: //����
      SetConsoleTextAttribute(col, 133);
      break;
   case 4: //�ϴ�
      SetConsoleTextAttribute(col, 139);
      break;
   case 5: //���
      SetConsoleTextAttribute(col, 142);
      break;
   case 6: //�ʷ�
      SetConsoleTextAttribute(col, 138);
      break;
   case 7: //����
      SetConsoleTextAttribute(col, 140);
      break;
   case 8: //��ȫ
      SetConsoleTextAttribute(col, 141);
      break;
   case 9: //ȸ��
      SetConsoleTextAttribute(col, 135);
      break;
   case 10: //�������� ����ؽ�Ʈ 10t
      SetConsoleTextAttribute(col, 15);
      break;
   case 11: //������
      SetConsoleTextAttribute(col, 128);
      break;
   case 12: //����
      SetConsoleTextAttribute(col, 129);
      break;
   case 13: //���ϴ�
      SetConsoleTextAttribute(col, 131);
      break;
   case 14: //���ʷ�
      SetConsoleTextAttribute(col, 130);
      break;
   case 'Z': //������ ������
   case 'Y':
   case 'X':
   case 'W':
   case 'V':
   case 'U':
   case 'T':
   case 'S':
      SetConsoleTextAttribute(col, 31);
      break;
   case 'A': //������ ������
   case 'B':
   case 'C':
   case 'D':
   case 'E':
   case 'F':
   case 'G':
   case 'H':
      SetConsoleTextAttribute(col, 223);
      break;
   default:   // - ���̸� ���������� ����
      SetConsoleTextAttribute(col, 128);
      break;
   }
}