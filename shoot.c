#include "shoot.h"
#include "armsitem.h"
#include "bullet.h"
#include "keycontrol.h"
#include "mychar.h"
#include "mycparam.h"
#include "caret.h"
#include "sound.h"

static s32 empty;

//Polar Star
void ShootBullet_PoleStar(s32 level)
{
	s32 bul_no;
	
	switch (level)
	{
		case 1:
			bul_no = 4;
			break;
		case 2:
			bul_no = 5;
			break;
		case 3:
			bul_no = 6;
			break;
	}
	
	if (CountArmsBullet(2) > 1)
		return;
	
	if (gKeyTrg & gKeyShot)
	{
		if (!UseArmsEnergy(1))
		{
			PlaySoundObject(37, 1);
		}
		else
		{
			if (gMC.up)
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (1 * 0x200), gMC.y - (8 * 0x200), 1);
					SetCaret(gMC.x - (1 * 0x200), gMC.y - (8 * 0x200), 3, 0);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (1 * 0x200), gMC.y - (8 * 0x200), 1);
					SetCaret(gMC.x + (1 * 0x200), gMC.y - (8 * 0x200), 3, 0);
				}
			}
			else if (gMC.down)
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (1 * 0x200), gMC.y + (8 * 0x200), 3);
					SetCaret(gMC.x - (1 * 0x200), gMC.y + (8 * 0x200), 3, 0);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (1 * 0x200), gMC.y + (8 * 0x200), 3);
					SetCaret(gMC.x + (1 * 0x200), gMC.y + (8 * 0x200), 3, 0);
				}
			}
			else
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (6 * 0x200), gMC.y + (3 * 0x200), 0);
					SetCaret(gMC.x - (12 * 0x200), gMC.y + (3 * 0x200), 3, 0);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (6 * 0x200), gMC.y + (3 * 0x200), 2);
					SetCaret(gMC.x + (12 * 0x200), gMC.y + (3 * 0x200), 3, 0);
				}
			}
			
			if (level == 3)
				PlaySoundObject(49, 1);
			else
				PlaySoundObject(32, 1);
		}
	}
}

//Missile Launcher
void ShootBullet_Missile(s32 level, BOOL bSuper)
{
	s32 bul_no;
	
	if (bSuper)
	{
		switch (level)
		{
			case 1:
				bul_no = 28;
				break;
			case 2:
				bul_no = 29;
				break;
			case 3:
				bul_no = 30;
				break;
		}
		
		switch (level)
		{
			case 1:
				if (CountArmsBullet(10) > 0)
					return;
				if (CountArmsBullet(11) > 0)
					return;
				break;
				
			case 2:
				if (CountArmsBullet(10) > 1)
					return;
				if (CountArmsBullet(11) > 1)
					return;
				break;
				
			case 3:
				if (CountArmsBullet(10) > 3)
					return;
				if (CountArmsBullet(11) > 3)
					return;
				break;
		}
	}
	else
	{
		switch (level)
		{
			case 1:
				bul_no = 13;
				break;
			case 2:
				bul_no = 14;
				break;
			case 3:
				bul_no = 15;
				break;
		}
		
		switch (level)
		{
			case 1:
				if (CountArmsBullet(5) > 0)
					return;
				if (CountArmsBullet(6) > 0)
					return;
				break;
				
			case 2:
				if (CountArmsBullet(5) > 1)
					return;
				if (CountArmsBullet(6) > 1)
					return;
				break;
				
			case 3:
				if (CountArmsBullet(5) > 3)
					return;
				if (CountArmsBullet(6) > 3)
					return;
				break;
		}
	}
	
	if (gKeyTrg & gKeyShot)
	{
		if (level < 3)
		{
			if (!UseArmsEnergy(1))
			{
				PlaySoundObject(37, 1);
				
				if (empty == 0)
				{
					SetCaret(gMC.x, gMC.y, 16, 0);
					empty = 50;
				}
				return;
			}

			if (gMC.up)
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (1 * 0x200), gMC.y - (8 * 0x200), 1);
					SetCaret(gMC.x - (1 * 0x200), gMC.y - (8 * 0x200), 3, 0);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (1 * 0x200), gMC.y - (8 * 0x200), 1);
					SetCaret(gMC.x + (1 * 0x200), gMC.y - (8 * 0x200), 3, 0);
				}
			}
			else if (gMC.down)
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (1 * 0x200), gMC.y + (8 * 0x200), 3);
					SetCaret(gMC.x - (1 * 0x200), gMC.y + (8 * 0x200), 3, 0);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (1 * 0x200), gMC.y + (8 * 0x200), 3);
					SetCaret(gMC.x + (1 * 0x200), gMC.y + (8 * 0x200), 3, 0);
				}
			}
			else
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (6 * 0x200), gMC.y, 0);
					SetCaret(gMC.x - (12 * 0x200), gMC.y, 3, 0);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (6 * 0x200), gMC.y, 2);
					SetCaret(gMC.x + (12 * 0x200), gMC.y, 3, 0);
				}
			}
		}
		else
		{
			if (!UseArmsEnergy(1))
			{
				PlaySoundObject(37, 1);
				
				if (empty == 0)
				{
					SetCaret(gMC.x, gMC.y, 16, 0);
					empty = 50;
				}
				return;
			}
			
			if (gMC.up)
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (1 * 0x200), gMC.y - (8 * 0x200), 1);
					SetCaret(gMC.x - (1 * 0x200), gMC.y - (8 * 0x200), 3, 0);
					SetBullet(bul_no, gMC.x + (3 * 0x200), gMC.y, 1);
					SetBullet(bul_no, gMC.x - (3 * 0x200), gMC.y, 1);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (1 * 0x200), gMC.y - (8 * 0x200), 1);
					SetCaret(gMC.x + (1 * 0x200), gMC.y - (8 * 0x200), 3, 0);
					SetBullet(bul_no, gMC.x + (3 * 0x200), gMC.y, 1);
					SetBullet(bul_no, gMC.x - (3 * 0x200), gMC.y, 1);
				}
			}
			else if (gMC.down)
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (1 * 0x200), gMC.y + (8 * 0x200), 3);
					SetCaret(gMC.x - (1 * 0x200), gMC.y + (8 * 0x200), 3, 0);
					SetBullet(bul_no, gMC.x + (3 * 0x200), gMC.y, 3);
					SetBullet(bul_no, gMC.x - (3 * 0x200), gMC.y, 3);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (1 * 0x200), gMC.y + (8 * 0x200), 3);
					SetCaret(gMC.x + (1 * 0x200), gMC.y + (8 * 0x200), 3, 0);
					SetBullet(bul_no, gMC.x - (3 * 0x200), gMC.y, 3);
					SetBullet(bul_no, gMC.x + (3 * 0x200), gMC.y, 3);
				}
			}
			else
			{
				if (gMC.direct == 0)
				{
					SetBullet(bul_no, gMC.x - (6 * 0x200), gMC.y + (1 * 0x200), 0);
					SetCaret(gMC.x - (12 * 0x200), gMC.y + (1 * 0x200), 3, 0);
					SetBullet(bul_no, gMC.x, gMC.y - (8 * 0x200), 0);
					SetBullet(bul_no, gMC.x + (4 * 0x200), gMC.y - (1 * 0x200), 0);
				}
				else
				{
					SetBullet(bul_no, gMC.x + (6 * 0x200), gMC.y + (1 * 0x200), 2);
					SetCaret(gMC.x + (12 * 0x200), gMC.y + (1 * 0x200), 3, 0);
					SetBullet(bul_no, gMC.x, gMC.y - (8 * 0x200), 2);
					SetBullet(bul_no, gMC.x - (4 * 0x200), gMC.y - (1 * 0x200), 2);
				}
			}
		}
		
		PlaySoundObject(32, 1);
	}
}

//Spur
s32 spur_charge;

void ResetSpurCharge()
{
	spur_charge = 0;
	if (gArmsData[gSelectedArms].code == 13)
		ZeroExpMyChar();
}

//Shoot bullet function
void ShootBullet()
{
	static s32 soft_rensha;
	
	if (empty != 0)
		empty--;
	
	//Only let the player shoot every 4 frames
	if (soft_rensha != 0)
		soft_rensha--;
	
	if (gKeyTrg & gKeyShot)
	{
		if (soft_rensha != 0)
			return;
		soft_rensha = 4;
	}
	
	// Run functions
	if (gMC.cond & 2)
		return;
	
	switch (gArmsData[gSelectedArms].code)
	{
		case 1:
			//ShootBullet_Frontia1(gArmsData[gSelectedArms].level);
			break;
		case 2:
			ShootBullet_PoleStar(gArmsData[gSelectedArms].level);
			break;
		case 3:
			//ShootBullet_FireBall(gArmsData[gSelectedArms].level);
			break;
		case 4:
			//ShootBullet_Machinegun1(gArmsData[gSelectedArms].level);
			break;
		case 5:
			ShootBullet_Missile(gArmsData[gSelectedArms].level, FALSE);
			break;
		case 7:
			switch (gArmsData[gSelectedArms].level)
			{
				case 1:
					//ShootBullet_Bubblin1();
					break;
				case 2:
					//ShootBullet_Bubblin2(2);
					break;
				case 3:
					//ShootBullet_Bubblin2(3);
					break;
			}
			break;
		case 9:
			switch (gArmsData[gSelectedArms].level)
			{
				case 1:
					//ShootBullet_Sword(1);
					break;
				case 2:
					//ShootBullet_Sword(2);
					break;
				case 3:
					//ShootBullet_Sword(3);
					break;
			}
			break;
		case 10:
			ShootBullet_Missile(gArmsData[gSelectedArms].level, TRUE);
			break;
		case 12:
			//ShootBullet_Nemesis(gArmsData[gSelectedArms].level);
			break;
		case 13:
			//ShootBullet_Spur(gArmsData[gSelectedArms].level);
			break;
	}
}
