/*!
@file       powerups.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      contains defininition of Player functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "powerups.h"

// reference to player
extern struct Player {
	CP_Vector playerPos, tempPos, direction;
	CP_Vector weaponPos, bulletPos;
	int speed, alive, damage, weapon, attacking, ammo;
	float GPA, timer, projVelocity;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; extern struct Player player;
extern int randomX, randomY;

void itemInit(struct Item *item,float posX, float posY, float width, float height, float mod) {
	(*item).position = CP_Vector_Set(posX,posY);
	(*item).Width = width;
	(*item).Height = height;
	(*item).isActive = 1; 
	(*item).timer = 1.0f;
	(*item).Modifier = mod;
}

void playerHeal(struct Item* item, struct Player* player) {
	if (IsAreaClicked((*item).position.x, (*item).position.y, (*item).Width, (*item).Height, (*player).playerPos.x, (*player).playerPos.y) && (*item).isActive){
		if ((*player).GPA < 3) {
			(*player).GPA += (*item).Modifier;
		}
		else {
			(*player).GPA = 5;
		}
		(*item).isActive = 0;
		(*item).timer = 10.0f;
	}
}

void playerSpeedUp(struct Item* item, struct Player* player) {
	if (IsAreaClicked((*item).position.x, (*item).position.y, (*item).Width, (*item).Height, (*player).playerPos.x, (*player).playerPos.y) && (*item).isActive) {
		(*player).speed += (*item).Modifier;
		(*item).isActive = 0;
		(*item).timer = 5.0f;
	}
	if ((*item).timer < 3.0f) {
		(*player).speed = 500;
	}
}

void coolDown(struct Item* item, float deltatime) {
	(*item).timer -= deltatime;
}

void respawnItem(struct Item* item/*, float posX, float posY*/) {
	randomX = CP_Random_RangeFloat(200, 1700);
	randomY = CP_Random_RangeFloat(200, 800);
	// FOR AFTER collision - If in wall set to another pos
	(*item).position = CP_Vector_Set(randomX, randomY);
	(*item).isActive = 1;
}
