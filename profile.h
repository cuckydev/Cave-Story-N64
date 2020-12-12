#ifndef PROFILE_H
#define PROFILE_H

#include "game_def.h"
#include "armsitem.h"
#include "selstage.h"
#include "flags.h"

extern BOOL gGoodEEPROM;

//Profile data structure
typedef struct
{
	char code[8];
	u8 stage;
	u8 music;
	s32 x;
	s32 y;
	u8 direct;
	u8 max_life;
	u8 star;
	u8 life;
	u8 select_arms;
	u8 equip;
	ARMS arms[ARMS_MAX];
	ITEM items[ITEM_MAX];
	PERMIT_STAGE permitstage[PERMIT_STAGE_MAX];
	u8 flags[NPC_FLAG_BYTES];
	u8 pad[3];
} PROFILE_DATA;

//Profile functions
void LoadFromProfile(const PROFILE_DATA *profile_data);
void InitProfile();
BOOL SaveProfile();
BOOL LoadProfile();
BOOL HasProfile();
BOOL InitializeGame();

#endif
