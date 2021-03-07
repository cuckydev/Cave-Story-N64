#include "mapname.h"
#include "draw.h"
#include <string.h>

static char map_name[0x20];
static u8 map_wait = 0;

void ReadyMapName(const char *name)
{
	if (name[0] == 'u' && name[1] == '\0')
		strcpy(map_name, "Studio Pixel presents"); //original translation puts 2 spaces before this text
	else
		strcpy(map_name, name);
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
	
	if (map_name != NULL)
	{
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
}
