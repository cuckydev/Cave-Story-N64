#include "carets.h"
#include "triangle.h"
#include "draw.h"
#include "game.h"

static const RECT rctest = {0, 0, 16, 16};

//Caret 00
void ActCaret00(CARET *crt)
{
	(void)crt;
}

void PutCaret00(CARET *crt, s32 fx, s32 fy)
{
	(void)crt; (void)fx; (void)fy;
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
			crt->cond = 0;
	}
}

void PutCaret01(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 02
void ActCaret02(CARET *crt)
{
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
				crt->cond = 0;
			break;
			
		case 2:
			//Animate
			if (++crt->ani_wait > 2)
			{
				crt->ani_wait = 0;
				crt->ani_no++;
			}
			
			if (crt->ani_no > 3)
				crt->cond = 0;
			break;
			
		case 1:
			//Animate
			if (crt->ani_wait > 24)
				crt->cond = 0;
			break;
	}
}

void PutCaret02(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 03
void ActCaret03(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 2)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 3)
			crt->cond = 0;
	}
}

void PutCaret03(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 04
void ActCaret04(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 1)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 2)
			crt->cond = 0;
	}
}

void PutCaret04(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 05
void ActCaret05(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 4)
	{
		crt->ani_wait = 0;
		crt->ani_no++;
	}
	
	if (crt->ani_no > 6)
		crt->cond = 0;
	
	//Move
	crt->x += 0x80;
	crt->y -= 0x80;
}

void PutCaret05(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 07
void ActCaret07(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 1)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 6)
			crt->cond = 0;
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

void PutCaret07(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 08
void ActCaret08(CARET *crt)
{
	(void)crt;
}

void PutCaret08(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 09
void ActCaret09(CARET *crt)
{
	//Move and delete after 32 frames
	if (++crt->ani_wait < 5)
		crt->y -= 0x800;
	if (crt->ani_wait == 32)
		crt->cond = 0;
}

void PutCaret09(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 10
void ActCaret10(CARET *crt)
{
	//Move up and delete after 80 frames
	crt->ani_wait++;
	if (crt->direct == 0)
	{
		if (crt->ani_wait < 20)
			crt->y -= 2 * 0x200;
		if (crt->ani_wait == 80)
			crt->cond = 0;
	}
	else
	{
		if (crt->ani_wait < 20)
			crt->y -= 1 * 0x200;
		if (crt->ani_wait == 80)
			crt->cond = 0;
	}
}

void PutCaret10(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 11
void ActCaret11(CARET *crt)
{
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
			crt->cond = 0;
	}
}

void PutCaret11(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 12
void ActCaret12(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 2)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 1)
			crt->cond = 0;
	}
}

void PutCaret12(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 13
void ActCaret13(CARET *crt)
{
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
		crt->cond = 0;
}

void PutCaret13(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 14
void ActCaret14(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 1)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 4)
			crt->cond = 0;
	}
}

void PutCaret14(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 15
void ActCaret15(CARET *crt)
{
	//Animate
	if (++crt->ani_wait > 2)
	{
		crt->ani_wait = 0;
		if (++crt->ani_no > 3)
			crt->cond = 0;
	}
}

void PutCaret15(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 16
void ActCaret16(CARET *crt)
{
	//Move and delete after 40 frames
	if (++crt->ani_wait < 10)
		crt->y -= 2 * 0x200;
	if (crt->ani_wait == 40)
		crt->cond = 0;
}

void PutCaret16(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}

//Caret 17
void ActCaret17(CARET *crt)
{
	//Delete after 40 frames
	if (++crt->ani_wait >= 40)
		crt->ani_wait = 0;
}

void PutCaret17(CARET *crt, s32 fx, s32 fy)
{
	PutBitmap(&rctest, (crt->x / 0x200) - (fx / 0x200) - 8, (crt->y / 0x200) - (fy / 0x200) - 8);
}