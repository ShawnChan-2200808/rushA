/*!
@file       credits.c
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
	CP_Graphics_DrawRect((float)(windowWidth/2), (float)(windowHeight/2), 1900.f, 800.f);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Development Team - RushA", (float)(windowWidth / 4), (float)((windowHeight / 9) + 200));
	CP_Font_DrawText("Shawn Chan", (float)(windowWidth / 4), (float)((windowHeight / 6) + 50 +200));
	CP_Font_DrawText("Sun Wei Hao", (float)(windowWidth / 4), (float)((windowHeight / 6) + 100 + 200));
	CP_Font_DrawText("Low Ee Loong", (float)(windowWidth / 4), (float)((windowHeight / 6) + 150 + 200));
	CP_Font_DrawText("Justin Yeo", (float)(windowWidth / 4), (float)((windowHeight / 6) + 200 + 200));
	CP_Font_DrawText("Special Thanks", (float)(windowWidth / 4), (float)((windowHeight / 6) + 350 + 200));
	CP_Font_DrawText("Bryan Lee", (float)(windowWidth / 4), (float)((windowHeight / 6) + 400 + 200));
	CP_Font_DrawText("DigiPen Institute of Technology", ((float)(windowWidth / 4) * 3),(float)((windowHeight / 6) + 300 + 200));
	CP_Font_DrawText("Claude Comair - President", ((float)(windowWidth / 4) * 3), (float)((windowHeight / 6) + 350 + 200));
	CP_Font_DrawText("Instructors", (float)((windowWidth / 4) * 3), (float)((windowHeight / 9) + 200));
	CP_Font_DrawText("Cheng Ding Xiang", (float)((windowWidth / 4) * 3), (float)((windowHeight / 6) + 50 + 200));
	CP_Font_DrawText("Gerald Wong", (float)((windowWidth / 4) * 3), (float)((windowHeight / 6) + 100 + 200));
	CP_Font_DrawText("DigiPen Institute of Technology", (float)((windowWidth / 4) * 3), (float)((windowHeight / 6) + 300 + 200));
	CP_Font_DrawText("Claude Comair - President", (float)((windowWidth / 4) * 3), (float)((windowHeight / 6) + 350 + 200));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("All content 2022 DigiPen Institute of Technology Singapore, all rights reserved", (float)(windowWidth / 2), (float)((windowHeight / 20)+150)); //©  <- FOR JUSTIN
	CP_Settings_Fill(red);
}