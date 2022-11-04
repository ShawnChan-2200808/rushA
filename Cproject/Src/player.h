/*!
@file       player.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      contains Declarations of Player functions
*//*_________________________________________________________________________________*/
void playerInit(struct Player* player);
void isPlayerAlive(struct Player* player);
void moveForward(struct Player* player, CP_Vector direction);
void moveBack(struct Player* player, CP_Vector direction);
void meleeVec(struct Player* player,int scale);
int switchWeapon(int weapon);