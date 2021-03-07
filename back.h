#ifndef BACK_H
#define BACK_H

#include <ultra64.h>
#include "game_def.h"

//Back structures
typedef void (*BACK_DRAW)(s32, s32);

typedef struct
{
	BACK_DRAW draw;
	s32 type;
	s32 fx;
} BACK;

extern BACK gBack;
extern s32 gWaterY;

//Back functions
BOOL InitBack(BACK_DRAW draw, s32 type);
void ActBack();
void PutBack(s32 fx, s32 fy);
void PutFront(s32 fx, s32 fy);

#endif
