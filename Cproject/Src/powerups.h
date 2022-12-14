/*!
@file       powerups.h
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       27/11/2022 (last updated)
@brief      contains Declarations of Powerups functions
*//*_________________________________________________________________________________*/


#pragma once
struct Item {
	CP_Vector position;
	float randX, randY;
	float Width;
	float Height;
	int isActive;
	float timer;
	float Modifier;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; struct Item bbt, coffee, snacks;
void itemInit(struct Item* item, float posX, float posY, float width, float height, float mod);
void playerHeal(struct Item* item, struct Player* player);
void playerSpeedUp(struct Item* item, struct Player* player);
void coolDown(struct Item* item, float deltatime);
void randomItemPos(struct Item* item);
void respawnItem(struct Item* item,float posX, float posY);
