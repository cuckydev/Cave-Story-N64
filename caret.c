#include "caret.h"
#include "carets.h"
#include <string.h>

//Carets structure
CARET gCrt[CARET_MAX];

//Caret table
static const struct
{
	s32 view_left;
	s32 view_top;
} gCaretTable[18] = {
	{0, 0},                   // CARET_NULL
	{ 4 * 0x200,  4 * 0x200}, // CARET_BUBBLE
	{ 8 * 0x200,  8 * 0x200}, // CARET_PROJECTILE_DISSIPATION
	{ 8 * 0x200,  8 * 0x200}, // CARET_SHOOT
	{ 8 * 0x200,  8 * 0x200}, // CARET_SNAKE_AFTERIMAGE
	{ 4 * 0x200,  4 * 0x200}, // CARET_ZZZ
	{ 8 * 0x200,  8 * 0x200}, // CARET_SNAKE_AFTERIMAGE_DUPLICATE
	{ 4 * 0x200,  4 * 0x200}, // CARET_EXHAUST
	{ 8 * 0x200,  8 * 0x200}, // CARET_DROWNED_QUOTE
	{ 8 * 0x200,  8 * 0x200}, // CARET_QUESTION_MARK
	{28 * 0x200,  8 * 0x200}, // CARET_LEVEL_UP
	{ 4 * 0x200,  4 * 0x200}, // CARET_HURT_PARTICLES
	{16 * 0x200, 16 * 0x200}, // CARET_EXPLOSION
	{ 4 * 0x200,  4 * 0x200}, // CARET_TINY_PARTICLES
	{20 * 0x200, 20 * 0x200}, // CARET_UNKNOWN
	{ 4 * 0x200,  4 * 0x200}, // CARET_PROJECTILE_DISSIPATION_TINY
	{20 * 0x200,  4 * 0x200}, // CARET_EMPTY
	{52 * 0x200,  4 * 0x200}  // CARET_PUSH_JUMP_KEY
};

//Caret functions
static const struct
{
	void (*act)(CARET*);
	void (*put)(CARET*, s32, s32);
} gpCaretFuncTbl[18] = {
	{ActCaret00, PutCaret00},
	{ActCaret01, PutCaret01},
	{ActCaret02, PutCaret02},
	{ActCaret03, PutCaret03},
	{ActCaret04, PutCaret04},
	{ActCaret05, PutCaret05},
	{ActCaret04, PutCaret04}, //Caret 04 instead of 06 (which doesn't exist)
	{ActCaret07, PutCaret07},
	{ActCaret08, PutCaret08},
	{ActCaret09, PutCaret09},
	{ActCaret10, PutCaret10},
	{ActCaret11, PutCaret11},
	{ActCaret12, PutCaret12},
	{ActCaret13, PutCaret13},
	{ActCaret14, PutCaret14},
	{ActCaret15, PutCaret15},
	{ActCaret16, PutCaret16},
	{ActCaret17, PutCaret17},
};

//Caret functions
void InitCaret()
{
	memset(gCrt, 0, sizeof(gCrt));
}

void ActCaret()
{
	for (s32 i = 0; i < CARET_MAX; i++)
		if (gCrt[i].cond & 0x80)
			gpCaretFuncTbl[gCrt[i].code].act(&gCrt[i]);
}

void PutCaret(s32 fx, s32 fy)
{
	for (s32 i = 0; i < CARET_MAX; i++)
		if (gCrt[i].cond & 0x80)
			gpCaretFuncTbl[gCrt[i].code].put(&gCrt[i], fx, fy);
}

void SetCaret(s32 x, s32 y, s32 code, s32 dir)
{
	s32 c;
	for (c = 0; c < CARET_MAX; c++)
		if (gCrt[c].cond == 0)
			break;
	
	if (c == CARET_MAX)
		return;
	
	memset(&gCrt[c], 0, sizeof(CARET));
	gCrt[c].cond = 0x80;
	gCrt[c].code = code;
	gCrt[c].x = x;
	gCrt[c].y = y;
	gCrt[c].view_left = gCaretTable[code].view_left;
	gCrt[c].view_top = gCaretTable[code].view_top;
	gCrt[c].direct = dir;
}
