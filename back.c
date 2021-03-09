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
		case 0:
			if (gBack.draw != NULL)
				gBack.draw(0, 0);
			break;
		case 1:
			if (gBack.draw != NULL)
				gBack.draw(fx / 2 / 0x200, fy / 2 / 0x200);
			break;
		case 2:
			if (gBack.draw != NULL)
				gBack.draw(fx / 0x200, fy / 0x200);
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
