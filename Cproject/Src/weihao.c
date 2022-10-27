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

extern CP_Color gray,blue,green,red;
extern int windowWidth, windowHeight;
extern float fps, deltaTime;

extern struct player
{
    CP_Color color;
    float pointx;
    float pointy;
    float diameter;
    CP_Vector direction, temppos, playerpos;
    int speed;
    float GPA;
};
extern struct player player1;

extern CP_Vector Up, Down, Left, Right; 

void weihao_Init()
{
    red = CP_Color_Create(255, 0, 0, 255);
    blue = CP_Color_Create(50, 50, 255, 255);
    green = CP_Color_Create(0, 255, 0, 255);
    player1.color = red;
    player1.GPA = 5.0f;
    player1.pointx = windowWidth / 2;
    player1.pointy = windowHeight / 2;
    player1.playerpos = CP_Vector_Set(player1.pointx, player1.pointy);
    player1.speed = 50;
    player1.diameter = 60.0;

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
    deltaTime = CP_System_GetDt();
    CP_Graphics_ClearBackground(gray);
    CP_Settings_Fill(red);
    CP_Graphics_DrawCircle(player1.pointx, player1.pointy, player1.diameter);


    if (CP_Input_KeyDown(KEY_W) && player1.playerpos.y > 1)
    {
        moveForward(&player1,Up);
    }
    if (CP_Input_KeyDown(KEY_A) && player1.playerpos.x > 1)
    {
        moveForward(&player1,Left);
    }
    if (CP_Input_KeyDown(KEY_S) && player1.playerpos.y < windowHeight)
    {
        moveForward(&player1,Down);
    }
    if (CP_Input_KeyDown(KEY_D) && player1.playerpos.x < windowWidth)
    {
        moveForward(&player1,Right);
    }

    CP_Settings_RectMode(CP_POSITION_CORNER);
    // RENDER HEALTHBAR
    CP_Settings_Fill(green);
    CP_Graphics_DrawRect(windowWidth / 10, windowHeight / 54, player1.GPA * 100, 30);

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


}
void weihao_Exit()
{

}
