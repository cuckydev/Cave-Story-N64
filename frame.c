#include "frame.h"
#include "mychar.h"
#include "npchar.h"
#include "map.h"
#include "game.h"
#include "config.h"

//Frame structure
FRAME gFrame;

//Frame functions
static void ClampFrame()
{
	//Get map dimensions
	s16 map_w, map_l;
	GetMapData(NULL, &map_w, &map_l);
	
	//Clamp frame
	if (gFrame.x / 0x200 < 0)
		gFrame.x = 0;
	if (gFrame.y / 0x200 < 0)
		gFrame.y = 0;
	
	if (gFrame.x > (((map_w - 1) * 16) - SCREEN_WIDTH) * 0x200)
		gFrame.x = (((map_w - 1) * 16) - SCREEN_WIDTH) * 0x200;
	if (gFrame.y > (((map_l - 1) * 16) - SCREEN_HEIGHT) * 0x200)
		gFrame.y = (((map_l - 1) * 16) - SCREEN_HEIGHT) * 0x200;
}

void MoveFrame3()
{
	//Move towards target and clamp
	if (gFrame.tgt_x != NULL && gFrame.tgt_y != NULL & gFrame.wait != 0)
	{
		gFrame.x += (*gFrame.tgt_x - (SCREEN_WIDTH * 0x200 / 2) - gFrame.x) / gFrame.wait;
		gFrame.y += (*gFrame.tgt_y - (SCREEN_HEIGHT * 0x200 / 2) - gFrame.y) / gFrame.wait;
	}
	ClampFrame();
	
	//Quake
	if (gFrame.quake2)
	{
		gFrame.x += (Random(-5, 5) * 0x200);
		gFrame.y += (Random(-3, 3) * 0x200);
		gFrame.quake2--;
	}
	else if (gFrame.quake)
	{
		gFrame.x += (Random(-1, 1) * 0x200);
		gFrame.y += (Random(-1, 1) * 0x200);
		gFrame.quake--;
	}
}

void GetFramePosition(s32 *fx, s32 *fy)
{
	if (fx != NULL)
		*fx = gFrame.x;
	if (fy != NULL)
		*fy = gFrame.y;
}

void SetFramePosition(s32 fx, s32 fy)
{
	gFrame.x = fx;
	gFrame.y = fy;
}

void SetFrameMyChar()
{
	gFrame.x = gMC.x - ((SCREEN_WIDTH / 2) * 0x200);
	gFrame.y = gMC.y - ((SCREEN_HEIGHT / 2) * 0x200);
	ClampFrame();
}

void SetFrameTargetMyChar(s32 wait)
{
	gFrame.tgt_x = &gMC.tgt_x;
	gFrame.tgt_y = &gMC.tgt_y;
	gFrame.wait = wait;
}

void SetFrameTargetNpChar(s32 event, s32 wait)
{
	s32 i;
	for (i = 0; i < NPC_MAX; i++)
		if (gNPC[i].code_event == event)
			break;
	
	if (i == NPC_MAX)
		return;
	
	gFrame.tgt_x = &gNPC[i].x;
	gFrame.tgt_y = &gNPC[i].y;
	gFrame.wait = wait;
}

void SetFrameTargetBoss(s32 no, s32 wait)
{
	
}

void SetQuake(s32 time)
{
	gFrame.quake = time;
}

void SetQuake2(s32 time)
{
	gFrame.quake2 = time;
}

void ResetQuake()
{
	gFrame.quake = 0;
	gFrame.quake2 = 0;
}
