#include "fade.h"
#include "draw.h"
#include <string.h>

//Fade structure
FADE gFade;

//Fade functions
void InitFade()
{
	memset(&gFade, 0, sizeof(FADE));
}

void SetFadeMask()
{
	gFade.bMask = TRUE;
}

void ClearFade()
{
	gFade.bMask = FALSE;
	gFade.mode = 0;
}

void StartFadeOut(s8 dir)
{
	gFade.mode = 2;
	gFade.count = 0;
	gFade.dir = dir;
	gFade.bMask = FALSE;
}

void StartFadeIn(s8 dir)
{
	gFade.mode = 1;
	gFade.count = 0;
	gFade.dir = dir;
	gFade.bMask = TRUE;
}

void ProcFade()
{
	if (gFade.mode != 0)
	{
		//Increment counter
		if (++gFade.count > FADE_TIME)
		{
			gFade.bMask = gFade.mode == 2;
			gFade.mode = 0;
		}
		else
		{
			gFade.bMask = FALSE;
		}
	}
}

#include "data/bitmap/fade.inc.c"

void PutFade()
{
	s32 i, v;
	s32 count, dir;
	RECT rect;
	static const RECT rcFadeH = {0, 0, 256,  16};
	static const RECT rcFadeV = {0, 0,  16, 256};
	static const s8 fout_map[] = {2, 3, 0, 1, 4};
	
	//Draw screen mask
	if (gFade.bMask)
	{
		CortBox(&grcFull, RGB(0x00, 0x00, 0x20));
		return;
	}
	
	if (gFade.mode)
	{
		//Get count and direction (hacky solution so I don't duplicate a bunch of code lol
		switch (gFade.mode)
		{
			case 1:
				count = gFade.count;
				dir = gFade.dir;
				break;
			case 2:
				count = FADE_TIME - gFade.count;
				dir = fout_map[gFade.dir];
				break;
		}
		
		//Draw fading in
		LoadTLUT_CI4(fade_tlut);
		switch (dir)
		{
			case 0:
				LoadTex_CI4(256, 16, fade_h_tex);
				rect.left = 0;
				rect.top = 0;
				rect.right = SCREEN_WIDTH - (count * 16);
				rect.bottom = SCREEN_HEIGHT;
				CortBox(&rect, RGB(0x00, 0x00, 0x20));
				for (i = 0; i < FADE_HEIGHT; i++)
					PutBitmap_X(&rcFadeH, rect.right, i * 16);
				break;
			case 1:
				LoadTex_CI4(16, 256, fade_v_tex);
				rect.left = 0;
				rect.top = 0;
				rect.right = SCREEN_WIDTH;
				rect.bottom = SCREEN_HEIGHT - (count * 16);
				CortBox(&rect, RGB(0x00, 0x00, 0x20));
				for (i = 0; i <= FADE_WIDTH; i++)
					PutBitmap_Y(&rcFadeV, i * 16, rect.bottom);
				break;
			case 2:
				LoadTex_CI4(256, 16, fade_h_tex);
				rect.left = count * 16;
				rect.top = 0;
				rect.right = SCREEN_WIDTH;
				rect.bottom = SCREEN_HEIGHT;
				CortBox(&rect, RGB(0x00, 0x00, 0x20));
				for (i = 0; i <= FADE_HEIGHT; i++)
					PutBitmap(&rcFadeH, rect.left - 256, i * 16);
				break;
			case 3:
				LoadTex_CI4(16, 256, fade_v_tex);
				rect.left = 0;
				rect.top = count * 16;
				rect.right = SCREEN_WIDTH;
				rect.bottom = SCREEN_HEIGHT;
				CortBox(&rect, RGB(0x00, 0x00, 0x20));
				for (i = 0; i <= FADE_WIDTH; i++)
					PutBitmap(&rcFadeV, i * 16, rect.top - 256);
				break;
			case 4:
				LoadTex_CI4(256, 16, fade_h_tex);
				for (i = 0; i <= FADE_HEIGHT; i++)
				{
					//Get v
					v = (count - 8 + ((i < (FADE_HEIGHT / 2)) ? i : ((FADE_HEIGHT - 1) - i)));
					
					//Draw left
					rect.left = 0;
					rect.top = i * 16;
					rect.right = (SCREEN_WIDTH / 2) - (v * 16);
					rect.bottom = rect.top + 16;
					CortBox(&rect, RGB(0x00, 0x00, 0x20));
					PutBitmap_X(&rcFadeH, rect.right, i * 16);
					
					//Draw right
					rect.left = (SCREEN_WIDTH / 2) + (v * 16);
					rect.top = i * 16;
					rect.right = SCREEN_WIDTH;
					rect.bottom = rect.top + 16;
					CortBox(&rect, RGB(0x00, 0x00, 0x20));
					PutBitmap(&rcFadeH, rect.left - 256, i * 16);
				}
				break;
		}
	}
}

BOOL GetFadeActive()
{
	return gFade.mode != 0;
}
