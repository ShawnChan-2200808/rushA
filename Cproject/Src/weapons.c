/*!
@file       weapons.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains defininition of Enemy functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "weapons.h"
#include <stdio.h>

// Laser global variables
float playerangle;
float laserw, laserh;
float vectorX, vectorY;
// angleflag , 1 for updown, 2 for leftright
int angleflag;

struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	CP_Color lasercolour;
	int speed, alive;
	float HP, damage;
	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; struct Enemy;

struct Player {
	CP_Vector playerPos, tempPos, direction;
	CP_Vector weaponPos, bulletPos;
	int speed, alive, damage, weapon, attacking, ammo;
	float GPA, timer, projVelocity;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; struct Player;


float elapsedtime =0;
int laser(struct Enemy* enemy, struct Player* player)
{

	CP_Color lasercolourchargeup;
	float deltaTime = CP_System_GetDt();
	elapsedtime += (deltaTime*1000);
	lasercolourchargeup = CP_Color_Create((*enemy).lasercolour.r, (*enemy).lasercolour.g, (*enemy).lasercolour.b, (*enemy).lasercolour.a - 100);
	int lasertime = (int)elapsedtime % 5000;
	//printf("total elsapse:%f\n", totalElapsedTimeMS);

	//Break down laser into timing
	//laser x and y draw coordinates
	if (lasertime < 10) {
		//gets which rect to print based on angle and centralise laser beam to enemy
		playerangle = enemyPlayerAngle(enemy, player);
		printf("angle:%f\n", playerangle);
		if (playerangle > 135 && playerangle < 225) {
			laserw = 100;
			laserh = 500;
			angleflag = 1;
			printf("down");
		}
		if (playerangle > 45 && playerangle < 135) {
			laserw = 500;
			laserh = 100;
			printf("right");
			angleflag = 2;
		}
		if (playerangle > 225 && playerangle < 315)
		{
			laserw = -500;
			laserh = 100;
			printf("left");
			angleflag = 2;
		}
		if (playerangle < 45 || playerangle > 315) {
			laserw = 100;
			laserh = -500;
			printf("up");
			angleflag = 1;
		}
	}

	if (lasertime < 375) {
		//if ()

		(* enemy).lasercolour = lasercolourchargeup;
		CP_Settings_Fill(lasercolourchargeup);
		if (angleflag == 1)
			CP_Graphics_DrawRect((*enemy).EnemyPos.x - laserw / 2, (*enemy).EnemyPos.y, laserw, laserh);
		else
			CP_Graphics_DrawRect((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - laserh / 2, laserw, laserh);
	}
	else if (lasertime < 525) {
		(*enemy).lasercolour = lasercolourchargeup;
		CP_Settings_Fill(lasercolourchargeup);
		if (angleflag == 1)
			CP_Graphics_DrawRect((*enemy).EnemyPos.x - laserw / 2, (*enemy).EnemyPos.y, laserw, laserh);
		else
			CP_Graphics_DrawRect((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - laserh / 2, laserw, laserh);
		//vectorX = player.playerPos.x - quiz1.EnemyPos.x;
		//vectorY = player.playerPos.y - quiz1.EnemyPos.y;
	}
	else if (lasertime < 2000) {
		if (angleflag == 1) {
			CP_Settings_Fill((*enemy).lasercolour);
			CP_Graphics_DrawRect((* enemy).EnemyPos.x - laserw / 2, (*enemy).EnemyPos.y, laserw, laserh);
			if (1 == IsRectEntered((*enemy).EnemyPos.x - laserw / 2, (*enemy).EnemyPos.y, laserw, laserh, (*player).playerPos.x, (*player).playerPos.y)) {
				printf("DIE!\n");
				return 1;
			}
		}
		else {
			CP_Settings_Fill((*enemy).lasercolour);
			CP_Graphics_DrawRect((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - laserh / 2, laserw, laserh);
			if (1 == IsRectEntered((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - laserh / 2, laserw, laserh, (*player).playerPos.x, (*player).playerPos.y)) {
				printf("DIE!\n");
				return 1;
			}
		}
	}
	return 0;
}
