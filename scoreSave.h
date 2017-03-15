#ifndef SCORESAVE_H
#define SCORESAVE_H

typedef struct RankNode {
	int rank;
	int score;
	char ID[30];
	int HoldFlag;
	struct RankNode* Next;
}Node;

void ReadRankFile();
void SaveRankFile();
Node* Create_RankNode(int rank, int score, char* ID, int HoldFlag);
void AppendNode(Node** Head, Node* NewNode);
void DisplayRank();
int RankSearch(char* ID);
Node *SearchID(char *ID);
void SortGameResult(int GameScore, char *ID_1p, int isHoldMode);

extern Node* Head;

#endif