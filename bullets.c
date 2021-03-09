#include "bullets.h"
#include "caret.h"
#include "mychar.h"
#include "npchar.h"
#include "draw.h"
#include "sound.h"

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

//Fireball
#include "data/bitmap/bullet_fireball.inc.c"

void Bullet_FireBall_Act(BULLET *bul, s32 level)
{
	//Move
	BOOL bBreak;
	
	if (++bul->count1 > bul->life_count)
	{
		bul->cond = 0;
		SetCaret(bul->x, bul->y, 3, 0);
		return;
	}
	
	bBreak = FALSE;
	if (bul->flag & 2 && bul->flag & 8)
		bBreak = TRUE;
	if (bul->flag & 1 && bul->flag & 4)
		bBreak = TRUE;
	
	if (bul->direct == 0 && bul->flag & 1)
		bul->direct = 2;
	if (bul->direct == 2 && bul->flag & 4)
		bul->direct = 0;
	
	if (bBreak)
	{
		bul->cond = 0;
		SetCaret(bul->x, bul->y, 2, 0);
		PlaySoundObject(28, 1);
		return;
	}
	
	if (bul->act_no == 0)
	{
		bul->act_no = 1;
		
		switch (bul->direct)
		{
			case 0:
				bul->xm = -0x400;
				break;
				
			case 1:
				bul->xm = gMC.xm;
				
				if (gMC.xm < 0)
					bul->direct = 0;
				else
					bul->direct = 2;
				
				if (gMC.direct == 0)
					bul->xm -= 0x80;
				else
					bul->xm += 0x80;
				bul->ym = -0x5FF;
				break;
				
			case 2:
				bul->xm = 0x400;
				break;
				
			case 3:
				bul->xm = gMC.xm;
				
				if (gMC.xm < 0)
					bul->direct = 0;
				else
					bul->direct = 2;
				
				bul->ym = 0x5FF;
				break;
		}
	}
	else
	{
		if (bul->flag & 8)
			bul->ym = -0x400;
		else if (bul->flag & 1)
			bul->xm = 0x400;
		else if (bul->flag & 4)
			bul->xm = -0x400;
		
		bul->ym += 85;
		if (bul->ym > 0x3FF)
			bul->ym = 0x3FF;
		
		bul->x += bul->xm;
		bul->y += bul->ym;
		
		if (bul->flag & 0xD)
			PlaySoundObject(34, 1);
	}
	
	//Animation
	bul->ani_no++;
	
	if (level == 1)
	{
		if (bul->ani_no > 3)
			bul->ani_no = 0;
	}
	else
	{
		if (bul->ani_no > 2)
			bul->ani_no = 0;
		
		if (level == 2)
			SetNpChar(129, bul->x, bul->y, 0, -0x200, bul->ani_no, NULL, 0x100);
		else
			SetNpChar(129, bul->x, bul->y, 0, -0x200, bul->ani_no + 3, NULL, 0x100);
	}
}

void Bullet_FireBall_Put(BULLET *bul, s32 level, s32 x, s32 y)
{
	static const RECT rect1[2][4] = {
		{
			{ 0, 0, 16, 16},
			{16, 0, 32, 16},
			{32, 0, 48, 16},
			{48, 0, 64, 16},
		},
		{
			{ 0, 16, 16, 32},
			{16, 16, 32, 32},
			{32, 16, 48, 32},
			{48, 16, 64, 32},
		}
	};
	
	static const RECT rect2[2][3] = {
		{
			{64, 16,  80, 32},
			{80, 16,  96, 32},
			{96, 16, 112, 32},
		},
		{
			{96, 16, 112, 32},
			{80, 16,  96, 32},
			{64, 16,  80, 32},
		},
	};
	
	LoadTLUT_CI4(bullet_fireball_tlut);
	LoadTex_CI4(112, 32, bullet_fireball_tex);
	if (level == 1)
		PutBitmap(&rect1[bul->direct != 0][bul->ani_no], x, y);
	else
		PutBitmap(&rect2[bul->direct != 0][bul->ani_no], x, y);
}

//Missile Launcher
#include "data/bitmap/bullet_missilelauncher.inc.c"

void Bullet_MissileLauncher_Act(BULLET *bul, s32 level)
{
	BOOL bHit;
	static u32 inc;
	
	if (++bul->count1 > bul->life_count)
	{
		bul->cond = 0;
		SetCaret(bul->x, bul->y, 3, 0);
		return;
	}
	
	bHit = FALSE;
	
	if (bul->life != 10)
		bHit = TRUE;
	if (bul->direct == 0 && bul->flag & 1)
		bHit = TRUE;
	if (bul->direct == 2 && bul->flag & 4)
		bHit = TRUE;
	if (bul->direct == 1 && bul->flag & 2)
		bHit = TRUE;
	if (bul->direct == 3 && bul->flag & 8)
		bHit = TRUE;
	if (bul->direct == 0 && bul->flag & 0x80)
		bHit = TRUE;
	if (bul->direct == 0 && bul->flag & 0x20)
		bHit = TRUE;
	if (bul->direct == 2 && bul->flag & 0x40)
		bHit = TRUE;
	if (bul->direct == 2 && bul->flag & 0x10)
		bHit = TRUE;
	
	if (bHit)
	{
		SetBullet(level + 15, bul->x, bul->y, 0);
		bul->cond = 0;
	}
	
	switch (bul->act_no)
	{
		case 0:
			bul->act_no = 1;
			
			switch (bul->direct)
			{
				case 0:
				case 2:
					bul->tgt_y = bul->y;
					break;
				case 1:
				case 3:
					bul->tgt_x = bul->x;
					break;
			}
			
			if (level == 3)
			{
				switch (bul->direct)
				{
					case 0:
					case 2:
						if (bul->y > gMC.y)
							bul->ym = 0x100;
						else
							bul->ym = -0x100;
						bul->xm = Random(-0x200, 0x200);
						break;
						
					case 1:
					case 3:
						if (bul->x > gMC.x)
							bul->xm = 0x100;
						else
							bul->xm = -0x100;
						bul->ym = Random(-0x200, 0x200);
						break;
				}
				
				switch (++inc % 3)
				{
					case 0:
						bul->ani_no = 0x80;
						break;
					case 1:
						bul->ani_no = 0x40;
						break;
					case 2:
						bul->ani_no = 0x33;
						break;
				}
			}
			else
			{
				bul->ani_no = 0x80;
			}
			//Fallthrough
		case 1:
			switch (bul->direct)
			{
				case 0:
					bul->xm += -bul->ani_no;
					break;
				case 1:
					bul->ym += -bul->ani_no;
					break;
				case 2:
					bul->xm += bul->ani_no;
					break;
				case 3:
					bul->ym += bul->ani_no;
					break;
			}
			
			if (level == 3)
			{
				switch (bul->direct)
				{
					case 0:
					case 2:
						if (bul->y < bul->tgt_y)
							bul->ym += 0x20;
						else
							bul->ym -= 0x20;
						break;
						
					case 1:
					case 3:
						if (bul->x < bul->tgt_x)
							bul->xm += 0x20;
						else
							bul->xm -= 0x20;
						break;
				}
			}
			
			if (bul->xm < -0xA00)
				bul->xm = -0xA00;
			if (bul->xm > 0xA00)
				bul->xm = 0xA00;
			if (bul->ym < -0xA00)
				bul->ym = -0xA00;
			if (bul->ym > 0xA00)
				bul->ym = 0xA00;
			
			bul->x += bul->xm;
			bul->y += bul->ym;
			break;
	}
	
	if (++bul->count2 > 2)
	{
		bul->count2 = 0;
		switch (bul->direct)
		{
			case 0:
				SetCaret(bul->x + (8 * 0x200), bul->y, 7, 2);
				break;
			case 1:
				SetCaret(bul->x, bul->y + (8 * 0x200), 7, 3);
				break;
			case 2:
				SetCaret(bul->x - (8 * 0x200), bul->y, 7, 0);
				break;
			case 3:
				SetCaret(bul->x, bul->y - (8 * 0x200), 7, 1);
				break;
		}
	}
}

void Bullet_MissileLauncher_Put(BULLET *bul, s32 level, s32 x, s32 y)
{
	static const RECT rect[3][4] = {
		{
			{0, 0, 16, 16},
			{16, 0, 32, 16},
			{32, 0, 48, 16},
			{48, 0, 64, 16},
		},
		{
			{0, 16, 16, 32},
			{16, 16, 32, 32},
			{32, 16, 48, 32},
			{48, 16, 64, 32},
		},
		{
			{0, 32, 16, 48},
			{16, 32, 32, 48},
			{32, 32, 48, 48},
			{48, 32, 64, 48},
		}
	};
	
	LoadTLUT_CI4(bullet_missilelauncher_tlut);
	LoadTex_CI4(64, 48, bullet_missilelauncher_tex);
	PutBitmap(&rect[level - 1][bul->direct], x, y);
}

//Missile Launcher explosion
void Bullet_Bom_Act(BULLET *bul, s32 level)
{
	switch (bul->act_no)
	{
		case 0:
			bul->act_no = 1;
			
			switch (level)
			{
				case 1:
					bul->act_wait = 10;
					break;
				case 2:
					bul->act_wait = 15;
					break;
				case 3:
					bul->act_wait = 5;
					break;
			}
			
			PlaySoundObject(44, 1);
			//Fallthrough
		case 1:
			switch (level)
			{
				case 1:
					if (bul->act_wait % 3 == 0)
						SetDestroyNpCharUp(bul->x + (Random(-16, 16) * 0x200), bul->y + (Random(-16, 16) * 0x200), bul->enemyXL, 2);
					break;
				case 2:
					if (bul->act_wait % 3 == 0)
						SetDestroyNpCharUp(bul->x + (Random(-32, 32) * 0x200), bul->y + (Random(-32, 32) * 0x200), bul->enemyXL, 2);
					break;
				case 3:
					if (bul->act_wait % 3 == 0)
						SetDestroyNpCharUp(bul->x + (Random(-40, 40) * 0x200), bul->y + (Random(-40, 40) * 0x200), bul->enemyXL, 2);
					break;
			}
			
			if (--bul->act_wait < 0)
				bul->cond = 0;
			break;
	}
}
