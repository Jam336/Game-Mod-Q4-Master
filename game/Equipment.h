#ifndef __GAME_EQUIP_H__
#define __GAME_EQUIP_H__





#pragma once


enum wep{Blaster,Machine_Gun,Shotgun,Nail_Gun,Gauntlet,Rocket,Mistake,Dark,Rail,Lightning};

enum arm { Helmet, Light, Medium, Heavy, God};

enum item {MedKit, PortableCover, ArmorPiercingBullets, Grenade, BattlePowder};


int attack(wep w, arm a);

int calcDmg(wep w);

bool isBasic(wep w);

bool isHeavy(wep w);



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

void useItem(item, idActor*);









#endif /* !__GAME_RPG_H__ */