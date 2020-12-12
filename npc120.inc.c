//NPC 125 - Hidden item
void Npc125_Act(NPCHAR *npc)
{
	if (npc->life < 990)
	{
		SetDestroyNpChar(npc->x, npc->y, npc->view.back, 8);
		PlaySoundObject(70, 1);
		if (npc->direct == 0)
			SetNpChar(87, npc->x, npc->y, 0, 0, 2, NULL, 0);
		else
			SetNpChar(86, npc->x, npc->y, 0, 0, 2, NULL, 0);
		npc->cond = 0;
	}
}
