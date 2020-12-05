#include "textscr.h"
#include "game.h"
#include "mychar.h"
#include "mycparam.h"
#include "npchar.h"
#include "draw.h"
#include "keycontrol.h"
#include "stage.h"
#include "mapname.h"
#include "frame.h"
#include "flash.h"
#include "flags.h"
#include "profile.h"
#include "armsitem.h"
#include "fade.h"
#include <string.h>

//Text script globals
#define TEXT_LEFT (SCREEN_WIDTH / 2 - 108)
#define IS_COMMAND(c1, c2, c3) (gTS.p_read[1] == (c1) && gTS.p_read[2] == (c2) && gTS.p_read[3] == (c3))

//Text script structure
TEXT_SCRIPT gTS;
static char text[4][0x40];

#include "data/head_script.inc.c"

//Text script functions
void InitTextScript()
{
	//Clear state
	gTS.mode = 0;
	g_GameFlags &= ~4;
	memset(text, 0, sizeof(text));
	gTS.data = NULL;
}

void LoadTextScript_Stage(const char *script)
{
	//Use given script
	gTS.head = TRUE;
	gTS.data = script;
}

void LoadTextScript(const char *script)
{
	//Use given script
	gTS.head = FALSE;
	gTS.data = script;
}

const char *GetTextScript()
{
	return gTS.data;
}

s32 GetTextScriptNo(const char *a)
{
	s32 b = 0;
	b += (*a++ - '0') * 1000;
	b += (*a++ - '0') * 100;
	b += (*a++ - '0') * 10;
	b += (*a++   - '0');
	return b;
}

BOOL JumpTextScriptEvent(const char *script, s32 no)
{
	//Find where event starts
	gTS.p_read = script;
	
	while (1)
	{
		//Check if we are still in the proper range
		if (*gTS.p_read == '\0')
			return FALSE;
		
		//Check if we are at an event
		if (*gTS.p_read == '#')
		{
			//Check if this is our event
			int event_no = GetTextScriptNo(++gTS.p_read);
			if (no == event_no)
				break;
			if (no < event_no)
				return FALSE;
		}
		
		gTS.p_read++;
	}
	
	//Advance until new-line
	while (*gTS.p_read != '\n')
		gTS.p_read++;
	gTS.p_read++;
	
	return TRUE;
}

void StartTextScript(s32 no)
{
	//Reset state
	gTS.mode = 1;
	g_GameFlags |= 5;
	gTS.line = 0;
	gTS.p_write = 0;
	gTS.wait = 4;
	gTS.flags = 0;
	gTS.wait_beam = 0;
	gTS.face = 0;
	gTS.item = 0;
	
	gMC.shock = 0;
	
	//Jump to given event
	if (gTS.head == FALSE || !JumpTextScriptEvent(head_script, no))
		JumpTextScriptEvent(gTS.data, no);
}

void JumpTextScript(s32 no)
{
	s32 i;
	
	//Set state
	gTS.mode = 1;
	g_GameFlags |= 4;
	gTS.line = 0;
	gTS.p_write = 0;
	gTS.wait = 4;
	gTS.wait_beam = 0;

	//Clear text lines
	for (i = 0; i < 4; i++)
	{
		gTS.ypos_line[i] = i * 16;
		memset(text[i], 0, sizeof(text[0]));
	}
	
	//Jump to given event
	if (gTS.head == FALSE || !JumpTextScriptEvent(head_script, no))
		JumpTextScriptEvent(gTS.data, no);
}

void StopTextScript()
{
	//End TSC and reset flags
	gTS.mode = 0;
	g_GameFlags &= ~4;
	g_GameFlags |= 3;
	gTS.flags = 0;
}

void CheckNewLine()
{
	if (gTS.ypos_line[gTS.line % 4] == 48)
	{
		gTS.mode = 3;
		g_GameFlags |= 4;
		memset(text[gTS.line % 4], 0, sizeof(text[0]));
	}
}

s32 gNumberTextScript[4];

void SetNumberTextScript(s32 index)
{
	char str[5];
	BOOL bZero;
	s32 a;
	s32 b;
	s32 offset;
	s32 i;

	//Get digit table
	s32 table[3];
	table[0] = 1000;
	table[1] = 100;
	table[2] = 10;
	
	//Get number to print
	a = gNumberTextScript[index];
	
	bZero = FALSE;
	offset = 0;
	
	//Trim leading zeroes
	for (i = 0; i < 3; i++)
	{
		if (a / table[i] || bZero)
		{
			b = a / table[i];
			str[offset] = '0' + (char)b;
			bZero = TRUE;
			a -= b * table[i];
			offset++;
		}
	}
	
	//Set last digit of string, and add null terminator
	str[offset] = '0' + (char)a;
	str[offset + 1] = '\0';
	
	//Append number to line
	strcat(text[gTS.line % 4], str);
	
	//Play sound and reset blinking cursor
	//PlaySoundObject(2, SOUND_MODE_PLAY);
	gTS.wait_beam = 0;
	
	//Check if should move to next line
	gTS.p_write += (int)strlen(str);
	if (gTS.p_write >= 35)
	{
		gTS.p_write = 0;
		gTS.line++;
		CheckNewLine();
	}
}

void ClearTextLine(void)
{
	s32 i;
	
	gTS.line = 0;
	gTS.p_write = 0;
	
	for (i = 0; i < 4; ++i)
	{
		gTS.ypos_line[i] = i * 16;
		memset(text[i], 0, sizeof(text[0]));
	}
}

#include "data/bitmap/textbox.inc.c"
#include "data/bitmap/yesno.inc.c"
#include "data/bitmap/armsimage.inc.c"
#include "data/bitmap/itemimage.inc.c"

#include "data/bitmap/face_00.inc.c"
#include "data/bitmap/face_10.inc.c"
#include "data/bitmap/face_20.inc.c"
#include "data/bitmap/face_30.inc.c"
#include "data/bitmap/face_40.inc.c"
#include "data/bitmap/face_50.inc.c"
#include "data/bitmap/face_01.inc.c"
#include "data/bitmap/face_11.inc.c"
#include "data/bitmap/face_21.inc.c"
#include "data/bitmap/face_31.inc.c"
#include "data/bitmap/face_41.inc.c"
#include "data/bitmap/face_51.inc.c"
#include "data/bitmap/face_02.inc.c"
#include "data/bitmap/face_12.inc.c"
#include "data/bitmap/face_22.inc.c"
#include "data/bitmap/face_32.inc.c"
#include "data/bitmap/face_42.inc.c"
#include "data/bitmap/face_52.inc.c"
#include "data/bitmap/face_03.inc.c"
#include "data/bitmap/face_13.inc.c"
#include "data/bitmap/face_23.inc.c"
#include "data/bitmap/face_33.inc.c"
#include "data/bitmap/face_43.inc.c"
#include "data/bitmap/face_53.inc.c"
#include "data/bitmap/face_04.inc.c"
#include "data/bitmap/face_14.inc.c"
#include "data/bitmap/face_24.inc.c"
#include "data/bitmap/face_34.inc.c"
#include "data/bitmap/face_44.inc.c"
#include "data/bitmap/face_54.inc.c"

static const struct
{
	u8 *tex;
	u16 *tlut;
} face_tex[] = {
	{face_00_tex, face_00_tlut},
	{face_10_tex, face_10_tlut},
	{face_20_tex, face_20_tlut},
	{face_30_tex, face_30_tlut},
	{face_40_tex, face_40_tlut},
	{face_50_tex, face_50_tlut},
	{face_01_tex, face_01_tlut},
	{face_11_tex, face_11_tlut},
	{face_21_tex, face_21_tlut},
	{face_31_tex, face_31_tlut},
	{face_41_tex, face_41_tlut},
	{face_51_tex, face_51_tlut},
	{face_02_tex, face_02_tlut},
	{face_12_tex, face_12_tlut},
	{face_22_tex, face_22_tlut},
	{face_32_tex, face_32_tlut},
	{face_42_tex, face_42_tlut},
	{face_52_tex, face_52_tlut},
	{face_03_tex, face_03_tlut},
	{face_13_tex, face_13_tlut},
	{face_23_tex, face_23_tlut},
	{face_33_tex, face_33_tlut},
	{face_43_tex, face_43_tlut},
	{face_53_tex, face_53_tlut},
	{face_04_tex, face_04_tlut},
	{face_14_tex, face_14_tlut},
	{face_24_tex, face_24_tlut},
	{face_34_tex, face_34_tlut},
	{face_44_tex, face_44_tlut},
	{face_54_tex, face_54_tlut},
};

void PutTextScript()
{
	static u16 textscr_text_tlut[] = {
		0x0000, GPACK_RGBA5551(0xFF, 0xFF, 0xFF, 1),
	};
	
	s32 msg_box_y, text_offset;
	s32 i;
	
	static const RECT rcFrame = {0, 0, 256, 16};
	static const RECT rcItemBox1 = {6, 0, 70, 16};
	static const RECT rcItemBox2 = {238, 0, 256, 16};
	static const RECT rcItemBox3 = {6, 0, 70, 16};
	static const RECT rcItemBox4 = {238, 0, 256, 16};
		
	static const RECT rect_yesno = {16, 0, 128, 32};
	static const RECT rect_cur = {0, 0, 16, 16};
	RECT rect;
	
	//Make sure we're in a drawable state
	if (gTS.mode == 0)
		return;
	if ((gTS.flags & 1) == 0)
		return;
	
	//Get textbox position
	if (gTS.flags & 0x20)
		msg_box_y = 32;
	else
		msg_box_y = SCREEN_HEIGHT - 56;
	
	//Draw message box frame
	if (gTS.flags & 2)
	{
		LoadTLUT_CI4(textbox_tlut);
		
		LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 0);
		PutBitmap(&rcFrame, (SCREEN_WIDTH - 256) / 2, msg_box_y - 10);
		
		LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 1);
		PutBitmap(&rcFrame, (SCREEN_WIDTH - 256) / 2, msg_box_y - 10 + 16);
		PutBitmap(&rcFrame, (SCREEN_WIDTH - 256) / 2, msg_box_y - 10 + 32);
		
		LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 2);
		PutBitmap(&rcFrame, (SCREEN_WIDTH - 256) / 2, msg_box_y - 10 + 48);
	}
	
	//Draw face
	if (gTS.face_x > 0)
		gTS.face_x -= 8;
	
	if (gTS.face != 0)
	{
		rect.left = gTS.face_x;
		rect.top = 3;
		rect.right = 48;
		rect.bottom = 48;
		LoadTLUT_CI4(face_tex[gTS.face].tlut);
		LoadTex_CI4(48, 48, face_tex[gTS.face].tex);
		PutBitmap(&rect, SCREEN_WIDTH / 2 - 108, msg_box_y);
	}
	
	//Draw text
	if (gTS.face != 0)
		text_offset = 56;
	else
		text_offset = 0;
	
	for (i = 0; i < 4; i++)
	{
		if (gTS.ypos_line[i] > -8 && gTS.ypos_line[i] < 40)
			PutText(TEXT_LEFT + text_offset, msg_box_y + gTS.ypos_line[i], text[i], textscr_text_tlut);
	}
	
	//Draw NOD cursor
	if ((gTS.wait_beam++ % 20 > 12) && gTS.mode == 2)
	{
		rect.left = TEXT_LEFT + text_offset + GetTextWidth(text[gTS.line % 4]) + 1;
		rect.top = msg_box_y + gTS.ypos_line[gTS.line % 4];
		rect.right = rect.left + 5;
		rect.bottom = rect.top + 11;
		CortBox(&rect, RGB(0xFF, 0xFF, 0xFE));
	}
	
	//Draw item image
	if (gTS.item != 0)
	{
		//Move item image
		if (gTS.item_y < SCREEN_HEIGHT - 104)
			gTS.item_y++;
		
		//Draw frame
		LoadTLUT_CI4(textbox_tlut);
		
		LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 0);
		PutBitmap(&rcItemBox1, (SCREEN_WIDTH / 2) - 38, SCREEN_HEIGHT - 112);
		PutBitmap(&rcItemBox2, (SCREEN_WIDTH / 2) + 26, SCREEN_HEIGHT - 112);
		
		LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 2);
		PutBitmap(&rcItemBox3, (SCREEN_WIDTH / 2) - 38, SCREEN_HEIGHT - 96);
		PutBitmap(&rcItemBox4, (SCREEN_WIDTH / 2) + 26, SCREEN_HEIGHT - 96);
		
		//Draw contents
		if (gTS.item < 1000)
		{
			//Arms Image
			rect.left = 16 * gTS.item;
			rect.right = rect.left + 16;
			rect.top = 0;
			rect.bottom = 16;
			LoadTLUT_CI4(armsimage_tlut);
			LoadTex_CI4(256, 16, armsimage_tex);
			PutBitmap(&rect, (SCREEN_WIDTH - 16) / 2, gTS.item_y);
		}
		else
		{
			//Item Image
			rect.left = 32 * ((gTS.item - 1000) % 8);
			rect.right = rect.left + 32;
			rect.top = 0;
			rect.bottom = 16;
			LoadTLUT_CI4(itemimage_tlut);
			LoadTex_CI4(256, 16, itemimage_tex + (128 * 16) * ((gTS.item - 1000) / 8));
			PutBitmap(&rect, (SCREEN_WIDTH - 32) / 2, gTS.item_y);
		}
	}
	
	//Draw Yes/No dialogue
	if (gTS.mode == 6)
	{
		LoadTLUT_CI4(yesno_tlut);
		LoadTex_CI4(128, 32, yesno_tex);
		
		if (gTS.wait < 2)
			i = (SCREEN_HEIGHT - 96) + (2 - gTS.wait) * 4;
		else
			i = SCREEN_HEIGHT - 96;

		PutBitmap(&rect_yesno, (SCREEN_WIDTH / 2) + 56, i);
		if (gTS.wait == 16)
			PutBitmap(&rect_cur, (gTS.select * 41) + (SCREEN_WIDTH / 2) + 51, SCREEN_HEIGHT - 86);
	}
	
}

s32 TextScriptProc()
{
	s32 i;
	char c[3];
	char str[72];
	s32 w, x, y, z;
	
	BOOL bExit;
	
	switch (gTS.mode)
	{
		case 1: //PARSE
			//Type out (faster if ok or cancel are held)
			++gTS.wait;

			if (!(g_GameFlags & 2) && gKey & (gKeyOk | gKeyCancel))
				gTS.wait += 4;

			if (gTS.wait < 4)
				break;

			gTS.wait = 0;

			//Parsing time
			bExit = FALSE;
			
			while (!bExit)
			{
				if (*gTS.p_read == '<')
				{
					if (IS_COMMAND('E','N','D'))
					{
						gTS.mode = 0;
						gMC.cond &= ~1;
						g_GameFlags |= 3;
						gTS.face = 0;
						bExit = TRUE;
					}
					else if (IS_COMMAND('L','I','+'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						AddLifeMyChar(x);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('M','L','+'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						AddMaxLifeMyChar(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('A','E','+'))
					{
						FullArmsEnergy();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('I','T','+'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						//PlaySoundObject(38, SOUND_MODE_PLAY);
						AddItemData(x);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('I','T','-'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						SubItemData(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('E','Q','+'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						EquipItem(z, TRUE);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('E','Q','-'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						EquipItem(z, FALSE);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('A','M','+'))
					{
						w = GetTextScriptNo(gTS.p_read + 4);
						x = GetTextScriptNo(gTS.p_read + 9);
						
						gNumberTextScript[0] = x;
						//PlaySoundObject(38, SOUND_MODE_PLAY);
						AddArmsData(w, x);
						gTS.p_read += 13;
					}
					else if (IS_COMMAND('A','M','-'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						SubArmsData(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('Z','A','M'))
					{
						ZeroArmsEnergy_All();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('T','A','M'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						z = GetTextScriptNo(gTS.p_read + 14);
						TradeArms(x, y, z);
						gTS.p_read += 18;
					}
					else if (IS_COMMAND('P','S','+'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						//AddPermitStage(x, y);
						gTS.p_read += 13;
					}
					else if (IS_COMMAND('M','P','+'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						//SetMapping(x);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('U','N','I'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						ChangeMyUnit(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('S','T','C'))
					{
						//SaveTimeCounter();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('T','R','A'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						w = GetTextScriptNo(gTS.p_read + 9);
						x = GetTextScriptNo(gTS.p_read + 14);
						y = GetTextScriptNo(gTS.p_read + 19);
						
						TransferStage(z, w, x, y);
					}
					else if (IS_COMMAND('M','O','V'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						SetMyCharPosition(x * 0x200 * 0x10, y * 0x200 * 0x10);
						gTS.p_read += 13;
					}
					else if (IS_COMMAND('H','M','C'))
					{
						ShowMyChar(FALSE);
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('S','M','C'))
					{
						ShowMyChar(TRUE);
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('F','L','+'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						SetNPCFlag(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('F','L','-'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						CutNPCFlag(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('S','K','+'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						SetSkipFlag(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('S','K','-'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						CutSkipFlag(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('K','E','Y'))
					{
						g_GameFlags &= ~2;
						g_GameFlags |= 1;
						gMC.up = FALSE;
						gMC.shock = 0;
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('P','R','I'))
					{
						g_GameFlags &= ~3;
						gMC.shock = 0;
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('F','R','E'))
					{
						g_GameFlags |= 3;
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('N','O','D'))
					{
						gTS.mode = 2;
						gTS.p_read += 4;
						bExit = TRUE;
					}
					else if (IS_COMMAND('C','L','R'))
					{
						ClearTextLine();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('M','S','G'))
					{
						ClearTextLine();
						gTS.flags |= 0x03;
						gTS.flags &= ~0x30;
						if (gTS.flags & 0x40)
							gTS.flags |= 0x10;
						gTS.p_read += 4;
						bExit = TRUE;
					}
					else if (IS_COMMAND('M','S','2'))
					{
						ClearTextLine();
						gTS.flags &= ~0x12;
						gTS.flags |= 0x21;
						if (gTS.flags & 0x40)
							gTS.flags |= 0x10;
						gTS.face = 0;
						gTS.p_read += 4;
						bExit = TRUE;
					}
					else if (IS_COMMAND('M','S','3'))
					{
						ClearTextLine();
						gTS.flags &= ~0x10;
						gTS.flags |= 0x23;
						if (gTS.flags & 0x40)
							gTS.flags |= 0x10;
						gTS.p_read += 4;
						bExit = TRUE;
					}
					else if (IS_COMMAND('W','A','I'))
					{
						gTS.mode = 4;
						gTS.wait_next = GetTextScriptNo(gTS.p_read + 4);
						gTS.p_read += 8;
						bExit = TRUE;
					}
					else if (IS_COMMAND('W','A','S'))
					{
						gTS.mode = 7;
						gTS.p_read += 4;
						bExit = TRUE;
					}
					else if (IS_COMMAND('T','U','R'))
					{
						gTS.p_read += 4;
						gTS.flags |= 0x10;
					}
					else if (IS_COMMAND('S','A','T'))
					{
						gTS.p_read += 4;
						gTS.flags |= 0x40;
					}
					else if (IS_COMMAND('C','A','T'))
					{
						gTS.p_read += 4;
						gTS.flags |= 0x40;
					}
					else if (IS_COMMAND('C','L','O'))
					{
						gTS.flags &= ~0x33;
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('E','V','E'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						JumpTextScript(z);
					}
					else if (IS_COMMAND('Y','N','J'))
					{
						gTS.next_event = GetTextScriptNo(gTS.p_read + 4);
						gTS.p_read += 8;
						gTS.mode = 6;
						//PlaySoundObject(5, SOUND_MODE_PLAY);
						gTS.wait = 0;
						gTS.select = 0;
						bExit = TRUE;
					}
					else if (IS_COMMAND('F','L','J'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						z = GetTextScriptNo(gTS.p_read + 9);
						
						if (GetNPCFlag(x))
							JumpTextScript(z);
						else
							gTS.p_read += 13;
					}
					else if (IS_COMMAND('S','K','J'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						z = GetTextScriptNo(gTS.p_read + 9);
						
						if (GetSkipFlag(x))
							JumpTextScript(z);
						else
							gTS.p_read += 13;
					}
					else if (IS_COMMAND('I','T','J'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						z = GetTextScriptNo(gTS.p_read + 9);
						
						if (CheckItem(x))
							JumpTextScript(z);
						else
							gTS.p_read += 13;
					}
					else if (IS_COMMAND('A','M','J'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						z = GetTextScriptNo(gTS.p_read + 9);
						
						if (CheckArms(x))
							JumpTextScript(z);
						else
							gTS.p_read += 13;
					}
					else if (IS_COMMAND('U','N','J'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						z = GetTextScriptNo(gTS.p_read + 9);
						
						if (GetUnitMyChar() == x)
							JumpTextScript(z);
						else
							gTS.p_read += 13;
					}
					else if (IS_COMMAND('E','C','J'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						z = GetTextScriptNo(gTS.p_read + 9);
						
						if (GetNpCharAlive(x))
							JumpTextScript(z);
						else
							gTS.p_read += 13;
					}
					else if (IS_COMMAND('N','C','J'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						z = GetTextScriptNo(gTS.p_read + 9);
						
						if (IsNpCharCode(x))
							JumpTextScript(z);
						else
							gTS.p_read += 13;
					}
					else if (IS_COMMAND('M','P','J'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						
						if (FALSE)//IsMapping())
							JumpTextScript(x);
						else
							gTS.p_read += 8;
					}
					else if (IS_COMMAND('S','S','S'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						SetNoise(1, x);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('C','S','S'))
					{
						CutNoise();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('S','P','S'))
					{
						SetNoise(2, 0);
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('C','P','S'))
					{
						CutNoise();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('Q','U','A'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						SetQuake(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('F','L','A'))
					{
						//SetFlash(0, 0, 2);
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('F','A','I'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						StartFadeIn(z);
						gTS.mode = 5;
						gTS.p_read += 8;
						bExit = TRUE;
					}
					else if (IS_COMMAND('F','A','O'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						StartFadeOut(z);
						gTS.mode = 5;
						gTS.p_read += 8;
						bExit = TRUE;
					}
					else if (IS_COMMAND('M','N','A'))
					{
						StartMapName();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('F','O','M'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						SetFrameTargetMyChar(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('F','O','N'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						SetFrameTargetNpChar(x, y);
						gTS.p_read += 13;
					}
					else if (IS_COMMAND('F','O','B'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						SetFrameTargetBoss(x, y);
						gTS.p_read += 13;
					}
					else if (IS_COMMAND('S','O','U'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						//PlaySoundObject(z, SOUND_MODE_PLAY);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('C','M','U'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						//ChangeMusic((MusicID)z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('F','M','U'))
					{
						//SetOrganyaFadeout();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('R','M','U'))
					{
						//ReCallMusic();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('M','L','P'))
					{
						gTS.p_read += 4;
						bExit = TRUE;

						//switch (MiniMapLoop())
						//{
						//	case enum_ESCRETURN_exit:
						//		return enum_ESCRETURN_exit;
						//	case enum_ESCRETURN_restart:
						//		return enum_ESCRETURN_restart;
						//}
					}
					else if (IS_COMMAND('S','L','P'))
					{
						bExit = TRUE;
						
						//switch (StageSelectLoop(&z))
						//{
						//	case enum_ESCRETURN_exit:
						//		return enum_ESCRETURN_exit;
						//	case enum_ESCRETURN_restart:
						//		return enum_ESCRETURN_restart;
						//}
						
						JumpTextScript(z);
						g_GameFlags &= ~3;
					}
					else if (IS_COMMAND('D','N','P'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						DeleteNpCharEvent(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('D','N','A'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						DeleteNpCharCode(z, TRUE);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('B','O','A'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						//SetBossCharActNo(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('C','N','P'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						z = GetTextScriptNo(gTS.p_read + 14);
						ChangeNpCharByEvent(x, y, z);
						gTS.p_read += 18;
					}
					else if (IS_COMMAND('A','N','P'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						z = GetTextScriptNo(gTS.p_read + 14);
						SetNpCharActionNo(x, y, z);
						gTS.p_read += 18;
					}
					else if (IS_COMMAND('I','N','P'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						z = GetTextScriptNo(gTS.p_read + 14);
						ChangeCheckableNpCharByEvent(x, y, z);
						gTS.p_read += 18;
					}
					else if (IS_COMMAND('S','N','P'))
					{
						w = GetTextScriptNo(gTS.p_read + 4);
						x = GetTextScriptNo(gTS.p_read + 9);
						y = GetTextScriptNo(gTS.p_read + 14);
						z = GetTextScriptNo(gTS.p_read + 19);
						SetNpChar(w, x * 0x200 * 0x10, y * 0x200 * 0x10, 0, 0, z, NULL, 0x100);
						gTS.p_read += 23;
					}
					else if (IS_COMMAND('M','N','P'))
					{
						w = GetTextScriptNo(gTS.p_read + 4);
						x = GetTextScriptNo(gTS.p_read + 9);
						y = GetTextScriptNo(gTS.p_read + 14);
						z = GetTextScriptNo(gTS.p_read + 19);
						MoveNpChar(w, x * 0x200 * 0x10, y * 0x200 * 0x10, z);
						gTS.p_read += 23;
					}
					else if (IS_COMMAND('S','M','P'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						ShiftMapParts(x, y);
						gTS.p_read += 13;
					}
					else if (IS_COMMAND('C','M','P'))
					{
						x = GetTextScriptNo(gTS.p_read + 4);
						y = GetTextScriptNo(gTS.p_read + 9);
						z = GetTextScriptNo(gTS.p_read + 14);
						ChangeMapParts(x, y, z);
						gTS.p_read += 18;
					}
					else if (IS_COMMAND('B','S','L'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						
						//if (z != 0)
						//	StartBossLife(z);
						//else
						//	StartBossLife2();
						
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('M','Y','D'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						SetMyCharDirect(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('M','Y','B'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						BackStepMyChar(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('M','M','0'))
					{
						ZeroMyCharXMove();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('I','N','I'))
					{
						InitializeGame();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('S','V','P'))
					{
						SaveProfile(NULL);
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('L','D','P'))
					{
						if (!LoadProfile(NULL))
							InitializeGame();
					}
					else if (IS_COMMAND('F','A','C'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						if (gTS.face != z)
						{
							gTS.face = z;
							gTS.face_x = 48;
						}
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('G','I','T'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						gTS.item = z;
						gTS.item_y = SCREEN_HEIGHT - 112;
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('N','U','M'))
					{
						//This supports up to four different values, but only one is actually used (a second is used erroneously)
						z = GetTextScriptNo(gTS.p_read + 4);
						SetNumberTextScript(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('C','R','E'))
					{
						g_GameFlags |= 8;
						//StartCreditScript();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('S','I','L'))
					{
						z = GetTextScriptNo(gTS.p_read + 4);
						//SetCreditIllust(z);
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('C','I','L'))
					{
						//CutCreditIllust();
						gTS.p_read += 4;
					}
					else if (IS_COMMAND('X','X','1'))
					{
						bExit = TRUE;
						z = GetTextScriptNo(gTS.p_read + 4);
						
						//switch (Scene_DownIsland(z))
						//{
						//	case enum_ESCRETURN_exit:
						//		return enum_ESCRETURN_exit;
						//	case enum_ESCRETURN_restart:
						//		return enum_ESCRETURN_restart;
						//}
						
						gTS.p_read += 8;
					}
					else if (IS_COMMAND('E','S','C'))
					{
						return 0;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					if (*gTS.p_read == '\n')
					{
						//Go to new-line
						gTS.p_read++;
						gTS.p_write = 0;
						if (gTS.flags & 1)
						{
							gTS.line++;
							CheckNewLine();
						}
					}
					else if (gTS.flags & 0x10)
					{
						//SAT/CAT/TUR printing
						x = 0;
						while (gTS.p_read[x] != '<' && gTS.p_read[x] != '\r')
						{
							//Skip if SHIFT-JIS
							if (gTS.p_read[x] & 0x80)
								x++;
							x++;
						}
						
						//Get text to copy
						memcpy(str, gTS.p_read, x);
						str[x] = '\0';
						gTS.p_write += x;
						
						//Print text
						strcpy(text[gTS.line % 4], str);
						
						//Check if should move to next line
						gTS.p_read += x;
						if (gTS.p_write >= 35)
							CheckNewLine();
						
						bExit = TRUE;
					}
					else
					{
						//Get text to print
						c[0] = *gTS.p_read;
						if (c[0] & 0x80)
						{
							c[1] = gTS.p_read[1];
							c[2] = '\0';
						}
						else
						{
							c[1] = '\0';
						}
						
						//Print text
						strcat(text[gTS.line % 4], c);
						//PlaySoundObject(2, SOUND_MODE_PLAY);
						gTS.wait_beam = 0;
						
						//Offset read and write positions
						if (c[0] & 0x80)
						{
							gTS.p_read += 2;
							gTS.p_write += 2;
						}
						else
						{
							gTS.p_read += 1;
							gTS.p_write += 1;
						}
						
						if (gTS.p_write >= 35)
						{
							CheckNewLine();
							gTS.p_write = 0;
							gTS.line++;
							CheckNewLine();
						}
						
						bExit = TRUE;
					}
				}
			}
			break;
			
		case 2: //NOD
			if (gKeyTrg & (gKeyOk | gKeyCancel))
				gTS.mode = 1;
			break;
			
		case 3: //NEW LINE
			for (i = 0; i < 4; ++i)
			{
				gTS.ypos_line[i] -= 4;
				if (gTS.ypos_line[i] == 0)
					gTS.mode = 1;
				if (gTS.ypos_line[i] == -16)
					gTS.ypos_line[i] = 48;
			}
			break;
			
		case 4: //WAI
			if (gTS.wait_next == 9999)
				break;
			
			if (gTS.wait != 9999)
				++gTS.wait;
			
			if (gTS.wait < gTS.wait_next)
				break;
			
			gTS.mode = 1;
			gTS.wait_beam = 0;
			break;
			
		case 5: //FAI/FAO
			if (GetFadeActive())
				break;
			gTS.mode = 1;
			gTS.wait_beam = 0;
			break;
			
		case 7: //WAS
			if ((gMC.flag & 8) == 0)
				break;
			gTS.mode = 1;
			gTS.wait_beam = 0;
			break;
			
		case 6: //YNJ
			if (gTS.wait < 16)
			{
				gTS.wait++;
			}
			else
			{
				//Select option
				if (gKeyTrg & gKeyOk)
				{
					//PlaySoundObject(18, SOUND_MODE_PLAY);
					
					if (gTS.select == 1)
					{
						JumpTextScript(gTS.next_event);
					}
					else
					{
						gTS.mode = 1;
						gTS.wait_beam = 0;
					}
				}
				//Yes
				else if (gKeyTrg & gKeyLeft)
				{
					gTS.select = 0;
					//PlaySoundObject(1, SOUND_MODE_PLAY);
				}
				//No
				else if (gKeyTrg & gKeyRight)
				{
					gTS.select = 1;
					//PlaySoundObject(1, SOUND_MODE_PLAY);
				}
			}
			break;
	}
	
	if (gTS.mode == 0)
		g_GameFlags &= ~4;
	else
		g_GameFlags |= 4;
}
