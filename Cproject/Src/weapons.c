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
#include "enemy.h"
#include "player.h"
#include <math.h>
#include <stdio.h>

// Laser global variables
float playerangle;
float laserw, laserh;
float vectorX, vectorY;
int rotation;

static float elapsedtime = 0;
static float transparency = -255;
extern CP_Color red;

//Returns 4 states:
// 1: For when laser is tracking player
// 2: For when laser is charging up
// 3: For when laser is firing but player is not being damaged
// 4: For when laser is firing & player is being damaged

int laser(struct Enemy* enemy, struct Player* player)
{
	CP_Color lasercolourchargeup = (*enemy).lasercolour;
	float deltaTime = CP_System_GetDt();
	elapsedtime += (deltaTime * 1000);
	lasercolourchargeup = CP_Color_Create((*enemy).lasercolour.r, (*enemy).lasercolour.g + 30, (*enemy).lasercolour.b + 30, (*enemy).lasercolour.a + transparency);
	int lasertime = (int)elapsedtime % 3000;
	float opposite;
	//printf("total elsapse:%f\n", elapsedtime);

	//Break down laser into timing
	//laser x and y draw coordinates
	if (lasertime < 100) {
		//gets which rect to print based on angle and centralise laser beam to enemy
		playerangle = enemyPlayerAngle(enemy, player);
		printf("angle:%f\n", playerangle);
		//checking for 8 predetermined angles
		if (playerangle > 337.5 || playerangle < 22.5) {
			laserw = (*enemy).laserB;
			laserh = -(*enemy).laserL;
			rotation = 0;
			printf("up\n");
		}
		else if (playerangle <= 67.5) {
			laserw = (*enemy).laserL;
			laserh = (*enemy).laserB;
			rotation = 315;
			printf("upright\n");
		}
		else if (playerangle <= 112.5) {
			laserw = (*enemy).laserL;
			laserh = (*enemy).laserB;
			rotation = 270;
			printf("right\n");
		}
		else if (playerangle <= 157.5) {
			laserw = (*enemy).laserL;
			laserh = (*enemy).laserB;
			rotation = 45;
			printf("bottom right\n");
		}
		else if (playerangle <= 202.5) {
			laserw = (*enemy).laserB;
			laserh = (*enemy).laserL;
			rotation = 180;
			printf("down\n");
		}
		else if (playerangle <= 247.5) {
			laserw = (*enemy).laserL;
			laserh = (*enemy).laserB;
			rotation = 135;
			printf("bottomleft\n");
		}
		else if (playerangle <= 292.5) {
			laserw = -(*enemy).laserL;
			laserh = (*enemy).laserB;
			rotation = 90;
			printf("left\n");
		}
		else if (playerangle <= 337.5) {
			laserw = (*enemy).laserL;
			laserh = (*enemy).laserB;
			rotation = 225;
			printf("upleft\n");
		}
		return 1;

		/*if (playerangle > 135 && playerangle < 225) {

		}
		if (playerangle > 45 && playerangle < 135) {

		}
		if (playerangle > 225 && playerangle < 315)
		{

		}*/


		//advacned shit with rotation
	}
	else if (lasertime < 600) {
		if (transparency < -200) {
			transparency += lasertime / 300;
		}
		CP_Settings_Fill(lasercolourchargeup);
		opposite = ((laserw / 2) / (sqrt(2))) / 2;
		switch (rotation) {
		case 0:
		case 180:
			CP_Graphics_DrawRect((*enemy).EnemyPos.x - laserw / 2, (*enemy).EnemyPos.y, laserw, laserh);
			break;
		case 90:
		case 270:
			CP_Graphics_DrawRect((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - laserh / 2, laserw, laserh);
			break;
		case 45:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y - opposite, laserw, laserh, rotation, 0);
			break;
		case 135:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y + opposite, laserw, laserh, rotation, 0);
			break;
		case 225:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y + opposite, laserw, laserh, rotation, 0);
			break;
		case 315:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y - opposite, laserw, laserh, rotation, 0);
			break;
		}
		return 2;
		printf("recharging");
	}
	else if (lasertime < 2000) {
	//calculate opposite & adjacent
		opposite = ((laserw / 2) / (sqrt(2))) / 2;
		CP_Settings_Fill((*enemy).lasercolour);
		switch (rotation) {
		case 0:
		case 180:
			CP_Graphics_DrawRect((*enemy).EnemyPos.x - laserw / 2, (*enemy).EnemyPos.y, laserw, laserh);
			if (1 == IsRectEntered((*enemy).EnemyPos.x - laserw / 2, (*enemy).EnemyPos.y, laserw, laserh, (*player).playerPos.x, (*player).playerPos.y)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 90:
		case 270:
			CP_Graphics_DrawRect((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - laserh / 2, laserw, laserh);
			if (1 == IsRectEntered((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - laserh / 2, laserw, laserh, (*player).playerPos.x, (*player).playerPos.y)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 45:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y - opposite, laserw, laserh, rotation, 2);
			if (1 == isRectEnteredadvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y - opposite, laserw, laserh, rotation, player)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 135:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y + opposite, laserw, laserh, rotation, 2);
			if (1 == isRectEnteredadvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y + opposite, laserw, laserh, rotation, player)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 225:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y + opposite, laserw, laserh, rotation, 2);
			if (1 == isRectEnteredadvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y + opposite, laserw, laserh, rotation, player)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 315:
			CP_Graphics_DrawRectAdvanced(( * enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y - opposite, laserw, laserh, rotation, 2);
			if (1 == isRectEnteredadvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y - opposite, laserw, laserh, rotation, player)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		}
		transparency = -255;
		return 3;
	}
	return 1;
}