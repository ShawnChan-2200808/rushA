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
void weihao_Init()
{
    int speed = 50;
    red = CP_Color_Create(255, 0, 0, 255);
    player1.color = red;
    player1.pointx = windowWidth / 2;
    player1.pointy = windowHeight / 2;
    speed = 150;
    player1.diameter = 60;
}
void weihao_Update()
{
    CP_Graphics_ClearBackground(gray);
    CP_Settings_Fill(red);
    CP_Graphics_DrawCircle(player1.pointx, player1.pointy, player1.diameter);


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
void weihao_Exit()
{

}
