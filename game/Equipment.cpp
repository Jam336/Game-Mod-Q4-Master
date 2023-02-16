
#include "../idlib/precompiled.h"
#pragma hdrstop


#include "Equipment.h"
#include "RPG.h"



//
int attack(wep w, arm a)
{











    return 0;
}


int calcDmg(wep w)
{

    switch (w)
    {
    case Blaster:
        return(blaster());
        break;

    case Machine_Gun:
        return(machineGun());
        break;

    case Shotgun:
        return(shotGun());
        break;

    case Nail_Gun:
        return(nailGun());
        break;

    case Gauntlet:
        return(gauntlet());
        break;

    case Rocket:
        return(rocket());
        break;

    case Mistake:
        return(mistake());
        break;

    case Dark:
        return(dark());
        break;

    case Rail:
        return(rail());
        break;

    case Lightning:
        return(lightning());
        break;

    }









}

bool isBasic(wep w)
{
    if (w < 5)
    {
        return true;
    }





    return false;
}

bool isHeavy(wep w)
{
    if (w >= 5)
    {
        return true;
    }
    return false;
}

int blaster()
{
    return 0;
}

int machineGun()
{
    return 0;
}

int shotGun()
{
    return 10;
}

int nailGun()
{
    return 5;
}

int gauntlet()
{
    return 15;
}

int rocket()
{
    return 20;
}

int mistake()
{
    return 30;
}

int dark()
{
    return 25;
}

int rail()
{
    return 40;
}

int lightning()
{
    return 15;
}

void useItem(item i, idActor* A)
{
    switch (i)
    {
    case MedKit:
        hurt(A, -20);
        return;
    case PortableCover:
        //Something something, increase DEF
        return;
    case ArmorPiercingBullets:
        //increase ATK
        return;
    case Grenade:
        hurt(A, 30);
        return;
    case BattlePowder:
        //this is gonna be the hard one
        /*I'll need to make a fllag for having
        * just used battle power, let the actor finish their turn
        * then grant them an additional turn with a stat boost.
        */
        return;
        


    }
}



