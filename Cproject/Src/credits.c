/*!
@file       mainmenu.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains defininition of credits functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include "player.h"

void showCredits(void)
{

	CP_Graphics_ClearBackground(black);
	CP_Settings_Fill(gray);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	//draw the draw rect in the middle of the anchor point //draw play button
	CP_Graphics_DrawRect(windowWidth / 2, (windowHeight / 3) + 30, 1900, 750);
	CP_Settings_Fill(red);
	CP_Font_DrawText("Development Team - RushA", (windowWidth / 4), (windowHeight / 9));
	CP_Font_DrawText("Shawn Chan", (windowWidth / 4), (windowHeight / 6) + 50);
	CP_Font_DrawText("Sun Wei Hao", (windowWidth / 4), (windowHeight / 6) + 100);
	CP_Font_DrawText("Low Ee Loong", (windowWidth / 4), (windowHeight / 6) + 150);
	CP_Font_DrawText("Justin Yeo", (windowWidth / 4), (windowHeight / 6) + 200);
	CP_Font_DrawText("Special Thanks", (windowWidth / 4), (windowHeight / 6) + 350);
	CP_Font_DrawText("Bryan Lee", (windowWidth / 4), (windowHeight / 6) + 400);
	CP_Font_DrawText("DigiPen Institute of Technology", ((windowWidth / 4) * 3), ((windowHeight / 6) + 300));
	CP_Font_DrawText("Claude Comair - President", ((windowWidth / 4) * 3), (windowHeight / 6) + 350);
	CP_Font_DrawText("Instructors", ((windowWidth / 4) * 3), (windowHeight / 9));
	CP_Font_DrawText("Chen Ding Xiang", ((windowWidth / 4) * 3), (windowHeight / 6) + 50);
	CP_Font_DrawText("Gerald Wong", ((windowWidth / 4) * 3), (windowHeight / 6) + 100);
	CP_Font_DrawText("DigiPen Institute of Technology", ((windowWidth / 4) * 3), ((windowHeight / 6) + 300));
	CP_Font_DrawText("Claude Comair - President", ((windowWidth / 4) * 3), (windowHeight / 6) + 350);
	CP_Settings_Fill(red);
	//draw the draw 4th rect in the middle of the anchor point //draw exit button
	CP_Graphics_DrawRect(windowWidth / 2, (windowHeight / 2) + 350, 600, 100);
	CP_Settings_Fill(black);
	CP_Font_DrawText("Return to Main Menu", windowWidth / 2, (windowHeight / 2) + 350);

		//exit button light up
	if (IsAreaClicked((windowWidth / 2), (windowHeight / 2) + 350, 600, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		CP_Settings_Fill(blue);
		CP_Settings_RectMode(CP_POSITION_CENTER);
		//draw the draw rect in the middle of the anchor point
		CP_Graphics_DrawRect(windowWidth / 2, (windowHeight / 2) + 350, 600, 100);
		CP_Settings_Fill(black);
		//s_Font_DrawText("Return to Main Menu", windowWidth / 2, (windowHeight / 2) + 350);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	}

}
