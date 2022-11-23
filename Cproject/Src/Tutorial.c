/*!
@file       Tutorial.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/1965 (last updated)
@brief      This file contains the tutorial level that we integrate
		*** Ee Loong is a sad sad boy,i think he needs some company***
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
#include "collsion.h"
#include "mainmenu.h"

static int allDead;
static int Win;
static int GameOver;
extern CP_Color gray, blue, green, red;
extern int windowWidth, windowHeight;
extern float fps;
static float totalElapsedTime;
CP_Vector Up, Left, Down, Right;
extern int randomX, randomY;
float deltaTime, tutorialtime;
int paused, flag, stage, projectilecount;

void Tutorial_Init()
{
	initGame();
	initAssets();
	playerInit(&player);
	initAllEnemies(2, 2, 1);
	itemInit(&bbt, 600, 600, 55, 55, 1.0f);
	initallwall(5, 3);
	randomX = 0;
	randomY = 0;

	allDead = 0;
	Win = 0;
	GameOver = 0;
	//MUSIC
	CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
	CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
	CP_Sound_PlayAdvanced(levelOST, 0.3f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
	CP_Sound_PlayAdvanced(schoolBellSFX, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
	stage = 0;
	flag = 0;
	projectilecount = 0;
	tutorialtime = 0;
}

void Tutorial_Update()
{
	//Game Run Code
	if (paused == 0) {
		if (player.alive && !Win) {
			SpawnBG(Floor, 6, 9);
			if (stage >= 5) {
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
			}
			// SWITCH WEAPON
			if (CP_Input_KeyReleased(KEY_Q) || CP_Input_MouseWheel() && stage >= 8)
			{
				player.weapon = switchWeapon(player.weapon);
				if (player.weapon == 1) {
					CP_Sound_PlayAdvanced(playerSwapRangeSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
				}
				else if (player.weapon == 0)
				{
					CP_Sound_PlayAdvanced(playerSwapMeleeSFX, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
				}
			}

			// ATTACK
			if (CP_Input_MouseClicked() && stage >= 6) {
				// get vector and spawn hit point
				if (player.weapon == 1)
				{
					player.currentFrame = 2;
					CP_Sound_PlayAdvanced(playerRangedSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
					playerbulletInit(player.bulletIndex, &player);
					++projectilecount;
				}
				else if (player.weapon == 0)
				{
					player.currentFrame = 2;
					meleeVec(&player, 100);
					CP_Image_DrawAdvanced(hitBox, player.weaponPos.x - 75, player.weaponPos.y - 75, 150, 150, 255, mouseToplayerAngle(&player) - 70);
					for (int i = 0; i < 2; i++)
					{
						damageEnemy(&quiz[i], &player, 150, 150, 6);
					}
					for (int i = 0; i < 2; i++)
					{
						damageEnemy(&assignment[i], &player, 150, 150, 8);
						damageEnemy(&lab[i], &player, 150, 150, 8);
					}
					//if (randomiser==0 || randomiser == 4) {
					CP_Sound_PlayAdvanced(playerMeleeSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
					//}
				}
			}

			// BULLET SIMULATION (UPDATING POSITION)
//
			playerbulletUpdate(player.bulletIndex, deltaTime, 10, 8);
			// RENDER PLAYER
			//
			playerAnimation(playerSS, &player);
			updatePlayerAnimation(&player, deltaTime);

			// UI HUD
			//
			CP_Settings_RectMode(CP_POSITION_CORNER);
			// RENDER HEALTHBAR
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 150));
			CP_Graphics_DrawRect((float)(windowWidth / 10), (float)(windowHeight / 1.08), player.GPA * 100, 30);

			// RENDER TEXT (GPA)
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Settings_TextSize((float)(windowWidth / 38));
			CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
			CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
			CP_Settings_TextAlignment(horizontal, vertical);
			CP_Font_DrawText("GPA", (float)(windowWidth / 13), (float)(windowHeight / 1.07));

			// RENDER HEALTHBAR PLACEHOLDER
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
			CP_Graphics_DrawRect((float)(windowWidth / 10), (float)(windowHeight / 1.08), 500, 30);

			// DEBUG USE: SHOW CURRENT WEAPON
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			if (player.weapon == 1 && stage >= 8)
			{
				CP_Font_DrawText("Current weapon: Ranged", (float)(windowWidth / 1.2), (float)(windowHeight / 1.07));
			}
			else CP_Font_DrawText("Current weapon: Melee", (float)(windowWidth / 1.2), (float)(windowHeight / 1.07));

			if (CP_Input_KeyReleased(KEY_ESCAPE) && !Win && player.alive && stage >= 4)
			{
				paused = !paused;
				if (stage == 4) {
					flag = 1;
				}
			}

			//COLLISION
			CP_Settings_Fill(green);
			if (player.alive && !Win) {
				//drawtable chair
				for (int i = 0; i < 3; i++)
				{
					CP_Image_Draw(Table, table[i].x, table[i].y, table[i].width, table[i].height, 255);
				}
				for (int i = 0; i < 5; i++)
				{
					CP_Image_Draw(Chair, chair[i].x, chair[i].y, chair[i].width, chair[i].height, 255);
				}
				//pushback
				for (int j = 0;j < 5; j++)
				{
					pushback(&player, &chair[j]);
					for (int q = 0; q < 10; q++)
					{
						pushbackEnemy(&quiz[q], &chair[j]);
					}
					for (int w = 0; w < 8; w++)
					{
						pushbackEnemy(&lab[w], &chair[j]);
					}
					for (int e = 0; e < 8; e++)
					{
						pushbackEnemy(&assignment[e], &chair[j]);
					}
					pushbackEnemy(&boss, &chair[j]);
				}
				for (int i = 0; i < 3; i++)
				{
					pushback(&player, &table[i]);
					for (int q = 0; q < 10; q++)
					{
						pushbackEnemy(&quiz[q], &table[i]);
					}
					for (int w = 0; w < 8; w++)
					{
						pushbackEnemy(&lab[w], &table[i]);
					}
					for (int e = 0; e < 8; e++)
					{
						pushbackEnemy(&assignment[e], &table[i]);
					}
					pushbackEnemy(&boss, &table[i]);
				}
			}

			// TIME
			//
			deltaTime = CP_System_GetDt();
			totalElapsedTime += deltaTime;

			isPlayerAlive(&player);

			if (!player.alive)
			{
				if (GameOver == 0) {
					CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
					CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
					CP_Sound_PlayAdvanced(gameOverOST, 0.3f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
					GameOver = 1;
				}
				CP_Settings_Fill(red);
				CP_Font_DrawText("You failed...", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2));
				CP_Font_DrawText("Press SPACE to Re-Test, ESC to Drop Out :(", (float)((CP_System_GetWindowWidth() / 2)), (float)(CP_System_GetWindowHeight() / 2 + 420));
				if (CP_Input_KeyReleased(KEY_SPACE))
				{
					totalElapsedTime = 0;
					GameOver = 0;
					CP_Engine_SetNextGameStateForced(Tutorial_Init, Tutorial_Update, NULL);
				}

				if (CP_Input_KeyReleased(KEY_ESCAPE)) {
					CP_Engine_SetNextGameStateForced(Mainmenu_Init, Mainmenu_Update, NULL);
				}
			}
			//Tutorial Code

		}
		//CP_Settings_Fill(green);
		//if (player.alive && !Win) {
		//	//draw table and chair
		//	//for (int i = 0; i < 3; i++)
		//	//{
		//	//	CP_Image_Draw(Table, table[i].x, table[i].y, table[i].width, table[i].height, 255);
		//	//}
		//	//for (int i = 0; i < 5; i++)
		//	//{
		//	//	CP_Image_Draw(Chair, chair[i].x, chair[i].y, chair[i].width, chair[i].height, 255);
		//	//}
		//	//pushback
		//	for (int j = 0;j < 5; j++)
		//	{
		//		pushback(&player, &chair[j]);
		//		for (int q = 0; q < 10; q++)
		//		{
		//			pushbackEnemy(&quiz[q], &chair[j]);
		//		}
		//		for (int w = 0; w < 8; w++)
		//		{
		//			pushbackEnemy(&lab[w], &chair[j]);
		//		}
		//		for (int e = 0; e < 8; e++)
		//		{
		//			pushbackEnemy(&assignment[e], &chair[j]);
		//		}
		//		pushbackEnemy(&boss, &chair[j]);
		//	}
		//	for (int i = 0; i < 3; i++)
		//	{
		//		pushback(&player, &table[i]);
		//		for (int q = 0; q < 10; q++)
		//		{
		//			pushbackEnemy(&quiz[q], &table[i]);
		//		}
		//		for (int w = 0; w < 8; w++)
		//		{
		//			pushbackEnemy(&lab[w], &table[i]);
		//		}
		//		for (int e = 0; e < 8; e++)
		//		{
		//			pushbackEnemy(&assignment[e], &table[i]);
		//		}
		//		pushbackEnemy(&boss, &table[i]);
		//	}
		//}
		CP_Settings_Fill(white);
		switch (stage) {
		case 0:
			//@todo print instructions for w,a,s,d
			if (flag == 0)
				CP_Font_DrawText("PRESS W to move forward", windowWidth / 2, windowHeight / 2 - 300);
			if (CP_Input_KeyDown(KEY_W) && player.playerPos.y > 50)
			{
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 1:
			if (flag == 0)
				CP_Font_DrawText("PRESS A to move left", windowWidth / 2, windowHeight / 2 - 300);
			if (CP_Input_KeyDown(KEY_A) && player.playerPos.x > 50)
			{
				flag = 1;

			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 2:
			if (flag == 0)
				CP_Font_DrawText("PRESS S to move backwards", windowWidth / 2, windowHeight / 2 - 300);
			if (CP_Input_KeyDown(KEY_S) && player.playerPos.y < (windowHeight - 50))
			{
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 3:
			if (flag == 0)
				CP_Font_DrawText("PRESS D to move right", windowWidth / 2, windowHeight / 2 - 300);
			if (CP_Input_KeyDown(KEY_D) && player.playerPos.x < (windowWidth - 50))
			{
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 4:
			CP_Graphics_ClearBackground(black);
			if (flag == 0) {
				CP_Font_DrawText("PRESS esc to pause the game student", windowWidth / 2, windowHeight / 2 - 300);
			}
			if (flag == 1)
			{
				flag = 2;
				CP_Font_DrawText("congrats now PRESS esc again to unpause student", windowWidth / 2, windowHeight / 2 - 300);
			}
			if (flag == 2 && paused == 0) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
			// move to location
		case 5:
			if (flag == 0) {
				CP_Graphics_DrawRect(200, 800, 80, 80);
				CP_Font_DrawText("Go to the box with the WASD keys student", windowWidth / 2, windowHeight / 2 - 300);
			}
			//press esc to pause
			if (1 == IsRectEntered(200, 800, 80, 80, player.playerPos.x, player.playerPos.y)) {
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 6:
			if (flag == 0)
				CP_Font_DrawText("Click and aim to do melee damage student", windowWidth / 2, windowHeight / 2 - 300);
			if (CP_Input_MouseClicked()) {
				flag = 1;
				//if (randomiser==0 || randomiser == 4) {
				//}
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 7:
			if (flag == 0) {
				CP_Font_DrawText("Kill the quiz student", windowWidth / 2, windowHeight / 2 - 300);
				spawnWeekly(1, 0,		// 1Q 1A 1L spawn at 5s
					0, 0, 0,
					1, 0, 0,
					QuizSS, AssSS, LabSS);
				quiz[0].speed = 0;
			}
			if (quiz[0].alive == 0) {
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 8:
			if (flag == 0)
				CP_Font_DrawText("Use the q or scroll wheel to change weapon student", windowWidth / 2, windowHeight / 2 - 300);
			if (player.weapon == 1) {
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 9:
			if (flag == 0) {
				CP_Font_DrawText("Click the direction you would like to shoot projectiles in student", windowWidth / 2, windowHeight / 2 - 300);
				player.weapon = 1;
			}
			if (projectilecount == 7) {
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 10:
			if (flag == 0) {
				CP_Font_DrawText("Kill the assignment student", windowWidth / 2, windowHeight / 2 - 300);
				spawnWeekly(1, 0,		// 1Q 1A 1L spawn at 5s
					0, 0, 0,
					0, 1, 0,
					QuizSS, AssSS, LabSS);
			}
			if (assignment[0].alive == 0) {
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 11:
			if (flag == 0) {
				CP_Font_DrawText("Get the bubble tea to heal your health student", windowWidth / 2, windowHeight / 2 - 300);
				player.GPA = 4;
				if (!bbt.isActive) {
					randomItemPos(&bbt);
					respawnItem(&bbt, bbt.randX, bbt.randY); //CP_Random_RangeFloat(50, 1800), CP_Random_RangeFloat(50,900));
					bbt.isActive = 1;
				}
				//CP_Graphics_DrawRect(bbt.position.x, bbt.position.y, bbt.Width, bbt.Height);
				if (bbt.isActive && player.alive) {
					CP_Settings_Fill(green);
					//CP_Graphics_DrawRect(bbt.position.x, bbt.position.y, bbt.Width, bbt.Height);
					CP_Image_Draw(bbtSS, bbt.position.x, bbt.position.y, bbt.Width, bbt.Height, 255);
					playerHeal(&bbt, &player);
				}
			}
			if (player.GPA > 4) {
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 12:
			if (flag == 0) {
				CP_Font_DrawText("Kill EVERYTHING student", windowWidth / 2, windowHeight / 2 - 300);
				spawnWeekly(1, 0,		// 1Q 1A 1L spawn at 5s
					1, 1, 0,
					2, 2, 1,
					QuizSS, AssSS, LabSS);
			}
			if (assignment[1].alive == 0 && quiz[1].alive == 0 && lab[0].alive == 0) {
				flag = 1;
			}
			if (flag == 1) {
				CP_Font_DrawText("congrats student", windowWidth / 2, windowHeight / 2 - 300);
				tutorialtime += CP_System_GetDt();
				printf("delta time %f", tutorialtime);
				if (tutorialtime > 1.3) {
					++stage;
					tutorialtime = 0;
					flag = 0;
				}
			}
			break;
		case 13:
			CP_Font_DrawText("Congrats student you are now ready to enroll into school", windowWidth / 2, windowHeight / 2 - 300);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			CP_Settings_Fill(red);
			CP_Graphics_DrawRect((float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) + 110), 400, 90);
			CP_Settings_Fill(black);
			CP_Font_DrawText("Return to Menu", (float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) + 110));
			if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)((CP_System_GetWindowWidth() / 2)), (float)((CP_System_GetWindowHeight() / 2) + 110), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))// && !Win && player.alive))
			{
				CP_Engine_SetNextGameState(Mainmenu_Init, Mainmenu_Update, Mainmenu_Exit);
				stage = 0;
			}
			break;
		}

		// Player DIE
		//
		// GAME OVER SCREEN + RESET BUTTON

	}
	else {
		if (CP_Input_KeyReleased(KEY_ESCAPE) && !Win && player.alive)
		{
			paused = !paused;
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)((CP_System_GetWindowWidth() / 2) - 110), (float)((CP_System_GetWindowHeight() / 2) - 110), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))
		{
			paused = !paused;
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))// && !Win && player.alive))
		{
			paused = !paused;
			CP_Engine_SetNextGameStateForced(Tutorial_Init, Tutorial_Update, NULL);
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)((CP_System_GetWindowWidth() / 2)), (float)((CP_System_GetWindowHeight() / 2) + 110), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))// && !Win && player.alive))
		{
			paused = !paused;
			CP_Engine_SetNextGameState(Mainmenu_Init, Mainmenu_Update, Mainmenu_Exit);
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)((CP_System_GetWindowWidth() / 2)), (float)((CP_System_GetWindowHeight() / 2) + 220), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))// && !Win && player.alive))
		{
			CP_Engine_Terminate();
		}
		pauseScreen();
	}
}

//CP_Graphics_ClearBackground(CP_Color_Create(70, 70, 70, 70));
//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
//CP_Font_DrawText("GAME PAUSED", (float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) - 40));
//CP_Font_DrawText("Press Esc to resume studying, SPACE to Drop Out", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2));
//if (CP_Input_KeyReleased(KEY_SPACE)) {
//	CP_Engine_Terminate();
//}
//if (CP_Input_KeyDown(KEY_Q))
//{
//	CP_Engine_SetNextGameStateForced(Mainmenu_Init, Mainmenu_Update, NULL);
//}


void Tutorial_Exit()
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