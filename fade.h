#ifndef FADE_H
#define FADE_H

#include <ultra64.h>
#include "game_def.h"
#include "config.h"

//Fade constants
#define FADE_WIDTH  ((SCREEN_WIDTH - 15) / 16)
#define FADE_HEIGHT ((SCREEN_HEIGHT + 15) / 16)
#define FADE_TIME   (((FADE_WIDTH > FADE_HEIGHT) ? FADE_WIDTH : FADE_HEIGHT) + 16)

//Fade structure
typedef struct
{
	s32 mode;
	BOOL bMask;
	s32 count;
	s8 dir;
} FADE;

extern FADE gFade;

//Fade functions
void InitFade();
void SetFadeMask();
void ClearFade();
void StartFadeOut(s8 dir);
void StartFadeIn(s8 dir);
void ProcFade();
void PutFade();
BOOL GetFadeActive();

#endif
