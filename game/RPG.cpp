

#include "../idlib/precompiled.h"
#pragma hdrstop



#include "RPG.h"
#include "Actor.h"
#include "Game_Local.h"





void hurt(idActor* A, int dmg)
{
	if (A == 0)
	{
		return;
	}

	int curr = A->HP;

	curr -= dmg;

	A->HP = curr; //pls no die
	

}


void attack(idActor* attacker, bool basic, idActor* defender) //dmg is calculated as ATK*Weapon - DEF*Armor
{
	if (attacker == 0 || defender == 0)
	{
		return;
	}



	int atk = attacker->ATK;
	int atkSpd = attacker->SPD;
	if(attacker->lastUsed == ArmorPiercingBullets)
	{
		atk += 10;
	}

	
	if (attacker->lastUsed == BattlePowder)
	{
		atkSpd += 10;
	}
	

	int defSpd = defender->SPD;
	int def = defender->DEF;
	if(defender->lastUsed == PortableCover)
	{
		def += 10;
	}

	if (defender->lastUsed == BattlePowder)
	{
		defSpd += 10;
	}


	int dmg = 0; 
	if (basic) //because I ma bad at writing code, I have to use a bool for if we're using a basic or not
	{
		dmg = atk * calcDmg(attacker->BasicEquiped);
	}
	else 
	{
		dmg = atk * calcDmg(attacker->HeavyEquiped);
	}

	
	//I suffer
	int defp = def * calcDefVal(defender->ArmorEquiped);

	
	//Only runs if dmg-def is greater than 0
	if (dmg - defp > 0)
	{
		hurt(defender, dmg);
	}
	

	
	return;

}




void attackBasic(idActor* attacker, idActor* defender)
{
	if (attacker == 0 || defender == 0)
	{
		return;
	}

	//for now, we'll pretend STATS don't exist and simply apply DMG based upon the weapon index+1 - armor index

	int weapon = attacker->BasicEquiped;

	int armor = defender->ArmorEquiped;

	int dmg = ((weapon + 1) * attacker->ATK) - (armor * defender->DEF); //We'll have a bit more complex dmg equation later

	if (dmg >= 1) //only run hurt() if we'll actually be dealing dmg
	{
		hurt(defender, dmg);
	}

	return;

}

void attackHeavy(idActor* attacker, idActor* defender)
{
	if (attacker == 0 || defender == 0)
	{
		return;
	}
	//for now, we'll pretend STATS don't exist and simply apply DMG based upon the weapon (index+1)*5 - armor index+1*2

	int weapon = attacker->BasicEquiped;

	int armor = defender->ArmorEquiped;

	int dmg = ((weapon + 1) * attacker->ATK)*5  - ((armor)*defender->DEF)*2; //We'll have a bit more complex dmg equation later

	if (dmg >= 1) //only run hurt() if we'll actually be dealing dmg
	{
		hurt(defender, dmg);
	}

	return;

}


//We'll probably be determining things on a case by case basis, which will make me want to die <3
void special(idActor* attacker, idActor* defender, int Case)
{
	if (attacker == 0 || defender == 0)
	{
		return;
	}



	return;

}



void RPGMenu()
{
	uiManager->ListGuis();
}



bool xpThresh()
{
	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player == 0)
	{
		return false;
	}

	if (player->xp >= 100)
	{
		return true;
	}



	return false;
}

void levelUp()
{

	idPlayer* player = gameLocal.GetLocalPlayer();
	if (player == 0)
	{
		return;
	}

	player->xp -= 100;
	player->ATK +=5;
	player->DEF +=5;
	player->SPD +=5;
	player->maxHP += 25;

	gameLocal.Printf("Leveled Up!");


	return;
}

void Machine()
{
	PhaseMachine phase = START;
	//RPGUI = NULL;
	//RPGUI = uiManager->FindGui("guis/RPGMenu.gui"); //This should hopefully load the UI

	idActor *enemy = new idActor();
	idPlayer *player = gameLocal.GetLocalPlayer();
	idActor *target = nullptr; //used for item usage



	if (enemy == 0 || player == 0)
	{
		gameLocal.Printf("NULL POINTERS, EXITING COMBAT");
	}


	enemy->setLoadout(enemy, Enemy, Helmet, Rocket);
	enemy->setStats(enemy, 150, 1, 1, 1);


	//This is for testing, in the future, combat should
	enemy->HP = enemy->maxHP;
	player->HP = player->maxHP;


	

	gameLocal.Printf("Player Loadout: %u, %u, %u, HP: %u", player->BasicEquiped, player->ArmorEquiped, player->HeavyEquiped, player->HP);
	gameLocal.Printf("Enemy Loadout: %u, %u, %u, HP: %u", enemy->BasicEquiped, enemy->ArmorEquiped, enemy->HeavyEquiped, enemy->HP);

	bool basic, heavy;
	item i;
	

	heavy = true;

	Choice c = ATTACK;


	while (true)
	{
		switch (phase)
		{
		case START:
			gameLocal.Printf("GLORIOUS COMBAT!\n");
			phase = SELECT;
			continue;
		case SELECT:
			gameLocal.Printf("GLORIOUS SELECTIONS!\n");



			//TODO, REPLACE THESE IFS WITH PROPER EVENT UI HANDLING

			switch(c)
			{
			case ATTACK:
				phase = ATK_MENU;
				break;
			case DEFEND:
				phase = DEF_MENU;
				break;
			case ITEM:
				phase = ITM_MENU;
				break;
			}

			continue;
		case ATK_MENU:
			gameLocal.Printf("GLORIOUS ATTACK MENU!\n");

			//TODO SET UP PROPER EVENT HANDLING FOR WEAPON CHOICE




			phase = ATK_ACT;
			continue;
		case ATK_ACT:
			gameLocal.Printf("GLORIOUS ATTACK ACTION\n");

			if (basic)
			{
				attack(player, true,enemy);
			}
			else if (heavy)
			{
				attack(player, false, enemy);
			}
			gameLocal.Printf("Enemy HP: %u", enemy->HP);
			phase = DEF_ACT;
			continue;


		case DEF_MENU:
			gameLocal.Printf("GLORIOUS DEFENSIVE MANEUVER!\n");

			phase = DEF_ACT;
			continue;

		case DEF_ACT:
			gameLocal.Printf("GLORIOUS DODGING!\n");

			//TODO, Add randomness to enemy actions


			attackHeavy(enemy, player);




			gameLocal.Printf("player HP: %u", player->HP);
			phase = END;
			continue;

		case ITM_MENU:

			//I'll have some better code for how targeting works but for now, this is good enough



			i = Grenade;
			target = enemy;
			
			phase = ITM_USE;
			continue;

		case ITM_USE:

			useItem(i, player, target);

			phase = END;

			continue;



		case END:
			gameLocal.Printf("GLORIOUS END!\n");
			player->xp += 5;
			while (xpThresh())
			{
				levelUp();
			}

			return;

		case DEFEAT:
			gameLocal.Printf("EMBARASSING FAILURE\n");
			return;



		default:
			return;
		}
	}


}
















