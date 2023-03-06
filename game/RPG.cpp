

#include "../idlib/precompiled.h"
#pragma hdrstop



#include "RPG.h"
#include "Actor.h"
#include "Game_Local.h"
#include "StartFight.h"

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
	if (attacker == NULL || defender == NULL)
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
	if (player == NULL)
	{
		return;
	}

	player->xp -= 100;
	player->ATK +=5;
	player->DEF +=5;
	player->SPD +=5;
	player->maxHP += 25;

	gameLocal.Printf("Leveled Up!\n");


	return;
}




Choice makeChoice(idPlayer* player) //DEPRECATED
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


void choiceToString(char* outStr, Choice c) //DEPRECATED
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






void StartFight()
{

	

	gameLocal.Printf("STARTING FIGHT\n");
	phase = START;
	EnemyList [0] = new idActor();
	EnemyList[1] = new idActor();
	EnemyList[2] = new idActor();
	player = gameLocal.GetLocalPlayer();

	if (EnemyList == NULL || player == NULL)
	{
		gameLocal.Printf("NULL POINTERS, EXITING COMBAT\n");
		return;
	}
	
	for (idActor *a : EnemyList)
	{
		if (a == NULL)
		{
			//gameLocal.Printf("NULL POINTERS, EXITING COMBAT");
			continue;
		}
		idActor* enemy = a;
		enemy->setLoadout(enemy, Enemy, Helmet, Rocket);
		enemy->setStats(enemy, 100, 1, 1, 1);
		enemy->HP = enemy->maxHP;

	}
	


	//Setting enemy and player HP to their max at the start of combat
	
	player->HP = player->maxHP;


}


bool initialized = false;

bool defended = false;






void Machine()
{
	

	

	//RPG *handler = new RPG();
	//handler->InitializeRPGMenu();






	idActor* enemy = EnemyList[0];
	idPlayer* player = gameLocal.GetLocalPlayer();




	if (enemy == NULL || player == NULL||!initialized)
	{
		StartFight();

		idActor* enemy = EnemyList[0];
		idPlayer* player = gameLocal.GetLocalPlayer();
		initialized = true;
	}









	bool basic, heavy;
	item i;

	


	heavy = true;
	basic = false;
	Choice c = ATTACK;

	
	
	
	//RPGUI = NULL;
	//RPGUI = uiManager->FindGui("guis/RPGMenu.gui"); //This should hopefully load the UI

	
	
	
	
	idActor *target = nullptr; //used for item usage

	

	if (enemy == NULL || player == NULL)
	{
		gameLocal.Printf("NULL POINTERS, EXITING COMBAT\n");
		return;
	}


	c = player->playerChoice;

	PhaseMachine phase = player->playerPhase;


	

	gameLocal.Printf("Player Loadout: %u, %u, %u, HP: %u\n", player->BasicEquiped, player->ArmorEquiped, player->HeavyEquiped, player->HP);
	gameLocal.Printf("Enemy Loadout: %u, %u, %u, HP: %u\n", enemy->BasicEquiped, enemy->ArmorEquiped, enemy->HeavyEquiped, enemy->HP);

	bool endFlag; //determines if player goes to endPhase from combat


		switch (phase)
		{
		case START:
			gameLocal.Printf("GLORIOUS COMBAT!\n");
			//StartFight();
			
			player->playerPhase = SELECT;
			
			player->ActionSelect = true;
			
			gameLocal.Printf("MAKE AN ACTION SELECTION\n");
			
			//continue;
			break;
		case SELECT:
			

			//c = makeChoice(player);

			//TODO, REPLACE THESE IFS WITH PROPER EVENT UI HANDLING

			switch(c)
			{
			case ATTACK:
				player->playerPhase = ATK_MENU;
				gameLocal.Printf("SELECTED ATTACK! CHOOSE YOUR ATTACK\n");
				player->ActionSelect = false;
				player->AttackSelect = true;
				break;
			case DEFEND:
				player->playerPhase = DEF_MENU;
				gameLocal.Printf("SELECTED DEFENSE!\n");
				player->ActionSelect = false;
				
				break;
			case ITEM:
				player->playerPhase = ITM_MENU;
				gameLocal.Printf("SELECTED ITEMS! CHOOSE YOUR ITEM\n");
				player->ActionSelect = false;
				player->ItemSelect = true;
				break;
			}

			//continue;
			break;
		case ATK_MENU:
			gameLocal.Printf("GLORIOUS ATTACK MENU!\n");

			//TODO SET UP PROPER EVENT HANDLING FOR WEAPON CHOICE




			player->playerPhase = ATK_ACT;
			//continue;
			break;
		case ATK_ACT:
			gameLocal.Printf("GLORIOUS ATTACK ACTION\n");
			
			if (player->lastUsed == ArmorPiercingBullets && player->itemUsed == false)
			{
				
				player->ATK += 5;
				gameLocal.Printf("Used Armor Piercing Bullets! Increased ATK!\n");
			}





			if (basic)
			{
				attack(player, true,enemy);
			}
			else if (heavy)
			{
				//Heavy attacks target all enemies
				for (idActor *a : EnemyList)
				{
					if (a == NULL) continue;
					attack(player, false, a);
					gameLocal.Printf("Enemy HP: %u\n", a->HP);
				}
				
			}
			


			if (player->lastUsed == ArmorPiercingBullets && player->itemUsed == false)
			{
				player->ATK -= 5;
				player->itemUsed = true;;
			}



			endFlag = true;

			for (idActor* a : EnemyList)
			{
				if (a == NULL) continue;
				if (a->HP > 1) endFlag = false; break;
			}




			player->AttackSelect = false;


			if (endFlag)
			{
				player->playerPhase = END;
				break;
			}
			else
			{
				player->playerPhase = DEF_ACT;
			}
			


			
			//continue;
			break;


		case DEF_MENU:
			gameLocal.Printf("GLORIOUS DEFENSIVE MANEUVER!\n");

			player->playerPhase = DEF_ACT;
			defended = true;
			//continue;
			break;

		case DEF_ACT:
			gameLocal.Printf("GLORIOUS DODGING!\n");

			//TODO, Add randomness to enemy actions

			if (defended)
			{
				player->DEF = player->DEF * 2;
			}

			if (player->lastUsed == PortableCover && player->itemUsed == false)
			{

				player->itemUsed = true;
				gameLocal.Printf("Used portable shield! avoided DMG!\n");
			}
			else{ 
				
				for (idActor* a : EnemyList)
				{
					if (a == NULL || a->HP == 0) continue;
					
					attackBasic(a, player);

				}
				
			
			}

			//need to loop through the enemy list

			












			

			if (defended)
			{
				player->DEF = player->DEF / 2;
				defended = false;
			}




			gameLocal.Printf("player HP: %u \n", player->HP);

			if (player->HP == 0)
			{
				player->playerPhase = DEFEAT;
			}
			else
			{
				player->playerPhase = START;
			}


			
			//continue;
			break;

		case ITM_MENU:

			//I'll have some better code for how targeting works but for now, this is good enough

			gameLocal.Printf("GLORIOUS ITEM MENU!\n");

			//i = NONE;
			
			player->playerPhase = ITM_USE;

			break;
			

		case ITM_USE:


			gameLocal.Printf("GLORIOUS ITEM USE!\n");

			player->itemUsed = false;

			i = player->playerItem;

			if (i == Grenade)
			{
				target = enemy;
			}
			else
			{
				target = player;
			}



			useItem(i, player, target);

			gameLocal.Printf("Target HP: %u", target->HP);

			player->ItemSelect = false;

			player->playerPhase = DEF_ACT;

			break;

			



		case END:
			gameLocal.Printf("GLORIOUS END!\n");
			player->xp += 20;
			while (xpThresh())
			{
				levelUp();
			}
			player->playerPhase = START;
			initialized = false;

			return;

		case DEFEAT:
			gameLocal.Printf("EMBARASSING FAILURE\n");
			initialized = false;
			player->playerPhase = START;
			return;



		default:
			return;
		}
	


}















