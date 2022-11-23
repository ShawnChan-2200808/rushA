/*!
@file       mainmenu.c
@course     csd1401 Software Engineering Project
@author		Justin Yeo
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains defininition of credits functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"

void CreditsWords(void) {
	CP_Settings_Fill(gray);
	//draw the draw rect in the middle of the anchor point
	CP_Graphics_DrawRect(windowWidth/2, windowHeight/2, 1900, 800);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Development Team - RushA", (windowWidth / 4), (windowHeight / 9) + 200);
	CP_Font_DrawText("Shawn Chan", (windowWidth / 4), (windowHeight / 6) + 50 +200);
	CP_Font_DrawText("Sun Wei Hao", (windowWidth / 4), (windowHeight / 6) + 100 + 200);
	CP_Font_DrawText("Low Ee Loong", (windowWidth / 4), (windowHeight / 6) + 150 + 200);
	CP_Font_DrawText("Justin Yeo", (windowWidth / 4), (windowHeight / 6) + 200 + 200);
	CP_Font_DrawText("Special Thanks", (windowWidth / 4), (windowHeight / 6) + 350 + 200);
	CP_Font_DrawText("Bryan Lee", (windowWidth / 4), (windowHeight / 6) + 400 + 200);
	CP_Font_DrawText("DigiPen Institute of Technology", ((windowWidth / 4) * 3), ((windowHeight / 6) + 300 + 200));
	CP_Font_DrawText("Claude Comair - President", ((windowWidth / 4) * 3), (windowHeight / 6) + 350 + 200);
	CP_Font_DrawText("Instructors", ((windowWidth / 4) * 3), (windowHeight / 9) + 200);
	CP_Font_DrawText("Cheng Ding Xiang", ((windowWidth / 4) * 3), (windowHeight / 6) + 50 + 200);
	CP_Font_DrawText("Gerald Wong", ((windowWidth / 4) * 3), (windowHeight / 6) + 100 + 200);
	CP_Font_DrawText("DigiPen Institute of Technology", ((windowWidth / 4) * 3), ((windowHeight / 6) + 300 + 200));
	CP_Font_DrawText("Claude Comair - President", ((windowWidth / 4) * 3), (windowHeight / 6) + 350 + 200);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("All content 2022 DigiPen Institute of Technology Singapore, all rights reserved", (windowWidth / 2), (windowHeight / 20)+150); //©  <- FOR JUSTIN
	CP_Settings_Fill(red);
}