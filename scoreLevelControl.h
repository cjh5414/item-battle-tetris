#ifndef SCORELEVELCONTROL_H
#define SCORELEVELCONTROL_H

extern int curGameLevel;

void ShowCurrentScoreAndLevel(int mode);
void ShowCurrentCombo(int player);
void GameLevelUp(void);
void AddGameScore(int score);
void GameComboChange(int num,int player);
int getGameCombo(int player);
int getGameLevel(void);
int getGameScore(void);
void InitGameState(void);

#endif