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
#include "valueview.h"

//Stage table
#include "data/stage/eggs.inc.c"
#include "data/stage/mimi.inc.c"
#include "data/stage/cave.inc.c"
#include "data/stage/start.inc.c"
#include "data/stage/barr.inc.c"
#include "data/stage/pool.inc.c"
#include "data/stage/cemet.inc.c"
#include "data/stage/plant.inc.c"
#include "data/stage/shelt.inc.c"
#include "data/stage/mibox.inc.c"
#include "data/stage/kings.inc.c"
#include "data/stage/pole.inc.c"

#include "data/tilesets/prt_cave.inc.c"
#include "data/tilesets/prt_eggs.inc.c"
#include "data/tilesets/prt_store.inc.c"
#include "data/tilesets/prt_white.inc.c"
#include "data/tilesets/prt_mimi.inc.c"

#include "data/back/bk_blue.inc.c"
#include "data/back/bk_green.inc.c"

struct 
{
	const StageData *stage_data;
	const TilesetData *tileset_data;
	const char *name;
	const BACK_TEX *back_tex;
	s32 back_type;
} gTMT[] = {
	{NULL, NULL, "Null", NULL, 4},
	{NULL, NULL, "Arthur's House", NULL, 4},
	{&eggs_data, &prt_eggs, "Egg Corridor", NULL, 4},
	{NULL, NULL, "Egg No. 00", NULL, 4},
	{NULL, NULL, "Egg No. 06", NULL, 4},
	{NULL, NULL, "Egg Observation Room", NULL, 4},
	{NULL, NULL, "Grasstown", NULL, 4},
	{NULL, NULL, "Santa's House", NULL, 4},
	{NULL, NULL, "Chaco's House", NULL, 4},
	{NULL, NULL, "Labyrinth I", NULL, 4},
	{NULL, NULL, "Sand Zone", NULL, 4},
	{&mimi_data, &prt_mimi, "Mimiga Village", &bk_blue, 1},
	{&cave_data, &prt_cave, "First Cave", NULL, 4},
	{&start_data, &prt_cave, "Start Point", NULL, 4},
	{&barr_data, &prt_mimi, "Shack", NULL, 4},
	{&pool_data, &prt_mimi, "Reservoir", &bk_blue, 1},
	{&cemet_data, &prt_mimi, "Graveyard", NULL, 4},
	{&plant_data, &prt_mimi, "Yamashita Farm", &bk_green, 1},
	{&shelt_data, &prt_store, "Shelter", NULL, 4},
	{NULL, NULL, "Assembly Hall", NULL, 4},
	{&mibox_data, &prt_mimi, "Save Point", NULL, 4},
	{NULL, NULL, "Side Room", NULL, 4},
	{NULL, NULL, "Cthulhu's Abode", NULL, 4},
	{NULL, NULL, "Egg No. 01", NULL, 4},
	{NULL, NULL, "Arthur's House", NULL, 4},
	{NULL, NULL, "Power Room", NULL, 4},
	{NULL, NULL, "Save Point", NULL, 4},
	{NULL, NULL, "Execution Chamber", NULL, 4},
	{NULL, NULL, "Gum", NULL, 4},
	{NULL, NULL, "Sand Zone Residence", NULL, 4},
	{NULL, NULL, "Grasstown Hut", NULL, 4},
	{NULL, NULL, "Main Artery", NULL, 4},
	{NULL, NULL, "Small Room", NULL, 4},
	{NULL, NULL, "Jenka's House", NULL, 4},
	{NULL, NULL, "Deserted House", NULL, 4},
	{NULL, NULL, "Sand Zone Storehouse", NULL, 4},
	{NULL, NULL, "Jenka's House", NULL, 4},
	{NULL, NULL, "Sand Zone", NULL, 4},
	{NULL, NULL, "Labyrinth H", NULL, 4},
	{NULL, NULL, "Labyrinth W", NULL, 4},
	{NULL, NULL, "Camp", NULL, 4},
	{NULL, NULL, "Clinic Ruins", NULL, 4},
	{NULL, NULL, "Labyrinth Shop", NULL, 4},
	{NULL, NULL, "Labyrinth B", NULL, 4},
	{NULL, NULL, "Boulder Chamber", NULL, 4},
	{NULL, NULL, "Labyrinth M", NULL, 4},
	{NULL, NULL, "Dark Place", NULL, 4},
	{NULL, NULL, "Core", NULL, 4},
	{NULL, NULL, "Waterway", NULL, 4},
	{NULL, NULL, "Egg Corridor?", NULL, 4},
	{NULL, NULL, "Cthulhu's Abode?", NULL, 4},
	{NULL, NULL, "Egg Observation Room?", NULL, 4},
	{NULL, NULL, "Egg No. 00", NULL, 4},
	{NULL, NULL, "Outer Wall", NULL, 4},
	{NULL, NULL, "Side Room", NULL, 4},
	{NULL, NULL, "Storehouse", NULL, 4},
	{NULL, NULL, "Plantation", NULL, 4},
	{NULL, NULL, "Jail No. 1", NULL, 4},
	{NULL, NULL, "Hideout", NULL, 4},
	{NULL, NULL, "Rest Area", NULL, 4},
	{NULL, NULL, "Teleporter", NULL, 4},
	{NULL, NULL, "Jail No. 2", NULL, 4},
	{NULL, NULL, "Balcony", NULL, 4},
	{NULL, NULL, "Final Cave", NULL, 4},
	{NULL, NULL, "Throne Room", NULL, 4},
	{NULL, NULL, "The King's Table", NULL, 4},
	{NULL, NULL, "Prefab Building", NULL, 4},
	{NULL, NULL, "Last Cave (Hidden)", NULL, 4},
	{NULL, NULL, "Black Space", NULL, 4},
	{NULL, NULL, "Little House", NULL, 4},
	{NULL, NULL, "Balcony", NULL, 4},
	{NULL, NULL, "Fall", NULL, 4},
	{&kings_data, &prt_white, "u", NULL, 4},
	{NULL, NULL, "Waterway Cabin", NULL, 4},
	{NULL, NULL, "", NULL, 4},
	{NULL, NULL, "", NULL, 4},
	{NULL, NULL, "", NULL, 4},
	{NULL, NULL, "", NULL, 4},
	{NULL, NULL, "", NULL, 4},
	{NULL, NULL, "Prefab House", NULL, 4},
	{NULL, NULL, "Sacred Ground - B1", NULL, 4},
	{NULL, NULL, "Sacred Ground - B2", NULL, 4},
	{NULL, NULL, "Sacred Ground - B3", NULL, 4},
	{NULL, NULL, "Storage", NULL, 4},
	{NULL, NULL, "Passage?", NULL, 4},
	{NULL, NULL, "Passage?", NULL, 4},
	{NULL, NULL, "Statue Chamber", NULL, 4},
	{NULL, NULL, "Seal Chamber", NULL, 4},
	{NULL, NULL, "Corridor", NULL, 4},
	{NULL, NULL, "", NULL, 4},
	{&pole_data, &prt_cave, "Hermit Gunsmith", NULL, 4},
	{NULL, NULL, "", NULL, 4},
	{NULL, NULL, "Seal Chamber", NULL, 4},
	{NULL, NULL, "", NULL, 4},
	{NULL, NULL, "Clock Room", NULL, 4},
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
	InitBack(gTMT[no].back_tex, gTMT[no].back_type);
	
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
