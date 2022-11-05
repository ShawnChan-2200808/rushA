/*!
@file       enemy.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains defininition of Enemy functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "collsion.h"
#include "player.h"
#include "enemy.h"

float hitCircleSize, deltaTime;
extern CP_Color red,green;

void wall1init(struct wall * wall1, float width, float height, float posX, float posY) 
{
	(*wall1).x = posX;
	(*wall1).y = posY;
	(*wall1).width = width;
	(*wall1).height = height;
	(*wall1).wallmin = CP_Vector_Set((* wall1).x, (* wall1).y);
	(*wall1).wallmax = CP_Vector_Set((* wall1).x + (* wall1).width, (* wall1).y + (* wall1).height);
}


int collision(struct Player* player, struct wall* wall1)
{
	(*player).playermin = (CP_Vector){ ((*player).playerPos.x - ((*player).hitboxX)) , ((*player).playerPos.y - ((*player).hitboxY)) };
	(*player).playermax = (CP_Vector){ ((*player).playerPos.x + ((*player).hitboxX)) , ((*player).playerPos.y + ((*player).hitboxY)) };

	(*wall1).wallmin = (CP_Vector){ (*wall1).x, (*wall1).y };
	(*wall1).wallmax = (CP_Vector){ (*wall1).x + (*wall1).width, (*wall1).y + (*wall1).height };

	//check if player is IN the box
	int is_x_withinbox = (*player).playermax.x > (*wall1).wallmin.x && (*wall1).wallmax.x > (*player).playermin.x;
	int is_y_withinbox = (*player).playermax.y > (*wall1).wallmin.y && (*wall1).wallmax.y > (*player).playermin.y;

	//if the player is not colliding with the box
	if (!is_x_withinbox || !is_y_withinbox)
		return 0;
	
	//if player collide with the box
	//left collision
	if (((*player).playermin.x < (*wall1).wallmax.x && (*player).playermax.x >(*wall1).wallmax.x) && ((*player).playerPos.y > (*wall1).wallmin.y && (*player).playerPos.y < (*wall1).wallmax.y))
		return 1;
	//right collision
	if (((*player).playermax.x > (*wall1).wallmin.x && (*player).playermin.x < (*wall1).wallmin.x) && ((*player).playerPos.y > (*wall1).wallmin.y && (*player).playerPos.y < (*wall1).wallmax.y))
		return 2;
	//bottom collsion
	if (((*player).playermin.y < (*wall1).wallmax.y && (*player).playermax.y >(*wall1).wallmax.y) && ((*player).playerPos.x > (*wall1).wallmin.x && (*player).playerPos.x < (*wall1).wallmax.x))
		return 3;
	//top collision
	if (((*player).playermax.y > (*wall1).wallmin.y && (*player).playermin.y < (*wall1).wallmin.y) && ((*player).playerPos.x > (*wall1).wallmin.x && (*player).playerPos.x < (*wall1).wallmax.x))
		return 4;

	//not colliding 
	return 0;
}










