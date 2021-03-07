#ifndef STAGE_H
#define STAGE_H

#include <ultra64.h>
#include "npchar.h"
#include "map.h"

//Stage globals
extern s32 gStageNo;

//Stage functions
void TransferStage(s32 no, s32 w, s32 x, s32 y);
void PutStage_Front(s32 fx, s32 fy);
void PutStage_Back(s32 fx, s32 fy);

#endif
