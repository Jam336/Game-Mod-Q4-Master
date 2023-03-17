
#ifndef __GAME_RPG_H__
#define __GAME_RPG_H__




#pragma once
#include "Actor.h"


//idUserInterfaceManager* uiManager;

//idUserInterface* RPGUI;


class RPG
{
public:
	RPG();
	void InitializeRPGMenu();
private:
	//uiManager->FindGui("guis/buymenu.gui", true, false, true);
	idUserInterface* RPGMenu;


	

};

enum Choice { ATTACK, DEFEND, ITEM }; //simple three choices

enum PhaseMachine { START, SELECT, ATK_MENU, ATK_ACT, DEF_MENU, ITM_MENU, ITM_USE, FLEE, DEF_ACT, END, DEFEAT, TRGT};



void hurt(idActor*,int); //an actor is hurt! deals damadge to their HP

void attack(idActor* attacker, bool basic, idActor* defender); //:3

void attackBasic(idActor* attacker, idActor* defender); //an Actor Attacks! Determines how hurt a defender is, and calls hurt() as needed

void attackHeavy(idActor* attacker, idActor* defender); //an Actor Attacks! Determines how hurt a defender is, and calls hurt() as needed

void special(idActor* attacker, idActor* defender, int Case); //While mainly item usage, this could also be used for boss events

bool validItem(int i); //checks if a given item is valid

bool xpThresh();

void levelUp();

void choiceToString(char* outStr, Choice c);













void StartFight(int startCase);

void Machine();

/* State machine ideas
* 
* START -> (Player) SELECT -> SUBMENU(s) -> ACTION -> DEFEND -> START
* 
* Loop repeats until reaching either END or DEFEAT
* 
* START: the initial phase of the machine, also serves as a 'Cleanup' section should it be needed.
* 
* SELECT: The player selects an action they'd like to take (Attack, Defend, Item, Flee,) and if brought to a corresponding submenu where they can select further
* 
* SUBMENU(S): the player having picked an action can further define what they want to do, either what weapon or item to use, to careful or quick flee, or to counterattack after a successful defend
* the player can also return to the SELECT state of the machin though this isn't shown in the main Loop
* 
* ACTION: if it requires, the player will do a corresponding QTE or similair action, and will see the results of their actions, this section can also result in END.
* 
* DEFEND: Enemies attack the player, the player must take effort to dodge/defend, which will directly correspond to how much DMG they take, this section will either turn to START, or DEFEAT if the player dies.
* 
* END: The battle ends, either with a flee, or defeating the enemies. if the later, the player is rewarded with XP
* 
* 
* DEFEAT: The player loses the battle, and is defeated, which prompts a gameover or similair ending
* 
* 
* 
*/









#endif /* !__GAME_RPG_H__ */