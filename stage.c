#include "stage.h"
#include "draw.h"
#include "mychar.h"
#include "map.h"
#include "mapname.h"

//Stage table
#include "data/stage/eggs.inc.c"
#include "data/stage/cave.inc.c"
#include "data/stage/start.inc.c"

#include "data/tilesets/prt_cave.inc.c"
#include "data/tilesets/prt_eggs.inc.c"

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
};

//Stage globals
s32 gStageNo;

//Stage functions
void TransferStage(s32 no, s32 w, s32 x, s32 y)
{
	//Move character
	SetMyCharPosition(x * 0x10 * 0x200, y * 0x10 * 0x200);
	
	//Load stage data
	const StageData *stage_data = gTMT[no].stage_data;
	const TilesetData *tileset_data = gTMT[no].tileset_data;
	LoadMapData(stage_data->width, stage_data->height, stage_data->map);
	LoadTilesetData(tileset_data->tex, tileset_data->tlut, tileset_data->attr);
	
	//Initialize map state
	ReadyMapName(gTMT[no].name);
	
	//StartTextScript(w);
	//SetFrameMyChar();
	//ClearBullet();
	//InitCaret();
	//ClearValueView();
	//ResetQuake();
	//InitBossChar(gTMT[no].boss_no);
	//ResetFlash();
	gStageNo = no;
}
