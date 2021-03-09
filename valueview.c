#include "valueview.h"
#include "draw.h"
#include <string.h>

//Value view structure
#define VALUEVIEW_MAX 0x10

typedef struct
{
	BOOL flag;
	BOOL minus;
	s32 *px;
	s32 *py;
	s32 value;
	s32 offset_y;
	s32 count;
	s32 width;
	s8 c[5];
} VALUEVIEW;

VALUEVIEW gVV[VALUEVIEW_MAX];
s32 gVVIndex;

void ClearValueView()
{
	memset(gVV, 0, sizeof(gVV));
	gVVIndex = 0;
}

void SetValueView(s32 *px, s32 *py, s32 value)
{
	s32 v;
	
	s32 index;
	s32 i;
	
	static const s32 dig[4] = {
		1,
		10,
		100,
		1000,
	};
	s32 fig[4];
	
	BOOL sw;
	
	//Find value view slot to use
	for (i = 0; i < VALUEVIEW_MAX; i++)
	{
		if (gVV[i].flag && gVV[i].px == px)
		{
			if (gVV[i].value < 0 && value < 0)
				break;
			if (gVV[i].value > 0 && value > 0)
				break;
		}
	}
	
	if (i == VALUEVIEW_MAX)
	{
		index = gVVIndex++;
		
		if (gVVIndex == VALUEVIEW_MAX)
			gVVIndex = 0;
		
		gVV[index].count = 0;
		gVV[index].offset_y = 0;
		gVV[index].value = value;
	}
	else
	{
		index = i;
		
		gVV[index].count = 32;
		gVV[index].value += value;
		value = gVV[index].value;
	}
	
	//Set properties
	gVV[index].flag = TRUE;
	gVV[index].px = px;
	gVV[index].py = py;
	
	//Get if negative or not
	if (value < 0)
	{
		value *= -1;
		gVV[index].minus = TRUE;
	}
	else
	{
		gVV[index].minus = FALSE;
	}
	
	//Get width
	if (value >= 1000)
		gVV[index].width = 5;
	else if (value >= 100)
		gVV[index].width = 4;
	else if (value >= 10)
		gVV[index].width = 3;
	else
		gVV[index].width = 2;
	
	//Get digits
	v = value;
	for (i = 3; i >= 0; i--)
	{
		fig[i] = 0;
		while (v >= dig[i])
		{
			v -= dig[i];
			++fig[i];
		}
	}
	
	//Write string
	memset(gVV[index].c, 0, sizeof(gVV[index].c));
	gVV[index].c[0] = 10;
	
	sw = FALSE;
	for (i = 3; i >= 0; i--)
	{
		if (!sw && i != 0 && fig[i] == 0)
			continue;
		sw = TRUE;
		gVV[index].c[gVV[index].width - i - 1] = fig[i];
	}
}

void ActValueView()
{
	s32 v;
	for (v = 0; v < VALUEVIEW_MAX; v++)
	{
		if (gVV[v].flag == FALSE)
			continue;
		if (++gVV[v].count < 32)
			gVV[v].offset_y -= 0x100;
		if (gVV[v].count > 80)
			gVV[v].flag = FALSE;
	}
}

#include "data/bitmap/numbers.inc.c"

void PutValueView(s32 flx, s32 fly)
{
	s32 v, i, x, y, sc;
	RECT rect;
	
	LoadTLUT_CI4(numbers_tlut);
	LoadTex_CI4(16, 96, numbers_tex);
	
	for (v = 0; v < VALUEVIEW_MAX; v++)
	{
		if (gVV[v].flag == FALSE)
			continue;
		
		rect.left = gVV[v].minus ? 8 : 0;
		rect.right = rect.left + 8;
		
		x = (*gVV[v].px / 0x200) - (gVV[v].width * 4) - (flx / 0x200);
		y = (*gVV[v].py / 0x200) + (gVV[v].offset_y / 0x200) - (fly / 0x200) - 4;
		
		sc = gVV[v].count - 72;
		if (sc < 0)
			sc = 0;
		
		for (i = 0; i < gVV[v].width; i++)
		{
			rect.top = gVV[v].c[i] * 8 + sc;
			rect.bottom = rect.top + 8 - sc;
			PutBitmap(&rect, x, y);
			x += 8;
		}
	}
}
