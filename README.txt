QUAKE 4 THE RPG MOD

Finished Features:


Battling
-To select an action to take in battle, hit the left and right arrow keys, which changes the actions you wish to take
-The gui will update according to what action you currently need to take, telling you when a selection is required
-Selections can be made the same as actions with the left and right arrow keys and confirmed w/ z
-you can also hit x to return to the selection menu, should you wish change your mind about an action.
-After confirming an action to either Attack, or use and Item, you'll be prompted to select a target.
-There are 3 enemy slots in a battle, and as such, you can attack an enemy by selecting their relative index (starting with 0)
-the player can target themselves as well however, choosing the "3rd" enemy in the list, which will be themselves.
-when using an item such as a medkit, this is how the player would heal themselves, but they can also heal enemies, or attack themselves if they wish!
Items


-There are 5 items in the game
--Grenade, Medkit, Armor Penetrating bullets, Portable Shield, and Battle powder
--Grenades deal damage directly, ignoring armor
--Medkits heal those who they are used on.
--The portable shield lets the player block all damage except for those as a result of special/boss attacks
--Armor Penetrating bullets increase the player's attack (thus dealing more damadge on their next turn)
--and battle powder increases the players speed


Equipment - Equipment can be changed by using the command set_PL_Loadout which takes three arguments. the index for basic, armor, and heavy weapon in that order. One thing of not is that the heavy weapon index begins at 5 rather than 0
-there are 3 types of equipment, each with 5 types, Basic Weapon, Armor, and Heavy Weapon
--The basic weapons directly target a single enemy, it does less damage than a heavy overall, but allows the player to target a single enemy for more damage
--the heavy weapons target all enemies ina  battle, doing more overal damage than a basic, but less per individual
--the armor options allows the player to block more damage, letting them face enemies with higher stats they wouldn't be able to otherwise



Leveling up- After a player finished  abttle, they recieve some XP, when they collect enouggh (100) they level up! which increases their max HP and their stats
--These stat increases make the player stronger and let them fight tougher enemies aswell as last longer in battle
--There are 4 stats in the game, HP, ATK, DEF, and SPD
--HP is the players max health, and how much damadge they can take in a battle
--Atk is a multiplier to a players weapon, increasing their damage
--DEF is a multiplier to the players armor, increasing how much damage they can block.


GUI- The gui Presents the players current Health, and scales as they level up. It also shows what selection the player is making


Bosses- There are three bosses in the game can be summoned by doing the command boss [1-3], which will restart combat with the relative boss
1-Itemmie,the item boss. Itemmie is a little stupid and uses whatever item the player just used targeting the player, if the player hasn't used an item, they'll simply lob a grenade at them.
2-Helen, the healer. Helen heals herself and her allies during combat, keeping the player from finishing the fight quickly (and even reviving them after death!)
3-ZORGAX RISER OF CORPSES. Zorgac RISER OF CORPSES, is a necromancer. Should an ally fall in battle, Zorgax forces them to fight on, having their dead ally make 2 attacks instead of one, effectively doubling their damage!

