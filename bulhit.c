#include "bulhit.h"
#include "bullet.h"
#include "caret.h"
#include "npchar.h"
#include "map.h"
#include "sound.h"

static void Vanish(BULLET *bul)
{
	if (bul->code_bullet != 37 && bul->code_bullet != 38 && bul->code_bullet != 39)
		PlaySoundObject(28, 1);
	else
		SetCaret(bul->x, bul->y, 2, 1);
	
	bul->cond = 0;
	SetCaret(bul->x, bul->y, 2, 2);
}

s32 JudgeHitBulletBlock(s32 x, s32 y, BULLET *bul)
{
	s32 i;
	s32 hit = 0;
	if (bul->x - bul->blockXL < ((x * 16) + 8) * 0x200
		&& bul->x + bul->blockXL > ((x * 16) - 8) * 0x200
		&& bul->y - bul->blockYL < ((y * 16) + 8) * 0x200
		&& bul->y + bul->blockYL > ((y * 16) - 8) * 0x200)
		hit |= 0x200;
	
	if (hit && bul->bbits & 0x60 && GetAttribute(x, y) == 0x43)
	{
		if (!(bul->bbits & 0x40))
			bul->cond = 0;
		
		SetCaret(bul->x, bul->y, 2, 0);
		PlaySoundObject(12, 1);
		
		for (i = 0; i < 4; i++)
			SetNpChar(4, x * 0x200 * 0x10, y * 0x200 * 0x10, Random(-0x200, 0x200), Random(-0x200, 0x200), 0, NULL, 0x100);
		
		ShiftMapParts(x, y);
	}
	
	return hit;
}

s32 JudgeHitBulletBlock2(s32 x, s32 y, unsigned char *atrb, BULLET *bul)
{
	BOOL block[4];
	s32 workX, workY;
	s32 hit, i;
	
	hit = 0;
	
	if (bul->bbits & 0x40)
	{
		for (i = 0; i < 4; i++)
		{
			if (*atrb == 0x41 || *atrb == 0x61)
				block[i] = TRUE;
			else
				block[i] = FALSE;
			atrb++;
		}
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			if (*atrb == 0x41 || *atrb == 0x43 || *atrb == 0x61)
				block[i] = TRUE;
			else
				block[i] = FALSE;
			atrb++;
		}
	}
	
	workX = ((x * 16) + 8) * 0x200;
	workY = ((y * 16) + 8) * 0x200;
	
	//Left wall
	if (block[0] && block[2])
	{
		if (bul->x - bul->blockXL < workX)
			hit |= 1;
	}
	else if (block[0] && !block[2])
	{
		if (bul->x - bul->blockXL < workX && bul->y - bul->blockYL < workY - (3 * 0x200))
			hit |= 1;
	}
	else if (!block[0] && block[2])
	{
		if (bul->x - bul->blockXL < workX && bul->y + bul->blockYL > workY + (3 * 0x200))
			hit |= 1;
	}
	
	//Right wall
	if (block[1] && block[3])
	{
		if (bul->x + bul->blockXL > workX)
			hit |= 4;
	}
	else if (block[1] && !block[3])
	{
		if (bul->x + bul->blockXL > workX && bul->y - bul->blockYL < workY - (3 * 0x200))
			hit |= 4;
	}
	else if (!block[1] && block[3])
	{
		if (bul->x + bul->blockXL > workX && bul->y + bul->blockYL > workY + (3 * 0x200))
			hit |= 4;
	}
	
	//Ceiling
	if (block[0] && block[1])
	{
		if (bul->y - bul->blockYL < workY)
			hit |= 2;
	}
	else if (block[0] && !block[1])
	{
		if (bul->y - bul->blockYL < workY && bul->x - bul->blockXL < workX - (3 * 0x200))
			hit |= 2;
	}
	else if (!block[0] && block[1])
	{
		if (bul->y - bul->blockYL < workY && bul->x + bul->blockXL > workX + (3 * 0x200))
			hit |= 2;
	}
	
	//Ground
	if (block[2] && block[3])
	{
		if (bul->y + bul->blockYL > workY)
			hit |= 8;
	}
	else if (block[2] && !block[3])
	{
		if (bul->y + bul->blockYL > workY && bul->x - bul->blockXL < workX - (3 * 0x200))
			hit |= 8;
	}
	else if (!block[2] && block[3])
	{
		if (bul->y + bul->blockYL > workY && bul->x + bul->blockXL > workX + (3 * 0x200))
			hit |= 8;
	}
	
	//Clip
	if (bul->bbits & 8)
	{
		if (hit & 1)
			bul->x = workX + bul->blockXL;
		else if (hit & 4)
			bul->x = workX - bul->blockXL;
		else if (hit & 2)
			bul->y = workY + bul->blockYL;
		else if (hit & 8)
			bul->y = workY - bul->blockYL;
	}
	else
	{
		if (hit & 0xF)
			Vanish(bul);
	}
	
	return hit;
}

s32 JudgeHitBulletTriangleA(s32 x, s32 y, BULLET *bul)
{
	s32 hit = 0;
	if (bul->x < ((x * 16) + 8) * 0x200
		&& bul->x > ((x * 16) - 8) * 0x200
		&& bul->y - (2 * 0x200) < ((y * 16) * 0x200) - ((bul->x - ((x * 16) * 0x200)) / 2) + (4 * 0x200)
		&& bul->y + (2 * 0x200) > ((y * 16) - 8) * 0x200)
	{
		if (bul->bbits & 8)
			bul->y = ((y * 16) * 0x200) - ((bul->x - ((x * 16) * 0x200)) / 2) + (6 * 0x200);
		else
			Vanish(bul);
		hit |= 0x82;
	}
	return hit;
}

s32 JudgeHitBulletTriangleB(s32 x, s32 y, BULLET *bul)
{
	s32 hit = 0;
	if (bul->x < ((x * 16) + 8) * 0x200
		&& bul->x > ((x * 16) - 8) * 0x200
		&& bul->y - (2 * 0x200) < ((y * 16) * 0x200) - ((bul->x - ((x * 16) * 0x200)) / 2) - (4 * 0x200)
		&& bul->y + (2 * 0x200) > ((y * 16) - 8) * 0x200)
	{
		if (bul->bbits & 8)
			bul->y = ((y * 16) * 0x200) - ((bul->x - ((x * 16) * 0x200)) / 2) - (2 * 0x200);
		else
			Vanish(bul);
		hit |= 0x82;
	}
	return hit;
}

s32 JudgeHitBulletTriangleC(s32 x, s32 y, BULLET *bul)
{
	s32 hit = 0;
	if (bul->x < ((x * 16) + 8) * 0x200
		&& bul->x > ((x * 16) - 8) * 0x200
		&& bul->y - (2 * 0x200) < ((y * 16) * 0x200) + ((bul->x - ((x * 16) * 0x200)) / 2) - (4 * 0x200)
		&& bul->y + (2 * 0x200) > ((y * 16) - 8) * 0x200)
	{
		if (bul->bbits & 8)
			bul->y = ((y * 16) * 0x200) + ((bul->x - ((x * 16) * 0x200)) / 2) - (2 * 0x200);
		else
			Vanish(bul);
		hit |= 0x42;
	}
	return hit;
}

s32 JudgeHitBulletTriangleD(s32 x, s32 y, BULLET *bul)
{
	s32 hit = 0;
	if (bul->x < ((x * 16) + 8) * 0x200
		&& bul->x > ((x * 16) - 8) * 0x200
		&& bul->y - (2 * 0x200) < ((y * 16) * 0x200) + ((bul->x - ((x * 16) * 0x200)) / 2) + (4 * 0x200)
		&& bul->y + (2 * 0x200) > ((y * 16) - 8) * 0x200)
	{
		if (bul->bbits & 8)
			bul->y = ((y * 16) * 0x200) + ((bul->x - ((x * 16) * 0x200)) / 2) + (6 * 0x200);
		else
			Vanish(bul);
		hit |= 0x42;
	}
	return hit;
}

s32 JudgeHitBulletTriangleE(s32 x, s32 y, BULLET *bul)
{
	s32 hit = 0;
	if (bul->x < ((x * 16) + 8) * 0x200
		&& bul->x - (1 * 0x200) > ((x * 16) - 8) * 0x200
		&& bul->y + (2 * 0x200) > ((y * 16) * 0x200) + ((bul->x - ((x * 16) * 0x200)) / 2) - (4 * 0x200)
		&& bul->y - (2 * 0x200) < ((y * 16) + 8) * 0x200)
	{
		if (bul->bbits & 8)
			bul->y = ((y * 16) * 0x200) + ((bul->x - ((x * 16) * 0x200)) / 2) - (6 * 0x200);
		else
			Vanish(bul);
		hit |= 0x28;
	}
	return hit;
}

s32 JudgeHitBulletTriangleF(s32 x, s32 y, BULLET *bul)
{
	s32 hit = 0;
	if (bul->x < ((x * 16) + 8) * 0x200
		&& bul->x > ((x * 16) - 8) * 0x200
		&& bul->y + (2 * 0x200) > ((y * 16) * 0x200) + ((bul->x - ((x * 16) * 0x200)) / 2) + (4 * 0x200)
		&& bul->y - (2 * 0x200) < ((y * 16) + 8) * 0x200)
	{
		if (bul->bbits & 8)
			bul->y = ((y * 16) * 0x200) + ((bul->x - ((x * 16) * 0x200)) / 2) + (2 * 0x200);
		else
			Vanish(bul);
		hit |= 0x28;
	}
	return hit;
}

s32 JudgeHitBulletTriangleG(s32 x, s32 y, BULLET *bul)
{
	s32 hit = 0;
	if (bul->x < ((x * 16) + 8) * 0x200
		&& bul->x > ((x * 16) - 8) * 0x200
		&& bul->y + (2 * 0x200) > ((y * 16) * 0x200) - ((bul->x - ((x * 16) * 0x200)) / 2) + (4 * 0x200)
		&& bul->y - (2 * 0x200) < ((y * 16) + 8) * 0x200)
	{
		if (bul->bbits & 8)
			bul->y = ((y * 16) * 0x200) - ((bul->x - ((x * 16) * 0x200)) / 2) + (2 * 0x200);
		else
			Vanish(bul);
		hit |= 0x18;
	}
	return hit;
}

s32 JudgeHitBulletTriangleH(s32 x, s32 y, BULLET *bul)
{
	s32 hit = 0;
	if (bul->x < ((x * 16) + 8) * 0x200
		&& bul->x > ((x * 16) - 8) * 0x200
		&& bul->y + (2 * 0x200) > ((y * 16) * 0x200) - ((bul->x - ((x * 16) * 0x200)) / 2) - (4 * 0x200)
		&& bul->y - (2 * 0x200) < ((y * 16) + 8) * 0x200)
	{
		if (bul->bbits & 8)
			bul->y = ((y * 16) * 0x200) - ((bul->x - ((x * 16) * 0x200)) / 2) - (6 * 0x200);
		else
			Vanish(bul);
		hit |= 0x18;
	}
	return hit;
}

void HitBulletMap()
{
	s32 i, j, x, y;
	u8 atrb[4];
	static const s32 offx[4] = {0, 1, 0, 1};
	static const s32 offy[4] = {0, 0, 1, 1};
	
	for (i = 0; i < BULLET_MAX; i++)
	{
		if (!(gBul[i].cond & 0x80))
			continue;
		
		x = gBul[i].x / 0x10 / 0x200;
		y = gBul[i].y / 0x10 / 0x200;
		
		//Get surrounding tiles
		atrb[0] = GetAttribute(x,     y);
		atrb[1] = GetAttribute(x + 1, y);
		atrb[2] = GetAttribute(x,     y + 1);
		atrb[3] = GetAttribute(x + 1, y + 1);
		
		//Clear flag
		gBul[i].flag = 0;
		
		if (!(gBul[i].bbits & 4))
		{
			for (j = 0; j < 4; j++)
			{
				if (!(gBul[i].cond & 0x80))
					continue;
				
				switch (atrb[j])
				{
					case 0x41:
					case 0x43:
					case 0x44:
					case 0x61:
					case 0x64:
						gBul[i].flag |= JudgeHitBulletBlock(x + offx[j], y + offy[j], &gBul[i]);
						break;
						
					case 0x50:
					case 0x70:
						gBul[i].flag |= JudgeHitBulletTriangleA(x + offx[j], y + offy[j], &gBul[i]);
						break;
						
					case 0x51:
					case 0x71:
						gBul[i].flag |= JudgeHitBulletTriangleB(x + offx[j], y + offy[j], &gBul[i]);
						break;
						
					case 0x52:
					case 0x72:
						gBul[i].flag |= JudgeHitBulletTriangleC(x + offx[j], y + offy[j], &gBul[i]);
						break;
						
					case 0x53:
					case 0x73:
						gBul[i].flag |= JudgeHitBulletTriangleD(x + offx[j], y + offy[j], &gBul[i]);
						break;
						
					case 0x54:
					case 0x74:
						gBul[i].flag |= JudgeHitBulletTriangleE(x + offx[j], y + offy[j], &gBul[i]);
						break;
						
					case 0x55:
					case 0x75:
						gBul[i].flag |= JudgeHitBulletTriangleF(x + offx[j], y + offy[j], &gBul[i]);
						break;
						
					case 0x56:
					case 0x76:
						gBul[i].flag |= JudgeHitBulletTriangleG(x + offx[j], y + offy[j], &gBul[i]);
						break;
						
					case 0x57:
					case 0x77:
						gBul[i].flag |= JudgeHitBulletTriangleH(x + offx[j], y + offy[j], &gBul[i]);
						break;
				}
			}
			
			gBul[i].flag |= JudgeHitBulletBlock2(x, y, atrb, &gBul[i]);
		}
	}
}
