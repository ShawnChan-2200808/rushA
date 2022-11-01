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
#include "bullet.h"

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
extern struct Enemy quiz1, lab1, assignment1;
struct Bullet bullets[10];
extern CP_Color gray, blue, green, red;
extern int windowWidth, windowHeight;
extern float fps;
extern float hitCircleSize, totalElapsedTime;
extern CP_Vector Up, Left, Down, Right;
int chSize = 10;

extern float deltaTime;

CP_Image playerSS;
CP_Image QuizSS;
CP_Image AssSS;
CP_Image LabSS;
CP_Image Floor;



void Level_Init()
{
	initGame();

	playerSS = CP_Image_Load("Assets/player_idle_64h.png");
	QuizSS = CP_Image_Load("Assets/QUIZ.png");
	AssSS = CP_Image_Load("Assets/ASS_SS_64.png");
	LabSS = CP_Image_Load("Assets/LAB_SS_64.png");
	Floor = CP_Image_Load("Assets/School_Hall_Floor.png");

	playerInit(&player);
	quizInit(&quiz1, 300, 300);
	assInit(&assignment1, 500, 300);
	labInit(&lab1, 1000,300);

	for (int i = 0; i < 10; ++i)
	{
		bulletInit(&bullets[i]);
	}
}

void Level_Update()
{
	// PLAYER CROSSHAIR
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 0));
	//CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), chSize);

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
		if (CP_Input_KeyDown(KEY_S) && player.playerPos.y < (windowHeight-50))
		{
			moveForward(&player, Down);
		}
		if (CP_Input_KeyDown(KEY_D) && player.playerPos.x < (windowWidth-50))
		{
			moveForward(&player, Right);
		}

		// SWITCH WEAPON
		if (CP_Input_KeyReleased(KEY_Q))
		{
			player.weapon = switchWeapon(player.weapon);
			
			//TESTING THE LAB TRANSITION
			lab1.currentFrame+=1;
			if (lab1.currentFrame >7) {
				lab1.currentFrame = 0;
			}
		}


		// ATTACK
		if (CP_Input_MouseClicked()) {
			// get vector and spawn hit point
			{
				if (player.weapon == 1)
				{
					if (player.ammo > 0)
					{
						for (int i = 0; i < 10; ++i)
						{
							if (bullets[i].ready == 1)
							{
								bullets[i].active = 1;
								bullets[i].velocity = 1;
							}
						}
					}
				}
				else
				{
					meleeVec(&player,100);
					CP_Settings_Fill(blue);
					CP_Settings_RectMode(CP_POSITION_CENTER);
					CP_Graphics_DrawRect(player.weaponPos.x, player.weaponPos.y, 80, 80);
					damageEnemy(&quiz1,&player, 150, 150);
					damageEnemy(&assignment1, &player, 150, 150);
					damageEnemy(&lab1, &player, 150, 150);
				}
			}
		}
	}

	// GAME OVER SCREEN + RESET BUTTON
	else
	{
		CP_Settings_Fill(red);
		CP_Font_DrawText("You failed :(", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2);
		CP_Font_DrawText("Press Esc to retest", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2 + 420);
		if (CP_Input_KeyReleased(KEY_ESCAPE))
		{
			CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, NULL);
		}
	}

	// SPAWNS
	isPlayerAlive(&player);
	isEnemyAlive(&quiz1);
	isEnemyAlive(&assignment1);
	isEnemyAlive(&lab1);

	deltaTime = CP_System_GetDt();
	totalElapsedTime += deltaTime;


	for (int i = 0; i < 10; ++i)
	{
		updatePosition(&bullets[i]);
		CP_Graphics_DrawCircle(bullets[i].Pos.x, bullets[i].Pos.y, 20);
	}

	//testing GPA
	//if (player.GPA >0) {
	//	player.GPA -= deltaTime;
	//}
	//else {
	//	player.GPA = 5.00f;
	//}

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	// ENEMY
	// 
	// QUIZ is rendered and chase player
	if (quiz1.alive && player.alive) {
		// If enemy come into contact with player deal damage
		damagePlayer(&quiz1, &player);
		updateEnemyAnimation(&quiz1, deltaTime);
		enemyAnimation(QuizSS, &quiz1);
		enemyChase(&quiz1, &player);
		//testing for quiz without sprite
		//if (quiz1.HP == 1) { CP_Settings_Fill(CP_Color_Create(200, 0, 0, 255)); }
		//else { CP_Settings_Fill(red); }
		//CP_Settings_Fill(red);
		//CP_Graphics_DrawCircle(quiz1.EnemyPos.x, quiz1.EnemyPos.y, circleSize+20.0f);
		//CP_Settings_TextSize(windowWidth / 60);
		//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		//CP_Font_DrawText("quiz", quiz1.EnemyPos.x, quiz1.EnemyPos.y);
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&quiz1);
	}
	if (!quiz1.alive) {
		// reset enemy values
		respawnEnemy(&quiz1,10,10);
	}

	// Assignment1 Logic
	if (assignment1.alive && player.alive) {
		updateEnemyAnimation(&assignment1, deltaTime);
		enemyAnimation(AssSS, &assignment1);
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&assignment1);
	}
	if (!assignment1.alive) {
		// reset enemy values
		respawnEnemy(&assignment1, 500, 50);
	}

	// Lab1 Logic
	if (lab1.alive && player.alive) {
		enemyAnimation(LabSS, &lab1);
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&lab1);
	}
	if (!lab1.alive) {
		// reset enemy values
		respawnEnemy(&lab1, 1000, 50);
	}

	if (player.alive) {
		playerAnimation(playerSS,&player);
		updatePlayerAnimation(&player,deltaTime);
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
}

void Level_Exit()
{
	CP_Image_Free(&QuizSS);
	CP_Image_Free(&playerSS);
	CP_Image_Free(&LabSS);
	CP_Image_Free(&AssSS);
	CP_Image_Free(&Floor);
}