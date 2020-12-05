#include "mychit.h"
#include "mychar.h"
#include "mycparam.h"
#include "npchar.h"
#include "textscr.h"
#include "keycontrol.h"
#include "map.h"
#include "caret.h"

void ResetMyCharFlag()
{
	gMC.flag = 0;
}

static void PutlittleStar()
{
	if (!(gMC.cond & 2) && gMC.ym < -0x200)
	{
		//PlaySoundObject(3, SOUND_MODE_PLAY);
		SetCaret(gMC.x, gMC.y - gMC.hit.top, CARET_TINY_PARTICLES, 0);
		SetCaret(gMC.x, gMC.y - gMC.hit.top, CARET_TINY_PARTICLES, 0);
	}
}

s32 JudgeHitMyCharBlock(s32 x, s32 y)
{
	s32 hit = 0;
	
	//Left wall
	if (gMC.y - gMC.hit.top < (y * 0x10 + 4) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 4) * 0x200
		&& gMC.x - gMC.hit.back < (x * 0x10 + 8) * 0x200
		&& gMC.x - gMC.hit.back > x * 0x10 * 0x200)
	{
		//Clip
		gMC.x = ((x * 0x10 + 8) * 0x200) + gMC.hit.back;
		
		//Halt momentum
		if (gMC.xm < -0x180)
			gMC.xm = -0x180;
		if (!(gKey & gKeyLeft) && gMC.xm < 0)
			gMC.xm = 0;
		
		//Set that a left wall was hit
		hit |= 1;
	}
	
	//Right wall
	if (gMC.y - gMC.hit.top < (y * 0x10 + 4) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 4) * 0x200
		&& gMC.x + gMC.hit.back > (x * 0x10 - 8) * 0x200
		&& gMC.x + gMC.hit.back < x * 0x10 * 0x200)
	{
		//Clip
		gMC.x = ((x * 0x10 - 8) * 0x200) - gMC.hit.back;
		
		//Halt momentum
		if (gMC.xm > 0x180)
			gMC.xm = 0x180;
		if (!(gKey & gKeyRight) && gMC.xm > 0)
			gMC.xm = 0;
		
		//Set that a right wall was hit
		hit |= 4;
	}
	
	//Ceiling
	if (gMC.x - gMC.hit.back < (x * 0x10 + 5) * 0x200
		&& gMC.x + gMC.hit.back > (x * 0x10 - 5) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 + 8) * 0x200
		&& gMC.y - gMC.hit.top > y * 0x10 * 0x200)
	{
		//Clip
		gMC.y = ((y * 0x10 + 8) * 0x200) + gMC.hit.top;
		
		//Halt momentum
		if (!(gMC.cond & 2) && gMC.ym < -0x200)
			PutlittleStar();
		if (gMC.ym < 0)
			gMC.ym = 0;
		
		//Set that a ceiling was hit
		hit |= 2;
	}
	
	//Floor
	if (gMC.x - gMC.hit.back < (x * 0x10 + 5) * 0x200
		&& gMC.x + gMC.hit.back > ((x * 0x10 - 5) * 0x200)
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 8) * 0x200
		&& gMC.y + gMC.hit.bottom < y * 0x10 * 0x200)
	{
		//Clip
		gMC.y = ((y * 0x10 - 8) * 0x200) - gMC.hit.bottom;
		
		//Halt momentum
		//if (gMC.ym > 0x400)
		//	PlaySoundObject(23, SOUND_MODE_PLAY);
		if (gMC.ym > 0)
			gMC.ym = 0;
		
		//Set that a floor was hit
		hit |= 8;
	}
	
	return hit;
}

s32 JudgeHitMyCharTriangleA(s32 x, s32 y)
{
	s32 hit = 0;
	
	if (gMC.x < (x * 0x10 + 8) * 0x200
		&& gMC.x > (x * 0x10 - 8) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 * 0x200) - (gMC.x - x * 0x10 * 0x200) / 2 + 0x800
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 8) * 0x200)
	{
		//Clip
		gMC.y = (y * 0x10 * 0x200) - ((gMC.x - x * 0x10 * 0x200) / 2) + 0x800 + gMC.hit.top;
		
		//Halt momentum
		if (!(gMC.cond & 2) && gMC.ym < -0x200)
			PutlittleStar();
		if (gMC.ym < 0)
			gMC.ym = 0;
		
		//Set that hit a ceiling
		hit |= 2;
	}
	
	return hit;
}

s32 JudgeHitMyCharTriangleB(s32 x, s32 y)
{
	s32 hit = 0;
	
	if (gMC.x < (x * 0x10 + 8) * 0x200
		&& gMC.x > (x * 0x10 - 8) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 * 0x200) - ((gMC.x - x * 0x10 * 0x200) / 2) - 0x800
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 8) * 0x200)
	{
		//Clip
		gMC.y = (y * 0x10 * 0x200) - ((gMC.x - x * 0x10 * 0x200) / 2) - 0x800 + gMC.hit.top;
		
		//Halt momentum
		if (!(gMC.cond & 2) && gMC.ym < -0x200)
			PutlittleStar();
		if (gMC.ym < 0)
			gMC.ym = 0;
		
		//Set that hit a ceiling
		hit |= 2;
	}
	
	return hit;
}

s32 JudgeHitMyCharTriangleC(s32 x, s32 y)
{
	s32 hit = 0;
	
	if (gMC.x < (x * 0x10 + 8) * 0x200
		&& gMC.x > (x * 0x10 - 8) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 * 0x200) + ((gMC.x - x * 0x10 * 0x200) / 2) - 0x800
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 8) * 0x200)
	{
		//Clip
		gMC.y = (y * 0x10 * 0x200) + ((gMC.x - x * 0x10 * 0x200) / 2) - 0x800 + gMC.hit.top;
		
		//Halt momentum
		if (!(gMC.cond & 2) && gMC.ym < -0x200)
			PutlittleStar();
		if (gMC.ym < 0)
			gMC.ym = 0;
		
		//Set that hit a ceiling
		hit |= 2;
	}
	
	return hit;
}

s32 JudgeHitMyCharTriangleD(s32 x, s32 y)
{
	s32 hit = 0;
	
	if (gMC.x < (x * 0x10 + 8) * 0x200
		&& gMC.x > (x * 0x10 - 8) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 * 0x200) + ((gMC.x - x * 0x10 * 0x200) / 2) + 0x800
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 8) * 0x200)
	{
		//Clip
		gMC.y = (y * 0x10 * 0x200) + ((gMC.x - x * 0x10 * 0x200) / 2) + 0x800 + gMC.hit.top;
		
		//Halt momentum
		if (!(gMC.cond & 2) && gMC.ym < -0x200)
			PutlittleStar();
		if (gMC.ym < 0)
			gMC.ym = 0;
		
		//Set that hit a ceiling
		hit |= 2;
	}
	
	return hit;
}

s32 JudgeHitMyCharTriangleE(s32 x, s32 y)
{
	s32 hit = 0;
	hit |= 0x10000;
	
	if (gMC.x < (x * 0x10 + 8) * 0x200
		&& gMC.x > (x * 0x10 - 8) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 * 0x200) + ((gMC.x - x * 0x10 * 0x200) / 2) - 0x800
		&& gMC.y - gMC.hit.top < (y * 0x10 + 8) * 0x200)
	{
		//Clip
		gMC.y = (y * 0x10 * 0x200) + ((gMC.x - x * 0x10 * 0x200) / 2) - 0x800 - gMC.hit.bottom;
		
		//Halt momentum
		//if (gMC.ym > 0x400)
		//	PlaySoundObject(23, SOUND_MODE_PLAY);
		if (gMC.ym > 0)
			gMC.ym = 0;
		
		//Set that hit this slope
		hit |= 0x28;
	}
	
	return hit;
}

s32 JudgeHitMyCharTriangleF(s32 x, s32 y)
{
	s32 hit = 0;
	hit |= 0x20000;
	
	if (gMC.x < (x * 0x10 + 8) * 0x200
		&& gMC.x > (x * 0x10 - 8) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 * 0x200) + ((gMC.x - x * 0x10 * 0x200) / 2) + 0x800
		&& gMC.y - gMC.hit.top < (y * 0x10 + 8) * 0x200)
	{
		//Clip
		gMC.y = (y * 0x10 * 0x200) + ((gMC.x - x * 0x10 * 0x200) / 2) + 0x800 - gMC.hit.bottom;
		
		//Halt momentum
		//if (gMC.ym > 0x400)
		//	PlaySoundObject(23, SOUND_MODE_PLAY);
		if (gMC.ym > 0)
			gMC.ym = 0;
		
		//Set that hit this slope
		hit |= 0x28;
	}
	
	return hit;
}

s32 JudgeHitMyCharTriangleG(s32 x, s32 y)
{
	s32 hit = 0;
	hit |= 0x40000;
	
	if (gMC.x < (x * 0x10 + 8) * 0x200
		&& gMC.x > (x * 0x10 - 8) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 * 0x200) - ((gMC.x - x * 0x10 * 0x200) / 2) + 0x800
		&& gMC.y - gMC.hit.top < (y * 0x10 + 8) * 0x200)
	{
		//Clip
		gMC.y = (y * 0x10 * 0x200) - ((gMC.x - x * 0x10 * 0x200) / 2) + 0x800 - gMC.hit.bottom;
		
		//Halt momentum
		//if (gMC.ym > 0x400)
		//	PlaySoundObject(23, SOUND_MODE_PLAY);
		if (gMC.ym > 0)
			gMC.ym = 0;
		
		//Set that hit this slope
		hit |= 0x18;
	}
	
	return hit;
}

s32 JudgeHitMyCharTriangleH(s32 x, s32 y)
{
	s32 hit = 0;
	hit |= 0x80000;
	
	if (gMC.x < (x * 0x10 + 8) * 0x200
		&& gMC.x > (x * 0x10 - 8) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 * 0x200) - ((gMC.x - x * 0x10 * 0x200) / 2) - 0x800
		&& gMC.y - gMC.hit.top < (y * 0x10 + 8) * 0x200)
	{
		//Clip
		gMC.y = (y * 0x10 * 0x200) - ((gMC.x - x * 0x10 * 0x200) / 2) - 0x800 - gMC.hit.bottom;
		
		//Halt momentum
		//if (gMC.ym > 0x400)
		//	PlaySoundObject(23, SOUND_MODE_PLAY);
		if (gMC.ym > 0)
			gMC.ym = 0;
		
		//Set that hit this slope
		hit |= 0x18;
	}
	
	return hit;
}

s32 JudgeHitMyCharWater(s32 x, s32 y)
{
	s32 hit = 0;
	if (gMC.x - gMC.hit.back < (x * 0x10 + 5) * 0x200
		&& gMC.x + gMC.hit.back > ((x * 0x10 - 5) * 0x200)
		&& gMC.y - gMC.hit.top < ((y * 0x10 + 5) * 0x200)
		&& gMC.y + gMC.hit.bottom > y * 0x10 * 0x200)
		hit |= 0x100;
	return hit;
}

s32 JudgeHitMyCharDamage(s32 x, s32 y)
{
	s32 hit = 0;
	if (gMC.x - 0x800 < (x * 0x10 + 4) * 0x200
		&& gMC.x + 0x800 > (x * 0x10 - 4) * 0x200
		&& gMC.y - 0x800 < (y * 0x10 + 3) * 0x200
		&& gMC.y + 0x800 > (y * 0x10 - 3) * 0x200)
		hit |= 0x400;
	return hit;
}

s32 JudgeHitMyCharDamageW(s32 x, s32 y)
{
	s32 hit = 0;
	if (gMC.x - 0x800 < (x * 0x10 + 4) * 0x200
		&& gMC.x + 0x800 > (x * 0x10 - 4) * 0x200
		&& gMC.y - 0x800 < (y * 0x10 + 3) * 0x200
		&& gMC.y + 0x800 > (y * 0x10 - 3) * 0x200)
		hit |= 0xD00;
	return hit;
}

s32 JudgeHitMyCharVectLeft(s32 x, s32 y)
{
	s32 hit = 0;
	if (gMC.x - gMC.hit.back < (x * 0x10 + 6) * 0x200
		&& gMC.x + gMC.hit.back > (x * 0x10 - 6) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 + 6) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 6) * 0x200)
		hit |= 0x1000;
	return hit;
}

s32 JudgeHitMyCharVectUp(s32 x, s32 y)
{
	s32 hit = 0;
	if (gMC.x - gMC.hit.back < (x * 0x10 + 6) * 0x200
		&& gMC.x + gMC.hit.back > (x * 0x10 - 6) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 + 6) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 6) * 0x200)
		hit |= 0x2000;
	return hit;
}

s32 JudgeHitMyCharVectRight(s32 x, s32 y)
{
	s32 hit = 0;
	if (gMC.x - gMC.hit.back < (x * 0x10 + 6) * 0x200
		&& gMC.x + gMC.hit.back > (x * 0x10 - 6) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 + 6) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 6) * 0x200)
		hit |= 0x4000;
	return hit;
}

s32 JudgeHitMyCharVectDown(s32 x, s32 y)
{
	s32 hit = 0;
	if (gMC.x - gMC.hit.back < (x * 0x10 + 6) * 0x200
		&& gMC.x + gMC.hit.back > (x * 0x10 - 6) * 0x200
		&& gMC.y - gMC.hit.top < (y * 0x10 + 6) * 0x200
		&& gMC.y + gMC.hit.bottom > (y * 0x10 - 6) * 0x200)
		hit |= 0x8000;
	return hit;
}

void HitMyCharMap()
{
	s32 x, y;
	u8 atrb;
	
	//Check tiles in the player's hitbox
	for (x = (gMC.x - gMC.hit.back + 0x1000) / 0x2000; x <= (gMC.x + gMC.hit.back + 0x1000) / 0x2000; x++)
	{
		for (y = (gMC.y - gMC.hit.top + 0x1000) / 0x2000; y <= (gMC.y + gMC.hit.bottom + 0x1000) / 0x2000; y++)
		{
			//Handle tile
			atrb = GetAttribute(x, y);
			
			switch (atrb)
			{
				//Block
				case 0x05:
				case 0x41:
				case 0x43:
				case 0x46:
					gMC.flag |= JudgeHitMyCharBlock(x, y);
					break;
					
				//Slopes
				case 0x50:
					gMC.flag |= JudgeHitMyCharTriangleA(x, y);
					break;
					
				case 0x51:
					gMC.flag |= JudgeHitMyCharTriangleB(x, y);
					break;
					
				case 0x52:
					gMC.flag |= JudgeHitMyCharTriangleC(x, y);
					break;
					
				case 0x53:
					gMC.flag |= JudgeHitMyCharTriangleD(x, y);
					break;
					
				case 0x54:
					gMC.flag |= JudgeHitMyCharTriangleE(x, y);
					break;
					
				case 0x55:
					gMC.flag |= JudgeHitMyCharTriangleF(x, y);
					break;
					
				case 0x56:
					gMC.flag |= JudgeHitMyCharTriangleG(x, y);
					break;
					
				case 0x57:
					gMC.flag |= JudgeHitMyCharTriangleH(x, y);
					break;
					
				//Spikes
				case 0x42:
					gMC.flag |= JudgeHitMyCharDamage(x, y);
					break;
					
				//Water spikes
				case 0x62:
					gMC.flag |= JudgeHitMyCharDamageW(x, y);
					break;
					
				//Wind
				case 0x80:
					gMC.flag |= JudgeHitMyCharVectLeft(x, y);
					break;
					
				case 0x81:
					gMC.flag |= JudgeHitMyCharVectUp(x, y);
					break;
					
				case 0x82:
					gMC.flag |= JudgeHitMyCharVectRight(x, y);
					break;
					
				case 0x83:
					gMC.flag |= JudgeHitMyCharVectDown(x, y);
					break;
					
				//Water
				case 0x02:
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				//Water and water blocks (same as the previous case)
				case 0x60:
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0x61:
					gMC.flag |= JudgeHitMyCharBlock(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				//Water slopes
				case 0x70:
					gMC.flag |= JudgeHitMyCharTriangleA(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0x71:
					gMC.flag |= JudgeHitMyCharTriangleB(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0x72:
					gMC.flag |= JudgeHitMyCharTriangleC(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0x73:
					gMC.flag |= JudgeHitMyCharTriangleD(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0x74:
					gMC.flag |= JudgeHitMyCharTriangleE(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0x75:
					gMC.flag |= JudgeHitMyCharTriangleF(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0x76:
					gMC.flag |= JudgeHitMyCharTriangleG(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0x77:
					gMC.flag |= JudgeHitMyCharTriangleH(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				//Water current
				case 0xA0:
					gMC.flag |= JudgeHitMyCharVectLeft(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0xA1:
					gMC.flag |= JudgeHitMyCharVectUp(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0xA2:
					gMC.flag |= JudgeHitMyCharVectRight(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
					
				case 0xA3:
					gMC.flag |= JudgeHitMyCharVectDown(x, y);
					gMC.flag |= JudgeHitMyCharWater(x, y);
					break;
			}
		}
	}
}

s32 JudgeHitMyCharNPC(NPCHAR *npc)
{
	s32 hit = 0;
	
	if (gMC.y - gMC.hit.top < npc->y + npc->hit.bottom - (3 * 0x200)
		&& gMC.y + gMC.hit.bottom > npc->y - npc->hit.top + (3 * 0x200)
		&& gMC.x - gMC.hit.back < npc->x + npc->hit.back
		&& gMC.x - gMC.hit.back > npc->x)
	{
		if (gMC.xm < 0x200)
			gMC.xm += 0x200;
		hit |= 1;
	}
	
	if (gMC.y - gMC.hit.top < npc->y + npc->hit.bottom - (3 * 0x200)
		&& gMC.y + gMC.hit.bottom > npc->y - npc->hit.top + (3 * 0x200)
		&& gMC.x + gMC.hit.back - 0x200 > npc->x - npc->hit.back
		&& gMC.x + gMC.hit.back - 0x200 < npc->x)
	{
		if (gMC.xm > -0x200)
			gMC.xm -= 0x200;
		hit |= 4;
	}
	
	if (gMC.x - gMC.hit.back < npc->x + npc->hit.back - (3 * 0x200)
		&& gMC.x + gMC.hit.back > npc->x - npc->hit.back + (3 * 0x200)
		&& gMC.y - gMC.hit.top < npc->y + npc->hit.bottom
		&& gMC.y - gMC.hit.top > npc->y)
	{
		if (gMC.ym < 0)
			gMC.ym = 0;
		hit |= 2;
	}
	
	if (gMC.x - gMC.hit.back < npc->x + npc->hit.back - (3 * 0x200)
		&& gMC.x + gMC.hit.back > npc->x - npc->hit.back + (3 * 0x200)
		&& gMC.y + gMC.hit.bottom > npc->y - npc->hit.top
		&& gMC.hit.bottom + gMC.y < npc->y + (3 * 0x200))
	{
		if (npc->bits & NPC_BOUNCY)
		{
			gMC.ym = npc->ym - 0x200;
			hit |= 8;
		}
		else if (!(gMC.flag & 8) && gMC.ym > npc->ym)
		{
			gMC.y = npc->y - npc->hit.top - gMC.hit.bottom + 0x200;
			gMC.ym = npc->ym;
			gMC.x += npc->xm;
			hit |= 8;
		}
	}
	
	return hit;
}

u8 JudgeHitMyCharNPC3(NPCHAR *npc)
{
	if (npc->direct == 0)
	{
		if (gMC.x + (2 * 0x200) > npc->x - npc->hit.front
			&& gMC.x - (2 * 0x200) < npc->x + npc->hit.back
			&& gMC.y + (2 * 0x200) > npc->y - npc->hit.top
			&& gMC.y - (2 * 0x200) < npc->y + npc->hit.bottom)
			return 1;
	}
	else
	{
		if (gMC.x + (2 * 0x200) > npc->x - npc->hit.back
			&& gMC.x - (2 * 0x200) < npc->x + npc->hit.front
			&& gMC.y + (2 * 0x200) > npc->y - npc->hit.top
			&& gMC.y - (2 * 0x200) < npc->y + npc->hit.bottom)
			return 1;
	}
	return 0;
}

s32 JudgeHitMyCharNPC4(NPCHAR *npc)
{
	s32 hit = 0;
	
	f32 fy1;
	f32 fx1;
	f32 fx2;
	f32 fy2;
	
	if (npc->x > gMC.x)
		fx1 = (f32)(npc->x - gMC.x);
	else
		fx1 = (f32)(gMC.x - npc->x);
	
	if (npc->y > gMC.y)
		fy1 = (f32)(npc->y - gMC.y);
	else
		fy1 = (f32)(gMC.y - npc->y);
	
	fx2 = (f32)npc->hit.back;
	fy2 = (f32)npc->hit.top;
	
	if (fx1 == 0.0f)
		fx1 = 1.0f;
	if (fx2 == 0.0f)
		fx2 = 1.0f;
	
	if (fy1 / fx1 > fy2 / fx2)
	{
		if (gMC.x - gMC.hit.back < npc->x + npc->hit.back && gMC.x + gMC.hit.back > npc->x - npc->hit.back)
		{
			if (gMC.y - gMC.hit.top < npc->y + npc->hit.bottom && gMC.y - gMC.hit.top > npc->y)
			{
				if (gMC.ym < npc->ym)
				{
					gMC.y = npc->y + npc->hit.bottom + gMC.hit.top + 0x200;
					gMC.ym = npc->ym;
				}
				else
				{
					if (gMC.ym < 0)
						gMC.ym = 0;
				}
				hit |= 2;
			}
			
			if (gMC.y + gMC.hit.bottom > npc->y - npc->hit.top && gMC.hit.bottom + gMC.y < npc->y + (3 * 0x200))
			{
				//if (gMC.ym - npc->ym > 2 * 0x200)
				//	PlaySoundObject(23, SOUND_MODE_PLAY);
				
				if (gMC.unit == 1)
				{
					gMC.y = npc->y - npc->hit.top - gMC.hit.bottom + 0x200;
					hit |= 8;
				}
				else if (npc->bits & NPC_BOUNCY)
				{
					gMC.ym = npc->ym - 0x200;
					hit |= 8;
				}
				else if (!(gMC.flag & 8) && gMC.ym > npc->ym)
				{
					gMC.y = npc->y - npc->hit.top - gMC.hit.bottom + 0x200;
					gMC.ym = npc->ym;
					gMC.x += npc->xm;
					hit |= 8;
				}
			}
		}
	}
	else
	{
		if (gMC.y - gMC.hit.top < npc->y + npc->hit.bottom && gMC.y + gMC.hit.bottom > npc->y - npc->hit.top)
		{
			if (gMC.x - gMC.hit.back < npc->x + npc->hit.back && gMC.x - gMC.hit.back > npc->x)
			{
				if (gMC.xm < npc->xm)
					gMC.xm = npc->xm;
				gMC.x = npc->x + npc->hit.back + gMC.hit.back;
				hit |= 1;
			}
			
			if (gMC.x + gMC.hit.back > npc->x - npc->hit.back && gMC.hit.back + gMC.x < npc->x)
			{
				if (gMC.xm > npc->xm)
					gMC.xm = npc->xm;
				gMC.x = npc->x - npc->hit.back - gMC.hit.back;
				hit |= 4;
			}
		}
	}
	
	return hit;
}

void HitMyCharNpChar()
{
	s32 i;
	s32 hit = 0;
	
	if (!(gMC.cond & 0x80) || gMC.cond & 2)
		return;
	
	for (i = 0; i < NPC_MAX; ++i)
	{
		if (!(gNPC[i].cond & 0x80))
			continue;
		
		hit = 0;
		
		if (gNPC[i].bits & NPC_SOLID_SOFT)
		{
			hit = JudgeHitMyCharNPC(&gNPC[i]);
			gMC.flag |= hit;
		}
		else if (gNPC[i].bits & NPC_SOLID_HARD)
		{
			hit = JudgeHitMyCharNPC4(&gNPC[i]);
			gMC.flag |= hit;
		}
		else
		{
			hit = JudgeHitMyCharNPC3(&gNPC[i]);
		}
		
		//Special NPCs (pickups)
		if (hit != 0 && gNPC[i].code_char == 1)
		{
			//PlaySoundObject(14, SOUND_MODE_PLAY);
			//AddExpMyChar(gNPC[i].exp);
			gNPC[i].cond = 0;
		}
		
		if (hit != 0 && gNPC[i].code_char == 86)
		{
			//PlaySoundObject(42, SOUND_MODE_PLAY);
			//AddBulletMyChar(gNPC[i].code_event, gNPC[i].exp);
			gNPC[i].cond = 0;
		}
		
		if (hit != 0 && gNPC[i].code_char == 87)
		{
			//PlaySoundObject(20, SOUND_MODE_PLAY);
			AddLifeMyChar(gNPC[i].exp);
			gNPC[i].cond = 0;
		}
		
		//Run event on contact
		if (!(g_GameFlags & 4) && hit != 0 && gNPC[i].bits & NPC_EVENT_WHEN_TOUCHED)
			StartTextScript(gNPC[i].code_event);
		
		//NPC damage
		if (g_GameFlags & 2 && !(gNPC[i].bits & NPC_INTERACTABLE))
		{
			if (gNPC[i].bits & NPC_REAR_AND_TOP_DONT_HURT)
			{
				if (hit & 4 && gNPC[i].xm < 0)
					DamageMyChar(gNPC[i].damage);
				if (hit & 1 && gNPC[i].xm > 0)
					DamageMyChar(gNPC[i].damage);
				if (hit & 8 && gNPC[i].ym < 0)
					DamageMyChar(gNPC[i].damage);
				if (hit & 2 && gNPC[i].ym > 0)
					DamageMyChar(gNPC[i].damage);
			}
			else if (hit != 0 && gNPC[i].damage && !(g_GameFlags & 4))
			{
				DamageMyChar(gNPC[i].damage);
			}
		}
		
		//Interaction
		if (!(g_GameFlags & 4) && hit != 0 && gMC.cond & 1 && gNPC[i].bits & NPC_INTERACTABLE)
		{
			StartTextScript(gNPC[i].code_event);
			gMC.xm = 0;
			gMC.ques = FALSE;
		}
	}
	
	//Create question mark when NPC hasn't been interacted with
	if (gMC.ques)
		SetCaret(gMC.x, gMC.y, CARET_QUESTION_MARK, 0);
}
