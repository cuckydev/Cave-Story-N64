#ifndef FRAME_H
#define FRAME_H

#include <ultra64.h>

//Frame structure
typedef struct
{
	s32 x;
	s32 y;
	s32 *tgt_x;
	s32 *tgt_y;
	s32 wait;
	s32 quake;
	s32 quake2;
} FRAME;

extern FRAME gFrame;

//Frame functions
void MoveFrame3();
void GetFramePosition(s32 *fx, s32 *fy);
void SetFramePosition(s32 fx, s32 fy);
void SetFrameMyChar();
void SetFrameTargetMyChar(s32 wait);
void SetFrameTargetNpChar(s32 event, s32 wait);
void SetFrameTargetBoss(s32 no, s32 wait);
void SetQuake(s32 time);
void SetQuake2(s32 time);
void ResetQuake();

#endif
