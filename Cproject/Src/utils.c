/*!
@file       utils.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date        / /2022 (last updated)
@brief      This file contains all the shared utilities that is global throughout
*//*_________________________________________________________________________*/

#include "cprocessing.h"



CP_Color gray,blue, green, red;
int windowWidth, windowHeight;
float fps;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	// check if the x and y pos of the is within the width and height
	if (click_x <= area_center_x + area_width / 2 && click_x >= area_center_x - area_width / 2 &&
		click_y <= area_center_y + area_height / 2 && click_y >= area_center_y - area_height / 2)
		{
			/*
			Returns 1 if the point given by click_xand click_y is within the rectangle given by
			area_center_x, area_center_y, area_width and area_height. Otherwise it will return 0.
			*/
			return 1;
		}
	return 0;
}

int isCircleEntered(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	if (click_x <= circle_center_x + diameter / 2 && click_x >= circle_center_x - diameter / 2 &&
		click_y <= circle_center_y + diameter / 2 && click_y >= circle_center_y - diameter / 2)
		{
			return 1;
		}
	return 0;
}

struct Player {
	CP_Vector playerPos, tempPos, direction;
	CP_Vector weaponPos, Pos;
	int speed, alive, damage, weapon, attacking, ammo;
	float GPA, timer, projVelocity;
}; struct Player player;

struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	int speed, alive;
	float HP, damage;
}; struct Enemy quiz1, lab1, assignment1;

struct Bullet {
	CP_Vector Pos, Vector;
	int velocity, active, ready;
}; struct Bullet playerBullets[10];

float circleSize, deltaTime;
CP_Vector Up, Left, Down, Right;

// Move forward
void moveForward(struct Player* player, CP_Vector direction) {
	(*player).tempPos = CP_Vector_Normalize(direction);
	(*player).tempPos = CP_Vector_Scale((*player).tempPos, (*player).speed * deltaTime);
	(*player).playerPos = CP_Vector_Add((*player).playerPos, (*player).tempPos);
}

// Move backwards
void moveBack(struct Player* player, CP_Vector direction) {
	(*player).tempPos = CP_Vector_Normalize(direction);
	(*player).tempPos = CP_Vector_Scale((*player).tempPos, (*player).speed * deltaTime);
	(*player).playerPos = CP_Vector_Subtract((*player).playerPos, (*player).tempPos);
}

// Move forward
void enemyChase(struct Enemy* enemy, struct Player* player) {
	CP_Vector update = CP_Vector_Set((*player).playerPos.x- (*enemy).EnemyPos.x,(*player).playerPos.y- (*enemy).EnemyPos.y);
	(*enemy).tempPos = CP_Vector_Normalize(update);
	(*enemy).tempPos = CP_Vector_Scale((*enemy).tempPos, (*enemy).speed * deltaTime);
	(*enemy).EnemyPos = CP_Vector_Add((*enemy).EnemyPos, (*enemy).tempPos);
}

void meleeVec(struct Player* player) {
	CP_Vector update = CP_Vector_Set(CP_Input_GetMouseX()-(*player).playerPos.x, CP_Input_GetMouseY()-(*player).playerPos.y);
	CP_Vector temp = CP_Vector_Normalize(update);
	(*player).weaponPos = CP_Vector_Add((*player).playerPos, CP_Vector_Scale(temp, 100));
}

int switchWeapon(int weapon)
{
	return !weapon;
}

void fireWeapon(struct Bullet bullet, CP_Vector direction)
{
	bullet.Vector = CP_Vector_Normalize(direction);
	bullet.Vector = CP_Vector_Scale(bullet.Vector, bullet.velocity * deltaTime);
	bullet.Pos = CP_Vector_Subtract(bullet.Pos, bullet.Vector);
}
