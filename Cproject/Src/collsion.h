/*!
@file       enemy.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains declarations of Enemy functions
*//*_________________________________________________________________________________*/
#pragma once
#include "player.h"
#include "enemy.h"

struct wall
{
	float x, y, width, height;
	CP_Vector wallmin, wallmax;
}; struct wall table[3], chair[5];

int collision(struct Player* player, struct wall* wall1);
int collisionEnemy(struct Enemy* Enemy, struct wall* object);
void tableinit(struct wall* table, float posX, float posY);
void chairinit(struct wall* chair, float posX, float posY);
void initallwall(int numOfchair, int numOftable);
int pushback(struct Player* player, struct wall* object);
int pushbackEnemy(struct Enemy* Enemy, struct wall* object);

