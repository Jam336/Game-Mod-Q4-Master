

#include "../idlib/precompiled.h"
#pragma hdrstop



#include "RPG.h"
#include "Actor.h"





//idUserInterfaceManager* uiManager = NULL;


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
	if(attacker->lastUsed == ArmorPiercingBullets)
	{
		atk += 10;
	}
	
	int def = defender->DEF;
	if(defender->lastUsed == PortableCover)
	{
		def += 10;
	}


	int dmg; 
	if (basic) //because I ma bad at writing code, I have to use a bool for if we're using a basic or not
	{
		dmg == atk * calcDmg(attacker->BasicEquiped);
	}
	else 
	{
		dmg = atk * calcDmg(attacker->HeavyEquiped);
	}

	
	//I suffer
	def = def * calcDefVal(defender->ArmorEquiped);

	
	//Only runs if dmg-def is greater than 0
	if (dmg - def > 0)
	{
		hurt(defender, dmg);
	}
	

	


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

	idActor *enemy = new idActor();
	idPlayer *player = gameLocal.GetLocalPlayer();

	if (enemy == 0 || player == 0)
	{
		gameLocal.Printf("NULL POINTERS, EXITING COMBAT");
	}


	enemy->setLoadout(enemy, 2, 1, 3);
	enemy->setStats(enemy, 150, 1, 1, 1);


	//This is for testing, in the future, combat should
	enemy->HP = enemy->maxHP;
	player->HP = player->maxHP;

	

	gameLocal.Printf("Player Loadout: %u, %u, %u, HP: %u", player->BasicEquiped, player->ArmorEquiped, player->HeavyEquiped, player->HP);
	gameLocal.Printf("Enemy Loadout: %u, %u, %u, HP: %u", enemy->BasicEquiped, enemy->ArmorEquiped, enemy->HeavyEquiped, enemy->HP);

	bool attacking, defend, item, basic, heavy;

	attacking = true;

	heavy = true;


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

			if (attacking)
			{
				phase = ATK_MENU;
			}
			else if (defend)
			{
				phase = DEF_MENU;
			}
			else if (item)
			{
				phase = ITM_MENU;
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

		case END:
			gameLocal.Printf("GLORIOUS END!\n");
			player->xp += 5;
			while (xpThresh())
			{
				levelUp();
			}



			return;





		default:
			return;
		}
	}






}
















