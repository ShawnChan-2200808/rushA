/*!
@file       powerups.c
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      contains defininition of item powerups functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "powerups.h"
#include "player.h"
#include "collsion.h"

// initialising of items - Shawn
void itemInit(struct Item *item,float posX, float posY, float width, float height, float mod) {
	(*item).position = CP_Vector_Set(posX,posY);
	(*item).Width = width;
	(*item).Height = height;
	(*item).isActive = 1; 
	(*item).timer = 1.0f;
	(*item).Modifier = mod;
}

// Bubble Tea powerup function which heal player GPA - Shawn
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

// Unused Speed up function that was initially planned for a coffee powerup function -Shawn
void playerSpeedUp(struct Item* item, struct Player* player) {
	if (IsAreaClicked((*item).position.x, (*item).position.y, (*item).Width, (*item).Height, (*player).playerPos.x, (*player).playerPos.y) && (*item).isActive) {
		(float)(*player).speed += ((*item).Modifier);
		(*item).isActive = 0;
		(*item).timer = 5.0f;
	}
	if ((*item).timer < 3.0f) {
		(*player).speed = 500;
	}
}

// Start the countdown for the cooldown - Shawn
void coolDown(struct Item* item, float deltatime) {
	(*item).timer -= deltatime;
}

// Randoming the spawn position of item - Shawn
void randomItemPos(struct Item* item) {
	(*item).randX = CP_Random_RangeFloat(200, 1700);
	(*item).randY = CP_Random_RangeFloat(200, 800);
}

// Respawning the item to position - Shawn
void respawnItem(struct Item* item, float posX, float posY) {
	// FOR AFTER collision - If in wall set to another pos
	for (int i = 0; i < 3; ++i) {
		if (posX <= table[i].wallmax.x && posX >=table[i].wallmin.x) {
			posX += table[i].width*3.0f;
		}
		if (posY <= table[i].wallmax.y && posY >=table[i].wallmin.y) {
			posY += table[i].height*3.0f;
		}
	}
	for (int i = 0; i < 5; ++i) {
		if (posX <= chair[i].wallmax.x && posX >= chair[i].wallmin.x) {
			posX += chair[i].width*3.0f;
		}
		if (posY <= chair[i].wallmax.y && posY >= chair[i].wallmin.y) {
			posY += chair[i].height*3.0f;
		}
		if (posX < 50) {
			posX += 100;
		}
		if (posX > (windowHeight - 50))
		{
			posX -= 100;
		}
		if (posY < 50) {
			posY += 100;
		}
		if (posY > (windowHeight - 50))
		{
			posY -= 100;
		}
	(*item).position = CP_Vector_Set(posX, posY);
	}
	(*item).isActive = 1;
}
