/*!
@file       level.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date        / /2022 (last updated)
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

extern struct Player {
	CP_Vector playerPos, tempPos, direction;
	CP_Vector weaponPos, bulletPos;
	int speed, alive, damage, weapon, attacking, ammo;
	float GPA, timer, projVelocity;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
};

extern struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	int speed, alive;
	float HP, damage;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
};

extern struct Player player;
extern struct Enemy quiz1, lab, assignment;
extern CP_Color gray, blue, green, red;
extern int windowWidth, windowHeight;
extern float fps;
extern float hitCircleSize, totalElapsedTime;
extern CP_Vector Up, Left, Down, Right;
int chSize = 10;

extern float deltaTime;

CP_Image Spritesheet;
CP_Image Floor;

void Level_Init()
{
	initGame();
	Spritesheet = CP_Image_Load("Assets/QUIZ.png");
	Floor = CP_Image_Load("Assets/School_Hall_Floor.png");

	playerInit(&player);
	quizInit(&quiz1, 300, 300);
}

void Level_Update()
{
	SpawnBG(Floor, 6, 9);
	// PLAYER CROSSHAIR
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 0));
	//CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), chSize);


	// PLAYER MOVEMENT + BOUNDARIES
	if (player.alive) {
		if (CP_Input_KeyDown(KEY_W) && player.playerPos.y > 1)
		{
			moveForward(&player, Up);
		}
		if (CP_Input_KeyDown(KEY_A) && player.playerPos.x > 1)
		{
			moveForward(&player, Left);
		}
		if (CP_Input_KeyDown(KEY_S) && player.playerPos.y < windowHeight)
		{
			moveForward(&player, Down);
		}
		if (CP_Input_KeyDown(KEY_D) && player.playerPos.x < windowWidth)
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
			{
				if (player.weapon == 1)
				{
					if (player.ammo > 0)
					{
						meleeVec(&player);
						CP_Settings_Fill(red);
						CP_Graphics_DrawCircle(player.weaponPos.x, player.weaponPos.y, 10);

					}


				}
				else
				{
					meleeVec(&player);
					CP_Settings_Fill(blue);
					CP_Settings_RectMode(CP_POSITION_CENTER);
					CP_Graphics_DrawRect(player.weaponPos.x, player.weaponPos.y, 80, 80);
					if (IsAreaClicked(player.weaponPos.x, player.weaponPos.y, 120, 120, quiz1.EnemyPos.x, quiz1.EnemyPos.y) && quiz1.alive) {
						quiz1.HP -= player.damage;
					}
				}
			}
		}


		// UI AND HUD
		//CP_Graphics_DrawRect(player.weaponPos.x, player.weaponPos.y, 10, 10);
		CP_Settings_RectMode(CP_POSITION_CORNER);
		// RENDER HEALTHBAR
		CP_Settings_Fill(green);
		CP_Graphics_DrawRect(windowWidth / 10, windowHeight / 54, player.GPA * 100, 30);
	}

	// GAME OVER SCREEN + RESET BUTTON
	else
	{
		CP_Settings_Fill(red);
		CP_Font_DrawText("GAME OVER", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2);
		CP_Font_DrawText("Press Esc to retry", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2 + 20);
		if (CP_Input_KeyReleased(KEY_ESCAPE))
		{
			CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, NULL);
		}
	}

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

	// If enemy come into contact with player deal damage
	damagePlayer(&quiz1, &player);
	//if (isCircleEntered(quiz1.EnemyPos.x, quiz1.EnemyPos.y, circleSize, player.playerPos.x, player.playerPos.y) && player.alive) {
	//	player.GPA -= quiz1.damage;
	//}

	// DEBUG USE: SHOW CURRENT WEAPON
	CP_Settings_Fill(blue);
	if (player.weapon == 1)
	{
		CP_Font_DrawText("Current weapon: Ranged", windowWidth / 6, 90);
	}
	else CP_Font_DrawText("Current weapon: Melee", windowWidth / 6, 90);



	// SPAWNS
	isPlayerAlive(&player);
	//quiz1.alive = 0;
	isEnemyAlive(&quiz1);

	deltaTime = CP_System_GetDt();
	totalElapsedTime += deltaTime;

	//if (player.GPA >0) {
	//	player.GPA -= deltaTime;
	//}
	//else {
	//	player.GPA = 5.00f;
	//}

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	// ENEMY
	// 
	// Enemy is rendered chase player
	if (quiz1.alive && player.alive) {

		UpdateEnemyAnimation(&quiz1, deltaTime);
		EnemyAnimation(Spritesheet, &quiz1);
		enemyChase(&quiz1, &player);
		/*if (quiz1.HP == 1) {
			CP_Settings_Fill(CP_Color_Create(200, 0, 0, 255));
		}
		else
		{
			CP_Settings_Fill(red);
		}*/
		//CP_Settings_Fill(red);
		//CP_Graphics_DrawCircle(quiz1.EnemyPos.x, quiz1.EnemyPos.y, circleSize+20.0f);
		//CP_Settings_TextSize(windowWidth / 60);
		//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		//CP_Font_DrawText("quiz", quiz1.EnemyPos.x, quiz1.EnemyPos.y);
	}
	else {
		// move dead enemy to out of screen
		quiz1.EnemyPos.x = -100;
		quiz1.EnemyPos.y = -100;
	}

	if (!quiz1.alive) {
		// reset enemy values
		quiz1.HP = 2;
		quiz1.EnemyPos.x = 10;
		quiz1.EnemyPos.y = 10;
		quiz1.alive = 1;
	}

	if (player.alive) {
		CP_Settings_Fill(blue);
		CP_Graphics_DrawCircle(player.playerPos.x, player.playerPos.y, hitCircleSize);
	}


	// END GAME
	// 
	//if (totalElapsedTime >= 20) {
	//	CP_Engine_Terminate();
	//}
}

void Level_Exit()
{
	CP_Image_Free(&Spritesheet);
	CP_Image_Free(&Floor);
}