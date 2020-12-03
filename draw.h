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
} RenderState;

//Render constants
extern const RECT grcFull;

//Render macros
#define RGB(r, g, b) ((GPACK_RGBA5551((r), (g), (b), 1) << 16) | GPACK_RGBA5551((r), (g), (b), 1))

//Render globals
extern Gfx *glistp;

//Render interface
void InitDirectDraw(NUGfxFunc vblank_callback);
void StartDirectDraw();
void StartFrame();
void EndFrame();
void LoadTLUT(u16 *tlut);
void LoadTex_CI4(u32 width, u32 height, u8 *tex);
void LoadTex_CI8(u32 width, u32 height, u8 *tex);
void PutBitmap(const RECT *src, s32 x, s32 y);
void CortBox(const RECT *rect, u32 col);
s32 GetTextWidth(const char *text);
void PutText(s32 x, s32 y, const char *text, u16 *tlut);

#endif
