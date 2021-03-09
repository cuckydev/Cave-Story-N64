#ifndef BULLET_H
#define BULLET_H

#include <ultra64.h>
#include "game_def.h"

//Bullet structure
#define BULLET_MAX 0x40

typedef struct
{
	s32 flag;
	s32 code_bullet;
	s32 bbits;
	s32 cond;
	s32 x;
	s32 y;
	s32 xm;
	s32 ym;
	s32 tgt_x;
	s32 tgt_y;
	s32 act_no;
	s32 act_wait;
	s32 ani_wait;
	s32 ani_no;
	u8 direct;
	s32 count1;
	s32 count2;
	s32 life_count;
	s32 damage;
	s32 life;
	s32 enemyXL;
	s32 enemyYL;
	s32 blockXL;
	s32 blockYL;
	RECT2 view;
} BULLET;

typedef struct
{
	s8 damage;
	s8 life;
	s32 life_count;
	s32 bbits;
	s32 enemyXL;
	s32 enemyYL;
	s32 blockXL;
	s32 blockYL;
	RECT2 view;
} BULLET_TABLE;

extern BULLET gBul[BULLET_MAX];

//Bullet functions
void InitBullet();
s32 CountArmsBullet(s32 arms_code);
s32 CountBulletNum(s32 bullet_code);
void DeleteBullet(s32 code);
void ClearBullet();
void PutBullet(s32 fx, s32 fy);
void SetBullet(s32 no, s32 x, s32 y, s32 dir);
void ActBullet();

#endif
