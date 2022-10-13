/*!
@file       level.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date        / /2022 (last updated)
@brief      This file contains the main level that we integrate 
		*** ONLY UPDATE THIS AFTER APPROVAL OF TEAM ***
*//*_________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
//#include "level.h"
//#include "stdio.h" 
//#include "stdlib.h"

extern CP_Color gray;
extern CP_Color red;
extern int windowWidth, windowHeight;
int diameter = 60;
float pointx = 0;
float pointy = 0;
int speed;


	struct player
	{
		CP_Color color;
		float pointx;
		float pointy;
		float diameter;
		//float hp;
	};
	struct player player1;

void Level_Init()
{
	int speed = 50;
	red = CP_Color_Create(255, 0, 0, 255);
	player1.color = red;
	pointx = windowWidth/2;
	pointy = windowHeight/2;
	speed = 150;


}

void Level_Update()
{
	CP_Graphics_ClearBackground(gray);
	CP_Settings_Fill(player1.color);
	CP_Graphics_DrawCircle(player1.pointx,player1.pointy,player1.diameter);


		if (CP_Input_KeyDown(KEY_W))
		{
			player1.pointy -= speed * CP_System_GetDt();
		}

		if (CP_Input_KeyDown(KEY_S))
		{
			player1.pointy += speed * CP_System_GetDt();
		}
		if (CP_Input_KeyDown(KEY_A))
		{
			player1.pointx -= speed * CP_System_GetDt();
		}

		if (CP_Input_KeyDown(KEY_D))
		{
			player1.pointx += speed * CP_System_GetDt();
		}

}

void Level_Exit()
{

}