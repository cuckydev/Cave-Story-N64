#include "npcxxx.h"
#include "game.h"
#include "mychar.h"
#include "draw.h"

//NPC 359 - Water Droplet Generator
void Npc359_Act(NPCHAR *npc)
{
	s32 x;
	if (gMC.x < npc->x + (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.x > npc->x - (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.y < npc->y + (((SCREEN_HEIGHT / 2) + 200) * 0x200) && gMC.y > npc->y - (((SCREEN_HEIGHT / 2) + 40) * 0x200) && Random(0, 100) == 2)
	{
		x = npc->x + (Random(-6, 6) * 0x200);
		SetNpChar(73, x, npc->y - (7 * 0x200), 0, 0, 0, 0, 0);
	}
}
