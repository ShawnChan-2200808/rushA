/*!
@file       level.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      This file contains the main level that we integrate
		*** ONLY UPDATE THIS AFTER APPROVAL OF TEAM ***
*//*_________________________________________________________________________*/

//#include "stdio.h" 
//#include "stdlib.h"
#include "cprocessing.h"
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "anim.h"
#include "weapons.h"
#include "powerups.h"
#include "bullet.h"
#include "collsion.h"
#include "mainmenu.h"


extern CP_Color gray, blue, green, red;
extern int windowWidth, windowHeight;
extern float fps;
static float totalElapsedTime;
CP_Vector Up, Left, Down, Right;
extern int randomX, randomY;
float deltaTime;
int paused;

static int allDead;
static int Win;
static int GameOver;
static int bossOut;

void Level_Init()
{
	initGame();
	initAssets();
	playerInit(&player);
	initAllEnemies(10, 8, 8);
	bossInit(&boss);
	wall1init(&wall1, 100, 100, windowWidth / 4, windowHeight / 4);
	itemInit(&bbt, 600, 600, 55, 55, 1);
	randomX = 0;
	randomY = 0;
	bulletReset(bulletIndex);

	allDead = 0;
	Win = 0;
	GameOver = 0;
	bossOut = 0;
	totalElapsedTime = 0;

	//MUSIC
	//
	CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
	CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
	CP_Sound_PlayAdvanced(levelOST, 0.3f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
	CP_Sound_PlayAdvanced(schoolBellSFX,0.1f,1.0f,FALSE, CP_SOUND_GROUP_SFX);
}

void Level_Update()
{
	if (paused == 0)
	{
		// PLAYER MOVEMENT + BOUNDARIES
		if (player.alive && !Win) {
			SpawnBG(Floor, 6, 9);
			if (CP_Input_KeyDown(KEY_W) && player.playerPos.y > 50)
			{
				moveForward(&player, Up);
			}
			if (CP_Input_KeyDown(KEY_A) && player.playerPos.x > 50)
			{
				moveForward(&player, Left);
			}
			if (CP_Input_KeyDown(KEY_S) && player.playerPos.y < (windowHeight - 50))
			{
				moveForward(&player, Down);
			}
			if (CP_Input_KeyDown(KEY_D) && player.playerPos.x < (windowWidth - 50))
			{
				moveForward(&player, Right);
			}

			// SWITCH WEAPON
			if (CP_Input_KeyReleased(KEY_Q))
			{
				player.weapon = switchWeapon(player.weapon);
				if (player.weapon == 1) {
					CP_Sound_PlayAdvanced(playerSwapRangeSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
				}
				else if(player.weapon == 0)
				{
					CP_Sound_PlayAdvanced(playerSwapMeleeSFX, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
				}
			}


			// ATTACK
			if (CP_Input_MouseClicked()) {
				// get vector and spawn hit point
				if (player.weapon == 1)
				{
					player.currentFrame = 2;
					bulletInit(bulletIndex, &player);
					CP_Sound_PlayAdvanced(playerRangedSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
				}
				else if(player.weapon == 0)
				{
					player.currentFrame = 2;
					meleeVec(&player, 100);
					CP_Image_DrawAdvanced(hitBox, player.weaponPos.x - 75, player.weaponPos.y -75, 150, 150 ,255, mouseToplayerAngle(&player)- 70);
					for (int i = 0; i < 10; i++)
					{
						damageEnemy(&quiz[i], &player, 150, 150, 6);
					}
					for (int i = 0; i < 8; i++)
					{
						damageEnemy(&assignment[i], &player, 150, 150, 8);
						damageEnemy(&lab[i], &player, 150, 150,8);
					}
					damageEnemy(&boss, &player, 150, 150, 4);
					CP_Sound_PlayAdvanced(playerMeleeSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
				}
			}
		}

		// Player DIE
		//
		// GAME OVER SCREEN + RESET BUTTON
		if(!player.alive)
		{
			if (GameOver == 0) {
				CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
				CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
				CP_Sound_PlayAdvanced(gameOverOST, 0.3f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
				GameOver = 1;
			}
			CP_Settings_Fill(red);
			CP_Font_DrawText("You failed :(", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2);
			CP_Font_DrawText("Press SPACE to retest, ESC to Quit", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2 + 420);
			if (CP_Input_KeyReleased(KEY_SPACE))
			{
				totalElapsedTime = 0;
				GameOver = 0;
				CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, NULL);
			}

			if (CP_Input_KeyReleased(KEY_ESCAPE)) {
				CP_Engine_Terminate();
			}

			//if (CP_Input_KeyDown(KEY_Q))
			//{
			//	CP_Engine_SetNextGameStateForced(Mainmenu_Init, Mainmenu_Update, NULL);
			//}
		}

		//COLLISION
		CP_Settings_Fill(green);
		if (player.alive&& !Win) {
			CP_Graphics_DrawRect(wall1.x, wall1.y, wall1.width, wall1.height);
			// TEST FOR PLAYER HITBOX
			//CP_Settings_RectMode(CP_POSITION_CENTER);
			//CP_Graphics_DrawRect(player.playerPos.x, player.playerPos.y, player.worldSizeW, player.worldSizeH);
		}

		// TIME
		//
		deltaTime = CP_System_GetDt();
		totalElapsedTime += deltaTime;

		isPlayerAlive(&player);
		if (!Win && player.alive) {
			// GAME SPAWN LOGIC 
			//
			spawnWeekly(totalElapsedTime, 5.0f,		// 1Q 1A 1L spawn at 5s
				0, 0, 0,
				1, 1, 1,
				QuizSS, AssSS, LabSS);
			spawnWeekly(totalElapsedTime, 15.0f,	// 1Q 1A 1L spawn at 15s
				1, 1, 1,
				3, 2, 2,
				QuizSS, AssSS, LabSS);
			spawnWeekly(totalElapsedTime, 25.0f,	// 2Q 2A 1L spawn at 25s
				3, 2, 2,
				5, 4, 3,
				QuizSS, AssSS, LabSS);
			spawnWeekly(totalElapsedTime, 45.0f,	// 2Q 2A 2L spawn at 45s
				5, 4, 3,
				7, 6, 5,
				QuizSS, AssSS, LabSS);
			spawnWeekly(totalElapsedTime, 65.0f,	// 3Q 2A 2L spawn at 1min 5s
				7, 6, 5,
				10, 8, 7,
				QuizSS, AssSS, LabSS);
			spawnBoss(totalElapsedTime, /*0.*/85.0f, BossSS); // Boss spawn at 1min 25s

			// BOSS OST
			//
			if (boss.inGame == 1 && bossOut == 0) {
				CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
				CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
				CP_Sound_PlayAdvanced(bossSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
				CP_Sound_PlayAdvanced(bossOST, 0.3f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
				bossOut = 1;
			}
		}

		// END GAME
		// 
		if (totalElapsedTime >= 300 || boss.alive == 0 && boss.inGame == 1) {
			boss.inGame = 0;
			//CP_Engine_Terminate();
		}

		// WIN GAME
		//
		if (Win == 0 && boss.inGame == 0 && boss.alive == 0) {
			CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
			CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
			CP_Sound_PlayAdvanced(winOST, 0.4f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
			Win = 1;
		}
		if (Win) {
			CP_Settings_Fill(red);
			CP_Font_DrawText("You WIN :)", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2);
			CP_Font_DrawText("Press SPACE to Replay, ESC to Quit", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2 + 420);

			if (CP_Input_KeyReleased(KEY_SPACE))
			{
				Win = 0;
				totalElapsedTime = 0;
				CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, NULL);
			}

			if (CP_Input_KeyReleased(KEY_ESCAPE)) {
				CP_Engine_Terminate();
			}

			//if (CP_Input_KeyDown(KEY_Q))
			//{
			//	CP_Engine_SetNextGameStateForced(Mainmenu_Init, Mainmenu_Update, NULL);
			//}
		}
		 
		//boss extra spawns
		//spawnWeekly(totalElapsedTime, 85.0f,
		//9, 2, 2, 5, 3, 3, QuizSS, AssSS, LabSS);


		// RENDERING POWERUP / PLAYER / BULLETS / HUD
		//
		if (player.alive && !Win) {
			// POWER UP
			//
			if (bbt.isActive && player.alive && totalElapsedTime > 10.0f) {
				CP_Settings_Fill(green);
				//CP_Graphics_DrawRect(bbt.position.x, bbt.position.y, bbt.Width, bbt.Height);
				CP_Image_Draw(bbtSS, bbt.position.x, bbt.position.y, bbt.Width, bbt.Height, 255);
				playerHeal(&bbt, &player);
			}if (!bbt.isActive) {
				coolDown(&bbt, deltaTime);
			}
			if (bbt.timer <= 0 && !bbt.isActive) {
				respawnItem(&bbt, randomX, randomY); //CP_Random_RangeFloat(50, 1800), CP_Random_RangeFloat(50,900));
			}

			// BULLET SIMULATION (UPDATING POSITION)
			//
			bulletUpdate(bulletIndex, deltaTime, 10, 8);
			// RENDER PLAYER
			//
			playerAnimation(playerSS, &player);
			updatePlayerAnimation(&player, deltaTime);

			// UI HUD
			//
			CP_Settings_RectMode(CP_POSITION_CORNER);
			// RENDER HEALTHBAR
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 150));
			CP_Graphics_DrawRect(windowWidth / 10, windowHeight / 1.08, player.GPA * 100, 30);

			// RENDER TEXT (GPA)
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Settings_TextSize(windowWidth / 38);
			CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
			CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
			CP_Settings_TextAlignment(horizontal, vertical);
			CP_Font_DrawText("GPA", windowWidth / 13, windowHeight / 1.07);

			// RENDER HEALTHBAR PLACEHOLDER
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
			CP_Graphics_DrawRect(windowWidth / 10, windowHeight / 1.08, 500, 30);

			// DEBUG USE: SHOW CURRENT WEAPON
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			if (player.weapon == 1)
			{
				CP_Font_DrawText("Current weapon: Ranged", windowWidth / 1.2, windowHeight / 1.07);
			}
			else CP_Font_DrawText("Current weapon: Melee", windowWidth / 1.2, windowHeight / 1.07);

		}

		// BOSS HEALTHBAR
		//
		if (boss.inGame && boss.alive && player.alive) {
			CP_Settings_RectMode(CP_POSITION_CORNER);
			// RENDER HEALTHBAR
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
			CP_Graphics_DrawRect(windowWidth / 2.8, windowHeight / 40, boss.HP*5, 30);
			// RENDER TEXT (GPA)
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Settings_TextSize(windowWidth / 38);
			CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
			CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
			CP_Settings_TextAlignment(horizontal, vertical);
			CP_Font_DrawText("BOSS", windowWidth / 3.2, windowHeight / 30);

			// RENDER HEALTHBAR PLACEHOLDER
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
			CP_Graphics_DrawRect(windowWidth / 2.8, windowHeight / 40, 500, 30);
		}


		// OLD UI HUD
		// 
		//if (player.alive) {
		//	
		//}

		// PAUSE KEY
		if (CP_Input_KeyReleased(KEY_ESCAPE) && !Win && player.alive)
		{
			paused = !paused;
		}

		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	}
	else
	{
		if (CP_Input_KeyReleased(KEY_ESCAPE) && !Win && player.alive)
		{
			paused = !paused;
		}
		//CP_Graphics_ClearBackground(CP_Color_Create(70, 70, 70, 70));
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("GAME PAUSED", (CP_System_GetWindowWidth() / 2), (CP_System_GetWindowHeight() / 2)-40);
		CP_Font_DrawText("Press Esc to resume, SPACE to quit", (CP_System_GetWindowWidth() / 2), (CP_System_GetWindowHeight() / 2));
		if (CP_Input_KeyReleased(KEY_SPACE)) {
			CP_Engine_Terminate();
		}
		//if (CP_Input_KeyDown(KEY_Q))
		//{
		//	CP_Engine_SetNextGameStateForced(Mainmenu_Init, Mainmenu_Update, NULL);
		//}
	}

	int push = 0;
	int collided = collision(&player, &wall1);
	//collide with right
	if (collided == 1)
	{
		push += (wall1.x + wall1.width) - (player.playerPos.x - (player.worldSizeW / 2));
		player.playerPos.x += push;
	}
	//collide with left
	if (collided == 2)
	{
		push += (player.playerPos.x + (player.worldSizeW / 2)) - (wall1.x);
		player.playerPos.x -= push;
	}
	//collide with bottom
	if (collided == 3)
	{
		push += (wall1.y + wall1.height) - (player.playerPos.y - (player.worldSizeW / 2));
		player.playerPos.y += push;
	}
	//collide with top
	if (collided == 4)
	{
		push += (player.playerPos.y + (player.worldSizeW / 2)) - (wall1.y);
		player.playerPos.y -= push;
	}


}

void Level_Exit()
{
	
	CP_Image_Free(&QuizSS);
	CP_Image_Free(&playerSS);
	CP_Image_Free(&LabSS);
	CP_Image_Free(&AssSS);
	CP_Image_Free(&Floor);
	CP_Image_Free(&bbtSS);
	CP_Image_Free(&BossSS);
	CP_Image_Free(&hitBox);
	
}