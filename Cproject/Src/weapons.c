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


extern CP_Color red;

//Returns 4 states:
// 1: For when laser is tracking player
// 2: For when laser is charging up
// 3: For when laser is firing but player is not being damaged
// 4: For when laser is firing & player is being damaged

int laser(struct Enemy* enemy, struct Player* player) {
	static float playerangle;
	
	(*enemy).lasercolourchargeup = (*enemy).lasercolour;
	(*enemy).floatlaserTime += (CP_System_GetDt() * 1000);
	(*enemy).lasercolourchargeup = CP_Color_Create((*enemy).lasercolour.r, (*enemy).lasercolour.g + 30, (*enemy).lasercolour.b + 30, (*enemy).lasercolour.a + (*enemy).transparency);
	float opposite;
	(*enemy).intlaserTime = (int)(*enemy).floatlaserTime % 3000;
	printf("total elsapse:%d\n", (*enemy).intlaserTime);
	//Break down laser into timing
	//laser x and y draw coordinates
	if ((*enemy).intlaserTime < 100) {
		(*enemy).transparency = -255;
		//gets which rect to print based on angle and centralise laser beam to enemy
		playerangle = enemyPlayerAngle(enemy, player);
		printf("angle:%f\n", playerangle);
		//checking for 8 predetermined angles
		if (playerangle > 337.5 || playerangle < 22.5) {
			(*enemy).laserw = (*enemy).laserB;
			(*enemy).laserh = -(*enemy).laserL;
			(*enemy).rotation = 0;
			printf("up\n");
		}
		else if (playerangle <= 67.5) {
			(*enemy).laserw = (*enemy).laserL;
			(*enemy).laserh = (*enemy).laserB;
			(*enemy).rotation = 315;
			printf("upright\n");
		}
		else if (playerangle <= 112.5) {
			(*enemy).laserw = (*enemy).laserL;
			(*enemy).laserh = (*enemy).laserB;
			(*enemy).rotation = 270;
			printf("right\n");
		}
		else if (playerangle <= 157.5) {
			(*enemy).laserw = (*enemy).laserL;
			(*enemy).laserh = (*enemy).laserB;
			(*enemy).rotation = 45;
			printf("bottom right\n");
		}
		else if (playerangle <= 202.5) {
			(*enemy).laserw = (*enemy).laserB;
			(*enemy).laserh = (*enemy).laserL;
			(*enemy).rotation = 180;
			printf("down\n");
		}
		else if (playerangle <= 247.5) {
			(*enemy).laserw = (*enemy).laserL;
			(*enemy).laserh = (*enemy).laserB;
			(*enemy).rotation = 135;
			printf("bottomleft\n");
		}
		else if (playerangle <= 292.5) {
			(*enemy).laserw = -(*enemy).laserL;
			(*enemy).laserh = (*enemy).laserB;
			(*enemy).rotation = 90;
			printf("left\n");
		}
		else if (playerangle <= 337.5) {
			(*enemy).laserw = (*enemy).laserL;
			(*enemy).laserh = (*enemy).laserB;
			(*enemy).rotation = 225;
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


		//advacned shit with (*enemy).rotation
	}
	else if ((*enemy).intlaserTime < 600) {
		if ((*enemy).transparency < -200) {
			(*enemy).transparency += (*enemy).intlaserTime / 300;
		}
		CP_Settings_Fill((*enemy).lasercolourchargeup);
		opposite = (((*enemy).laserw / 2) / (sqrt(2))) / 2;
		switch ((*enemy).rotation) {
		case 0:
		case 180:
			CP_Graphics_DrawRect((*enemy).EnemyPos.x - (*enemy).laserw / 2, (*enemy).EnemyPos.y, (*enemy).laserw, (*enemy).laserh);
			break;
		case 90:
		case 270:
			CP_Graphics_DrawRect((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - (*enemy).laserh / 2, (*enemy).laserw, (*enemy).laserh);
			break;
		case 45:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y - opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, 0);
			break;
		case 135:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y + opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, 0);
			break;
		case 225:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y + opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, 0);
			break;
		case 315:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y - opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, 0);
			break;
		}
		return 2;
		printf("recharging");
	}
	else if ((*enemy).intlaserTime < 2000) {
		//calculate opposite & adjacent
		opposite = (((*enemy).laserw / 2) / (sqrt(2))) / 2;
		CP_Settings_Fill((*enemy).lasercolour);
		switch ((*enemy).rotation) {
		case 0:
		case 180:
			CP_Graphics_DrawRect((*enemy).EnemyPos.x - (*enemy).laserw / 2, (*enemy).EnemyPos.y, (*enemy).laserw, (*enemy).laserh);
			if (1 == IsRectEntered((*enemy).EnemyPos.x - (*enemy).laserw / 2, (*enemy).EnemyPos.y, (*enemy).laserw, (*enemy).laserh, (*player).playerPos.x, (*player).playerPos.y)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 90:
		case 270:
			CP_Graphics_DrawRect((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - (*enemy).laserh / 2, (*enemy).laserw, (*enemy).laserh);
			if (1 == IsRectEntered((*enemy).EnemyPos.x, (*enemy).EnemyPos.y - (*enemy).laserh / 2, (*enemy).laserw, (*enemy).laserh, (*player).playerPos.x, (*player).playerPos.y)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 45:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y - opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, 2);
			if (1 == isRectEnteredadvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y - opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, player)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 135:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y + opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, 2);
			if (1 == isRectEnteredadvanced((*enemy).EnemyPos.x + opposite, (*enemy).EnemyPos.y + opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, player)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 225:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y + opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, 2);
			if (1 == isRectEnteredadvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y + opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, player)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		case 315:
			CP_Graphics_DrawRectAdvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y - opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, 2);
			if (1 == isRectEnteredadvanced((*enemy).EnemyPos.x - opposite, (*enemy).EnemyPos.y - opposite, (*enemy).laserw, (*enemy).laserh, (*enemy).rotation, player)) {
				printf("DIE!\n");
				return 4;
			}
			break;
		}
		(*enemy).transparency = -255;
		return 3;
	}
	return 1;
}

//Bullets



void bulletReset(int index) {
	for (index = 0; index < 10; ++index)
	{
		player.playerBullets[index].active = 0;
		player.playerBullets[index].velocity = 0;
	}
}

//Initialise Player Bullet
void bulletInit(int index, struct Player* player) {
	for (index = 0; index < 10; ++index)
	{
		if (player->playerBullets[index].active == 0)
		{
			player->playerBullets[index].active = 1;
			player->playerBullets[index].velocity = 1000;
			player->playerBullets[index].diameter = 20;
			player->playerBullets[index].damage = 1;
			player->playerBullets[index].Pos = (*player).playerPos;
			player->playerBullets[index].Vector = CP_Vector_Set((CP_Input_GetMouseX() - (*player).playerPos.x), (CP_Input_GetMouseY() - (*player).playerPos.y));
			player->playerBullets[index].Vector = CP_Vector_Normalize(player->playerBullets[index].Vector);
			player->playerBullets[index].Vector = CP_Vector_Scale(player->playerBullets[index].Vector, player->playerBullets[index].velocity);
			break;
		}
	}
}

//Definition for bulletupdates
void bulletUpdate(int index, float deltaTime, int numOfQuiz, int numOfAssLab) {
	for (index = 0; index < 10; ++index)
	{
		if (player.playerBullets[index].active == 1)
		{
			player.playerBullets[index].Pos.x += player.playerBullets[index].Vector.x * deltaTime;
			player.playerBullets[index].Pos.y += player.playerBullets[index].Vector.y * deltaTime;
			if (player.playerBullets[index].Pos.x < 0 || player.playerBullets[index].Pos.x >= CP_System_GetWindowWidth() || player.playerBullets[index].Pos.y < 0 || player.playerBullets[index].Pos.y >= CP_System_GetWindowHeight())
			{
				player.playerBullets[index].active = 0;
			}
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawCircle(player.playerBullets[index].Pos.x, player.playerBullets[index].Pos.y, player.playerBullets[index].diameter);
			// need to update
			for (int i = 0; i < numOfQuiz; i++)
			{
				if (bulletDamage(&quiz[i], player.playerBullets[index], 130, 130) == 1)
				{
					player.playerBullets[index].active = 0;
				}
			}
			for (int i = 0; i < numOfAssLab; i++)
			{
				if (bulletDamage(&assignment[i], player.playerBullets[index], 130, 130) == 1)
				{
					player.playerBullets[index].active = 0;
				}
				if (bulletDamage(&lab[i], player.playerBullets[index], 130, 130) == 1)
				{
					player.playerBullets[index].active = 0;
				}
			}
		}

	}
}

