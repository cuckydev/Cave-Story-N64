#ifndef PROFILE_H
#define PROFILE_H

#include "game_def.h"

extern BOOL gGoodEEPROM;

//Profile functions
void InitProfile();
BOOL SaveProfile();
BOOL LoadProfile();
BOOL HasProfile();
BOOL InitializeGame();

#endif
