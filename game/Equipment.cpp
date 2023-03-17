
#include "../idlib/precompiled.h"
#pragma hdrstop


#include "Equipment.h"
#include "RPG.h"



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
    case Enemy:
        return 20;
        break;

    }



}

int calcDefVal(arm a)
{
    switch (a)
    {
    case Helmet:
        return helmet();
    case Light:
        return light();
    case Medium:
        return medium();
    case Heavy:
        return heavy();
    case God:
        return god();
    }
            
            //Writing code like this is gonna give me an anyuerism
    return 0;
}


bool isBasic(wep w)
{
    if (w <= 5 || w == Enemy)
    {
        return true;
    }

    return false;
}

bool isHeavy(wep w)
{
    if (w > 5 && w != Enemy)
    {
        return true;
    }
    return false;
}

wep intToWep(int i)
{
    return wep(i);
}

arm intToArm(int i)
{
   
    return arm(i);
}

item intToItem(int i)
{

    return item(i);
}

int blaster()
{
    return 1;
}

int machineGun()
{
    return 2;
}

int shotGun()
{
    return 2;
}

int nailGun()
{
    return 1;
}

int gauntlet()
{
    return 5;
}

int rocket()
{
    return 5;
}

int mistake()
{
    return 10;
}

int dark()
{
    return 10;
}

int rail()
{
    return 10;
}

int lightning()
{
    return 15;
}

int helmet()
{
    return 1;
}

int light()
{
    return 2;
}

int medium()
{
    return 4;
}

int heavy()
{
    return 6;
}

int god()
{
    return 10;
}




void useItem(item i, idActor* A, idActor* target)
{

    if (A == 0 || target == 0)
    {
        return;
    }

    A->lastUsed = i;


    switch (i) //Armor Piercing and portable shield are covered in the Attack function!
    {
    case MedKit:
        hurt(target, -40);
        A->itemUsed = true;
        return;
    case Grenade:
        hurt(target, 30);
        A->itemUsed = true;
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



