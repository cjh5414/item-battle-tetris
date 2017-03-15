#ifndef KEYCURCONTROL_H
#define KEYCURCONTROL_H

#include "point.h"

extern int LEFT[3];
extern int RIGHT[3];

void CursorSetting(int set);
point GetCurrentCursorPos(void);
void SetCurrentCursorPos(int x, int y);
int ProcessKeyInput(int playerNum);
void InitKeyDelayRate(int rate);
void InitKeyDelayRate(int rate);
void KeyDelaySpeedCtl(int addSpeed);

#endif