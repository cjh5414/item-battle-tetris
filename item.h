#ifndef ITEM_H
#define ITEM_H

char* GetItemShape(char item);
void ItemInfo(int player, char item);
void MakeItem(int player, int itemInfo);
void ChoiceBlock(int player, int itemInfo);
void Item10t(int player);
void ItemSpecial(int player);
void ItemTwist(int player);
void ItemSteal(int user, int dest);
void ItemShield(int player, int num);
int IsShield(int player);
void ItemChangeMap(int user, int dest);
void ItemUse(int player, int useMode);
void ItemFly(int player, char *itemShape);

#endif

/* item infomation

+1      :  A   대상의 맨 아래 블록 한줄을 생성한다.
※      :  B   대상의 다음 블록 4개가 특수블록으로 나온다.
§      :  C   맵에 있는 블록들을 불규칙하게 변경한다.
↔      :  D   대상의 맵과 자신의 맵을 맞바꾼다.
☜      :  E   대상의 아이템을 가져온다.


-1      :  Z   대상의 맨 아래 블록 한 줄을 제거한다.
⑩      :  Y   10톤 블록 하나 생성한다.
▣      :  X    상대방이 자신에게 사용하는 아이템을 무력화시킨다.

*/