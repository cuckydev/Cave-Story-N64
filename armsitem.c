#include "armsitem.h"
#include "sound.h"
#include "shoot.h"
#include <string.h>

//Globals
ARMS gArmsData[ARMS_MAX];
ITEM gItemData[ITEM_MAX];

s32 gSelectedArms;
s32 gSelectedItem;

s32 gArmsEnergyX = 16;

void ClearArmsData()
{
	gSelectedArms = 0;
	gArmsEnergyX = 32;
	memset(gArmsData, 0, sizeof(gArmsData));
}

void ClearItemData()
{
	memset(gItemData, 0, sizeof(gItemData));
}

//Arms
BOOL AddArmsData(s32 code, s32 max_num)
{
	//Search for code
	s32 i = 0;
	while (i < ARMS_MAX)
	{
		if (gArmsData[i].code == code)
			break;	//Found identical
		if (gArmsData[i].code == 0)
			break;	//Found free slot
		i++;
	}
	
	if (i == ARMS_MAX)
		return FALSE;	//No space left
	
	if (gArmsData[i].code == 0)
	{
		//Initialize new weapon
		memset(&gArmsData[i], 0, sizeof(ARMS));
		gArmsData[i].level = 1;
	}
	
	//Set weapon and ammo
	gArmsData[i].code = code;
	gArmsData[i].max_num += max_num;
	gArmsData[i].num += max_num;
	
	//Cap the amount of current ammo to the maximum amount of ammo
	if (gArmsData[i].num > gArmsData[i].max_num)
		gArmsData[i].num = gArmsData[i].max_num;
	
	return TRUE;
}

BOOL SubArmsData(s32 code)
{
	//Search for code
	s32 i;
	for (i = 0; i < ARMS_MAX; i++)
		if (gArmsData[i].code == code)
			break;	//Found
	
	if (i == ARMS_MAX)
		return FALSE;	//Not found
	
	//Shift all arms from the right to the left
	for (i++; i < ARMS_MAX; i++)
		gArmsData[i - 1] = gArmsData[i];
	
	//Clear farthest weapon and select first
	gArmsData[i - 1].code = 0;
	gSelectedArms = 0;
	
	return TRUE;
}

BOOL TradeArms(s32 code1, s32 code2, s32 max_num)
{
	//Search for code1
	s32 i = 0;
	while (i < ARMS_MAX)
	{
		if (gArmsData[i].code == code1)
			break;	//Found identical
		i++;
	}
	
	if (i == ARMS_MAX)
		return FALSE;	//Not found
	
	//Initialize new weapon replacing old one, but adding the maximum ammunition to that of the old weapon.
	gArmsData[i].level = 1;
	gArmsData[i].code = code2;
	gArmsData[i].max_num += max_num;
	gArmsData[i].num += max_num;
	gArmsData[i].exp = 0;
	
	return TRUE;
}

BOOL CheckArms(s32 a)
{
	s32 i;
	for (i = 0; i < ARMS_MAX; i++)
		if (gArmsData[i].code == a)
			return TRUE;	//Found
	return FALSE;	//Not found
}

BOOL UseArmsEnergy(s32 num)
{
	if (gArmsData[gSelectedArms].max_num == 0)
		return TRUE;	//No ammo needed
	if (gArmsData[gSelectedArms].num == 0)
		return FALSE;	//No ammo left
	
	gArmsData[gSelectedArms].num -= num;
	if (gArmsData[gSelectedArms].num < 0)
		gArmsData[gSelectedArms].num = 0;
	
	return TRUE;	//Was able to spend ammo
}

BOOL ChargeArmsEnergy(s32 num)
{
	gArmsData[gSelectedArms].num += num;
	if (gArmsData[gSelectedArms].num > gArmsData[gSelectedArms].max_num)
		gArmsData[gSelectedArms].num = gArmsData[gSelectedArms].max_num;
	return TRUE;	//Always successfull
}

void FullArmsEnergy()
{
	s32 a;
	for (a = 0; a < ARMS_MAX; a++)
	{
		if (gArmsData[a].code == 0)
			continue;	//Don't change empty weapons
		gArmsData[a].num = gArmsData[a].max_num;
	}
}

s32 RotationArms()
{
	// Get amount of weapons
	s32 arms_num = 0;
	while (gArmsData[arms_num].code != 0)
		arms_num++;
	
	if (arms_num == 0)
		return 0;
	
	ResetSpurCharge();
	
	//Select next valid weapon
	gSelectedArms++;
	while (gSelectedArms < arms_num)
	{
		if (gArmsData[gSelectedArms].code)
			break;
		gSelectedArms++;
	}
	if (gSelectedArms == arms_num)
		gSelectedArms = 0;
	
	gArmsEnergyX = 32;
	PlaySoundObject(4, 1);
	
	return gArmsData[gSelectedArms].code;
}

s32 RotationArmsRev()
{
	// Get amount of weapons
	s32 arms_num = 0;
	while (gArmsData[arms_num].code != 0)
		++arms_num;
	
	if (arms_num == 0)
		return 0;
	
	ResetSpurCharge();
	
	// Select previous valid weapon
	gSelectedArms--;
	if (gSelectedArms < 0)
		gSelectedArms = arms_num - 1;
	
	while (gSelectedArms < arms_num)
	{
		if (gArmsData[gSelectedArms].code)
			break;
		gSelectedArms--;
	}
	
	gArmsEnergyX = 0;
	PlaySoundObject(4, 1);
	
	return gArmsData[gSelectedArms].code;
}

void ChangeToFirstArms()
{
	gSelectedArms = 0;
	gArmsEnergyX = 32;
	PlaySoundObject(4, 1);
}

//Item
BOOL AddItemData(s32 code)
{
	//Search for code
	s32 i = 0;
	while (i < ITEM_MAX)
	{
		if (gItemData[i].code == code)
			break;	//Found identical
		if (gItemData[i].code == 0)
			break;	//Found free slot
		i++;
	}
	
	if (i == ITEM_MAX)
		return FALSE;	//Not found
	
	gItemData[i].code = code;
	
	return TRUE;
}

BOOL SubItemData(s32 code)
{
	// Search for code
	s32 i;
	for (i = 0; i < ITEM_MAX; i++)
		if (gItemData[i].code == code)
			break;	//Found
	
	if (i == ITEM_MAX)
		return FALSE;	//Not found
	
	//Shift all items from the right to the left
	for (i++; i < ITEM_MAX; i++)
		gItemData[i - 1] = gItemData[i];
	
	gItemData[i - 1].code = 0;
	gSelectedItem = 0;
	
	return TRUE;
}

BOOL CheckItem(s32 a)
{
	s32 i;
	for (i = 0; i < ITEM_MAX; i++)
		if (gItemData[i].code == a)
			return TRUE;	//Found
	return FALSE;	//Not found
}
