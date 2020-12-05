#include "selstage.h"
#include <string.h>

//Permit stages
PERMIT_STAGE gPermitStage[PERMIT_STAGE_MAX];

void ClearPermitStage()
{
	memset(gPermitStage, 0, sizeof(gPermitStage));
}

BOOL AddPermitStage(s32 index, s32 event)
{
	s32 i = 0;
	
	while (i < PERMIT_STAGE_MAX)
	{
		if (gPermitStage[i].index == index)
			break;
		if (gPermitStage[i].index == 0)
			break;
		i++;
	}
	
	if (i == PERMIT_STAGE_MAX)
		return FALSE;
	
	gPermitStage[i].index = index;
	gPermitStage[i].event = event;
	
	return TRUE;
}

BOOL SubPermitStage(s32 index)
{
	s32 i;
	
	for (i = 0; i < PERMIT_STAGE_MAX; i++)
		if (gPermitStage[i].index == index)
			break;
	
	if (i == PERMIT_STAGE_MAX)
		return FALSE;
	
	for (i++; i < PERMIT_STAGE_MAX; i++)
		gPermitStage[i - 1] = gPermitStage[i];
	
	gPermitStage[i - 1].index = 0;
	gPermitStage[i - 1].event = 0;
	
	return TRUE;
}
