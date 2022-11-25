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

float hitCircleSize, deltaTime;
extern CP_Color red,green;


void tableinit(struct wall * table, float posX, float posY)
{
	(*table).x = posX;
	(*table).y = posY;
	(*table).width = 100;
	(*table).height = 100;
	(*table).wallmin = CP_Vector_Set((*table).x, (*table).y);
	(*table).wallmax = CP_Vector_Set((*table).x + (*table).width, (*table).y + (*table).height);
}

void chairinit(struct wall* chair, float posX, float posY)
{

	(*chair).x = posX;
	(*chair).y = posY;
	(*chair).width = 50;
	(*chair).height = 50;
	(*chair).wallmin = CP_Vector_Set((*chair).x, (*chair).y);
	(*chair).wallmax = CP_Vector_Set((*chair).x + (*chair).width, (*chair).y + (*chair).height);
}

void initallwall(int numOfchair, int numOftable) {
	float chairx[5] = { (windowWidth / 2) + 200, (windowWidth / 2) + 250, windowWidth / 3, 300, windowWidth - 200 };
	float chairy[5] = { (windowHeight / 2) - 50, (windowHeight / 2) - 50,(windowHeight-200), (windowHeight / 2)+50, windowHeight / 5 };
	float tablex[3] = { windowWidth / 4, (windowWidth / 2) + 200, windowWidth - 350 };
	float tabley[3] = { windowHeight / 4, windowHeight / 2, (windowHeight / 5) + 150 };
	for (int i = 0; i < numOfchair; i++)
	{
		chairinit(&chair[i],chairx[i], chairy[i]);
	}
	for (int i = 0; i < numOftable; i++)
	{
		tableinit(&table[i],tablex[i], tabley[i]);
	}
}

int collision(struct Player* player, struct wall* object)
{
	(*player).playermin = (CP_Vector){ ((*player).playerPos.x - ((*player).hitboxX)) , ((*player).playerPos.y - ((*player).hitboxY)) };
	(*player).playermax = (CP_Vector){ ((*player).playerPos.x + ((*player).hitboxX)) , ((*player).playerPos.y + ((*player).hitboxY)) };

	(*object).wallmin = (CP_Vector){ (*object).x, (*object).y };
	(*object).wallmax = (CP_Vector){ (*object).x + (*object).width, (*object).y + (*object).height };

	//check if player is IN the box
	int is_x_withinbox = (*player).playermax.x > (*object).wallmin.x && (*object).wallmax.x > (*player).playermin.x;
	int is_y_withinbox = (*player).playermax.y > (*object).wallmin.y && (*object).wallmax.y > (*player).playermin.y;

	//if the player is not colliding with the box
	if (!is_x_withinbox || !is_y_withinbox)
		return 0;
	
	//if player collide with the box
	//left collision
	if (((*player).playermin.x < (*object).wallmax.x && (*player).playermax.x >(*object).wallmax.x) && ((*player).playerPos.y > (*object).wallmin.y && (*player).playerPos.y < (*object).wallmax.y))
		return 1;
	//right collision
	if (((*player).playermax.x > (*object).wallmin.x && (*player).playermin.x < (*object).wallmin.x) && ((*player).playerPos.y > (*object).wallmin.y && (*player).playerPos.y < (*object).wallmax.y))
		return 2;
	//bottom collsion
	if (((*player).playermin.y < (*object).wallmax.y && (*player).playermax.y >(*object).wallmax.y) && ((*player).playerPos.x > (*object).wallmin.x && (*player).playerPos.x < (*object).wallmax.x))
		return 3;
	//top collision
	if (((*player).playermax.y > (*object).wallmin.y && (*player).playermin.y < (*object).wallmin.y) && ((*player).playerPos.x > (*object).wallmin.x && (*player).playerPos.x < (*object).wallmax.x))
		return 4;

	//not colliding 
	return 0;
}

int collisionEnemy(struct Enemy* Enemy, struct wall* object)
{
	(*Enemy).enemymin = (CP_Vector){ ((*Enemy).EnemyPos.x - ((*Enemy).hitboxX)) , ((*Enemy).EnemyPos.y - ((*Enemy).hitboxY)) };
	(*Enemy).enemymax = (CP_Vector){ ((*Enemy).EnemyPos.x + ((*Enemy).hitboxX)) , ((*Enemy).EnemyPos.y + ((*Enemy).hitboxY)) };

	(*object).wallmin = (CP_Vector){ (*object).x, (*object).y };
	(*object).wallmax = (CP_Vector){ (*object).x + (*object).width, (*object).y + (*object).height };

	//check if player is IN the box
	int is_x_withinbox = (*Enemy).EnemyPos.x > (*object).wallmin.x && (*object).wallmax.x > (*Enemy).EnemyPos.x;
	int is_y_withinbox = (*Enemy).EnemyPos.y > (*object).wallmin.y && (*object).wallmax.y > (*Enemy).EnemyPos.y;

	//if the player is not colliding with the box
	if (!is_x_withinbox || !is_y_withinbox)
		return 0;

	//if player collide with the box
	//left collision
	if (((*Enemy).enemymin.x < (*object).wallmax.x && (*Enemy).enemymax.x >(*object).wallmax.x) && ((*Enemy).EnemyPos.y > (*object).wallmin.y && (*Enemy).EnemyPos.y < (*object).wallmax.y))
		return 1;
	//right collision
	if (((*Enemy).enemymax.x > (*object).wallmin.x && (*Enemy).enemymin.x < (*object).wallmin.x) && ((*Enemy).EnemyPos.y > (*object).wallmin.y && (*Enemy).EnemyPos.y < (*object).wallmax.y))
		return 2;
	//bottom collsion
	if (((*Enemy).enemymin.y < (*object).wallmax.y && (*Enemy).enemymax.y >(*object).wallmax.y) && ((*Enemy).EnemyPos.x > (*object).wallmin.x && (*Enemy).EnemyPos.x < (*object).wallmax.x))
		return 3;
	//top collision
	if (((*Enemy).enemymax.y > (*object).wallmin.y && (*Enemy).enemymin.y < (*object).wallmin.y) && ((*Enemy).EnemyPos.x > (*object).wallmin.x && (*Enemy).EnemyPos.x < (*object).wallmax.x))
		return 4;

	//not colliding 
	return 0;
}


void pushback(struct Player* player, struct wall* object)
{
	float push = 0;
	int collided = collision(player, object);
	//collide with right
	if (collided == 1)
	{
		push += ((*object).x + 100) - ((*player).playerPos.x - ((*player).worldSizeW / 2));
		(*player).playerPos.x += push;
	}
	//collide with left
	if (collided == 2)
	{
		push += ((*player).playerPos.x + ((*player).worldSizeW / 2)) - ((*object).x);
		(*player).playerPos.x -= push;
	}
	//collide with bottom
	if (collided == 3)
	{
		push += ((*object).y + (*object).height) - ((*player).playerPos.y - ((*player).worldSizeW / 2));
		(*player).playerPos.y += push;
	}
	//collide with top
	if (collided == 4)
	{
		push += ((*player).playerPos.y + ((*player).worldSizeW / 2)) - ((*object).y);
		(*player).playerPos.y -= push;
	}
}
void pushbackEnemy(struct Enemy* Enemy, struct wall* object)
{
	float push = 0;
	int collided = collisionEnemy(Enemy, object);
	//collide with right
	if (collided == 1)
	{
		push += ((*object).x + 100) - ((*Enemy).EnemyPos.x - ((*Enemy).worldSizeW / 2));
		(*Enemy).EnemyPos.x += push;
	}
	//collide with left
	if (collided == 2)
	{
		push += ((*Enemy).EnemyPos.x + ((*Enemy).worldSizeW / 2)) - ((*object).x);
		(*Enemy).EnemyPos.x -= push;
	}
	//collide with bottom
	if (collided == 3)
	{
		push += ((*object).y + (*object).height) - ((*Enemy).EnemyPos.y - ((*Enemy).worldSizeW / 2));
		(*Enemy).EnemyPos.y += push;
	}
	//collide with top
	if (collided == 4)
	{
		push += ((*Enemy).EnemyPos.y + ((*Enemy).worldSizeW / 2)) - ((*object).y);
		(*Enemy).EnemyPos.y -= push;
	}

}








