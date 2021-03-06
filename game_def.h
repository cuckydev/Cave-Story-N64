#ifndef GAME_DEF_H
#define GAME_DEF_H

#include <ultra64.h>

typedef struct RECT
{
	s32 left, top, right, bottom;
} RECT;

typedef struct RECT2
{
	s32 front, top, back, bottom;
} RECT2;

#define BOOL s32
#define TRUE 1
#define FALSE 0

#ifdef NEWGCC
	#define ALIGNED8  __attribute__((aligned(8)))
	#define ALIGNED16 __attribute__((aligned(16)))
#else
	#define ALIGNED8
	#define ALIGNED16
#endif

#endif
