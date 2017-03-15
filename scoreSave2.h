#ifndef SCORESAVE2_H
#define SCORESAVE2_H

typedef struct RankNodeTwo {
	int rank;
	int record;
	int win;
	int lose;
	double rate;
	char ID[30];
	struct RankNodeTwo* Next;
}NodeTwo;

void ReadTwoRankFile();
void SaveTwoRankFile();
NodeTwo* Create_RankNodeTwo(int rank, int record, char* ID, int win, int lose, double rate);
void AppendNodeTwo(NodeTwo** Head, NodeTwo* NewNode);
void DisplayTwoRank();
NodeTwo* SearchNode(char* ID);
void SortGameResultTwo(char *winner, char *loser);
int RankSearchTwo(char* ID);

extern NodeTwo* HeadTwo;

#endif