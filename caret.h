#ifndef CARET_H
#define CARET_H

#include <ultra64.h>
#include "game.h"

//Caret structure
#define CARET_MAX 0x40

typedef struct
{
	s32 cond;
	s32 code;
	s32 direct;
	s32 x;
	s32 y;
	s32 xm;
	s32 ym;
	s32 act_no;
	s32 act_wait;
	s32 ani_no;
	s32 ani_wait;
	s32 view_left;
	s32 view_top;
	u8 *tex;
	s32 tex_w, tex_h;
	u16 *tlut;
	RECT rect;
} CARET;

extern CARET gCrt[CARET_MAX];

//Caret functions
void InitCaret();
void ActCaret();
void PutCaret(s32 fx, s32 fy);
void SetCaret(s32 x, s32 y, s32 code, s32 dir);

#endif
