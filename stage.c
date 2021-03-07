#include "stage.h"
#include "draw.h"
#include "textscr.h"
#include "mychar.h"
#include "map.h"
#include "mapname.h"
#include "frame.h"
#include "flash.h"
#include "caret.h"
#include "bullet.h"
#include "back.h"
#include "fade.h"
#include "valueview.h"
#include "mem.h"

#include <string.h>

//Stages
#define STAGE_START(name)_##name##SegmentRomStart
#define STAGE_END(name)_##name##SegmentRomEnd

#define INC_STAGE(name) extern u8 STAGE_START(name)[]; extern u8 STAGE_END(name)[];
#define REF_STAGE(name) STAGE_START(name), STAGE_END(name)
#define NULL_STAGE() NULL, NULL

INC_STAGE(pens1)
INC_STAGE(eggs)
INC_STAGE(eggx)
INC_STAGE(egg6)
INC_STAGE(eggr)
INC_STAGE(mimi)
INC_STAGE(cave)
INC_STAGE(start)
INC_STAGE(barr)
INC_STAGE(pool)
INC_STAGE(cemet)
INC_STAGE(plant)
INC_STAGE(shelt)
INC_STAGE(comu)
INC_STAGE(mibox)
INC_STAGE(egend1)
INC_STAGE(cthu)
INC_STAGE(egg1)
INC_STAGE(pens2)
INC_STAGE(kings)
INC_STAGE(pole)

//Tilesets
#define TILESET_START(name)_##name##SegmentRomStart

#define INC_TILESET(name) extern u8 TILESET_START(name)[];
#define REF_TILESET(name) TILESET_START(name)
#define NULL_TILESET() NULL

INC_TILESET(prt_pens)
INC_TILESET(prt_cave)
INC_TILESET(prt_eggs)
INC_TILESET(prt_eggx)
INC_TILESET(prt_eggin)
INC_TILESET(prt_store)
INC_TILESET(prt_white)
INC_TILESET(prt_mimi)

//Backgrounds
#include "data/back/bk_blue.inc.c"
#include "data/back/bk_green.inc.c"

struct 
{
	const u8 *stage_start, *stage_end;
	const u8 *tileset_start;
	const char *name;
	BACK_DRAW back_draw;
	s32 back_type;
} gTMT[] = {
	{NULL_STAGE(), NULL_TILESET(), "Null", NULL, 4},
	{REF_STAGE(pens1), REF_TILESET(prt_pens), "Arthur's House", bk_blue, 1},
	{REF_STAGE(eggs), REF_TILESET(prt_eggs), "Egg Corridor", bk_green, 1},
	{REF_STAGE(eggx), REF_TILESET(prt_eggx), "Egg No. 00", NULL, 4},
	{REF_STAGE(egg6), REF_TILESET(prt_eggin), "Egg No. 06", NULL, 4},
	{REF_STAGE(eggr), REF_TILESET(prt_store), "Egg Observation Room", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Grasstown", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Santa's House", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Chaco's House", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Labyrinth I", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Sand Zone", NULL, 4},
	{REF_STAGE(mimi), REF_TILESET(prt_mimi), "Mimiga Village", bk_blue, 1},
	{REF_STAGE(cave), REF_TILESET(prt_cave), "First Cave", NULL, 4},
	{REF_STAGE(start), REF_TILESET(prt_cave), "Start Point", NULL, 4},
	{REF_STAGE(barr), REF_TILESET(prt_mimi), "Shack", NULL, 4},
	{REF_STAGE(pool), REF_TILESET(prt_mimi), "Reservoir", bk_blue, 1},
	{REF_STAGE(cemet), REF_TILESET(prt_mimi), "Graveyard", NULL, 4},
	{REF_STAGE(plant), REF_TILESET(prt_mimi), "Yamashita Farm", bk_green, 1},
	{REF_STAGE(shelt), REF_TILESET(prt_store), "Shelter", NULL, 4},
	{REF_STAGE(comu), REF_TILESET(prt_pens), "Assembly Hall", NULL, 4},
	{REF_STAGE(mibox), REF_TILESET(prt_mimi), "Save Point", NULL, 4},
	{REF_STAGE(egend1), REF_TILESET(prt_store), "Side Room", NULL, 4},
	{REF_STAGE(cthu), REF_TILESET(prt_store), "Cthulhu's Abode", NULL, 4},
	{REF_STAGE(egg1), REF_TILESET(prt_eggin), "Egg No. 01", NULL, 4},
	{REF_STAGE(pens2), REF_TILESET(prt_pens), "Arthur's House", bk_blue, 1},
	{NULL_STAGE(), NULL_TILESET(), "Power Room", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Save Point", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Execution Chamber", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Gum", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Sand Zone Residence", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Grasstown Hut", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Main Artery", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Small Room", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Jenka's House", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Deserted House", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Sand Zone Storehouse", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Jenka's House", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Sand Zone", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Labyrinth H", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Labyrinth W", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Camp", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Clinic Ruins", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Labyrinth Shop", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Labyrinth B", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Boulder Chamber", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Labyrinth M", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Dark Place", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Core", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Waterway", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Egg Corridor?", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Cthulhu's Abode?", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Egg Observation Room?", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Egg No. 00", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Outer Wall", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Side Room", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Storehouse", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Plantation", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Jail No. 1", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Hideout", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Rest Area", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Teleporter", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Jail No. 2", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Balcony", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Final Cave", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Throne Room", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "The King's Table", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Prefab Building", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Last Cave (Hidden)", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Black Space", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Little House", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Balcony", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Fall", NULL, 4},
	{REF_STAGE(kings), REF_TILESET(prt_white), "u", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Waterway Cabin", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Prefab House", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Sacred Ground - B1", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Sacred Ground - B2", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Sacred Ground - B3", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Storage", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Passage?", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Passage?", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Statue Chamber", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Seal Chamber", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Corridor", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "", NULL, 4},
	{REF_STAGE(pole), REF_TILESET(prt_cave), "Hermit Gunsmith", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Seal Chamber", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "", NULL, 4},
	{NULL_STAGE(), NULL_TILESET(), "Clock Room", NULL, 4},
};

//Stage globals
s32 gStageNo;

//Stage data
u8 *stage_map = NULL;
static u8 *stage_script = NULL;

//Stage functions
void TransferStage(s32 no, s32 w, s32 x, s32 y)
{
	//Get stage data
	const u8 *stage_start = gTMT[no].stage_start;
	const u8 *stage_end   = gTMT[no].stage_end;
	const u8 *tileset_start = gTMT[no].tileset_start;
	if (stage_start == NULL || stage_end == NULL || tileset_start == NULL)
	{
		TransferStage(gStageNo, 94, (gMC.x + 0x1000) / 0x2000, (gMC.y + 0x1000) / 0x2000);
		ShowMyChar(TRUE);
	}
	else
	{
		//Read stage data
		u16 i;
		u16 width, height, events;
		u32 scr_len;
		EVENT *event, *eventp;
		
		u32 stage_size = ((u32)(stage_end - stage_start) + 0xF) & ~0xF;
		u8 *buffer = Mem_Alloc(stage_size);
		u8 *bufferp = buffer;
		
		nuPiReadRom((u32)stage_start, buffer, stage_size);
		
		//Map data
		width  = (*bufferp++ << 8) | (*bufferp++ << 0);
		height = (*bufferp++ << 8) | (*bufferp++ << 0);
		
		Mem_Free(stage_map);
		stage_map = Mem_Alloc(width * height);
		
		memcpy(stage_map, bufferp, width * height);
		bufferp += width * height;
		
		//Events
		events = (*bufferp++ << 8) | (*bufferp++ << 0);
		event = Mem_Alloc(events * sizeof(EVENT));
		
		eventp = event;
		for (i = 0; i < events; i++, eventp++)
		{
			eventp->x          = (*bufferp++ << 8) | (*bufferp++ << 0);
			eventp->y          = (*bufferp++ << 8) | (*bufferp++ << 0);
			eventp->code_flag  = (*bufferp++ << 8) | (*bufferp++ << 0);
			eventp->code_event = (*bufferp++ << 8) | (*bufferp++ << 0);
			eventp->code_char  = (*bufferp++ << 8) | (*bufferp++ << 0);
			eventp->bits       = (*bufferp++ << 8) | (*bufferp++ << 0);
		}
		
		//Script
		scr_len = (*bufferp++ << 24) | (*bufferp++ << 16) | (*bufferp++ << 8) | (*bufferp++ << 0);
		
		Mem_Free(stage_script);
		stage_script = Mem_Alloc(scr_len + 1);
		
		memcpy(stage_script, bufferp, scr_len);
		stage_script[scr_len] = 0;
		
		//Free buffer
		Mem_Free(buffer);
		
		//Move character
		SetMyCharPosition(x * 0x10 * 0x200, y * 0x10 * 0x200);
		
		//Load stage data
		LoadMapData(width, height, stage_map);
		LoadTilesetData((u32)tileset_start);
		LoadEvent(events, event);
		Mem_Free(event);
		LoadTextScript_Stage(stage_script);
		InitBack(gTMT[no].back_draw, gTMT[no].back_type);
		
		//Initialize map state
		ReadyMapName(gTMT[no].name);
		
		StartTextScript(w);
		SetFrameMyChar();
		ClearBullet();
		InitCaret();
		ClearValueView();
		ResetQuake();
		//InitBossChar(gTMT[no].boss_no);
		ResetFlash();
		gStageNo = no;
	}
}
