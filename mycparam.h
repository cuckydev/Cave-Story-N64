#ifndef MYCPARAM_H
#define MYCPARAM_H

#include <ultra64.h>
#include "game_def.h"

typedef struct
{
	int exp[3];
} ARMS_LEVEL;

extern const ARMS_LEVEL gArmsLevelTable[14];

//Arms functions
void AddExpMyChar(s32 x);
void ZeroExpMyChar();
BOOL IsMaxExpMyChar();
void ZeroArmsEnergy_All();
void AddBulletMyChar(s32 no, s32 val);
void PutArmsEnergy(BOOL flash);
void PutActiveArmsList();

//Life functions
void AddLifeMyChar(s32 x);
void AddMaxLifeMyChar(s32 val);
void DamageMyChar(s32 damage);
void PutMyLife(BOOL flash);

#endif
