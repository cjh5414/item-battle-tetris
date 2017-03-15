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

+1      :  A   ����� �� �Ʒ� ��� ������ �����Ѵ�.
��      :  B   ����� ���� ��� 4���� Ư��������� ���´�.
��      :  C   �ʿ� �ִ� ��ϵ��� �ұ�Ģ�ϰ� �����Ѵ�.
��      :  D   ����� �ʰ� �ڽ��� ���� �¹ٲ۴�.
��      :  E   ����� �������� �����´�.


-1      :  Z   ����� �� �Ʒ� ��� �� ���� �����Ѵ�.
��      :  Y   10�� ��� �ϳ� �����Ѵ�.
��      :  X    ������ �ڽſ��� ����ϴ� �������� ����ȭ��Ų��.

*/