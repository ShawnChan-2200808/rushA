/*!
@file       enemy.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains declarations of Enemy functions
*//*_________________________________________________________________________________*/


int collision(struct Player* player, struct wall* wall1);
void wall1init(struct wall* wall1, float width, float height, float posX, float posY);