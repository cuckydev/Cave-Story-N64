#include "mapname.h"
#include "draw.h"
#include <string.h>

static const char *map_name = NULL;
static u8 map_wait = 0;

void ReadyMapName(const char *name)
{
	if (!strcmp(name, "u"))
		map_name = "Studio Pixel presents"; //original translation puts 2 spaces before this text
	else
		map_name = name;
	map_wait = 0;
}

void StartMapName()
{
	map_wait = 160;
}

void PutMapName(BOOL bMini)
{
	s32 y;
	s32 width;
	static const RECT rcBack = {0, 7, SCREEN_WIDTH, 24};
	
	if (bMini)
	{
		//Put map name in front of black bar at the top of the screen
		CortBox(&rcBack, RGB(0x00, 0x00, 0x00));
		y = 10;
	}
	else if (map_wait > 0)
	{
		//Put map name near the middle of the screen
		y = (SCREEN_HEIGHT / 2) - 40;
		map_wait--;
	}
	else
	{
		//Don't draw (map name's time has worn out)
		return;
	}
	
	width = GetTextWidth(map_name);
	PutText((SCREEN_WIDTH - width) / 2, y + 1, map_name, RGB(0x11, 0x00, 0x22));
	PutText((SCREEN_WIDTH - width) / 2, y,     map_name, RGB(0xFF, 0xFF, 0xFF));
}
