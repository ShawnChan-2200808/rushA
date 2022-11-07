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


CP_Color gray, blue, green, red;
int windowWidth, windowHeight;
float fps;
float hitCircleSize, totalElapsedTime;
CP_Vector Up, Left, Down, Right;
int chSize = 10;
int randomX, randomY;
float deltaTime;
int paused,week1=0;

CP_Image playerSS;
CP_Image QuizSS;
CP_Image AssSS;
CP_Image LabSS;
CP_Image Floor;
CP_Image bbtSS;



void Level_Init()
{
	initGame();

	playerSS = CP_Image_Load("Assets/player_SS.png");
	QuizSS = CP_Image_Load("Assets/QUIZ.png");
	AssSS = CP_Image_Load("Assets/ASS_SS.png");
	LabSS = CP_Image_Load("Assets/LAB_SS.png");
	Floor = CP_Image_Load("Assets/School_Hall_Floor.png");
	bbtSS = CP_Image_Load("Assets/BBT.png");

	playerInit(&player);
	initAllEnemies(10, 8);
	//quizInit(&quiz, 300, 300);
	//assInit(&assignment, 500, 300);
	//labInit(&lab, 1000, 300);
	wall1init(&wall1, 100, 100, windowWidth / 4, windowHeight / 4);
	
	itemInit(&bbt, 600, 600, 55, 55, 1);
	randomX = 0;
	randomY = 0;
	bulletReset(bulletIndex);
	totalElapsedTime = 0;
}

void Level_Update()
{
	if (paused == 0)
	{
		// PLAYER MOVEMENT + BOUNDARIES
		if (player.alive) {
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
			}


			// ATTACK
			if (CP_Input_MouseClicked()) {
				// get vector and spawn hit point
				if (player.weapon == 1)
				{
					player.currentFrame = 2;
					bulletInit(bulletIndex, &player);
				}
				else
				{
					player.currentFrame = 2;
					meleeVec(&player, 100);
					CP_Settings_Fill(blue);
					//CP_Settings_RectMode(CP_POSITION_CENTER);
					CP_Graphics_DrawRect(player.weaponPos.x, player.weaponPos.y, 80, 80);
					for (int i = 0; i < 10; i++)
					{
						damageEnemy(&quiz[i], &player, 150, 150);
					}
					for (int i = 0; i < 8; i++)
					{
						damageEnemy(&assignment[i], &player, 150, 150);
						damageEnemy(&lab[i], &player, 150, 150);
					}

				}
			}
		}

		// GAME OVER SCREEN + RESET BUTTON
		else
		{
			CP_Settings_Fill(red);
			CP_Font_DrawText("You failed :(", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2);
			CP_Font_DrawText("Press SPACE to retest", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2 + 420);
			if (CP_Input_KeyReleased(KEY_SPACE))
			{
				CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, NULL);
			}
		}

		//// SPAWNS
		//isPlayerAlive(&player);
		//isEnemyAlive(&quiz1);
		//isEnemyAlive(&assignment1);
		//isEnemyAlive(&lab1);

		//collision
		CP_Settings_Fill(green);
		if (player.alive) {
		CP_Graphics_DrawRect(wall1.x, wall1.y, wall1.width, wall1.height);
		//CP_Settings_RectMode(CP_POSITION_CENTER);
		//CP_Graphics_DrawRect(player.playerPos.x, player.playerPos.y, player.worldSizeW, player.worldSizeH);
	}

		// TIME
		//
		deltaTime = CP_System_GetDt();
		totalElapsedTime += deltaTime;

		isPlayerAlive(&player);

		checkEnemyAlive(10,8);
		//isEnemyAlive(&quiz);
		//sEnemyAlive(&assignment);
		//isEnemyAlive(&lab);


		allEnemyLogic(10,8, QuizSS, AssSS, LabSS);
		/*
		if(totalElapsedTime >5.0){
			labLogic(LabSS, &lab, &player);
			//// Lab1 Logic
			//if (lab1.alive && player.alive) {
			//	if (1 == laser(&lab1, &player)) {
			//		player.GPA -= lab1.damage;
			//	}
			//	enemyAnimation(LabSS, &lab1);
			//	rotatenemy(&lab1, &player);
			//}
			//else {
			//	// move dead enemy to out of screen
			//	removeEnemy(&lab1);
			//}
			//if (!lab1.alive) {
			//	// reset enemy values
			//	respawnEnemy(&lab1, 1000, 50, 10);
			//}

			// ENEMY
			// 
			quizLogic(QuizSS, &quiz, &player);
			//// QUIZ is rendered and chase player
			//if (quiz1.alive && player.alive) {
			//	// If enemy come into contact with player deal damage
			//	updateEnemyAnimation(&quiz1, deltaTime);
			//	enemyAnimation(QuizSS, &quiz1);
			//	enemyChase(&quiz1, &player);
			//	damagePlayer(&quiz1, &player);
			//}
			//else {
			//	// move dead enemy to out of screen
			//	removeEnemy(&quiz1);
			//}
			//if (!quiz1.alive) {
			//	// reset enemy values
			//	respawnEnemy(&quiz1, 10, 10,15);
			//}

			assLogic(AssSS, &assignment, &player);
			//// Assignment1 Logic
			//if (assignment1.alive && player.alive) {
			//	updateEnemyAnimation(&assignment1, deltaTime);
			//	enemyAnimation(AssSS, &assignment1);
			//}
			//else {
			//	// move dead enemy to out of screen
			//	removeEnemy(&assignment1);
			//}
			//if (!assignment1.alive) {
			//	// reset enemy values
			//	respawnEnemy(&assignment1, 500, 50,5);
			//}
		}
		if (totalElapsedTime > 20.0f ) {
			spawnWeek1(&quiz,&assignment,&lab,week1);
		}

		*/

		// BULLET SIMULATION (UPDATING POSITION)
		//
		bulletUpdate(bulletIndex, deltaTime,10,8);

		// PowerUP 
		//
		if (bbt.isActive && player.alive) {
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


		if (player.alive) {
			playerAnimation(playerSS, &player);
			updatePlayerAnimation(&player, deltaTime);
			/* Testing player without sprite
			CP_Settings_Fill(blue);
			CP_Graphics_DrawCircle(player.playerPos.x, player.playerPos.y, hitCircleSize);
			*/
		}



		//UI HUD
		if (player.alive) {
			CP_Settings_RectMode(CP_POSITION_CORNER);
			// RENDER HEALTHBAR
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 150));
			CP_Graphics_DrawRect(windowWidth / 10, windowHeight / 54, player.GPA * 100, 30);

			// RENDER TEXT (GPA)
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Settings_TextSize(windowWidth / 38);
			CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
			CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
			CP_Settings_TextAlignment(horizontal, vertical);
			CP_Font_DrawText("GPA", windowWidth / 13, windowHeight / 30);

			// RENDER HEALTHBAR PLACEHOLDER
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
			CP_Graphics_DrawRect(windowWidth / 10, windowHeight / 54, 500, 30);

			// DEBUG USE: SHOW CURRENT WEAPON
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			if (player.weapon == 1)
			{
				CP_Font_DrawText("Current weapon: Ranged", windowWidth / 6, 90);
			}
			else CP_Font_DrawText("Current weapon: Melee", windowWidth / 6, 90);
		}

		// END GAME
		// 
		//if (totalElapsedTime >= 20) {
		//	CP_Engine_Terminate();
		//}

		// PAUSE KEY
		if (CP_Input_KeyReleased(KEY_ESCAPE))
		{
			paused = !paused;
		}

		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		}
		else
		{
		if (CP_Input_KeyReleased(KEY_ESCAPE))
		{
			paused = !paused;
		}
		CP_Graphics_ClearBackground(CP_Color_Create(70, 70, 70, 70));
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("GAME PAUSED", (CP_System_GetWindowWidth() / 3), (CP_System_GetWindowHeight() / 2));
		CP_Font_DrawText("Press Esc to resume", (CP_System_GetWindowWidth() / 2), (CP_System_GetWindowHeight() / 2));
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

	// END GAME
	// 
	//if (totalElapsedTime >= 20) {
	//	CP_Engine_Terminate();
	//}

}

void Level_Exit()
{
	CP_Image_Free(&QuizSS);
	CP_Image_Free(&playerSS);
	CP_Image_Free(&LabSS);
	CP_Image_Free(&AssSS);
	CP_Image_Free(&Floor);
	CP_Image_Free(&bbtSS);
}