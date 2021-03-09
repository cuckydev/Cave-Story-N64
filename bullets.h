#ifndef BULLETH_H
#define BULLETS_H

#include "bullet.h"

void Bullet_PoleStar_Act(BULLET *bul, s32 level);
void Bullet_PoleStar_Put(BULLET *bul, s32 level, s32 x, s32 y);
void Bullet_FireBall_Act(BULLET *bul, s32 level);
void Bullet_FireBall_Put(BULLET *bul, s32 level, s32 x, s32 y);
void Bullet_MissileLauncher_Act(BULLET *bul, s32 level);
void Bullet_MissileLauncher_Put(BULLET *bul, s32 level, s32 x, s32 y);
void Bullet_Bom_Act(BULLET *bul, s32 level);

#endif
