#include "caret.h"
#include "carets.h"
#include "config.h"
#include "game_def.h"
#include "draw.h"
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
void (*gpCaretFuncTbl[18])(CARET*) = {
	ActCaret00,
	ActCaret01,
	ActCaret02,
	ActCaret03,
	ActCaret04,
	ActCaret05,
	ActCaret04, //Caret 04 instead of 06 (which doesn't exist)
	ActCaret07,
	ActCaret08,
	ActCaret09,
	ActCaret10,
	ActCaret11,
	ActCaret12,
	ActCaret13,
	ActCaret14,
	ActCaret15,
	ActCaret16,
	ActCaret17,
};

//Caret functions
void InitCaret()
{
	memset(gCrt, 0, sizeof(gCrt));
}

void ActCaret()
{
	s32 i;
	for (i = 0; i < CARET_MAX; i++)
		if (gCrt[i].cond & 0x80)
			gpCaretFuncTbl[gCrt[i].code](&gCrt[i]);
}

static BOOL CaretVisible(CARET *crt, s32 fx, s32 fy)
{
	s32 lx = (crt->x / 0x200) - (fx / 0x200);
	s32 ly = (crt->y / 0x200) - (fy / 0x200);
	s32 pl = crt->view_left / 0x200;
	s32 pt = crt->view_top / 0x200;
	return (lx > -pl && ly > -pt && lx < (SCREEN_WIDTH + pl) && ly < (SCREEN_HEIGHT + pt));
}

void PutCaret(s32 fx, s32 fy)
{
	s32 i;
	for (i = 0; i < CARET_MAX; i++)
	{
		if ((gCrt[i].cond & 0x80) && gCrt[i].tex != NULL && CaretVisible(&gCrt[i], fx, fy))
		{
			LoadTLUT_CI4(gCrt[i].tlut);
			LoadTex_CI4(gCrt[i].tex_w, gCrt[i].tex_h, gCrt[i].tex);
			PutBitmap(&gCrt[i].rect, ((gCrt[i].x - gCrt[i].view_left) / 0x200) - (fx / 0x200), ((gCrt[i].y - gCrt[i].view_top) / 0x200) - (fy / 0x200));
		}
	}
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
