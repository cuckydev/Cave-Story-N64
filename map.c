#include "map.h"
#include "mem.h"
#include "draw.h"
#include "npchar.h"
#include <string.h>

//Map data
static u8 *map_data = NULL;
static u16 map_width;
static u16 map_length;

static u8 *map_tileset_tex;
static u16 *map_tileset_tlut;
static u8 map_attr[0x100];

//Map planes
#define VIEW_W ((SCREEN_WIDTH + 15) / 16)
#define VIEW_H ((SCREEN_HEIGHT + 15) / 16)
#define PLANE_H (16)
#define PLANE_PH (PLANE_H * 16)

static Gfx map_plane_dumaln[] = { gsSPEndDisplayList() };
ALIGNED8 static u8 map_plane[2][VIEW_W + 1][8 * PLANE_PH];
static s32 map_plane_fx, map_plane_fy;
static BOOL map_plane_dirty;

BOOL IsTileOnscreen(s32 x, s32 y)
{
	if (x < (map_plane_fx >> 4) || x > (map_plane_fx >> 4) + VIEW_W ||
	    y < (map_plane_fy >> 4) || y > (map_plane_fy >> 4) + VIEW_H)
		return FALSE;
	return TRUE;
}

void PutTile(s32 x, s32 y)
{
	u8 px, py, tile, atrb;
	
	//Get tile at coordinate
	px = x % (VIEW_W + 1);
	py = y % PLANE_H;
	tile = map_data[x + y * map_width];
	atrb = map_attr[tile];
	
	//Determine how to handle tile
	if (atrb < 0x20)
	{
		//Background
		memcpy(&map_plane[0][px][8 * 16 * py], &map_tileset_tex[8 * 16 * tile], 8 * 16);
		memset(&map_plane[1][px][8 * 16 * py], 0, 8 * 16);
	}
	else if (atrb >= 0x40 && atrb < 0x80)
	{
		//Foreground
		memcpy(&map_plane[1][px][8 * 16 * py], &map_tileset_tex[8 * 16 * tile], 8 * 16);
		memset(&map_plane[0][px][8 * 16 * py], 0, 8 * 16);
	}
	else
	{
		memset(&map_plane[0][px][8 * 16 * py], 0, 8 * 16);
		memset(&map_plane[1][px][8 * 16 * py], 0, 8 * 16);
	}
}

void UpdateMapPlane(s32 fx, s32 fy)
{
	s32 gx, gy;
	
	//Convert frame position to pixel coordinates
	fx /= 0x200;
	fx += 8;
	fy /= 0x200;
	fy += 8;
	
	//Update map plane
	if (map_plane_dirty == TRUE)
	{
		//Reload entire screen
		for (gx = (fx >> 4); gx <= (fx >> 4) + VIEW_W; gx++)
			for (gy = (fy >> 4); gy <= (fy >> 4) + VIEW_H; gy++)
				PutTile(gx, gy);
		map_plane_dirty = FALSE;
	}
	else
	{
		for (gx = (fx >> 4); gx <= (fx >> 4) + VIEW_W; gx++)
		{
			for (gy = (fy >> 4); gy <= (fy >> 4) + VIEW_H; gy++)
			{
				if (!IsTileOnscreen(gx, gy))
				    PutTile(gx, gy);
			}
		}
	}
	
	map_plane_fx = fx;
	map_plane_fy = fy;
}

//Map functions
void LoadMapData(u16 width, u16 length, const u8 *data)
{
	//Allocate map data
	if (map_data != NULL)
		Mem_Free(map_data);
	map_data = Mem_Alloc(width * length * sizeof(*map_data));
	
	//Copy map data
	memcpy(map_data, data, width * length * sizeof(*map_data));
	map_width = width;
	map_length = length;
	map_plane_dirty = TRUE;
}

void LoadTilesetData(u8 *tex, u16 *tlut, const u8 *attr)
{
	//Copy attribute data and use tileset
	map_tileset_tex = tex;
	map_tileset_tlut = tlut;
	memcpy(map_attr, attr, 0x100 * sizeof(*map_attr));
	map_plane_dirty = TRUE;
}

void GetMapData(u8 **data, s16 *mw, s16 *ml)
{
	if (data != NULL)
		*data = map_data;
	if (mw != NULL)
		*mw = map_width;
	if (ml != NULL)
		*ml = map_length;
}

u8 GetAttribute(s32 x, s32 y)
{
	if (x < 0 || x >= map_width || y < 0 || y >= map_length)
		return 0;
	return map_attr[map_data[x + y * map_width]];
}

void DeleteMapParts(s32 x, s32 y)
{
	map_data[x + y * map_width] = 0;
	if (IsTileOnscreen(x, y))
		PutTile(x, y);
}

void ShiftMapParts(s32 x, s32 y)
{
	map_data[x + y * map_width]--;
	if (IsTileOnscreen(x, y))
		PutTile(x, y);
}

BOOL ChangeMapParts(s32 x, s32 y, u8 no)
{
	s32 i;
	if (map_data[x + y * map_width] == no)
		return FALSE;
	map_data[x + y * map_width] = no;
	if (IsTileOnscreen(x, y))
		PutTile(x, y);
	for (i = 0; i < 3; ++i)
		SetNpChar(4, x * 0x200 * 0x10, y * 0x200 * 0x10, 0, 0, 0, NULL, 0);
	return TRUE;
}

#include "data/bitmap/snack.inc.c"

void PutStage_Back(s32 fx, s32 fy)
{
	s32 x, y;
	static const RECT rcPlane = {0, 0, 16, PLANE_PH};
	
	//Convert frame position to pixel coordinates
	fx = (fx / 0x200) + 8;
	fy = (fy / 0x200) + 8;
	
	//Render foreground plane
	LoadTLUT_CI4(map_tileset_tlut);
	for (x = (fx >> 4); x <= (fx >> 4) + VIEW_W; x++)
	{
		LoadTex_CI4(16, PLANE_PH, map_plane[0][x % (VIEW_W + 1)]);
		for (y = fy / PLANE_PH; y <= (fy + (PLANE_PH - 1)) / PLANE_PH; y++)
			PutBitmap(&rcPlane, (x * 16) - fx, (y * PLANE_PH) - fy);
	}
}

void PutStage_Front(s32 fx, s32 fy)
{
	s32 x, y;
	static const RECT rcPlane = {0, 0, 16, PLANE_PH};
	static const RECT rcSnack = {0, 0, 16, 16};
	
	//Convert frame position to pixel coordinates
	fx = (fx / 0x200) + 8;
	fy = (fy / 0x200) + 8;
	
	//Render foreground plane
	LoadTLUT_CI4(map_tileset_tlut);
	for (x = (fx >> 4); x <= (fx >> 4) + VIEW_W; x++)
	{
		LoadTex_CI4(16, PLANE_PH, map_plane[1][x % (VIEW_W + 1)]);
		for (y = fy / PLANE_PH; y <= (fy + (PLANE_PH - 1)) / PLANE_PH; y++)
			PutBitmap(&rcPlane, (x * 16) - fx, (y * PLANE_PH) - fy);
	}
	
	//Render additional foreground tiles
	LoadTLUT_CI4(snack_tlut);
	LoadTex_CI4(32, 32, snack_tex);
	for (x = (fx >> 4); x <= (fx >> 4) + VIEW_W; x++)
		for (y = (fy >> 4); y <= (fy >> 4) + VIEW_H; y++)
			if (GetAttribute(x, y) == 0x43)
				PutBitmap(&rcSnack, (x * 16) - fx, (y * 16) - fy);
}
