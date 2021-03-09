#include "bullet.h"
#include "bullets.h"
#include <string.h>

//Bullet structure
BULLET gBul[BULLET_MAX];

//Bullet tables
static const BULLET_TABLE gBulTbl[46] = {
	//Null
	{0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0}},
	//Snake
	{4, 1, 20, 36, 4, 4, 2, 2, {8, 8, 8, 8}},
	{6, 1, 23, 36, 4, 4, 2, 2, {8, 8, 8, 8}},
	{8, 1, 30, 36, 4, 4, 2, 2, {8, 8, 8, 8}},
	//Polar Star
	{1, 1, 8, 32, 6, 6, 2, 2, {8, 8, 8, 8}},
	{2, 1, 12, 32, 6, 6, 2, 2, {8, 8, 8, 8}},
	{4, 1, 16, 32, 6, 6, 2, 2, {8, 8, 8, 8}},
	//Fireball
	{2, 2, 100, 8, 8, 16, 4, 2, {8, 8, 8, 8}},
	{3, 2, 100, 8, 4, 4, 4, 2, {8, 8, 8, 8}},
	{3, 2, 100, 8, 4, 4, 4, 2, {8, 8, 8, 8}},
	//Machine Gun
	{2, 1, 20, 32, 2, 2, 2, 2, {8, 8, 8, 8}},
	{4, 1, 20, 32, 2, 2, 2, 2, {8, 8, 8, 8}},
	{6, 1, 20, 32, 2, 2, 2, 2, {8, 8, 8, 8}},
	//Missile Launcher
	{0, 10, 50, 40, 2, 2, 2, 2, {8, 8, 8, 8}},
	{0, 10, 70, 40, 4, 4, 4, 4, {8, 8, 8, 8}},
	{0, 10, 90, 40, 4, 4, 0, 0, {8, 8, 8, 8}},
	//Missile Launcher explosion
	{1, 100, 100, 20, 16, 16, 0, 0, {0, 0, 0, 0}},
	{1, 100, 100, 20, 16, 16, 0, 0, {0, 0, 0, 0}},
	{1, 100, 100, 20, 16, 16, 0, 0, {0, 0, 0, 0}},
	//Bubbline
	{1, 1, 20, 8, 2, 2, 2, 2, {4, 4, 4, 4}},
	{2, 1, 20, 8, 2, 2, 2, 2, {4, 4, 4, 4}},
	{2, 1, 20, 8, 4, 4, 4, 4, {4, 4, 4, 4}},
	//Bubbline level 3 thorns
	{3, 1, 32, 32, 2, 2, 2, 2, {4, 4, 4, 4}},
	//Blade slashes
	{0, 100, 0, 36, 8, 8, 8, 8, {12, 12, 12, 12}},
	//Falling spike that deals 127 damage
	{127, 1, 2, 4, 8, 4, 8, 4, {0, 0, 0, 0}},
	//Blade
	{15, 1, 30, 36, 8, 8, 4, 2, {8, 8, 8, 8}},
	{6, 3, 18, 36, 10, 10, 4, 2, {12, 12, 12, 12}},
	{1, 100, 30, 36, 6, 6, 4, 4, {12, 12, 12, 12}},
	//Super Missile Launcher
	{0, 10, 30, 40, 2, 2, 2, 2, {8, 8, 8, 8}},
	{0, 10, 40, 40, 4, 4, 4, 4, {8, 8, 8, 8}},
	{0, 10, 40, 40, 4, 4, 0, 0, {8, 8, 8, 8}},
	//Super Missile Launcher explosion
	{2, 100, 100, 20, 12, 12, 0, 0, {0, 0, 0, 0}},
	{2, 100, 100, 20, 12, 12, 0, 0, {0, 0, 0, 0}},
	{2, 100, 100, 20, 12, 12, 0, 0, {0, 0, 0, 0}},
	//Nemesis
	{4, 4, 20, 32, 4, 4, 3, 3, {8, 8, 24, 8}},
	{4, 2, 20, 32, 2, 2, 2, 2, {8, 8, 24, 8}},
	{1, 1, 20, 32, 2, 2, 2, 2, {8, 8, 24, 8}},
	//Spur
	{4, 4, 30, 64, 6, 6, 3, 3, {8, 8, 8, 8}},
	{8, 8, 30, 64, 6, 6, 3, 3, {8, 8, 8, 8}},
	{12, 12, 30, 64, 6, 6, 3, 3, {8, 8, 8, 8}},
	//Spur trail
	{3, 100, 30, 32, 6, 6, 3, 3, {4, 4, 4, 4}},
	{6, 100, 30, 32, 6, 6, 3, 3, {4, 4, 4, 4}},
	{11, 100, 30, 32, 6, 6, 3, 3, {4, 4, 4, 4}},
	//Curly's Nemesis
	{4, 4, 20, 32, 4, 4, 3, 3, {8, 8, 24, 8}},
	//Screen-nuke that kills all enemies
	{0, 4, 4, 4, 0, 0, 0, 0, {0, 0, 0, 0}},
	//Whimsical Star
	{1, 1, 1, 36, 1, 1, 1, 1, {1, 1, 1, 1}}
};

static const struct
{
	void (*act)(BULLET*, s32);
	void (*put)(BULLET*, s32, s32, s32);
	s32 level;
} gpBulletFuncTbl[] = {
	{NULL, NULL, 0},
	//Snake
	{NULL, NULL, 0},
	{NULL, NULL, 2},
	{NULL, NULL, 3},
	//Polar Star
	{Bullet_PoleStar_Act, Bullet_PoleStar_Put, 1},
	{Bullet_PoleStar_Act, Bullet_PoleStar_Put, 2},
	{Bullet_PoleStar_Act, Bullet_PoleStar_Put, 3},
	//Fireball
	{Bullet_FireBall_Act, Bullet_FireBall_Put, 1},
	{Bullet_FireBall_Act, Bullet_FireBall_Put, 2},
	{Bullet_FireBall_Act, Bullet_FireBall_Put, 3},
	//Machine Gun
	{NULL, NULL, 1},
	{NULL, NULL, 2},
	{NULL, NULL, 3},
	//Missile Launcher
	{Bullet_MissileLauncher_Act, Bullet_MissileLauncher_Put, 1},
	{Bullet_MissileLauncher_Act, Bullet_MissileLauncher_Put, 2},
	{Bullet_MissileLauncher_Act, Bullet_MissileLauncher_Put, 3},
	//Missile Launcher explosion
	{Bullet_Bom_Act, NULL, 1},
	{Bullet_Bom_Act, NULL, 2},
	{Bullet_Bom_Act, NULL, 3},
	//Bubbline
	{NULL, NULL, 0},
	{NULL, NULL, 0},
	{NULL, NULL, 0},
	//Bubbline level 3 thorns
	{NULL, NULL, 0},
	//Blade slashes
	{NULL, NULL, 0},
	//Falling spike that deals 127 damage
	{NULL, NULL, 0},
	//Blade
	{NULL, NULL, 0},
	{NULL, NULL, 0},
	{NULL, NULL, 0},
	//Super Missile Launcher
	{NULL, NULL, 1},
	{NULL, NULL, 2},
	{NULL, NULL, 3},
	//Super Missile Launcher explosion
	{NULL, NULL, 1},
	{NULL, NULL, 2},
	{NULL, NULL, 3},
	//Nemesis
	{NULL, NULL, 1},
	{NULL, NULL, 2},
	{NULL, NULL, 3},
	//Spur
	{NULL, NULL, 1},
	{NULL, NULL, 2},
	{NULL, NULL, 3},
	//Spur trail
	{NULL, NULL, 1},
	{NULL, NULL, 2},
	{NULL, NULL, 3},
	//Curly's Nemesis
	{NULL, NULL, 1},
	//Screen-nuke that kills all enemies
	{NULL, NULL, 0},
	//Whimsical Star
	{NULL, NULL, 0},
};

//Bullet functions
void InitBullet()
{
	s32 i;
	for (i = 0; i < BULLET_MAX; i++)
		gBul[i].cond = 0;
}

s32 CountArmsBullet(s32 arms_code)
{
	s32 i;
	s32 count = 0;
	for (i = 0; i < BULLET_MAX; i++)
		if (gBul[i].cond & 0x80 && (gBul[i].code_bullet + 2) / 3 == arms_code)
			++count;
	return count;
}

s32 CountBulletNum(s32 bullet_code)
{
	s32 i;
	s32 count = 0;
	for (i = 0; i < BULLET_MAX; i++)
		if (gBul[i].cond & 0x80 && gBul[i].code_bullet == bullet_code)
			++count;
	return count;
}

void DeleteBullet(s32 code)
{
	s32 i;
	for (i = 0; i < BULLET_MAX; i++)
		if (gBul[i].cond & 0x80 && (gBul[i].code_bullet + 2) / 3 == code)
			gBul[i].cond = 0;
}

void ClearBullet()
{
	s32 i;
	for (i = 0; i < BULLET_MAX; i++)
		gBul[i].cond = 0;
}

void PutBullet(s32 fx, s32 fy)
{
	s32 i;
	s32 x, y;
	
	for (i = 0; i < BULLET_MAX; i++)
	{
		if ((gBul[i].cond & 0x80) && gpBulletFuncTbl[gBul[i].code_bullet].put != NULL)
		{
			switch (gBul[i].direct)
			{
				case 0:
					x = gBul[i].x - gBul[i].view.front;
					y = gBul[i].y - gBul[i].view.top;
					break;
				case 1:
					x = gBul[i].x - gBul[i].view.top;
					y = gBul[i].y - gBul[i].view.front;
					break;
				case 2:
					x = gBul[i].x - gBul[i].view.back;
					y = gBul[i].y - gBul[i].view.top;
					break;
				case 3:
					x = gBul[i].x - gBul[i].view.top;
					y = gBul[i].y - gBul[i].view.back;
					break;
			}
			
			gpBulletFuncTbl[gBul[i].code_bullet].put(&gBul[i], gpBulletFuncTbl[gBul[i].code_bullet].level, (x / 0x200) - (fx / 0x200), (y / 0x200) - (fy / 0x200));
		}
	}
}

void SetBullet(s32 no, s32 x, s32 y, s32 dir)
{
	s32 i = 0;
	while (i < BULLET_MAX && gBul[i].cond & 0x80)
		i++;
	
	if (i >= BULLET_MAX)
		return;
	
	memset(&gBul[i], 0, sizeof(BULLET));
	gBul[i].code_bullet = no;
	gBul[i].cond = 0x80;
	gBul[i].direct = dir;
	gBul[i].damage = gBulTbl[no].damage;
	gBul[i].life = gBulTbl[no].life;
	gBul[i].life_count = gBulTbl[no].life_count;
	gBul[i].bbits = gBulTbl[no].bbits;
	gBul[i].enemyXL = gBulTbl[no].enemyXL * 0x200;
	gBul[i].enemyYL = gBulTbl[no].enemyYL * 0x200;
	gBul[i].blockXL = gBulTbl[no].blockXL * 0x200;
	gBul[i].blockYL = gBulTbl[no].blockYL * 0x200;
	gBul[i].view.back = gBulTbl[no].view.back * 0x200;
	gBul[i].view.front = gBulTbl[no].view.front * 0x200;
	gBul[i].view.top = gBulTbl[no].view.top * 0x200;
	gBul[i].view.bottom = gBulTbl[no].view.bottom * 0x200;
	gBul[i].x = x;
	gBul[i].y = y;
}

void ActBullet()
{
	s32 i;
	for (i = 0; i < BULLET_MAX; i++)
	{
		if (gBul[i].cond & 0x80)
		{
			if (gBul[i].life <= 0)
			{
				gBul[i].cond = 0;
				continue;
			}
			if (gpBulletFuncTbl[gBul[i].code_bullet].act != NULL)
				gpBulletFuncTbl[gBul[i].code_bullet].act(&gBul[i], gpBulletFuncTbl[gBul[i].code_bullet].level);
		}
	}
}
