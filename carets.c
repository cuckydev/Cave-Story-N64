#include "carets.h"
#include "triangle.h"
#include "game.h"

static const RECT rctest = {0, 0, 16, 16};

//Caret 00
void ActCaret00(CARET *crt)
{
	(void)crt;
}

//Caret 01
void ActCaret01(CARET *crt)
{
	//Initial velocity
	if (crt->act_no == 0)
	{
		crt->act_no = 1;
		crt->xm = Random(-0x400, 0x400);
		crt->ym = Random(-0x400, 0);
	}
	
	//Move
	crt->ym += 0x40;
	crt->x += crt->xm;
	crt->y += crt->ym;
	
	//Animate
	if (++crt->ani_wait > 5)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 3)
		{
			crt->cond = 0;
			return;
		}
	}
}

//Caret 02
#include "data/bitmap/caret_02.inc.c"

void ActCaret02(CARET *crt)
{
	static const RECT rect[3][4] = {
		{
			{0,  0, 16, 16},
			{16, 0, 32, 16},
			{32, 0, 48, 16},
			{48, 0, 64, 16},
		},
		{
			{0,  0, 16, 16},
			{32, 0, 48, 16},
			{16, 0, 32, 16},
			{0, 0, 0, 0},
		},
		{
			{0,  16, 16, 32},
			{16, 16, 32, 32},
			{32, 16, 48, 32},
			{48, 16, 64, 32},
		},
	};
	
	switch (crt->direct)
	{
		case 0:
			//Move
			crt->ym -= 0x10;
			crt->y += crt->ym;
			
			//Animate
			if (++crt->ani_wait > 5)
			{
				crt->ani_wait = 0;
				crt->ani_no++;
			}
			
			if (crt->ani_no > 3)
			{
				crt->cond = 0;
				return;
			}
			break;
			
		case 2:
			//Animate
			if (++crt->ani_wait > 2)
			{
				crt->ani_wait = 0;
				crt->ani_no++;
			}
			
			if (crt->ani_no > 3)
			{
				crt->cond = 0;
				return;
			}
			break;
			
		case 1:
			//Animate
			if (crt->ani_wait > 24)
			{
				crt->cond = 0;
				return;
			}
			break;
	}
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_02_tex;
		crt->tex_w = 64;
		crt->tex_h = 32;
		crt->tlut = caret_02_tlut;
	}
	crt->rect = rect[crt->direct][crt->ani_no];
}

//Caret 03
#include "data/bitmap/caret_03.inc.c"

void ActCaret03(CARET *crt)
{
	static const RECT rect[] = {
		{0,  0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
		{48, 0, 64, 16},
	};
	
	//Animate
	if (++crt->ani_wait > 2)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 3)
		{
			crt->cond = 0;
			return;
		}
	}
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_03_tex;
		crt->tex_w = 64;
		crt->tex_h = 16;
		crt->tlut = caret_03_tlut;
	}
	crt->rect = rect[crt->ani_no];
}

//Caret 04
void ActCaret04(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 1)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 2)
		{
			crt->cond = 0;
			return;
		}
	}
}

//Caret 05
#include "data/bitmap/caret_05.inc.c"

void ActCaret05(CARET *crt)
{
	static const RECT rect[] = {
		{0, 0,  8,  8},
		{0, 8,  8, 16},
		{8, 0, 16,  8},
		{8, 8, 16, 16},
		{8, 0, 16,  8},
		{8, 8, 16, 16},
		{8, 0, 16,  8},
	};
	
	//Animate
	if (++crt->ani_wait > 4)
	{
		crt->ani_wait = 0;
		crt->ani_no++;
	}
	
	if (crt->ani_no > 6)
	{
		crt->cond = 0;
		return;
	}
	
	//Move
	crt->x += 0x80;
	crt->y -= 0x80;
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_05_tex;
		crt->tex_w = 16;
		crt->tex_h = 16;
		crt->tlut = caret_05_tlut;
	}
	crt->rect = rect[crt->ani_no];
}

//Caret 07
void ActCaret07(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 1)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 6)
		{
			crt->cond = 0;
			return;
		}
	}
	
	//Move
	switch (crt->direct)
	{
		case 0:
			crt->x -= 2 * 0x200;
			break;
		case 1:
			crt->y -= 2 * 0x200;
			break;
		case 2:
			crt->x += 2 * 0x200;
			break;
		case 3:
			crt->y += 2 * 0x200;
			break;
	}
}

//Caret 08
#include "data/bitmap/caret_08.inc.c"

void ActCaret08(CARET *crt)
{
	static const RECT rcLeft = {0, 0, 16, 16};
	static const RECT rcRight = {16, 0, 32, 16};
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_08_tex;
		crt->tex_w = 32;
		crt->tex_h = 16;
		crt->tlut = caret_08_tlut;
	}
	if (crt->direct)
		crt->rect = rcRight;
	else
		crt->rect = rcLeft;
}

//Caret 09
#include "data/bitmap/caret_09.inc.c"

void ActCaret09(CARET *crt)
{
	static const RECT rcMark = {0, 0, 16, 16};
	
	//Move and delete after 32 frames
	if (++crt->ani_wait < 5)
		crt->y -= 0x800;
	if (crt->ani_wait == 32)
	{
		crt->cond = 0;
		return;
	}
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_09_tex;
		crt->tex_w = 16;
		crt->tex_h = 16;
		crt->tlut = caret_09_tlut;
		crt->rect = rcMark;
	}
}

//Caret 10
#include "data/bitmap/caret_10.inc.c"

void ActCaret10(CARET *crt)
{
	static const RECT rect[2][2] = {
		{
			{0,  0, 64, 16},
			{0, 16, 64, 32},
		},
		{
			{0, 32, 64, 48},
			{0, 48, 64, 64},
		},
	};
	
	//Move up and delete after 80 frames
	crt->ani_wait++;
	if (crt->direct == 0)
	{
		if (crt->ani_wait < 20)
			crt->y -= 2 * 0x200;
		if (crt->ani_wait == 80)
		{
			crt->cond = 0;
			return;
		}
	}
	else
	{
		if (crt->ani_wait < 20)
			crt->y -= 1 * 0x200;
		if (crt->ani_wait == 80)
		{
			crt->cond = 0;
			return;
		}
	}
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_10_tex;
		crt->tex_w = 64;
		crt->tex_h = 64;
		crt->tlut = caret_10_tlut;
	}
	crt->rect = rect[crt->direct != 0][crt->ani_wait / 2 % 2];
}

//Caret 11
#include "data/bitmap/caret_11.inc.c"

void ActCaret11(CARET *crt)
{
	static const RECT rect[] = {
		{ 0, 0,  8, 8},
		{ 8, 0, 16, 8},
		{16, 0, 24, 8},
		{24, 0, 32, 8},
		{32, 0, 40, 8},
		{40, 0, 48, 8},
		{48, 0, 56, 8},
	};
	
	//Initial velocity
	u8 deg;
	if (crt->act_no == 0)
	{
		crt->act_no = 1;
		deg = Random(0, 0xFF);
		crt->xm = GetCos(deg) * 2;
		crt->ym = GetSin(deg) * 2;
	}
	
	//Move
	crt->x += crt->xm;
	crt->y += crt->ym;
	
	//Animate
	if (++crt->ani_wait > 2)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 6)
		{
			crt->cond = 0;
			return;
		}
	}
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_11_tex;
		crt->tex_w = 64;
		crt->tex_h = 8;
		crt->tlut = caret_11_tlut;
	}
	crt->rect = rect[crt->ani_no];
}

//Caret 12
#include "data/bitmap/caret_12.inc.c"

void ActCaret12(CARET *crt)
{
	static const RECT rect[] = {
		{ 0, 0, 32, 32},
		{32, 0, 64, 32},
	};
	
	//Animate
	if (++crt->ani_wait > 2)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 1)
		{
			crt->cond = 0;
			return;
		}
	}
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_12_tex;
		crt->tex_w = 64;
		crt->tex_h = 32;
		crt->tlut = caret_12_tlut;
	}
	crt->rect = rect[crt->ani_no];
}

//Caret 13
#include "data/bitmap/caret_13.inc.c"

void ActCaret13(CARET *crt)
{
	static const RECT rect[2] = {
		{4, 4, 12, 12},
		{0, 0, 0, 0},
	};
	
	//Initial velocity
	if (crt->act_no == 0)
	{
		crt->act_no = 1;
		
		switch (crt->direct)
		{
			case 0:
				crt->xm = Random(-0x600, 0x600);
				crt->ym = Random(-0x200, 0x200);
				break;
				
			case 1:
				crt->ym = -0x200 * Random(1, 3);
				break;
		}
	}
	
	//Move
	switch (crt->direct)
	{
		case 0:
			crt->xm = (crt->xm * 4) / 5;
			crt->ym = (crt->ym * 4) / 5;
			break;
	}
	
	crt->x += crt->xm;
	crt->y += crt->ym;
	
	//Animate
	if (++crt->ani_wait > 20)
	{
		crt->cond = 0;
		return;
	}
	
	//Draw
	if (crt->tex == NULL)
	{
		crt->tex = caret_13_tex;
		crt->tex_w = 16;
		crt->tex_h = 16;
		crt->tlut = caret_13_tlut;
	}
	crt->rect = rect[crt->ani_wait / 2 % 2];
}

//Caret 14
void ActCaret14(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 1)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 4)
		{
			crt->cond = 0;
			return;
		}
	}
}

//Caret 15
void ActCaret15(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 2)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 3)
		{
			crt->cond = 0;
			return;
		}
	}
}

//Caret 16
void ActCaret16(CARET *crt)
{
	//Move and delete after 40 frames
	if (++crt->ani_wait < 10)
		crt->y -= 2 * 0x200;
	if (crt->ani_wait == 40)
	{
		crt->cond = 0;
		return;
	}
}

//Caret 17
void ActCaret17(CARET *crt)
{
	if (++crt->ani_wait >= 40)
		crt->ani_wait = 0;
}
