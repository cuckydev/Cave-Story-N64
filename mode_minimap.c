#include "mode_minimap.h"
#include "keycontrol.h"
#include "map.h"
#include "mapname.h"
#include "mychar.h"
#include "draw.h"
#include "mem.h"

GameMode minimap_return;

static s32 my_x, my_y, my_wait;
static u16 map_w, map_h;
static u16 pline, line;

static BOOL open;
static s8 frame_i;

static u8 *mapsurf = NULL;
static u16 mapsurf_pitch;
static u16 mapsurf_chky;
static u16 mapsurf_chks;

static Gfx mapsurf_tlut_dumaln[] = { gsSPEndDisplayList() };
__attribute__((aligned(8))) static u16 mapsurf_tlut[] = {
	RGB(0x00, 0x19, 0x00),  RGB(0x00, 0x4E, 0x00),  RGB(0x00, 0x98, 0x00),  RGB(0x00, 0xFF, 0x00)
};

u8 GetMiniMapPixel(u16 x, u16 y)
{
	u8 a = GetAttribute(x, y);
	
	// Yup, this really is an if/else chain.
	// No switch here.
	if (a == 0)
		return 0;
	if (a == 68 ||
		a == 1 ||
		a == 64 ||
		a == 128 ||
		a == 129 ||
		a == 130 ||
		a == 131 ||
		a == 81 ||
		a == 82 ||
		a == 85 ||
		a == 86 ||
		a == 2 ||
		a == 96 ||
		a == 113 ||
		a == 114 ||
		a == 117 ||
		a == 118 ||
		a == 160 ||
		a == 161 ||
		a == 162 ||
		a == 163)
		return 1;
	if (a == 67 ||
		a == 99 ||
		a == 80 ||
		a == 83 ||
		a == 84 ||
		a == 87 ||
		a == 96 ||	// This is already listed above, so that part of the expression is always false
		a == 112 ||
		a == 115 ||
		a == 116 ||
		a == 119)
		return 2;
	return 3;
}

void WriteMiniMapLine(u16 y)
{
	u8 *p = mapsurf + mapsurf_pitch * y;
	for (u16 x = 0; x < ((map_w + 1) >> 1); x++)
		*p++ = (GetMiniMapPixel(x << 1, y) << 4) | GetMiniMapPixel((x << 1) | 1, y);
}

void ModeMiniMap_Init()
{
	//Remember player position
	my_x = ((gMC.x / 0x200) + 8) / 16;
	my_y = ((gMC.y / 0x200) + 8) / 16;
	my_wait = 0;
	
	//Get map dimensions
	GetMapData(NULL, &map_w, &map_h);
	mapsurf_pitch = ((map_w + 0xF) & ~0xF) >> 1;
	mapsurf_chky = 2048 / mapsurf_pitch;
	mapsurf_chks = (map_h + mapsurf_chky - 1) / mapsurf_chky;
	
	//Allocate map surface
	mapsurf = Mem_Alloc(mapsurf_pitch * (mapsurf_chks * mapsurf_chky));
	
	//Initialize map state
	open = TRUE;
	
	frame_i = 0;
	
	pline = 0;
	line = 0;
}

GameMode ModeMiniMap_Proc()
{
	if (open)
	{
		if (frame_i > 8)
		{
			//Close when Ok or Cancel are pressed
			if (gKeyTrg & (gKeyOk | gKeyCancel))
				open = FALSE;
			
			//Increment line
			line += 2;
			if (line > map_h)
				line = map_h;
		}
		else
		{
			//Grow frame
			frame_i++;
		}
	}
	else
	{
		//Shrink frame
		if (--frame_i <= 0)
			return minimap_return;
	}
	
	return GameMode_MiniMap;
}

#include "frame.h"
#include "back.h"
#include "npchar.h"
#include "bullet.h"
#include "mychar.h"
#include "caret.h"
#include "flash.h"
#include "valueview.h"
#include "bosslife.h"
#include "fade.h"

void ModeMiniMap_Draw()
{
	RECT rcMiniMap = {0, 0, map_w, 0};
	RECT rcFrame;
	RECT rcMyc;
	u16 y;
	
	//TODO: draw a screen capture instead of the entire game
	s32 fx, fy;
	GetFramePosition(&fx, &fy);
	
	UpdateMapPlane(fx, fy);
	PutBack(fx, fy);
	PutStage_Back(fx, fy);
	PutNpChar(fx, fy);
	PutBullet(fx, fy);
	PutMyChar(fx, fy);
	PutStage_Front(fx, fy);
	PutFlash();
	PutCaret(fx, fy);
	PutValueView(fx, fy);
	PutBossLife();
	PutFade();
	
	if (frame_i <= 8)
	{
		//Draw frame growing / shrinking
		rcFrame.left = (SCREEN_WIDTH - (map_w * frame_i / 8)) / 2;
		rcFrame.top = (SCREEN_HEIGHT - (map_h * frame_i / 8)) / 2;
		rcFrame.right = (SCREEN_WIDTH + (map_w * frame_i / 8)) / 2;
		rcFrame.bottom = (SCREEN_HEIGHT + (map_h * frame_i / 8)) / 2;
		CortBox(&rcFrame, RGB(0x00, 0x00, 0x00));
	}
	else
	{
		//Draw frame
		rcFrame.left = (SCREEN_WIDTH - map_w) / 2 - 1;
		rcFrame.top = (SCREEN_HEIGHT - map_h) / 2 - 1;
		rcFrame.right = (SCREEN_WIDTH + map_w) / 2 + 1;
		rcFrame.bottom = (SCREEN_HEIGHT + map_h) / 2 + 1;
		CortBox(&rcFrame, RGB(0x00, 0x00, 0x00));
		
		//Write minimap lines
		for (; pline < line; pline++)
			WriteMiniMapLine(pline);
		
		//Draw minimap
		LoadTLUT_CI4(mapsurf_tlut);
		
		for (y = 0; y < line; y += mapsurf_chky)
		{
			LoadTex_CI4(mapsurf_pitch << 1, mapsurf_chky, mapsurf + mapsurf_pitch * y);
			rcMiniMap.top = 0;
			rcMiniMap.bottom = line - y;
			if (rcMiniMap.bottom > mapsurf_chky)
				rcMiniMap.bottom = mapsurf_chky;
			PutBitmap(&rcMiniMap, (SCREEN_WIDTH - map_w) / 2, (SCREEN_HEIGHT - map_h) / 2 + y);
		}
		
		//Draw player marker
		if (++my_wait / 8 % 2)
		{
			rcMyc.left = (SCREEN_WIDTH - map_w) / 2 + my_x;
			rcMyc.top = (SCREEN_HEIGHT- map_h) / 2 + my_y;
			rcMyc.right = rcMyc.left + 1;
			rcMyc.bottom = rcMyc.top + 1;
			CortBox(&rcMyc, RGB(0xFF, 0xFF, 0xFF));
		}
	}
	
	//Draw map's name
	PutMapName(TRUE);
}

void ModeMiniMap_Quit()
{
	//Free map surface
	Mem_Free(mapsurf);
}
