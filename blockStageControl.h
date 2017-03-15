#ifndef BLOCKSTAGECONTROL_H
#define BLOCKSTAGECONTROL_H

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

extern int isItemMode;
extern int isHoldMode;
extern int gameBoardInfo[3][GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];
extern int curPosX[3], curPosY[3];
extern char itemBucket[3][11];
extern int specialBlock[3];
extern int currentBlockModel[3];
extern int useHold[3];
extern int holdBlockModel[3];
extern int rotateSte[3];
extern const int START_CURPOS_X_1P;
extern const int START_CURPOS_Y_1P;
extern const int START_CURPOS_X_2P_1;
extern const int START_CURPOS_Y_2P_1;
extern const int START_CURPOS_X_2P_2;
extern const int START_CURPOS_Y_2P_2;
extern const int GBOARD_ORIGIN_X_1P;
extern const int GBOARD_ORIGIN_Y_1P;
extern const int GBOARD_ORIGIN_X_2P_1;
extern const int GBOARD_ORIGIN_Y_2P_1;
extern const int GBOARD_ORIGIN_X_2P_2;
extern const int GBOARD_ORIGIN_Y_2P_2;

void InitRandomBlock(void);
void InitNewBlockPos(int x, int y, int player);
void ChooseBlock(int player);
int GetCurrentBlockIdx(int player);
void ShowBlock(char blockInfo[][4]);
void DeleteBlock(char blockInfo[][4]);
int BlockDown(int player);
void ShiftLeft(int player);
void ShiftRight(int player);
void RotateBlock(int player);
int BlockHold(int player);
int DetectCollision(int posX, int posY, char blockModel[][4], int player);
void DrawGameBoard(int playerNum);
void DrawShieldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y);
void DrawHoldBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y);
void DrawNextBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y);
void DrawGameWall(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y);
void AddCurrentBlockInfoToBoard(char blockInfo[][4], int player);
int IsGameOver(int player);
void ShowLoser(int loser);
void DrawItemBucket(int player);
void DrawSolidBlocks(int player);
void AddLine(int player, int lineNum);
void SubLine(int player, int lineNum);
void RemoveFillUpLine(int player);
void InitGameBoardInfo();
void InitItemBucket(void);
void SolidCurrentBlock(int player);
void DrawItemBlock(int GBOARD_ORIGIN_X, int GBOARD_ORIGIN_Y);
void ShowID(int player);

#endif