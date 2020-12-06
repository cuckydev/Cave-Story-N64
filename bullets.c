#include "bullets.h"
#include "caret.h"
#include "draw.h"

//Polar Star
#include "data/bitmap/bullet_polarstar.inc.c"

void Bullet_PoleStar_Act(BULLET *bul, s32 level)
{
	if (++bul->count1 > bul->life_count)
	{
		bul->cond = 0;
		SetCaret(bul->x, bul->y, 3, 0);
		return;
	}
	
	if (bul->act_no == 0)
	{
		bul->act_no = 1;
		
		//Set speed
		switch (bul->direct)
		{
			case 0:
				bul->xm = -0x1000;
				break;
			case 1:
				bul->ym = -0x1000;
				break;
			case 2:
				bul->xm = 0x1000;
				break;
			case 3:
				bul->ym = 0x1000;
				break;
		}
		
		//Set hitbox
		switch (level)
		{
			case 1:
				switch (bul->direct)
				{
					case 0:
						bul->enemyYL = 0x400;
						break;
					case 1:
						bul->enemyXL = 0x400;
						break;
					case 2:
						bul->enemyYL = 0x400;
						break;
					case 3:
						bul->enemyXL = 0x400;
						break;
				}
				break;
			case 2:
				switch (bul->direct)
				{
					case 0:
						bul->enemyYL = 0x800;
						break;
					case 1:
						bul->enemyXL = 0x800;
						break;
					case 2:
						bul->enemyYL = 0x800;
						break;
					case 3:
						bul->enemyXL = 0x800;
						break;
				}
				break;
		}
	}
	else
	{
		//Move
		bul->x += bul->xm;
		bul->y += bul->ym;
	}
}

void Bullet_PoleStar_Put(BULLET *bul, s32 level, s32 x, s32 y)
{
	static const RECT rect[3][2] = {
		{
			{ 0, 0, 16, 16},
			{16, 0, 32, 16},
		},
		{
			{32, 0, 48, 16},
			{48, 0, 64, 16},
		},
		{
			{ 0, 16, 16, 32},
			{16, 16, 32, 32},
		},
	};
	
	LoadTLUT_CI4(bullet_polarstar_tlut);
	LoadTex_CI4(64, 32, bullet_polarstar_tex);
	PutBitmap(&rect[level - 1][bul->direct == 1 || bul->direct == 3], x, y);
}
