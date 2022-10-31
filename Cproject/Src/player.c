/*!
@file       player.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      contains defininition of Player functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"

// MAIN PLAYER STRUCT
struct Player {
	CP_Vector playerPos, tempPos, direction;
	CP_Vector weaponPos, bulletPos;
	int speed, alive, damage, weapon, attacking, ammo;
	float GPA, timer, projVelocity;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; struct Player player;

CP_Vector Up, Left, Down, Right;
extern CP_Color white, green;
extern float deltaTime,windowHeight,windowWidth;

// Initiallize player settings
void playerInit(struct Player* player) {

	Up = CP_Vector_Set(0, -1);
	Down = CP_Vector_Set(0, 1);
	Right = CP_Vector_Set(1, 0);
	Left = CP_Vector_Set(-1, 0);
	(*player).playerPos = CP_Vector_Set(1920 / 2, 1080 / 2);
	(*player).speed = 500;
	(*player).alive = 1;
	(*player).GPA = 5.00f;
	(*player).damage = 1;
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

}

void isPlayerAlive(struct Player* player) {
	(*player).alive = (*player).GPA <= 0 ? 0 : 1;
}

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

// Get position from player to direction of mouse
void meleeVec(struct Player* player, int scale) {
	CP_Vector update = CP_Vector_Set(CP_Input_GetMouseX() - (*player).playerPos.x, CP_Input_GetMouseY() - (*player).playerPos.y);
	CP_Vector temp = CP_Vector_Normalize(update);
	(*player).weaponPos = CP_Vector_Add((*player).playerPos, CP_Vector_Scale(temp, scale));
}

int switchWeapon(int weapon)
{
	return !weapon;
}