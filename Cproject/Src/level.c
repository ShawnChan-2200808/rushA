/*!
@file       level.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      This file contains our main level logic. 

	Shawn:	worked on player movement, player health HUD, player melee attack,
			spawning enemies and transitioning throught the weeks and to the end, 
			rendering background, spawning of powerups, audio.

	Justin: worked on 

   Wei Hao: worked on collision

  Ee Loong: worked on
*//*_________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "anim.h"
#include "weapons.h"
#include "powerups.h"
#include "collsion.h"
#include "mainmenu.h"
#include "pause.h"

extern CP_Color gray, blue, green, red;
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
int cheat;

void Level_Init(void)
{
	// Initialising everything for the level
	initGame();
	initAssets();
	playerInit(&player);
	initAllEnemies(10, 8, 8);
	bossInit(&boss);
	itemInit(&bbt, 600, 600, 55, 55, 1.0f);
	//tableinit(&table, windowWidth / 4, windowHeight / 4);
	//chairinit(&chair, windowWidth / 2 +50, windowHeight / 2 +50);
	initallwall(5, 3);
	randomX = 0;
	randomY = 0;

	allDead = 0;
	Win = 0;
	GameOver = 0;
	bossOut = 0;
	playerbulletReset(player.bulletIndex);
	totalElapsedTime = 0;

	//MUSIC - Shawn
	//
	CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
	CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
	CP_Sound_PlayAdvanced(levelOST, 0.3f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
	CP_Sound_PlayAdvanced(schoolBellSFX,0.1f,1.0f,FALSE, CP_SOUND_GROUP_SFX);

	cheat = 0;

	/*
	// FOR PITCH
	//
	quiz[0].EnemyPos = CP_Vector_Set((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 3));
	assignment[0].EnemyPos = CP_Vector_Set((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 3));
	lab[0].EnemyPos = CP_Vector_Set((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 3));
	boss.EnemyPos = CP_Vector_Set((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2.5));
	bbt.position = CP_Vector_Set((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 3));
	*/
}

void Level_Update(void)
{
	// CHEATS lol
	if (CP_Input_KeyDown(KEY_O)) {
		cheat = !cheat;
	}
	if (cheat) {
		player.damage = 1000;
	}
	else
	{
		player.damage = 3;
	}

	if (paused == 0)
	{
		// PLAYER MOVEMENT + BOUNDARIES - Shawn
		if (player.alive && !Win) {
			// render background
			SpawnBG(Floor, 6, 9);

			// WASD movement + offset so the player wont get off the screen
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

			// SWITCH WEAPON - Justin, Eeloong
			if (CP_Input_KeyReleased(KEY_Q) || CP_Input_MouseWheel() != 0)
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


			// ATTACK - Shawn Melee & Justin Ranged
			if (CP_Input_MouseClicked()) {
				
				if (player.weapon == 1)
				{
					// Set the hit animation frame
					player.currentFrame = 2;
					// Play Ranged attack sound
					CP_Sound_PlayAdvanced(playerRangedSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
					// Spawn the bullet
					playerbulletInit(player.bulletIndex, &player);
				}
				else if(player.weapon == 0)
				{
					// Set the hit animation frame
					player.currentFrame = 2;
					// Get vector and spawn hit point
					meleeVec(&player, 100.f);
					// Draws the hitbox sprite
					CP_Image_DrawAdvanced(hitBox, player.weaponPos.x - 75, player.weaponPos.y -75, 150, 150 ,255, mouseToplayerAngle(&player)- 70);
					// Looping through to check which enemy gets hit
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
					// Play Melee attack sound
					CP_Sound_PlayAdvanced(playerMeleeSFX, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
				}
			}
		}

		// Player DIE
		//
		// GAME OVER SCREEN + RESET BUTTON - Justin
		if(!player.alive)
		{
			if (GameOver == 0) {
				CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
				CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
				CP_Sound_PlayAdvanced(gameOverOST, 0.3f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
				GameOver = 1;
			}
			CP_Settings_Fill(red);
			CP_Font_DrawText("You failed...", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2));
			CP_Font_DrawText("Press SPACE to Re-Test, Q to main menu, ESC to Drop Out :(", (float)((CP_System_GetWindowWidth() / 2)), (float)(CP_System_GetWindowHeight() / 2 + 420));
			if (CP_Input_KeyReleased(KEY_SPACE))
			{
				totalElapsedTime = 0;
				GameOver = 0;
				CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, NULL);
			}

			if (CP_Input_KeyReleased(KEY_Q)) {
				CP_Engine_SetNextGameStateForced(Mainmenu_Init, Mainmenu_Update, NULL);
			}

			if (CP_Input_KeyReleased(KEY_ESCAPE)) {
				CP_Engine_Terminate();
			}
		}

		//COLLISION - WeiHao
		CP_Settings_Fill(green);
		if (player.alive&& !Win) {

			for (int i = 0; i < 3; i++)
			{
				CP_Image_Draw(Table, table[i].x, table[i].y, table[i].width, table[i].height, 255);
			}
			for (int i = 0; i < 5; i++)
			{
				CP_Image_Draw(Chair, chair[i].x, chair[i].y, chair[i].width, chair[i].height, 255);
			}
			// TEST FOR PLAYER HITBOX - WeiHao
			//CP_Settings_RectMode(CP_POSITION_CENTER);
			//CP_Graphics_DrawRect(player.playerPos.x, player.playerPos.y, player.worldSizeW, player.worldSizeH);
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

		//Check if player is alive
		isPlayerAlive(&player);

		if (!Win && player.alive) {
			
			// GAME SPAWN LOGIC - Shawn
			//
			// school is starting shows up when game starts
			if (totalElapsedTime < 3.0f && totalElapsedTime > 1.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("School is starting...", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}

			// show week 1
			if (totalElapsedTime < 5.0f && totalElapsedTime > 3.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("Get ready for Week 1!", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}

			spawnWeekly(totalElapsedTime, 5.0f,		// 1Q 1A 1L spawn at 5s
				0, 0, 0,
				1, 1, 1,
				QuizSS, AssSS, LabSS);

			// show week 2
			if (totalElapsedTime < 15.0f && totalElapsedTime > 12.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("Get ready for Week 2...", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			spawnWeekly(totalElapsedTime, 15.0f,	// 1Q 1A 1L spawn at 15s
				1, 1, 1,
				3, 2, 2,
				QuizSS, AssSS, LabSS);

			// show week 3
			if (totalElapsedTime < 25.0f && totalElapsedTime > 20.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("Get ready for Week 3...", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			spawnWeekly(totalElapsedTime, 25.0f,	// 2Q 2A 1L spawn at 25s
				3, 2, 2,
				5, 4, 3,
				QuizSS, AssSS, LabSS);

			// show week 4
			if (totalElapsedTime < 45.0f && totalElapsedTime > 42.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("Get ready for Week 4...", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			spawnWeekly(totalElapsedTime, 45.0f,	// 2Q 2A 2L spawn at 45s
				5, 4, 3,
				7, 6, 5,
				QuizSS, AssSS, LabSS);

			// show week 5
			if (totalElapsedTime < 65.0f && totalElapsedTime > 63.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("Get ready for Week 5, last week before finals...", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			spawnWeekly(totalElapsedTime, 65.0f,	// 3Q 2A 2L spawn at 1min 5s
				7, 6, 5,
				10, 8, 7,
				QuizSS, AssSS, LabSS);

			// show final week
			if (totalElapsedTime < 85.0f && totalElapsedTime > 83.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("Oh no its finals week...", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			spawnBoss(totalElapsedTime, 85.0f, BossSS); // Boss spawn at 1min 25s
			

			/*
//***** PRESENTATION LVL *****

			// school is starting shows up when game starts
			if (totalElapsedTime < 3.0f && totalElapsedTime > 1.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("Welcome to The Deliverables", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			if (totalElapsedTime < 8.0f && totalElapsedTime > 3.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("You are the student!", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}

			// show QUiZ
			if (totalElapsedTime < 18.0f && totalElapsedTime > 14.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("This is a quiz", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			quiz[0].speed = 50;
			spawnWeekly(totalElapsedTime, 15.0f,		// 1Quiz spawn at 15s
				0, 0, 0,
				1, 0, 0,
				QuizSS, AssSS, LabSS);

			// show ASS
			if (totalElapsedTime < 28.0f && totalElapsedTime > 24.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("This is an assignment", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			spawnWeekly(totalElapsedTime, 25.0f,	// 1Ass spawns at 25s
				0, 0, 0,
				0, 1, 0,
				QuizSS, AssSS, LabSS);

			// show LAB
			if (totalElapsedTime < 38.0f && totalElapsedTime > 34.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("This is a lab", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			spawnWeekly(totalElapsedTime, 35.0f,	// 1Lab spawn at 35s
				0, 0, 0,
				0, 0, 1,
				QuizSS, AssSS, LabSS);

			// show BBT
			if (totalElapsedTime < 48.0f && totalElapsedTime > 44.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("This is a Bubble Tea", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			if (bbt.isActive && player.alive && totalElapsedTime > 45.0f && totalElapsedTime < 50.0f) {
				CP_Image_Draw(bbtSS, bbt.position.x, bbt.position.y, bbt.Width, bbt.Height, 255);
				playerHeal(&bbt, &player);
				}if (!bbt.isActive) {
					coolDown(&bbt, deltaTime);
				}
				if (bbt.timer <= 0 && !bbt.isActive) {
					respawnItem(&bbt, (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 3));
				}

			// show Dr Wadini
			if (totalElapsedTime < 55.0f && totalElapsedTime > 49.0f) {
				CP_Settings_Fill(white);
				CP_Font_DrawText("This is Dr Wadini", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));
			}
			spawnBoss(totalElapsedTime, 50.0f, BossSS); // Boss spawn at 1min 25s
//***** END OF PRESENTATION LVL *****
			*/

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

		// END GAME - Shawn
		// 
		if (totalElapsedTime >= 300 || boss.alive == 0 && boss.inGame == 1) {
			boss.inGame = 0; // Turn Off the boss so that it triggers the below sequence
			boss.alive = 0; // For if the player survives until 5mins mark 
		}

		// WIN GAME - Shawn
		//
		if (Win == 0 && boss.inGame == 0 && boss.alive == 0) {
			// stop level music and play win music and trigger the rendering of the win screen
			CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
			CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
			CP_Sound_PlayAdvanced(winOST, 0.4f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
			Win = 1;
		}
		if (Win) {
			CP_Settings_Fill(red);
			CP_Font_DrawText("You got the Degree!!!", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2));
			CP_Font_DrawText("Press SPACE for better GPA, Q to main menu, ESC to Graduate!!!", ((float)(CP_System_GetWindowWidth() / 2)), (float)(CP_System_GetWindowHeight() / 2 + 420));

			if (CP_Input_KeyReleased(KEY_SPACE))
			{
				Win = 0;
				totalElapsedTime = 0;
				CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, NULL);
			}

			if (CP_Input_KeyReleased(KEY_ESCAPE)) {
				CP_Engine_Terminate();
			}

			if (CP_Input_KeyDown(KEY_Q))
			{
				CP_Engine_SetNextGameStateForced(Mainmenu_Init, Mainmenu_Update, NULL);
			}
		}
		//boss extra spawns if u want it to be harder xd
		//spawnWeekly(totalElapsedTime, 85.0f,
		//9, 2, 2, 5, 3, 3, QuizSS, AssSS, LabSS);


		// RENDERING POWERUP / PLAYER / BULLETS / HUD
		//
		if (player.alive && !Win) {
			
			// POWER UP (need to remove for pitch)
			//
			// render the bubble tea sprite if the item is ready and checks if player come into contact with it 
			if (bbt.isActive && player.alive && totalElapsedTime > 10.0f && totalElapsedTime < 65.0f) {
				//CP_Settings_Fill(green);
				//CP_Graphics_DrawRect(bbt.position.x, bbt.position.y, bbt.Width, bbt.Height);
				CP_Image_Draw(bbtSS, bbt.position.x, bbt.position.y, bbt.Width, bbt.Height, 255);
				playerHeal(&bbt, &player);

			// If the player has taken bubble tea it will not be active and activate the cooldown
			}if (!bbt.isActive && totalElapsedTime < 65.0f) {
				coolDown(&bbt, deltaTime);
			}

			// when the cooldown for bbt is up, respawn it at a random position
			if (bbt.timer <= 0 && !bbt.isActive && totalElapsedTime < 65.0f) {
				randomItemPos(&bbt);
				respawnItem(&bbt, bbt.randX, bbt.randY); //CP_Random_RangeFloat(50, 1800), CP_Random_RangeFloat(50,900));
			}
			

			// BULLET SIMULATION (UPDATING POSITION) - Justin
			//
			playerbulletUpdate(player.bulletIndex, deltaTime,10,8);
			// RENDER PLAYER
			//
			playerAnimation(playerSS, &player);
			updatePlayerAnimation(&player, deltaTime);

			// UI HUD - Shawn and Justin
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

			// DEBUG USE: SHOW CURRENT WEAPON - Justin
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			if (player.weapon == 1)
			{
				CP_Font_DrawText("Current weapon: Ranged", (float)(windowWidth / 1.2), (float)(windowHeight / 1.07));
			}
			else CP_Font_DrawText("Current weapon: Melee", (float)(windowWidth / 1.2), (float)(windowHeight / 1.07));

		}

		// BOSS HEALTHBAR - Shawn
		//
		if (boss.inGame && boss.alive && player.alive) {
			CP_Settings_RectMode(CP_POSITION_CORNER);
			// RENDER HEALTHBAR
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));
			CP_Graphics_DrawRect((float)(windowWidth / 2.8), (float)(windowHeight / 40), boss.HP * 5, 30);
			// RENDER TEXT (GPA)
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Settings_TextSize((float)(windowWidth / 38));
			CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
			CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
			CP_Settings_TextAlignment(horizontal, vertical);
			CP_Font_DrawText("DR WADINI", (float)(windowWidth / 3.5), (float)(windowHeight / 30));

			// RENDER HEALTHBAR PLACEHOLDER
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
			CP_Graphics_DrawRect((float)(windowWidth / 2.8), (float)(windowHeight / 40), 500, 30);
		}

		// PAUSE KEY - Justin
		//
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
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)((CP_System_GetWindowWidth() / 2) - 110), (float)((CP_System_GetWindowHeight() / 2) - 110), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))
		{
			paused = !paused;
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))// && !Win && player.alive))
		{
			paused = !paused;
			CP_Engine_SetNextGameStateForced(Level_Init, Level_Update, NULL);
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)((CP_System_GetWindowWidth() / 2)), (float)((CP_System_GetWindowHeight() / 2) + 110), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))// && !Win && player.alive))
		{
			paused = !paused;
			CP_Engine_SetNextGameState(Mainmenu_Init, Mainmenu_Update, Mainmenu_Exit);
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && (IsAreaClicked((float)((CP_System_GetWindowWidth() / 2)), (float)((CP_System_GetWindowHeight() / 2) + 220), 400, 90, CP_Input_GetMouseX(), CP_Input_GetMouseY())))// && !Win && player.alive))
		{
			freeAssets();
			CP_Engine_Terminate();
		}
		pauseScreen();
	}
}

void Level_Exit(void)
{
	
}