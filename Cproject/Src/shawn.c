/*!
@file       .c
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date        / /2022 (last updated)
@brief      Make prototype functions and test it here. Copy and paste from current level
			to see if it works before we integrate it into the main game
		*** AND MAKE A COPY for yourself + DONT FORGET TO MAKE .H file to test ***
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
//#include "level.h"
//#include "stdio.h" 
//#include "stdlib.h"

extern struct Player {
	CP_Vector playerPos, tempPos, direction;
	CP_Vector weaponPos, Pos;
	int speed, alive, damage, weapon, attacking, ammo;
	float GPA, timer, projVelocity;
};

extern struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	int speed, alive;
	float HP, damage;
};

extern struct Bullet {
	CP_Vector Pos, Vector;
	int velocity, active, ready;
};

extern struct Player player;
extern struct Bullet playerBullets[10];
extern struct Enemy quiz1, lab, assignment;
extern CP_Color gray,blue,green,red;
extern int windowWidth, windowHeight;
extern float fps;
extern float circleSize, totalElapsedTime;
extern CP_Vector Up, Left, Down, Right;
int chSize = 10;

extern float deltaTime;

void shawn_Level_Init()
{
	Up = CP_Vector_Set(0, -1);
	Down = CP_Vector_Set(0, 1);
	Right = CP_Vector_Set(1, 0);
	Left = CP_Vector_Set(-1, 0);


	player.playerPos = CP_Vector_Set(1920/2, 1080/2);
	player.speed = 500;
	player.alive = 1;
	player.GPA = 5.00f;
	player.damage = 1;
	player.timer = 0;
	player.weaponPos = CP_Vector_Set(player.playerPos.x, player.playerPos.y);
	player.weapon = 0;

	for (int i = 0; i < 10; i++)
	{
		playerBullets[i].active = 0;
		playerBullets[i].ready = 1;
	}

	quiz1.EnemyPos = CP_Vector_Set(300, 300);
	quiz1.speed = 400;
	quiz1.alive = 1;
	quiz1.HP = 3;
	quiz1.damage = 0.05f;
	circleSize = 50.0f;

	// Setting the window width and height
	windowWidth = 1920;
	windowHeight = 1080;

	// Set the colour for gray
	gray = CP_Color_Create(120, 120, 120, 255);
	blue = CP_Color_Create(50, 50, 255, 255);
	green = CP_Color_Create(0,255,0,255);
	red = CP_Color_Create(255, 0, 0, 255);

	fps = 120.0f;
	// Set fps to 120fps
	CP_System_SetFrameRate(fps);

	// Set the window when executed to the size of the splashscreen image
	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void shawn_Level_Update()
{
	// PLAYER CROSSHAIR
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 0));
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), chSize);


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
					for (int i = 0; i < 10; i++)
					{
						if (playerBullets[i].ready == 1)
						{
							playerBullets[i].active = 1;
							playerBullets[i].velocity = 10;
							playerBullets[i].Pos = player.playerPos;
						}
						continue;
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

		//BULLET SIMULATION
		for (int i = 0; i < 10; i++)
		{
			if (playerBullets[i].active == 1)
			{
				if (playerBullets[i].Pos.x <= 0 || playerBullets[i].Pos.x >= CP_System_GetWindowWidth() || playerBullets[i].Pos.y <= 0 || playerBullets[i].Pos.y >= CP_System_GetWindowHeight())
				{
					playerBullets[i].active = 0;
				}
				playerBullets[i].Vector = CP_Vector_Normalize(player.direction);
				playerBullets[i].Vector = CP_Vector_Scale(playerBullets[i].Vector, playerBullets[i].velocity * deltaTime);
				playerBullets[i].Pos = CP_Vector_Add(playerBullets[i].Pos, playerBullets[i].Vector);
				CP_Settings_Fill(red);
				CP_Graphics_DrawCircle(playerBullets[i].Pos.x, playerBullets[i].Pos.y, 20);
			}
		}

		// UI AND HUD
		//CP_Graphics_DrawRect(player.weaponPos.x, player.weaponPos.y, 10, 10);
		CP_Settings_RectMode(CP_POSITION_CORNER);
		// RENDER HEALTHBAR
		CP_Settings_Fill(green);
		CP_Graphics_DrawRect(windowWidth/10, windowHeight/54, player.GPA * 100, 30);
	}

	// GAME OVER SCREEN + RESET BUTTON
	else
	{
		CP_Settings_Fill(red);
		CP_Font_DrawText("GAME OVER", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2);
		CP_Font_DrawText("Press Esc to retry", (CP_System_GetWindowWidth() / 2), CP_System_GetWindowHeight() / 2 + 30);
		if (CP_Input_KeyReleased(KEY_ESCAPE))
		{
			CP_Engine_SetNextGameStateForced(shawn_Level_Init, shawn_Level_Update, NULL);
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

	if (isCircleEntered(quiz1.EnemyPos.x, quiz1.EnemyPos.y, circleSize, player.playerPos.x, player.playerPos.y) && player.alive) {
		player.GPA -= quiz1.damage;
	}

	//DEBUG USE: SHOW CURRENT WEAPON
	CP_Settings_Fill(blue);
	if (player.weapon == 1)
	{
		CP_Font_DrawText("Current weapon: Ranged", windowWidth / 6, 90);
	}
	else CP_Font_DrawText("Current weapon: Melee", windowWidth / 6, 90);



	//SPAWNS
	player.alive = player.GPA <= 0 ? 0 : 1;
	quiz1.alive = 0;
	//quiz1.alive = quiz1.HP <= 0 ? 0 : 1;

	deltaTime = CP_System_GetDt();
	totalElapsedTime += deltaTime;

	//if (player.GPA >0) {
	//	player.GPA -= deltaTime;
	//}
	//else {
	//	player.GPA = 5.00f;
	//}

	CP_Graphics_ClearBackground(gray);

	if (quiz1.alive) {
		enemyChase(&quiz1, &player);
		if (quiz1.HP == 1) {
			CP_Settings_Fill(CP_Color_Create(200, 0, 0, 255));
		}
		else
		{
			CP_Settings_Fill(red);
		}
		//CP_Settings_Fill(red);
		CP_Graphics_DrawCircle(quiz1.EnemyPos.x, quiz1.EnemyPos.y, circleSize+20.0f);

		CP_Settings_TextSize(windowWidth / 60);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("quiz", quiz1.EnemyPos.x, quiz1.EnemyPos.y);
	}
	else {
		quiz1.EnemyPos.x = -100;
		quiz1.EnemyPos.y = -100;
	}

	if (!quiz1.alive) {
		quiz1.HP = 2;
		quiz1.EnemyPos.x = 10;
		quiz1.EnemyPos.y = 10;
		quiz1.alive = 1;
	}

	if (player.alive) {
		CP_Settings_Fill(blue);
		CP_Graphics_DrawCircle(player.playerPos.x, player.playerPos.y, circleSize);
	}

	//if (totalElapsedTime >= 20) {
	//	CP_Engine_Terminate();
	//}
}

void shawn_Level_Exit()
{

}
