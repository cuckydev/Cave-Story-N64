#ifndef NPCHAR_H
#define NPCHAR_H

#include <ultra64.h>
#include "game_def.h"

//NPC enums
enum NPCCond
{
	NPCCOND_DAMAGE_BOSS = 0x10, // (boss npc exclusive) When set, damage the main boss
	NPCCOND_ALIVE = 0x80        // Whether the NPC is alive or not
};

enum
{
	NPC_SOLID_SOFT = 1<<0,                // Pushes Quote out
	NPC_IGNORE_TILE_44 = 1<<1,            // Ignores tile 44, which normally blocks NPCs
	NPC_INVULNERABLE = 1<<2,              // Can't be hurt
	NPC_IGNORE_SOLIDITY = 1<<3,           // Doesn't collide with anything
	NPC_BOUNCY = 1<<4,                    // Quote bounces on top of NPC
	NPC_SHOOTABLE = 1<<5,                 // Can be shot
	NPC_SOLID_HARD = 1<<6,                // Essentially acts as level tiles
	NPC_REAR_AND_TOP_DONT_HURT = 1<<7,    // Rear and top don't hurt when touched
	NPC_EVENT_WHEN_TOUCHED = 1<<8,        // Run event when touched
	NPC_EVENT_WHEN_KILLED = 1<<9,         // Run event when killed
	NPC_APPEAR_WHEN_FLAG_SET = 1<<11,     // Only appear when flag is set
	NPC_SPAWN_IN_OTHER_DIRECTION = 1<<12, // Spawn facing to the right (or however the NPC s32erprets the direction)
	NPC_INTERACTABLE = 1<<13,             // Run event when s32eracted with
	NPC_HIDE_WHEN_FLAG_SET = 1<<14,       // Hide when flag is set
	NPC_SHOW_DAMAGE = 1<<15               // Show the number of damage taken when harmed
};

//NPC structs
typedef struct NPCHAR
{
	u8 cond;
	s32 flag;
	s32 x;
	s32 y;
	s32 xm;
	s32 ym;
	s32 xm2;
	s32 ym2;
	s32 tgt_x;
	s32 tgt_y;
	s32 code_char;
	s32 code_flag;
	s32 code_event;
	//SurfaceID surf;
	s32 hit_voice;
	s32 destroy_voice;
	s32 life;
	s32 exp;
	s32 size;
	s32 direct;
	u16 bits;
	//RECT rect;
	s32 ani_wait;
	s32 ani_no;
	s32 count1;
	s32 count2;
	s32 act_no;
	s32 act_wait;
	RECT2 hit;
	RECT2 view;
	u8 shock;
	s32 damage_view;
	s32 damage;
	struct NPCHAR *pNpc;
} NPCHAR;

typedef struct
{
	s16 x;
	s16 y;
	s16 code_flag;
	s16 code_event;
	s16 code_char;
	u16 bits;
} EVENT;

typedef struct
{
	u8 front;
	u8 top;
	u8 back;
	u8 bottom;
} NPC_TBL_RECT;

typedef struct
{
	u16 bits;
	u16 life;
	u8 surf;
	u8 hit_voice;
	u8 destroy_voice;
	u8 size;
	s32 exp;
	s32 damage;
	NPC_TBL_RECT hit;
	NPC_TBL_RECT view;
} NPC_TABLE;

//NPC globals
#define NPC_MAX 0x200
extern NPCHAR gNPC[NPC_MAX];
extern s32 gCurlyShoot_wait;
extern s32 gCurlyShoot_x;
extern s32 gCurlyShoot_y;
extern s32 gSuperXpos;
extern s32 gSuperYpos;

//NPC functions
void InitNpChar();
void LoadEvent(u32 events, const EVENT *event);
void SetNpChar(s32 code_char, s32 x, s32 y, s32 xm, s32 ym, s32 dir, NPCHAR *npc, s32 start_index);
void SetDestroyNpChar(s32 x, s32 y, s32 w, s32 num);
void SetDestroyNpCharUp(s32 x, s32 y, s32 w, s32 num);
void SetExpObjects(s32 x, s32 y, s32 exp);
BOOL SetBulletObject(s32 x, s32 y, s32 val);
BOOL SetLifeObject(s32 x, s32 y, s32 val);
void VanishNpChar(NPCHAR *npc);
void PutNpChar(s32 fx, s32 fy);
void ActNpChar();
void ChangeNpCharByEvent(s32 code_event, s32 code_char, s32 dir);
void ChangeCheckableNpCharByEvent(s32 code_event, s32 code_char, s32 dir);
void SetNpCharActionNo(s32 code_event, s32 act_no, s32 dir);
void MoveNpChar(s32 code_event, s32 x, s32 y, s32 dir);
void BackStepMyChar(s32 code_event);
void DeleteNpCharEvent(s32 code);
void DeleteNpCharCode(s32 code, BOOL bSmoke);
void GetNpCharPosition(s32 *x, s32 *y, s32 i);
BOOL IsNpCharCode(s32 code);
BOOL GetNpCharAlive(s32 code_event);
s32 CountAliveNpChar();

#endif
