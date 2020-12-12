#include "npchar.h"
#include "flags.h"
#include "caret.h"
#include "mychar.h"
#include "npctbl.h"
#include "draw.h"
#include "sound.h"
#include "valueview.h"
#include "armsitem.h"
#include <string.h>

#define SHOW_UNIMPLEMENTED_NPCS

//NPC globals
NPCHAR gNPC[NPC_MAX];
s32 gCurlyShoot_wait;
s32 gCurlyShoot_x;
s32 gCurlyShoot_y;
s32 gSuperXpos;
s32 gSuperYpos;

//NPC functions
#include "data/npc_tbl.inc.c"

static void SetUniqueParameter(NPCHAR *npc)
{
	s32 code = npc->code_char;
	npc->hit_voice = gNpcTable[code].hit_voice;
	npc->destroy_voice = gNpcTable[code].destroy_voice;
	npc->damage = gNpcTable[code].damage;
	npc->size = gNpcTable[code].size;
	npc->life = gNpcTable[code].life;
	npc->hit.front = gNpcTable[code].hit.front * 0x200;
	npc->hit.back = gNpcTable[code].hit.back * 0x200;
	npc->hit.top = gNpcTable[code].hit.top * 0x200;
	npc->hit.bottom = gNpcTable[code].hit.bottom * 0x200;
	npc->view.front = gNpcTable[code].view.front * 0x200;
	npc->view.back = gNpcTable[code].view.back * 0x200;
	npc->view.top = gNpcTable[code].view.top * 0x200;
	npc->view.bottom = gNpcTable[code].view.bottom * 0x200;
}

void InitNpChar()
{
	memset(gNPC, 0, sizeof(gNPC));
}

void LoadEvent(u32 events, const EVENT *event)
{
	s32 i, n;
	const EVENT *eve = event;
	
	//Clear NPCs and load new ones from the given event list
	memset(gNPC, 0, sizeof(gNPC));
	
	n = 170;
	for (i = 0; i < events; i++, n++, eve++)
	{
		//Set NPC parameters
		gNPC[n].direct = (eve->bits & NPC_SPAWN_IN_OTHER_DIRECTION) ? 2 : 0;
		gNPC[n].code_char = eve->code_char;
		gNPC[n].code_event = eve->code_event;
		gNPC[n].code_flag = eve->code_flag;
		gNPC[n].x = eve->x * 0x10 * 0x200;
		gNPC[n].y = eve->y * 0x10 * 0x200;
		gNPC[n].bits = eve->bits;
		gNPC[n].bits |= gNpcTable[gNPC[n].code_char].bits;
		gNPC[n].exp = gNpcTable[gNPC[n].code_char].exp;
		SetUniqueParameter(&gNPC[n]);
		
		//Check flags
		if (gNPC[n].bits & NPC_APPEAR_WHEN_FLAG_SET)
		{
			if (GetNPCFlag(gNPC[n].code_flag) == TRUE)
				gNPC[n].cond |= 0x80;
		}
		else if (gNPC[n].bits & NPC_HIDE_WHEN_FLAG_SET)
		{
			if (GetNPCFlag(gNPC[n].code_flag) == FALSE)
				gNPC[n].cond |= 0x80;
		}
		else
		{
			gNPC[n].cond = 0x80;
		}
	}
}

void SetNpChar(s32 code_char, s32 x, s32 y, s32 xm, s32 ym, s32 dir, NPCHAR *npc, s32 start_index)
{
	s32 n = start_index;
	while (n < NPC_MAX && gNPC[n].cond)
		n++;
	
	if (n == NPC_MAX)
		return;
	
	//Set NPC parameters
	memset(&gNPC[n], 0, sizeof(NPCHAR));
	gNPC[n].cond |= 0x80;
	gNPC[n].direct = dir;
	gNPC[n].code_char = code_char;
	gNPC[n].x = x;
	gNPC[n].y = y;
	gNPC[n].xm = xm;
	gNPC[n].ym = ym;
	gNPC[n].pNpc = npc;
	gNPC[n].bits = gNpcTable[gNPC[n].code_char].bits;
	gNPC[n].exp = gNpcTable[gNPC[n].code_char].exp;
	SetUniqueParameter(&gNPC[n]);
}

void SetDestroyNpChar(s32 x, s32 y, s32 w, s32 num)
{
	s32 i;
	s32 offset_x;
	s32 offset_y;
	
	//Create smoke
	w /= 0x200;
	for (i = 0; i < num; i++)
	{
		offset_x = Random(-w, w) * 0x200;
		offset_y = Random(-w, w) * 0x200;
		SetNpChar(4, x + offset_x, y + offset_y, 0, 0, 0, NULL, 0x100);
	}
	
	//Flash effect
	SetCaret(x, y, 12, 0);
}

void SetDestroyNpCharUp(s32 x, s32 y, s32 w, s32 num)
{
	s32 i;
	s32 offset_x;
	s32 offset_y;
	
	//Create smoke
	w /= 0x200;
	for (i = 0; i < num; i++)
	{
		offset_x = Random(-w, w) * 0x200;
		offset_y = Random(-w, w) * 0x200;
		SetNpChar(4, x + offset_x, y + offset_y, 0, 0, 1, NULL, 0x100);
	}
	
	//Flash effect
	SetCaret(x, y, 12, 0);
}

void SetExpObjects(s32 x, s32 y, s32 exp)
{
	s32 n;
	s32 sub_exp;
	
	n = 0x100;
	while (exp)
	{
		while (n < NPC_MAX && gNPC[n].cond)
			n++;
		
		if (n == NPC_MAX)
			break;
		
		memset(&gNPC[n], 0, sizeof(NPCHAR));
		
		if (exp >= 20)
		{
			exp -= 20;
			sub_exp = 20;
		}
		else if (exp >= 5)
		{
			exp -= 5;
			sub_exp = 5;
		}
		else if (exp >= 1)
		{
			exp -= 1;
			sub_exp = 1;
		}
		
		gNPC[n].cond |= 0x80;
		gNPC[n].direct = 0;
		gNPC[n].code_char = 1;
		gNPC[n].x = x;
		gNPC[n].y = y;
		gNPC[n].bits = gNpcTable[gNPC[n].code_char].bits;
		gNPC[n].exp = sub_exp;
		
		SetUniqueParameter(&gNPC[n]);
	}
}

BOOL SetBulletObject(s32 x, s32 y, s32 val)
{
	s32 n;
	s32 bullet_no;	// The Linux debug data claims there's a 3-line gap between this and the next variable declaration. Just enough space for an 'if' statement.
	s32 tamakazu_ari[10];
	s32 t = 0;
	
	memset(tamakazu_ari, 0, sizeof(tamakazu_ari));
	
	for (n = 0; n < 8; n++)
	{
		switch (gArmsData[n].code)
		{
			case 5:
				tamakazu_ari[t++] = 0;
				break;
				
			case 10:
				tamakazu_ari[t++] = 1;
				break;
				
			default:
				tamakazu_ari[t] = 0;
				break;
		}
	}
	
	if (t == 0)
		return FALSE;
	
	n = Random(1, 10 * t);
	bullet_no = tamakazu_ari[n % t];
	
	n = 0x100;
	while (n < NPC_MAX && gNPC[n].cond)
		n++;
	
	if (n == NPC_MAX)
		return FALSE;
	
	memset(&gNPC[n], 0, sizeof(NPCHAR));
	gNPC[n].cond |= 0x80;
	gNPC[n].direct = 0;
	gNPC[n].code_event = bullet_no;
	gNPC[n].code_char = 86;
	gNPC[n].x = x;
	gNPC[n].y = y;
	gNPC[n].bits = gNpcTable[gNPC[n].code_char].bits;
	gNPC[n].exp = val;
	SetUniqueParameter(&gNPC[n]);
	return TRUE;
}

BOOL SetLifeObject(s32 x, s32 y, s32 val)
{
	s32 n = 0x100;
	while (n < NPC_MAX && gNPC[n].cond)
		n++;
	
	if (n == NPC_MAX)
		return FALSE;
	
	memset(&gNPC[n], 0, sizeof(NPCHAR));
	gNPC[n].cond |= 0x80;
	gNPC[n].direct = 0;
	gNPC[n].code_char = 87;
	gNPC[n].x = x;
	gNPC[n].y = y;
	gNPC[n].bits = gNpcTable[gNPC[n].code_char].bits;
	gNPC[n].exp = val;
	SetUniqueParameter(&gNPC[n]);
	return TRUE;
}

void VanishNpChar(NPCHAR *npc)
{
	s32 x, y;
	
	x = npc->x;
	y = npc->y;
	memset(npc, 0, sizeof(NPCHAR));
	npc->count1 = 0;
	npc->x = x;
	npc->y = y;
	npc->cond |= 0x80;
	npc->direct = 0;
	npc->code_char = 3;
	npc->bits = gNpcTable[npc->code_char].bits;
	npc->exp = gNpcTable[npc->code_char].exp;
	SetUniqueParameter(npc);
}

static BOOL NpCharVisible(NPCHAR *npc, s32 fx, s32 fy)
{
	s32 lx = (npc->x / 0x200) - (fx / 0x200);
	s32 ly = (npc->y / 0x200) - (fy / 0x200);
	s32 pl, pt, pr, pb;
	if (npc->direct)
	{
		pl = npc->view.back / 0x200;
		pr = npc->view.front / 0x200;
	}
	else
	{
		pl = npc->view.front / 0x200;
		pr = npc->view.back / 0x200;
	}
	pt = npc->view.top / 0x200;
	pb = npc->view.bottom / 0x200;
	return (lx > -pr && ly > -pb && lx < (SCREEN_WIDTH + pl) && ly < (SCREEN_HEIGHT + pt));
}

void PutNpChar(s32 fx, s32 fy)
{
	s32 i, a;
	for (i = 0; i < NPC_MAX; i++)
	{
		if (!(gNPC[i].cond & 0x80))
			continue;
		
		if (gpNpcFuncTbl[gNPC[i].code_char].put != NULL && NpCharVisible(&gNPC[i], fx, fy))
		{
			if (gNPC[i].shock)
			{
				a = 2 * ((gNPC[i].shock / 2) % 2) - 1;
			}
			else
			{
				a = 0;
				if (gNPC[i].bits & NPC_SHOW_DAMAGE && gNPC[i].damage_view)
				{
					SetValueView(&gNPC[i].x, &gNPC[i].y, gNPC[i].damage_view);
					gNPC[i].damage_view = 0;
				}
			}
			
			gpNpcFuncTbl[gNPC[i].code_char].put(&gNPC[i],
				((gNPC[i].x - (gNPC[i].direct ? gNPC[i].view.back : gNPC[i].view.front)) / 0x200) - (fx / 0x200) + a,
				((gNPC[i].y - gNPC[i].view.top) / 0x200) - (fy / 0x200)
			);
		}
		else
		{
			if (gNPC[i].shock == 0 && gNPC[i].bits & NPC_SHOW_DAMAGE && gNPC[i].damage_view)
			{
				SetValueView(&gNPC[i].x, &gNPC[i].y, gNPC[i].damage_view);
				gNPC[i].damage_view = 0;
			}
			#ifdef SHOW_UNIMPLEMENTED_NPCS
			if (gpNpcFuncTbl[gNPC[i].code_char].act == NULL && NpCharVisible(&gNPC[i], fx, fy))
			{
				char text[0x10];
				sprintf(text, "%d", gNPC[i].code_char);
				PutText(
					((gNPC[i].x - (gNPC[i].direct ? gNPC[i].view.back : gNPC[i].view.front)) / 0x200) - (fx / 0x200) + a,
					((gNPC[i].y - gNPC[i].view.top) / 0x200) - (fy / 0x200),
					text,
					RGB(0xFF, 0xFF, 0xFF));
			}
			#endif
		}
	}
}

void ActNpChar()
{
	s32 i;
	for (i = 0; i < NPC_MAX; i++)
	{
		if (gNPC[i].cond & 0x80)
		{
			if (gpNpcFuncTbl[gNPC[i].code_char].act != NULL)
				gpNpcFuncTbl[gNPC[i].code_char].act(&gNPC[i]);
			if (gNPC[i].shock)
				gNPC[i].shock--;
		}
	}
}

void ChangeNpCharByEvent(s32 code_event, s32 code_char, s32 dir)
{
	s32 n;
	for (n = 0; n < NPC_MAX; n++)
	{
		if ((gNPC[n].cond & 0x80) && gNPC[n].code_event == code_event)
		{
			gNPC[n].bits &= ~(NPC_SOLID_SOFT | NPC_IGNORE_TILE_44 | NPC_INVULNERABLE | NPC_IGNORE_SOLIDITY | NPC_BOUNCY | NPC_SHOOTABLE | NPC_SOLID_HARD | NPC_REAR_AND_TOP_DONT_HURT | NPC_SHOW_DAMAGE);	// Clear these flags
			gNPC[n].code_char = code_char;
			gNPC[n].bits |= gNpcTable[gNPC[n].code_char].bits;
			gNPC[n].exp = gNpcTable[gNPC[n].code_char].exp;
			SetUniqueParameter(&gNPC[n]);
			gNPC[n].cond |= 0x80;
			gNPC[n].act_no = 0;
			gNPC[n].act_wait = 0;
			gNPC[n].count1 = 0;
			gNPC[n].count2 = 0;
			gNPC[n].ani_no = 0;
			gNPC[n].ani_wait = 0;
			gNPC[n].xm = 0;
			gNPC[n].ym = 0;
			
			if (dir == 5)
			{
				//Nothing
			}
			else if (dir == 4)
			{
				if (gNPC[n].x < gMC.x)
					gNPC[n].direct = 2;
				else
					gNPC[n].direct = 0;
			}
			else
			{
				gNPC[n].direct = dir;
			}
			
			if (gpNpcFuncTbl[code_char].act != NULL)
				gpNpcFuncTbl[code_char].act(&gNPC[n]);
		}
	}
}

void ChangeCheckableNpCharByEvent(s32 code_event, s32 code_char, s32 dir)
{
	s32 n;
	
	for (n = 0; n < NPC_MAX; n++)
	{
		if (!(gNPC[n].cond & 0x80) && gNPC[n].code_event == code_event)
		{
			gNPC[n].bits &= ~(NPC_SOLID_SOFT | NPC_IGNORE_TILE_44 | NPC_INVULNERABLE | NPC_IGNORE_SOLIDITY | NPC_BOUNCY | NPC_SHOOTABLE | NPC_SOLID_HARD | NPC_REAR_AND_TOP_DONT_HURT | NPC_SHOW_DAMAGE);	// Clear these flags
			gNPC[n].bits |= NPC_INTERACTABLE;
			gNPC[n].code_char = code_char;
			gNPC[n].bits |= gNpcTable[gNPC[n].code_char].bits;
			gNPC[n].exp = gNpcTable[gNPC[n].code_char].exp;
			SetUniqueParameter(&gNPC[n]);
			gNPC[n].cond |= 0x80;
			gNPC[n].act_no = 0;
			gNPC[n].act_wait = 0;
			gNPC[n].count1 = 0;
			gNPC[n].count2 = 0;
			gNPC[n].ani_no = 0;
			gNPC[n].ani_wait = 0;
			gNPC[n].xm = 0;
			gNPC[n].ym = 0;
			
			if (dir == 5)
			{
				//Nothing
			}
			else if (dir == 4)
			{
				if (gNPC[n].x < gMC.x)
					gNPC[n].direct = 2;
				else
					gNPC[n].direct = 0;
			}
			else
			{
				gNPC[n].direct = dir;
			}
			
			if (gpNpcFuncTbl[code_char].act != NULL)
				gpNpcFuncTbl[code_char].act(&gNPC[n]);
		}
	}
}

void SetNpCharActionNo(s32 code_event, s32 act_no, s32 dir)
{
	s32 n = 0;
	while (n < NPC_MAX)
	{
		if ((gNPC[n].cond & 0x80) && gNPC[n].code_event == code_event)
			break;
		n++;
	}
	
	if (n == NPC_MAX)
		return;
	
	gNPC[n].act_no = act_no;
	
	if (dir == 5)
	{
		//Nothing
	}
	else if (dir == 4)
	{
		if (gNPC[n].x < gMC.x)
			gNPC[n].direct = 2;
		else
			gNPC[n].direct = 0;
	}
	else
	{
		gNPC[n].direct = dir;
	}
}

void MoveNpChar(s32 code_event, s32 x, s32 y, s32 dir)
{
	s32 n = 0;
	while (n < NPC_MAX)
	{
		if ((gNPC[n].cond & 0x80) && gNPC[n].code_event == code_event)
			break;
		n++;
	}
	
	if (n == NPC_MAX)
		return;
	
	gNPC[n].x = x;
	gNPC[n].y = y;
	
	if (dir == 5)
	{
		//Nothing
	}
	else if (dir == 4)
	{
		if (gNPC[n].x < gMC.x)
			gNPC[n].direct = 2;
		else
			gNPC[n].direct = 0;
	}
	else
	{
		gNPC[n].direct = dir;
	}
}

void BackStepMyChar(s32 code_event)
{
	s32 n = 0;
	
	gMC.cond &= ~1;
	gMC.ym = -0x200;
	
	if (code_event == 0)
	{
		gMC.direct = 0;
		gMC.xm = 0x200;
	}
	else if (code_event == 2)
	{
		gMC.direct = 2;
		gMC.xm = -0x200;
	}
	else
	{
		while (n < NPC_MAX)
		{
			if ((gNPC[n].cond & 0x80) && gNPC[n].code_event == code_event)
				break;
			n++;
		}
		
		if (n == NPC_MAX)
			return;

		if (gNPC[n].x < gMC.x)
		{
			gMC.direct = 0;
			gMC.xm = 0x200;
		}
		else
		{
			gMC.direct = 2;
			gMC.xm = -0x200;
		}
	}
}

void DeleteNpCharEvent(s32 code)
{
	s32 i;
	for (i = 0; i < NPC_MAX; i++)
	{
		if ((gNPC[i].cond & 0x80) && gNPC[i].code_event == code)
		{
			gNPC[i].cond = 0;
			SetNPCFlag(gNPC[i].code_flag);
		}
	}
}

void DeleteNpCharCode(s32 code, BOOL bSmoke)
{
	s32 n;
	for (n = 0; n < NPC_MAX; n++)
	{
		if ((gNPC[n].cond & 0x80) && gNPC[n].code_char == code)
		{
			gNPC[n].cond = 0;
			SetNPCFlag(gNPC[n].code_flag);
			
			if (bSmoke)
			{
				PlaySoundObject(gNPC[n].destroy_voice, 1);
				
				switch (gNPC[n].size)
				{
					case 1:
						SetDestroyNpChar(gNPC[n].x, gNPC[n].y, gNPC[n].view.back, 4);
						break;
						
					case 2:
						SetDestroyNpChar(gNPC[n].x, gNPC[n].y, gNPC[n].view.back, 8);
						break;
						
					case 3:
						SetDestroyNpChar(gNPC[n].x, gNPC[n].y, gNPC[n].view.back, 16);
						break;
				}
			}
		}
	}
}

void GetNpCharPosition(s32 *x, s32 *y, s32 i)
{
	*x = gNPC[i].x;
	*y = gNPC[i].y;
}

BOOL IsNpCharCode(s32 code)
{
	s32 i;
	for (i = 0; i < NPC_MAX; i++)
		if ((gNPC[i].cond & 0x80) && gNPC[i].code_char == code)
			return TRUE;
	return FALSE;
}

BOOL GetNpCharAlive(s32 code_event)
{
	s32 i;
	for (i = 0; i < NPC_MAX; i++)
		if ((gNPC[i].cond & 0x80) && gNPC[i].code_event == code_event)
			break;
	
	if (i < NPC_MAX)
		return TRUE;
	else
		return FALSE;
}

s32 CountAliveNpChar()
{
	s32 n;
	s32 count = 0;
	
	for (n = 0; n < NPC_MAX; n++)
		if (gNPC[n].cond & 0x80)
			count++;
	
	return count;
}
