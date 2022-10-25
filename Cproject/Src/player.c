/*!
@file       player.c
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      Make prototype functions and test it here. Copy and paste from current level
			to see if it works before we integrate it into the main game
		*** AND MAKE A COPY for yourself + DONT FORGET TO MAKE .H file to test ***
*//*_________________________________________________________________________________*/

#include "cprocessing.h"

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
extern float deltaTime;
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

void meleeVec(struct Player* player) {
	CP_Vector update = CP_Vector_Set(CP_Input_GetMouseX() - (*player).playerPos.x, CP_Input_GetMouseY() - (*player).playerPos.y);
	CP_Vector temp = CP_Vector_Normalize(update);
	(*player).weaponPos = CP_Vector_Add((*player).playerPos, CP_Vector_Scale(temp, 100));
}

int switchWeapon(int weapon)
{
	return !weapon;
}