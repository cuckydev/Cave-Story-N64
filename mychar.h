#ifndef MYCHAR_H
#define MYCHAR_H

#include <ultra64.h>
#include "game_def.h"

//Equippables
enum
{
	EQUIP_BOOSTER_0_8 = (1 << 0),
	EQUIP_MAP = (1 << 1),
	EQUIP_ARMS_BARRIER = (1 << 2),
	EQUIP_TURBOCHARGE = (1 << 3),
	EQUIP_AIR_TANK = (1 << 4),
	EQUIP_BOOSTER_2_0 = (1 << 5),
	EQUIP_MIMIGA_MASK = (1 << 6),
	EQUIP_WHIMSICAL_STAR = (1 << 7),
	EQUIP_NIKUMARU_COUNTER = (1 << 8)
};

//MyChar structure
typedef struct MYCHAR
{
	u8 cond;
	u32 flag;
	s32 direct;
	BOOL up;
	BOOL down;
	s32 unit;
	s32 equip;
	s32 x;
	s32 y;
	s32 tgt_x;
	s32 tgt_y;
	s32 index_x;
	s32 index_y;
	s32 xm;
	s32 ym;
	s32 ani_wait;
	s32 ani_no;
	RECT2 hit;
	RECT2 view;
	RECT rect;
	RECT rect_arms;
	s32 level;
	s32 exp_wait;
	s32 exp_count;
	u8 shock;
	u8 no_life;
	u8 rensha;
	u8 bubble;
	s16 life;
	s16 star;
	s16 max_life;
	s16 a;
	s32 lifeBr;
	s32 lifeBr_count;
	s32 air;
	s32 air_get;
	s8 sprash;
	s8 ques;
	s8 boost_sw;
	s32 boost_cnt;
} MYCHAR;

extern MYCHAR gMC;

//MyChar functions
void InitMyChar();
void AnimationMyChar(BOOL bKey);
void ShowMyChar(BOOL bShow);
void PutMyChar(s32 fx, s32 fy);
void ActMyChar(BOOL bKey);
void GetMyCharPosition(s32 *x, s32 *y);
void SetMyCharPosition(s32 x, s32 y);
void MoveMyChar(s32 x, s32 y);
void ZeroMyCharXMove();
s32 GetUnitMyChar();
void SetMyCharDirect(u8 dir);
void ChangeMyUnit(u8 a);
void PitMyChar();
void EquipItem(s32 flag, BOOL b);
void ResetCheck();
void SetNoise(s32 no, s32 freq);
void CutNoise();
void ResetNoise();
void SleepNoise();

#endif
