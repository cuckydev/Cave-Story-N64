#ifndef DRAW_H
#define DRAW_H

#include <nusys.h>
#include "game_def.h"
#include "config.h"

//Render types
typedef enum
{
	RS_Null,
	RS_Rect,
	RS_Tex,
	RS_Copy,
} RenderState;

//Render constants
extern const RECT grcFull;

//Render macros
#define RGB(r, g, b) (GPACK_RGBA5551((r), (g), (b), 1))

//Render globals
extern Gfx glist[GLIST_LENGTH];
extern Gfx *glistp;

//Render interface
void InitDirectDraw(NUGfxFunc vblank_callback);
void StartFrame();
void EndFrame();
void LoadTLUT_CI4(u16 *tlut);
void LoadTLUT_CI8(u16 *tlut);
void LoadTex_CI4(u32 width, u32 height, u8 *tex);
void LoadTex_CI8(u32 width, u32 height, u8 *tex);
void LoadTex_C16(u32 width, u32 height, u8 *tex);
void CopyBitmap(const RECT *src, s32 x, s32 y);
void PutBitmap(const RECT *src, s32 x, s32 y);
void PutBitmap_X(const RECT *src, s32 x, s32 y);
void PutBitmap_Y(const RECT *src, s32 x, s32 y);
void PutBitmap_XY(const RECT *src, s32 x, s32 y);
void CortBox(const RECT *rect, u16 col);
s32 GetTextWidth(const char *text);
void PutText(s32 x, s32 y, const char *text, u16 col);

#endif
