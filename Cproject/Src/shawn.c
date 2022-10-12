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
	CP_Vector weaponPos;
	int speed, alive, damage, weapon, attacking;
	float GPA, timer;
};

extern struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	int speed, alive;
	float HP, weapon;
};
extern struct Player player;
extern struct Enemy quiz1, lab1, assignment1;
extern CP_Color gray,blue,green,red;
extern int windowWidth, windowHeight;
extern float fps;
extern float circleSize, totalElapsedTime;
extern CP_Vector Up, Left, Down, Right;

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


	quiz1.EnemyPos = CP_Vector_Set(300, 300);
	quiz1.speed = 300;
	quiz1.alive = 1;
	quiz1.HP = 2;
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
	// BOUNDARIES
	if (player.alive) {
		if (CP_Input_KeyDown(KEY_W) && player.playerPos.y > 1)
		{
			moveForward(&player, Up);
		}
		if (CP_Input_KeyDown(KEY_A) && player.playerPos.x > 1)
		{
			moveForward(&player, Left);
		}
		if (CP_Input_KeyDown(KEY_S) && player.playerPos.y < 1080)
		{
			moveForward(&player, Down);
		}
		if (CP_Input_KeyDown(KEY_D) && player.playerPos.x < 1920)
		{
			moveForward(&player, Right);
		}

		//if (CP_Input_MouseClicked() && player.timer <= 0) {
		//	// get vector and spawn hit point
		//	// set timer
		//	// render hit point
		//	// timer--

		//}


		CP_Settings_Fill(green);
		CP_Graphics_DrawRect(20, 20, player.GPA * 100, 30);
	}
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
	CP_Graphics_DrawRect(20, 20, 500, 30);

	if (isCircleEntered(quiz1.EnemyPos.x, quiz1.EnemyPos.y, circleSize, player.playerPos.x, player.playerPos.y) && player.alive) {
		player.GPA -= 0.01;
	}

	if (player.GPA <= 0) {
		player.alive = 0;
	}

	deltaTime = CP_System_GetDt();
	totalElapsedTime += deltaTime;

	//if (player.GPA >0) {
	//	player.GPA -= deltaTime;
	//}
	//else {
	//	player.GPA = 5.00f;
	//}

	CP_Graphics_ClearBackground(gray);
	enemyChase(&quiz1, &player);
	CP_Settings_Fill(red);
	CP_Graphics_DrawCircle(quiz1.EnemyPos.x, quiz1.EnemyPos.y, circleSize);

	if (player.alive) {
		CP_Settings_Fill(blue);
		CP_Graphics_DrawCircle(player.playerPos.x, player.playerPos.y, circleSize);
	}
}

void shawn_Level_Exit()
{

}