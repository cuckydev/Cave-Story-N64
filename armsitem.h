#ifndef ARMSITEM_H
#define ARMSITEM_H

#include <ultra64.h>
#include "game_def.h"

//Arms item structures
typedef struct
{
	s32 code;
	s32 level;
	s32 exp;
	s32 max_num;
	s32 num;
} ARMS;

typedef struct
{
	s32 code;
} ITEM;

//Arms item globals
#define ARMS_MAX 8
#define ITEM_MAX 0x20

extern ARMS gArmsData[ARMS_MAX];
extern ITEM gItemData[ITEM_MAX];

extern s32 gSelectedArms;
extern s32 gSelectedItem;

extern s32 gArmsEnergyX;

//Arms functions
void ClearArmsData();
void ClearItemData();
BOOL AddArmsData(s32 code, s32 max_num);
BOOL SubArmsData(s32 code);
BOOL TradeArms(s32 code1, s32 code2, s32 max_num);
BOOL CheckArms(s32 a);
BOOL UseArmsEnergy(s32 num);
BOOL ChargeArmsEnergy(s32 num);
void FullArmsEnergy();
s32 RotationArms();
s32 RotationArmsRev();
void ChangeToFirstArms();

//Item functions
BOOL AddItemData(s32 code);
BOOL SubItemData(s32 code);
BOOL CheckItem(s32 a);

#endif
