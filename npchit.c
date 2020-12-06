#include "npchit.h"
#include "npchar.h"
#include "map.h"

void JadgeHitNpCharBlock(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	
	if (npc->y - npc->hit.top < (y * 0x10 + 5) * 0x200
		&& npc->y + npc->hit.bottom > (y * 0x10 - 5) * 0x200
		&& npc->x - npc->hit.back < (x * 0x10 + 8) * 0x200
		&& npc->x - npc->hit.back > x * 0x10 * 0x200)
	{
		npc->x = ((x * 0x10 + 8) * 0x200) + npc->hit.back;
		hit |= 1;
	}
	
	if (npc->y - npc->hit.top < (y * 0x10 + 5) * 0x200
		&& npc->y + npc->hit.bottom > (y * 0x10 - 5) * 0x200
		&& npc->x + npc->hit.back > (x * 0x10 - 8) * 0x200
		&& npc->x + npc->hit.back < x * 0x10 * 0x200)
	{
		npc->x = ((x * 0x10 - 8) * 0x200) - npc->hit.back;
		hit |= 4;
	}
	
	if (npc->x - npc->hit.back < (x * 0x10 + 5) * 0x200
		&& npc->x + npc->hit.back > (x * 0x10 - 5) * 0x200
		&& npc->y - npc->hit.top < (y * 0x10 + 8) * 0x200
		&& npc->y - npc->hit.top > y * 0x10 * 0x200)
	{
		npc->y = ((y * 0x10 + 8) * 0x200) + npc->hit.top;
		npc->ym = 0;
		hit |= 2;
	}
	
	if (npc->x - npc->hit.back < (x * 0x10 + 5) * 0x200
		&& npc->x + npc->hit.back > (x * 0x10 - 5) * 0x200
		&& npc->y + npc->hit.bottom > (y * 0x10 - 8) * 0x200
		&& npc->y + npc->hit.bottom < y * 0x10 * 0x200)
	{
		npc->y = ((y * 0x10 - 8) * 0x200) - npc->hit.bottom;
		npc->ym = 0;
		hit |= 8;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharTriangleA(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	
	if (npc->x < (x * 0x10 + 8) * 0x200
		&& npc->x > (x * 0x10 - 8) * 0x200
		&& npc->y - npc->hit.top < (y * 0x10 * 0x200) - ((npc->x - (x * 0x10 * 0x200)) / 2) + 0x800
		&& npc->y + npc->hit.bottom > (y * 0x10 - 8) * 0x200)
	{
		//Clip
		npc->y = (y * 0x10 * 0x200) - ((npc->x - (x * 0x10 * 0x200)) / 2) + 0x800 + npc->hit.top;
		
		//Halt momentum
		if (npc->ym < 0)
			npc->ym = 0;
		
		//Set that hit a ceiling
		hit |= 2;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharTriangleB(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	
	if (npc->x < (x * 0x10 + 8) * 0x200
		&& npc->x > (x * 0x10 - 8) * 0x200
		&& npc->y - npc->hit.top < (y * 0x10 * 0x200) - ((npc->x - (x * 0x10 * 0x200)) / 2) - 0x800
		&& npc->y + npc->hit.bottom > (y * 0x10 - 8) * 0x200)
	{
		//Clip
		npc->y = (y * 0x10 * 0x200) - ((npc->x - (x * 0x10 * 0x200)) / 2) - 0x800 + npc->hit.top;
		
		//Halt momentum
		if (npc->ym < 0)
			npc->ym = 0;
		
		//Set that hit a ceiling
		hit |= 2;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharTriangleC(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	
	if (npc->x < (x * 0x10 + 8) * 0x200
		&& npc->x > (x * 0x10 - 8) * 0x200
		&& npc->y - npc->hit.top < (y * 0x10 * 0x200) + ((npc->x - (x * 0x10 * 0x200)) / 2) - 0x800
		&& npc->y + npc->hit.bottom > (y * 0x10 - 8) * 0x200)
	{
		//Clip
		npc->y = (y * 0x10 * 0x200) + ((npc->x - (x * 0x10 * 0x200)) / 2) - 0x800 + npc->hit.top;
		
		//Halt momentum
		if (npc->ym < 0)
			npc->ym = 0;
		
		//Set that hit a ceiling
		hit |= 2;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharTriangleD(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	
	if (npc->x < (x * 0x10 + 8) * 0x200
		&& npc->x > (x * 0x10 - 8) * 0x200
		&& npc->y - npc->hit.top < (y * 0x10 * 0x200) + ((npc->x - (x * 0x10 * 0x200)) / 2) + 0x800
		&& npc->y + npc->hit.bottom > (y * 0x10 - 8) * 0x200)
	{
		//Clip
		npc->y = (y * 0x10 * 0x200) + ((npc->x - (x * 0x10 * 0x200)) / 2) + 0x800 + npc->hit.top;
		
		//Halt momentum
		if (npc->ym < 0)
			npc->ym = 0;
		
		//Set that hit a ceiling
		hit |= 2;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharTriangleE(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	hit |= 0x10000;
	
	if (npc->x < (x * 0x10 + 8) * 0x200
		&& npc->x > (x * 0x10 - 8) * 0x200
		&& npc->y + npc->hit.bottom > (y * 0x10 * 0x200) + ((npc->x - (x * 0x10 * 0x200)) / 2) - 0x800
		&& npc->y - npc->hit.top < (y * 0x10 + 8) * 0x200)
	{
		//Clip
		npc->y = (y * 0x10 * 0x200) + ((npc->x - (x * 0x10 * 0x200)) / 2) - 0x800 - npc->hit.bottom;
		
		//Halt momentum
		if (npc->ym > 0)
			npc->ym = 0;
		
		//Set that hit this slope
		hit |= 0x28;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharTriangleF(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	hit |= 0x20000;
	
	if (npc->x < (x * 0x10 + 8) * 0x200
		&& npc->x >= (x * 0x10 - 8) * 0x200	//Note that this function uses '>='. I'm not sure if this is a bug.
		&& npc->y + npc->hit.bottom > (y * 0x10 * 0x200) + ((npc->x - (x * 0x10 * 0x200)) / 2) + 0x800
		&& npc->y - npc->hit.top < (y * 0x10 + 8) * 0x200)
	{
		//Clip
		npc->y = (y * 0x10 * 0x200) + ((npc->x - (x * 0x10 * 0x200)) / 2) + 0x800 - npc->hit.bottom;
		
		//Halt momentum
		if (npc->ym > 0)
			npc->ym = 0;
		
		//Set that hit this slope
		hit |= 0x28;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharTriangleG(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	hit |= 0x40000;
	
	if (npc->x < (x * 0x10 + 8) * 0x200
		&& npc->x > (x * 0x10 - 8) * 0x200
		&& npc->y + npc->hit.bottom > (y * 0x10 * 0x200) - ((npc->x - (x * 0x10 * 0x200)) / 2) + 0x800
		&& npc->y - npc->hit.top < (y * 0x10 + 8) * 0x200)
	{
		//Clip
		npc->y = (y * 0x10 * 0x200) - ((npc->x - (x * 0x10 * 0x200)) / 2) + 0x800 - npc->hit.bottom;
		
		//Halt momentum
		if (npc->ym > 0)
			npc->ym = 0;
		
		//Set that hit this slope
		hit |= 0x18;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharTriangleH(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	hit |= 0x80000;
	
	if (npc->x < (x * 0x10 + 8) * 0x200
		&& npc->x > (x * 0x10 - 8) * 0x200
		&& npc->y + npc->hit.bottom > (y * 0x10 * 0x200) - ((npc->x - (x * 0x10 * 0x200)) / 2) - 0x800
		&& npc->y - npc->hit.top < (y * 0x10 + 8) * 0x200)
	{
		//Clip
		npc->y = (y * 0x10 * 0x200) - ((npc->x - (x * 0x10 * 0x200)) / 2) - 0x800 - npc->hit.bottom;
		
		//Halt momentum
		if (npc->ym > 0)
			npc->ym = 0;
		
		//Set that hit this slope
		hit |= 0x18;
	}
	
	npc->flag |= hit;
}

void JudgeHitNpCharWater(NPCHAR *npc, s32 x, s32 y)
{
	s32 hit = 0;
	if (npc->x - npc->hit.back < (x * 0x10 + 6) * 0x200
		&& npc->x + npc->hit.back > (x * 0x10 - 6) * 0x200
		&& npc->y - npc->hit.top < (y * 0x10 + 6) * 0x200
		&& npc->y + npc->hit.bottom > (y * 0x10 - 6) * 0x200)
		hit |= 0x100;
	npc->flag |= hit;
}

void HitNpCharMap()
{
	s32 i, x, y;
	u8 atrb;
	
	//Iterate through all NPCs performing collision
	for (i = 0; i < NPC_MAX; ++i)
	{
		if (!(gNPC[i].cond & 0x80))
			continue;
		if (gNPC[i].bits & NPC_IGNORE_SOLIDITY)
			continue;
		
		//Clear flag
		gNPC[i].flag = 0;
		
		//Check tiles 
		for (x = (gNPC[i].x - gNPC[i].hit.back + 0x1000) / 0x2000; x <= (gNPC[i].x + gNPC[i].hit.back + 0x1000) / 0x2000; x++)
		{
			for (y = (gNPC[i].y - gNPC[i].hit.top + 0x1000) / 0x2000; y <= (gNPC[i].y + gNPC[i].hit.bottom + 0x1000) / 0x2000; y++)
			{
				//Handle tile
				atrb = GetAttribute(x, y);
				
				switch (atrb)
				{
					//No NPC block
					case 0x44:
						if (gNPC[i].bits & NPC_IGNORE_TILE_44)
							break;
						//Fallthrough
					//Block
					case 0x03:
					case 0x05:
					case 0x41:
					case 0x43:
						JadgeHitNpCharBlock(&gNPC[i], x, y);
						break;
						
					//Slopes
					case 0x50:
						JudgeHitNpCharTriangleA(&gNPC[i], x, y);
						break;
						
					case 0x51:
						JudgeHitNpCharTriangleB(&gNPC[i], x, y);
						break;
						
					case 0x52:
						JudgeHitNpCharTriangleC(&gNPC[i], x, y);
						break;
						
					case 0x53:
						JudgeHitNpCharTriangleD(&gNPC[i], x, y);
						break;
						
					case 0x54:
						JudgeHitNpCharTriangleE(&gNPC[i], x, y);
						break;
						
					case 0x55:
						JudgeHitNpCharTriangleF(&gNPC[i], x, y);
						break;
						
					case 0x56:
						JudgeHitNpCharTriangleG(&gNPC[i], x, y);
						break;
						
					case 0x57:
						JudgeHitNpCharTriangleH(&gNPC[i], x, y);
						break;
						
					//Water
					case 0x02:
					case 0x60:
					case 0x62:
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					//Water block
					case 0x04:
					case 0x61:
					case 0x64:
						JadgeHitNpCharBlock(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					//Water slopes
					case 0x70:
						JudgeHitNpCharTriangleA(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					case 0x71:
						JudgeHitNpCharTriangleB(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					case 0x72:
						JudgeHitNpCharTriangleC(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					case 0x73:
						JudgeHitNpCharTriangleD(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					case 0x74:
						JudgeHitNpCharTriangleE(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					case 0x75:
						JudgeHitNpCharTriangleF(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					case 0x76:
						JudgeHitNpCharTriangleG(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					case 0x77:
						JudgeHitNpCharTriangleH(&gNPC[i], x, y);
						JudgeHitNpCharWater(&gNPC[i], x, y);
						break;
						
					case 0xA0:
						gNPC[i].flag |= 0x100;
						//Fallthrough
					case 0x80:
						gNPC[i].flag |= 0x1000;
						break;
						
					case 0xA1:
						gNPC[i].flag |= 0x100;
						//Fallthrough
					case 0x81:
						gNPC[i].flag |= 0x2000;
						break;
						
					case 0xA2:
						gNPC[i].flag |= 0x100;
						//Fallthrough
					case 0x82:
						gNPC[i].flag |= 0x4000;
						break;
						
					case 0xA3:
						gNPC[i].flag |= 0x100;
						//Fallthrough
					case 0x83:
						gNPC[i].flag |= 0x8000;
						break;
				}
			}
		}
	}
}
