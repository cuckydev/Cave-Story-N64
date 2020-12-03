#ifndef GAME_H
#define GAME_H

#include <ultra64.h>

//Mode enumeration
typedef enum
{
	GameMode_Null,
	//Standard modes
	GameMode_Opening,
	GameMode_Title,
	GameMode_Action,
	//Sub-modes
	GameMode_Camp,
	GameMode_MiniMap,
	GameMode_StageSelect,
	//Number
	GameMode_Num,
} GameMode;

//Game globals
extern s32 g_GameFlags;

//Game functions
s32 Random(s32 min, s32 max);
void InitGame();
void Game();

#endif
