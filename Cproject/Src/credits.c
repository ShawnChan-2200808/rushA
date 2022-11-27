/*!
@file       credits.c
@course     csd1401 Software Engineering Project
@author		Justin Yeo (justin.yeo@digipen.edu)
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains defininition of credits functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include "splashscreen.h"

void RollCredits(void) {
	CP_Settings_Fill(gray);
	//draw the draw rect in the middle of the anchor point
	CP_Graphics_DrawRect((float)(windowWidth/2), (float)(windowHeight/2), 1900.f, 800.f);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(80.0f);
	CP_Font_DrawText("Credits", (float)(windowWidth / 2), (float)(windowHeight / 20) + 150); //�  <- COPYRIGHT SYMBOL??
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(TeamLogo, (float)(windowWidth / 4), (float)(windowHeight / 2), 960, 540, 255);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Development Team - RushA", ((float)(windowWidth / 4) * 3), (float)(windowHeight / 9) + 200);
	CP_Font_DrawText("Shawn Chan", ((float)(windowWidth / 4) * 3), (float)(windowHeight / 6) + 50 + 200);
	CP_Font_DrawText("Sun Wei Hao", ((float)(windowWidth / 4) * 3), (float)(windowHeight / 6) + 100 + 200);
	CP_Font_DrawText("Low Ee Loong", ((float)(windowWidth / 4) * 3), (float)(windowHeight / 6) + 150 + 200);
	CP_Font_DrawText("Justin Yeo", ((float)(windowWidth / 4) * 3), (float)(windowHeight / 6) + 200 + 200);
	CP_Font_DrawText("Special Thanks", ((float)(windowWidth / 4) * 3), (float)(windowHeight / 6) + 350 + 200);
	CP_Font_DrawText("Bryan Lee", ((float)(windowWidth / 4) * 3), (float)(windowHeight / 6) + 400 + 200);
	CP_Settings_Fill(red);
	CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80);
	CP_Settings_TextSize(50.0f);
	CP_Graphics_DrawRect((float)(windowWidth * 0.935), (float)(windowHeight / 2) + 350, 200, 80);
	CP_Settings_Fill(black);
	CP_Font_DrawText("Back", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
	CP_Font_DrawText("Next", (float)(windowWidth * 0.935), (float)(windowHeight / 2) + 350);

}

void CreditsDigipen(void) {
	CP_Settings_Fill(gray);
	//draw the draw rect in the middle of the anchor point
	CP_Graphics_DrawRect((float)windowWidth / 2, windowHeight / 2, 1900, 800);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(80.0f);
	CP_Font_DrawText("Credits", (windowWidth / 2), (windowHeight / 20) + 150); //�  <- COPYRIGHT SYMBOL??
	CP_Settings_TextSize(50.0f);
	// DigiPen President
	CP_Font_DrawText("DigiPen Institute of Technology", (windowWidth / 2), (windowHeight / 10) + 200);
	CP_Font_DrawText("President", (windowWidth / 3), (windowHeight / 6) + 200);
	CP_Font_DrawText("Claude Comair", (windowWidth / 3), (windowHeight / 6) + 50 + 200);

	// Instructors
 	CP_Font_DrawText("Instructors", (windowWidth / 3) * 2, (windowHeight / 6) + 200);
	CP_Font_DrawText("Cheng Ding Xiang", (windowWidth / 3) * 2, (windowHeight / 6) + 250);
	CP_Font_DrawText("Gerald Wong", (windowWidth / 3) * 2, (windowHeight / 6) + 300);

	//Executives
	CP_Font_DrawText("Executives", (windowWidth / 2), (windowHeight / 6) + 250 + 200);
	CP_Settings_TextSize(40.0f);
	CP_Font_DrawText("Jason Chu | Christopher Comair | Michael Gats | Michele Comair | Raymond Yan | Samir Abou Samra | Prasanna Ghali", (windowWidth /2), (windowHeight / 6) + 300 + 200);
	CP_Font_DrawText("John Bauer | Dr. Erik Mohrmann | Melvin Gonsalvez | Angela Kugler | Dr. Charles Duba | Ben Ellinger | Johnny Deek", (windowWidth / 2), (windowHeight / 6) + 350 + 200);
	CP_Settings_Fill(red);
	CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80);
	CP_Settings_TextSize(50.0f);
	CP_Graphics_DrawRect((float)(windowWidth * 0.065), (float)(windowHeight / 2) + 350, 200, 80);
	CP_Settings_Fill(black);
	CP_Font_DrawText("Back", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
	CP_Font_DrawText("Previous", (float)(windowWidth * 0.065), (float)(windowHeight / 2) + 350);
}
