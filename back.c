#include "back.h"
#include "draw.h"
#include <string.h>

//Back globals
BACK gBack;
s32 gWaterY;

//Back functions
BOOL InitBack(BACK_DRAW draw, s32 type)
{
	gBack.draw = draw;
	gBack.type = type;
	gWaterY = 240 * 0x10 * 0x200;
}

void ActBack()
{
	switch (gBack.type)
	{
		case 5:
			gBack.fx += 6 * 0x200;
			break;
		case 6:
		case 7:
			gBack.fx++;
			gBack.fx %= 640;
			break;
	}
}

void PutBack(s32 fx, s32 fy)
{
	switch (gBack.type)
	{
		case 1:
			if (gBack.draw != NULL)
				gBack.draw(fx / 2 / 0x200, fy / 2 / 0x200);
			/*
			LoadTLUT_CI4(gBack.tex.tlut);
			LoadTex_CI4(gBack.tex.width, gBack.tex.height, gBack.tex.tex);
			for (y = -((fy / 2 / 0x200) % gBack.tex.height); y < SCREEN_HEIGHT; y += gBack.tex.height)
				for (x = -((fx / 2 / 0x200) % gBack.tex.width); x < SCREEN_WIDTH; x += gBack.tex.width)
					PutBitmap(&rect, x, y);
			*/
			break;
		case 4:
			CortBox(&grcFull, RGB(0x00, 0x00, 0x20));
			break;
		default:
			break;
	}
}

void PutFront(s32 fx, s32 fy)
{
	
}
