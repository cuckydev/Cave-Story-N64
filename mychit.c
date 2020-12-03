#include "mychit.h"
#include "mychar.h"
#include "keycontrol.h"
#include "map.h"

void ResetMyCharFlag()
{
	gMC.flag = 0;
}

static void PutlittleStar()
{
	if (!(gMC.cond & 2) && gMC.ym < -0x200)
	{
		//PlaySoundObject(3, SOUND_MODE_PLAY);
		//SetCaret(gMC.x, gMC.y - gMC.hit.top, CARET_TINY_PARTICLES, DIR_LEFT);
		//SetCaret(gMC.x, gMC.y - gMC.hit.top, CARET_TINY_PARTICLES, DIR_LEFT);
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
