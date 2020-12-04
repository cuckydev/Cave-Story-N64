#ifndef MAP_H
#define MAP_H

#include <ultra64.h>

//Map structures
typedef struct
{
	u8 *tex;
	u16 *tlut;
	const u8 *attr;
} TilesetData;

//Map functions
void UpdateMapPlane(s32 fx, s32 fy);
void LoadMapData(u16 width, u16 length, const u8 *data);
void LoadTilesetData(u8 *tex, u16 *tlut, const u8 *attr);
void GetMapData(u8 **data, s16 *mw, s16 *ml);
u8 GetAttribute(s32 x, s32 y);
void DeleteMapParts(s32 x, s32 y);
void ShiftMapParts(s32 x, s32 y);
void ChangeMapParts(s32 x, s32 y, u8 no);
void PutStage_Back(s32 fx, s32 fy);
void PutStage_Front(s32 fx, s32 fy);

#endif