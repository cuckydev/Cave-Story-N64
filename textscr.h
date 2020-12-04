#ifndef TEXTSCR_H
#define TEXTSCR_H

#include <ultra64.h>
#include "game_def.h"

//Text script structure
typedef struct TEXT_SCRIPT
{
	//Script data
	BOOL head;
	const char *data;
	
	//Mode (ex. NOD, WAI)
	s8 mode;
	
	//Flags
	u8 flags;
	
	//Current positions (read position in buffer, x position in line)
	const char *p_read;
	s32 p_write;

	//Current line to write to
	s32 line;

	//Line y positions
	s32 ypos_line[4];
	
	//Event stuff
	s32 wait;
	s32 wait_next;
	s32 next_event;
	
	//Yes/no selected
	s8 select;
	
	//Current face
	s32 face;
	s32 face_x;

	//Current item
	s32 item;
	s32 item_y;

	//NOD cursor blink
	u8 wait_beam;
} TEXT_SCRIPT;

extern TEXT_SCRIPT gTS;

//Text script functions
void InitTextScript();
void LoadTextScript_Stage(const char *script);
void LoadTextScript(const char *script);
const char *GetTextScript();
void StartTextScript(s32 no);
void PutTextScript();
s32 TextScriptProc();

#endif
