/*!
@file       player.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      contains defininition of Player functions
@authors

	Shawn: worked on player movement, player melee attack logic, player level logic

   Justin: worked on player projectile logic

*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "player.h"

CP_Vector Up, Left, Down, Right;
extern float deltaTime,windowHeight,windowWidth;

// Initiallize player settings - Shawn
void playerInit(struct Player* player) {

	Up = CP_Vector_Set(0, -1);
	Down = CP_Vector_Set(0, 1);
	Right = CP_Vector_Set(1, 0);
	Left = CP_Vector_Set(-1, 0);
	(*player).playerPos = CP_Vector_Set(windowWidth / 2, windowHeight / 2);
	(*player).speed = 500;
	(*player).alive = 1;
	(*player).GPA = 5.00f;
	(*player).damage = 3;
	(*player).timer = 0;
	(*player).weaponPos = CP_Vector_Set((*player).playerPos.x, (*player).playerPos.y);
	(*player).weapon = 0;
	(*player).ammo = 10;

	//animation idle
	(*player).animationElapsedTime = 0.0f;
	(*player).animationSpeed = 15;
	(*player).currentFrame = 0;
	(*player).animTotalFrames = 2;
	(*player).worldSizeW = 120.0f;
	(*player).worldSizeH = 120.0f;
	(*player).spriteWidth = 64.0f;
	(*player).SpriteHeight = 64.0f;
	(*player).displayTime = 2.0f;

	//collision
	(*player).hitboxX = ((*player).worldSizeW / 2);
	(*player).hitboxY = ((*player).worldSizeH / 2);
	(*player).playermin = CP_Vector_Set(((*player).playerPos.x - ((*player).hitboxX)), ((*player).playerPos.y - ((*player).hitboxY)));
	(*player).playermax = CP_Vector_Set(((*player).playerPos.x + ((*player).hitboxX)), ((*player).playerPos.y + ((*player).hitboxY)));

}

// check if player is alive - Shawn
void isPlayerAlive(struct Player* player) {
	(*player).alive = (*player).GPA <= 0 ? 0 : 1;
}

// Move forward - Shawn
void moveForward(struct Player* player, CP_Vector direction) {
	(*player).tempPos = CP_Vector_Normalize(direction);
	(*player).tempPos = CP_Vector_Scale((*player).tempPos, (*player).speed * deltaTime);
	(*player).playerPos = CP_Vector_Add((*player).playerPos, (*player).tempPos);
}

// Move backwards - Shawn
void moveBack(struct Player* player, CP_Vector direction) {
	(*player).tempPos = CP_Vector_Normalize(direction);
	(*player).tempPos = CP_Vector_Scale((*player).tempPos, (*player).speed * deltaTime);
	(*player).playerPos = CP_Vector_Subtract((*player).playerPos, (*player).tempPos);
}

// Get position from player to direction of mouse - Shawn
void meleeVec(struct Player* player, float scale) 
{
	CP_Vector update = CP_Vector_Set(CP_Input_GetMouseX() - (*player).playerPos.x, CP_Input_GetMouseY() - (*player).playerPos.y);
	CP_Vector temp = CP_Vector_Normalize(update);
	(*player).weaponPos = CP_Vector_Add((*player).playerPos, CP_Vector_Scale(temp, scale));
}

// Switch weapons - Justin
int switchWeapon(int weapon)
{
	return !weapon;
}

// Get angle from mouse to player - Justin
float mouseToplayerAngle(struct Player *player){
	CP_Vector update = CP_Vector_Set((*player).playerPos.x - CP_Input_GetMouseX(), (*player).playerPos.y - CP_Input_GetMouseY());
	CP_Vector normalised = CP_Vector_Normalize(update);
	//printf("X vector %f, Y Vector %f \n", normalised.x, normalised.y);
	CP_Vector unitVector = CP_Vector_Set(0.0f, 1.0f);
	if (normalised.x > 0) {
		normalised.y = -normalised.y;
	}
	float angle = CP_Vector_Angle(normalised, unitVector);
	//printf("angle utils %f \n", angle);
	return normalised.x > 0 ? angle : angle + 180;
}
