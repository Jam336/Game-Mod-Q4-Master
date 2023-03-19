
#include "../idlib/precompiled.h"
#pragma hdrstop


#include "Equipment.h"
#include "RPG.h"



int calcDmg(wep w)
{
    int outVal = 2;


    if (isHeavy(w))
    {
        outVal = 1;
    }

    switch (w)
    {
    case Blaster:
        return(outVal*blaster());
        break;

    case Machine_Gun:
        return(outVal * machineGun());
        break;

    case Shotgun:
        return(outVal * shotGun());
        break;

    case Nail_Gun:
        return(outVal * nailGun());
        break;

    case Gauntlet:
        return(outVal * gauntlet());
        break;

    case Rocket:
        return(outVal * rocket());
        break;

    case Mistake:
        return(outVal * mistake());
        break;

    case Dark:
        return(outVal * dark());
        break;

    case Rail:
        return(outVal * rail());
        break;

    case Lightning:
        return(outVal * lightning());
        break;
    case Enemy:
        return 10;
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
    return 5;
}

int machineGun()
{
    return 10;
}

int shotGun()
{
    return 15;
}

int nailGun()
{
    return 15;
}

int gauntlet()
{
    return 20;
}

int rocket()
{
    return 2;
}

int mistake()
{
    return 3;
}

int dark()
{
    return 4;
}

int rail()
{
    return 5;
}

int lightning()
{
    return 6;
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



