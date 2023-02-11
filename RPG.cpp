

#include "../idlib/precompiled.h"
#pragma hdrstop



#include "RPG.h"
#include "game/Actor.h"




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

void attackBasic(idActor* attacker, idActor* defender)
{
	if (attacker == 0 || defender == 0)
	{
		return;
	}

	//for now, we'll pretend STATS don't exist and simply apply DMG based upon the weapon index+1 - armor index

	int weapon = attacker->BasicEquiped;

	int armor = defender->ArmorEquiped;

	int dmg = weapon + 1 - armor; //We'll have a bit more complex dmg equation later

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

	int dmg = (weapon + 1)*5  - (armor + 1)*2; //We'll have a bit more complex dmg equation later

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
