#include "stage.h"
#include "draw.h"
#include "textscr.h"
#include "mychar.h"
#include "map.h"
#include "mapname.h"
#include "frame.h"
#include "caret.h"

//Stage table
#include "data/stage/eggs.inc.c"
#include "data/stage/cave.inc.c"
#include "data/stage/start.inc.c"
#include "data/stage/shelt.inc.c"
#include "data/stage/pole.inc.c"

#include "data/tilesets/prt_cave.inc.c"
#include "data/tilesets/prt_eggs.inc.c"
#include "data/tilesets/prt_store.inc.c"

struct 
{
	const StageData *stage_data;
	const TilesetData *tileset_data;
	const char *name;
} gTMT[] = {
	{NULL, NULL, "Null"},
	{NULL, NULL, "Arthur's House"},
	{&eggs_data, &prt_eggs, "Egg Corridor"},
	{NULL, NULL, "Egg No. 00"},
	{NULL, NULL, "Egg No. 06"},
	{NULL, NULL, "Egg Observation Room"},
	{NULL, NULL, "Grasstown"},
	{NULL, NULL, "Santa's House"},
	{NULL, NULL, "Chaco's House"},
	{NULL, NULL, "Labyrinth I"},
	{NULL, NULL, "Sand Zone"},
	{NULL, NULL, "Mimiga Village"},
	{&cave_data, &prt_cave, "First Cave"},
	{&start_data, &prt_cave, "Start Point"},
	{NULL, NULL, "Shack"},
	{NULL, NULL, "Reservoir"},
	{NULL, NULL, "Graveyard"},
	{NULL, NULL, "Yamashita Farm"},
	{&shelt_data, &prt_store, "Shelter"},
	{NULL, NULL, "Assembly Hall"},
	{NULL, NULL, "Save Point"},
	{NULL, NULL, "Side Room"},
	{NULL, NULL, "Cthulhu's Abode"},
	{NULL, NULL, "Egg No. 01"},
	{NULL, NULL, "Arthur's House"},
	{NULL, NULL, "Power Room"},
	{NULL, NULL, "Save Point"},
	{NULL, NULL, "Execution Chamber"},
	{NULL, NULL, "Gum"},
	{NULL, NULL, "Sand Zone Residence"},
	{NULL, NULL, "Grasstown Hut"},
	{NULL, NULL, "Main Artery"},
	{NULL, NULL, "Small Room"},
	{NULL, NULL, "Jenka's House"},
	{NULL, NULL, "Deserted House"},
	{NULL, NULL, "Sand Zone Storehouse"},
	{NULL, NULL, "Jenka's House"},
	{NULL, NULL, "Sand Zone"},
	{NULL, NULL, "Labyrinth H"},
	{NULL, NULL, "Labyrinth W"},
	{NULL, NULL, "Camp"},
	{NULL, NULL, "Clinic Ruins"},
	{NULL, NULL, "Labyrinth Shop"},
	{NULL, NULL, "Labyrinth B"},
	{NULL, NULL, "Boulder Chamber"},
	{NULL, NULL, "Labyrinth M"},
	{NULL, NULL, "Dark Place"},
	{NULL, NULL, "Core"},
	{NULL, NULL, "Waterway"},
	{NULL, NULL, "Egg Corridor?"},
	{NULL, NULL, "Cthulhu's Abode?"},
	{NULL, NULL, "Egg Observation Room?"},
	{NULL, NULL, "Egg No. 00"},
	{NULL, NULL, "Outer Wall"},
	{NULL, NULL, "Side Room"},
	{NULL, NULL, "Storehouse"},
	{NULL, NULL, "Plantation"},
	{NULL, NULL, "Jail No. 1"},
	{NULL, NULL, "Hideout"},
	{NULL, NULL, "Rest Area"},
	{NULL, NULL, "Teleporter"},
	{NULL, NULL, "Jail No. 2"},
	{NULL, NULL, "Balcony"},
	{NULL, NULL, "Final Cave"},
	{NULL, NULL, "Throne Room"},
	{NULL, NULL, "The King's Table"},
	{NULL, NULL, "Prefab Building"},
	{NULL, NULL, "Last Cave (Hidden)"},
	{NULL, NULL, "Black Space"},
	{NULL, NULL, "Little House"},
	{NULL, NULL, "Balcony"},
	{NULL, NULL, "Fall"},
	{NULL, NULL, "u"},
	{NULL, NULL, "Waterway Cabin"},
	{NULL, NULL, ""},
	{NULL, NULL, ""},
	{NULL, NULL, ""},
	{NULL, NULL, ""},
	{NULL, NULL, ""},
	{NULL, NULL, "Prefab House"},
	{NULL, NULL, "Sacred Ground - B1"},
	{NULL, NULL, "Sacred Ground - B2"},
	{NULL, NULL, "Sacred Ground - B3"},
	{NULL, NULL, "Storage"},
	{NULL, NULL, "Passage?"},
	{NULL, NULL, "Passage?"},
	{NULL, NULL, "Statue Chamber"},
	{NULL, NULL, "Seal Chamber"},
	{NULL, NULL, "Corridor"},
	{NULL, NULL, ""},
	{&pole_data, &prt_cave, "Hermit Gunsmith"},
	{NULL, NULL, ""},
	{NULL, NULL, "Seal Chamber"},
	{NULL, NULL, ""},
	{NULL, NULL, "Clock Room"},
};

//Stage globals
s32 gStageNo;

//Stage functions
void TransferStage(s32 no, s32 w, s32 x, s32 y)
{
	//Get stage data
	const StageData *stage_data = gTMT[no].stage_data;
	const TilesetData *tileset_data = gTMT[no].tileset_data;
	if (stage_data == NULL || tileset_data == NULL)
		return;
	
	//Move character
	SetMyCharPosition(x * 0x10 * 0x200, y * 0x10 * 0x200);
	
	//Load stage data
	LoadMapData(stage_data->width, stage_data->height, stage_data->map);
	LoadTilesetData(tileset_data->tex, tileset_data->tlut, tileset_data->attr);
	LoadEvent(stage_data->events, stage_data->event);
	LoadTextScript_Stage(stage_data->script);
	
	//Initialize map state
	ReadyMapName(gTMT[no].name);
	
	StartTextScript(w);
	SetFrameMyChar();
	//ClearBullet();
	InitCaret();
	//ClearValueView();
	ResetQuake();
	//InitBossChar(gTMT[no].boss_no);
	//ResetFlash();
	gStageNo = no;
}
