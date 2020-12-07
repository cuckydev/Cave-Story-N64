#ifndef BACK_H
#define BACK_H

#include <ultra64.h>
#include "game_def.h"

//Back structures
typedef struct
{
	u8 *tex;
	s32 width, height;
	u16 *tlut;
} BACK_TEX;

typedef struct
{
	BACK_TEX tex;
	s32 type;
	s32 fx;
} BACK;

extern BACK gBack;
extern s32 gWaterY;

//Back functions
BOOL InitBack(const BACK_TEX *tex, s32 type);
void ActBack();
void PutBack(s32 fx, s32 fy);
void PutFront(s32 fx, s32 fy);

#endif
