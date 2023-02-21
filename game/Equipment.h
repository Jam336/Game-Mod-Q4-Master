#ifndef __GAME_EQUIP_H__
#define __GAME_EQUIP_H__





#pragma once


enum wep{Blaster,Machine_Gun,Shotgun,Nail_Gun,Gauntlet,Rocket,Mistake,Dark,Rail,Lightning, Enemy};

enum arm {Helmet, Light, Medium, Heavy, God};

enum item {MedKit, PortableCover, ArmorPiercingBullets, Grenade, BattlePowder};




int calcDmg(wep w);

int calcDefVal(arm a);

bool isBasic(wep w);

bool isHeavy(wep w);

wep intToWep(int); 

arm intToArm(int);

item intToItem(int);



//individual weapon functions
int blaster();

int machineGun();

int shotGun();

int nailGun();

int gauntlet();

int rocket();

int mistake();

int dark();

int rail();

int lightning();

int helmet();

int light();

int medium();

int heavy();

int god();




void useItem(item, idActor*, idActor*);









#endif /* !__GAME_RPG_H__ */