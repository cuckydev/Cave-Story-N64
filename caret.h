#ifndef CARET_H
#define CARET_H

#include <ultra64.h>
#include "game.h"

//Caret enum
enum
{
	CARET_NULL = 0,
	CARET_BUBBLE = 1,
	CARET_PROJECTILE_DISSIPATION = 2,
	CARET_SHOOT = 3,
	CARET_SNAKE_AFTERIMAGE = 4,
	CARET_ZZZ = 5,
	CARET_SNAKE_AFTERIMAGE_DUPLICATE = 6,
	CARET_EXHAUST = 7,
	CARET_DROWNED_QUOTE = 8,
	CARET_QUESTION_MARK = 9,
	CARET_LEVEL_UP = 10,
	CARET_HURT_PARTICLES = 11,
	CARET_EXPLOSION = 12,
	CARET_TINY_PARTICLES = 13,
	CARET_UNKNOWN = 14,
	CARET_PROJECTILE_DISSIPATION_TINY = 15,
	CARET_EMPTY = 16,
	CARET_PUSH_JUMP_KEY = 17
};

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
