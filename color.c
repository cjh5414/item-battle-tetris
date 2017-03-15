/*Name : color.c 
* Content : 색 관련 정의
* Implementation : CJH, SYB
* Last modified 20014/12/01
*/

#include <Windows.h>
#include "color.h"

void SetColor(int blockIdx) {
   switch(blockIdx) {
   case 1: //파랑
      SetConsoleTextAttribute(col, 137);
      break;
   case 2: //주황
      SetConsoleTextAttribute(col, 132);
      break;
   case 3: //보라
      SetConsoleTextAttribute(col, 133);
      break;
   case 4: //하늘
      SetConsoleTextAttribute(col, 139);
      break;
   case 5: //노랑
      SetConsoleTextAttribute(col, 142);
      break;
   case 6: //초록
      SetConsoleTextAttribute(col, 138);
      break;
   case 7: //빨강
      SetConsoleTextAttribute(col, 140);
      break;
   case 8: //분홍
      SetConsoleTextAttribute(col, 141);
      break;
   case 9: //회색
      SetConsoleTextAttribute(col, 135);
      break;
   case 10: //검은바탕 흰색텍스트 10t
      SetConsoleTextAttribute(col, 15);
      break;
   case 11: //검은색
      SetConsoleTextAttribute(col, 128);
      break;
   case 12: //남색
      SetConsoleTextAttribute(col, 129);
      break;
   case 13: //하하늘
      SetConsoleTextAttribute(col, 131);
      break;
   case 14: //초초록
      SetConsoleTextAttribute(col, 130);
      break;
   case 'Z': //수비형 아이템
   case 'Y':
   case 'X':
   case 'W':
   case 'V':
   case 'U':
   case 'T':
   case 'S':
      SetConsoleTextAttribute(col, 31);
      break;
   case 'A': //공격형 아이템
   case 'B':
   case 'C':
   case 'D':
   case 'E':
   case 'F':
   case 'G':
   case 'H':
      SetConsoleTextAttribute(col, 223);
      break;
   default:   // - 값이면 검은색으로 설정
      SetConsoleTextAttribute(col, 128);
      break;
   }
}