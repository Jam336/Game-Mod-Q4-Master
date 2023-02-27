

#include "../idlib/precompiled.h"
#pragma hdrstop



#include "RPG.h"
#include "Actor.h"
#include "Game_Local.h"

//idPlayer *player;
//idActor *enemy;
//PhaseMachine phase;



RPG::RPG()
{
	RPGMenu = NULL;

}

void RPG::InitializeRPGMenu()
{
	RPGMenu = uiManager->FindGui("guis/mphud.gui", true, false, true);

	if (RPGMenu == NULL)
	{
		gameLocal.Printf("GUI NULL!!!!\n");
		return;
	}

	//RPGMenu->SetStateBool("gameDraw", true);



	RPGMenu->Activate(true, gameLocal.time);
	gameLocal.Printf("Attempted GUI find and launch\n");

}














void hurt(idActor* A, int dmg)
{
	if (A == 0)
	{
		return;
	}

	int curr = A->HP;


	if (curr <= dmg)
	{
		curr = 0;
	}
	else 
	{
		curr -= dmg;
	}
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

		if (dmg >= defender->HP)
		{
			hurt(defender, defender->HP);
			return;
		}
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




Choice makeChoice(idPlayer* player)
{

	if (player == NULL)
	{
		gameLocal.Printf("NULL POINTERS, EXITING CHOICE\n");
		return ATTACK;
	}

	player->inSelection = true;
	if(player->playerChoice == NULL)
	{
		player->playerChoice = ATTACK;
	}
	






	return ATTACK;





}



char atkStr[10] = "Attack";
char dfdStr[10] = "Defend";
char itmStr[10] = "Item";
char nullStr[10] = "Nulll";


void choiceToString(char* outStr, Choice c)
{
	char str[10];
	if (c == NULL)
	{
		outStr = nullStr;
		return;
	}
	switch (c)
	{
	case ATTACK:
		outStr = atkStr;
		return;
	case DEFEND:
		outStr = dfdStr;
		return;
	case ITEM:
		outStr = itmStr;
		return;
	}

}






/*
/*
void StartFight()
{
	phase = START;
	enemy = new idActor();
	player = gameLocal.GetLocalPlayer();

	if (enemy == NULL || player == NULL)
	{
		gameLocal.Printf("NULL POINTERS, EXITING COMBAT");
		return;
	}

	enemy->setLoadout(enemy, Enemy, Helmet, Rocket);
	enemy->setStats(enemy, 150, 1, 1, 1);


	//Setting enemy and player HP to their max at the start of combat
	enemy->HP = enemy->maxHP;
	player->HP = player->maxHP;


}
*/




void Machine()
{
	
	RPG *handler = new RPG();
	handler->InitializeRPGMenu();


	//PhaseMachine phase = START;
	PhaseMachine phase = START;
	idActor* enemy = new idActor();
	idPlayer* player = gameLocal.GetLocalPlayer();



	bool basic, heavy;
	item i;


	heavy = true;

	Choice c = ATTACK;

	
	
	
	//RPGUI = NULL;
	//RPGUI = uiManager->FindGui("guis/RPGMenu.gui"); //This should hopefully load the UI

	
	
	
	
	idActor *target = nullptr; //used for item usage



	if (enemy == NULL || player == NULL)
	{
		gameLocal.Printf("NULL POINTERS, EXITING COMBAT");
		return;
	}


	enemy->setLoadout(enemy, Enemy, Helmet, Rocket);
	enemy->setStats(enemy, 150, 1, 1, 1);


	//Setting enemy and player HP to their max at the start of combat
	enemy->HP = enemy->maxHP;
	player->HP = player->maxHP;
	c = player->playerChoice;




	

	gameLocal.Printf("Player Loadout: %u, %u, %u, HP: %u", player->BasicEquiped, player->ArmorEquiped, player->HeavyEquiped, player->HP);
	gameLocal.Printf("Enemy Loadout: %u, %u, %u, HP: %u", enemy->BasicEquiped, enemy->ArmorEquiped, enemy->HeavyEquiped, enemy->HP);




	while (true)
	{
		switch (phase)
		{
		case START:
			gameLocal.Printf("GLORIOUS COMBAT!\n");
			phase = SELECT;
			
			
			//StartFight();
			continue;
		case SELECT:
			gameLocal.Printf("GLORIOUS SELECTIONS!\n");

			//c = makeChoice(player);

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

			gameLocal.Printf("Enemy HP: %u", enemy->HP);


			phase = DEF_ACT;

			continue;



		case END:
			gameLocal.Printf("GLORIOUS END!\n");
			player->xp += 5;
			while (xpThresh())
			{
				levelUp();
			}
			phase = SELECT;

			return;

		case DEFEAT:
			gameLocal.Printf("EMBARASSING FAILURE\n");
			return;



		default:
			return;
		}
	}


}















