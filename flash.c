#include "flash.h"
#include "game_def.h"
#include "draw.h"

//Flash structure
static struct
{
	s32 mode;
	s32 act_no;
	BOOL flag;
	s32 cnt;
	s32 width;
	s32 x;
	s32 y;
	RECT rect1;
	RECT rect2;
} flash;

//Flash functions
void SetFlash(s32 x, s32 y, s32 mode)
{
	flash.act_no = 0;
	flash.flag = TRUE;
	flash.x = x;
	flash.y = y;
	flash.mode = mode;
	flash.cnt = 0;
	flash.width = 0;
}

void ActFlash_Explosion(s32 flx, s32 fly)
{
	s32 left, top, right, bottom;
	
	switch (flash.act_no)
	{
		case 0:
			flash.cnt += 0x200;
			flash.width += flash.cnt;
			
			left = (flash.x - flx - flash.width) / 0x200;
			top = (flash.y - fly - flash.width) / 0x200;
			right = (flash.x - flx + flash.width) / 0x200;
			bottom = (flash.y - fly + flash.width) / 0x200;
			
			if (left < 0)
				left = 0;
			if (top < 0)
				top = 0;
			if (right > SCREEN_WIDTH)
				right = SCREEN_WIDTH;
			if (bottom > SCREEN_HEIGHT)
				bottom = SCREEN_HEIGHT;
			
			flash.rect1.left = left;
			flash.rect1.right = right;
			flash.rect1.top = 0;
			flash.rect1.bottom = SCREEN_HEIGHT;
			
			flash.rect2.left = 0;
			flash.rect2.right = SCREEN_WIDTH;
			flash.rect2.top = top;
			flash.rect2.bottom = bottom;
			
			if (flash.width > (SCREEN_WIDTH * 0x200 * 4))
			{
				flash.act_no = 1;
				flash.cnt = 0;
				flash.width = (SCREEN_HEIGHT * 0x200);
			}
			
			break;
			
		case 1:
			flash.width -= flash.width / 8;
			
			if ((flash.width / 0x100) == 0)
				flash.flag = FALSE;
			
			top = (flash.y - fly - flash.width) / 0x200;
			if (top < 0)
				top = 0;
			
			bottom = (flash.y - fly + flash.width) / 0x200;
			if (bottom > SCREEN_HEIGHT)
				bottom = SCREEN_HEIGHT;
			
			flash.rect1.left = 0;
			flash.rect1.right = 0;
			flash.rect1.top = 0;
			flash.rect1.bottom = 0;
			
			flash.rect2.top = top;
			flash.rect2.bottom = bottom;
			flash.rect2.left = 0;
			flash.rect2.right = SCREEN_WIDTH;
			break;
	}
}

void ActFlash_Flash()
{
	flash.cnt++;
	
	flash.rect1.left = 0;
	flash.rect1.right = 0;
	flash.rect1.top = 0;
	flash.rect1.bottom = 0;
	
	if (flash.cnt / 2 % 2)
	{
		flash.rect2.top = 0;
		flash.rect2.bottom = SCREEN_HEIGHT;
		flash.rect2.left = 0;
		flash.rect2.right = SCREEN_WIDTH;
	}
	else
	{
		flash.rect2.left = 0;
		flash.rect2.right = 0;
		flash.rect2.top = 0;
		flash.rect2.bottom = 0;
	}
	
	if (flash.cnt > 20)
		flash.flag = FALSE;
}

void ActFlash(s32 flx, s32 fly)
{
	if (!flash.flag)
		return;
	
	switch (flash.mode)
	{
		case 1:
			ActFlash_Explosion(flx, fly);
			break;
		case 2:
			ActFlash_Flash();
			break;
	}
}

void PutFlash()
{
	if (!flash.flag)
		return;
	CortBox(&flash.rect1, RGB(0xFF, 0xFF, 0xFF));
	CortBox(&flash.rect2, RGB(0xFF, 0xFF, 0xFF));
}

void ResetFlash()
{
	flash.flag = FALSE;
}
