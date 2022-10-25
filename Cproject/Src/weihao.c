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
CP_Color red;
extern int windowWidth, windowHeight;
extern float fps, deltaTime;
int speed;

struct player
{
    CP_Color color;
    float pointx;
    float pointy;
    float diameter;
    CP_Vector direction, temppos, playerpos;
    int speed;
    //float hp;
};
struct player player1;

extern struct player player1;
extern CP_Vector Up, Down, Left, Right; 

void weihao_Init()
{
    int speed = 50;
    deltaTime = CP_System_GetDt();
    red = CP_Color_Create(255, 0, 0, 255);
    player1.color = red;
    player1.pointx = windowWidth / 2;
    player1.pointy = windowHeight / 2;
    speed = 150;
    player1.diameter = 60;

    Up = CP_Vector_Set(0, -1);
    Down = CP_Vector_Set(0, 1);
    Right = CP_Vector_Set(1, 0);
    Left = CP_Vector_Set(-1,0);

    fps = 120.0f;
    // Set fps to 120fps
    CP_System_SetFrameRate(fps);

}
void weihao_Update()
{
    CP_Graphics_ClearBackground(gray);
    CP_Settings_Fill(red);
    CP_Graphics_DrawCircle(player1.pointx, player1.pointy, player1.diameter);


    if (CP_Input_KeyDown(KEY_W) && player1.playerpos.y > 1)
    {
        moveForward(&player1,Up);
    }
    if (CP_Input_KeyDown(KEY_A) && player1.playerpos.x > 1)
    {
        moveBackward(&player1,Left);
    }
    if (CP_Input_KeyDown(KEY_S) && player1.playerpos.y < windowHeight)
    {
        moveBackward(&player1,Down);
    }
    if (CP_Input_KeyDown(KEY_D) && player1.playerpos.x < windowWidth)
    {
        moveForward(&player1,Right);
    }

}
void weihao_Exit()
{

}
