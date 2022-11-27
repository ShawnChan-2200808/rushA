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
#include "splashscreen.h"

void RollCredits(void) {
	CP_Settings_Fill(gray);
	//draw the draw rect in the middle of the anchor point
	CP_Graphics_DrawRect((float)(windowWidth/2), (float)(windowHeight/2), 1900.f, 800.f);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Credits", (windowWidth / 2), (windowHeight / 20) + 150); //�  <- FOR JUSTIN
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(TeamLogo, (windowWidth / 4), (windowHeight / 2), 960, 540, 255);
	// Development Team - Right Side
	CP_Font_DrawText("Development Team - RushA", ((windowWidth / 4) * 3), (windowHeight / 9) + 200);
	CP_Font_DrawText("Shawn Chan", ((windowWidth / 4) * 3), (windowHeight / 6) + 50 + 200);
	CP_Font_DrawText("Sun Wei Hao", ((windowWidth / 4) * 3), (windowHeight / 6) + 100 + 200);
	CP_Font_DrawText("Low Ee Loong", ((windowWidth / 4) * 3), (windowHeight / 6) + 150 + 200);
	CP_Font_DrawText("Justin Yeo", ((windowWidth / 4) * 3), (windowHeight / 6) + 200 + 200);
	CP_Font_DrawText("Special Thanks", ((windowWidth / 4) * 3), (windowHeight / 6) + 350 + 200);
	CP_Font_DrawText("Bryan Lee", ((windowWidth / 4) * 3), (windowHeight / 6) + 400 + 200);
	CP_Settings_Fill(red);
	CP_Graphics_DrawTriangle((windowWidth * 0.92), (windowHeight / 2) - 100, (windowWidth * 0.95), (windowHeight / 2), (windowWidth * 0.92), ((windowHeight / 2) + 100));
}

void CreditsDigipen(void) {
	CP_Settings_Fill(gray);
	//draw the draw rect in the middle of the anchor point
	CP_Graphics_DrawRect(windowWidth / 2, windowHeight / 2, 1900, 800);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Credits", (windowWidth / 2), (windowHeight / 20) + 150); //�  <- FOR JUSTIN

	// DigiPen President
	CP_Font_DrawText("DigiPen Institute of Technology", (windowWidth / 2), (windowHeight / 9) + 200);
	CP_Font_DrawText("President", (windowWidth / 2), (windowHeight / 6) + 350 + 200);
	CP_Font_DrawText("Claude Comair", (windowWidth / 2), (windowHeight / 6) + 400 + 200);

	// Instructors
	CP_Font_DrawText("Instructors", (windowWidth / 2), (windowHeight / 6) + 200);
	CP_Font_DrawText("Cheng Ding Xiang", (windowWidth / 2), (windowHeight / 6) + 50 + 200);
	CP_Font_DrawText("Gerald Wong", (windowWidth / 2), (windowHeight / 6) + 100 + 200);

	//Executives
	CP_Font_DrawText("Executives", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 330 + 200);
	CP_Font_DrawText("Jason Chu", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Christopher Comair", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Michael Gats", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Michele Comair", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Raymond Yan", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Samir Abou Samra", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Prasanna Ghali", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("John Bauer", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Dr. Erik Mohrmann", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Melvin Gonsalvez", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Angela Kugler", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Dr. Charles Duba", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Ben Ellinger", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Font_DrawText("Johnny Deek", ((windowWidth / 5) * 4.5), (windowHeight / 6) + 360 + 200);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Fill(red);
	CP_Graphics_DrawTriangle((windowWidth * 0.08), (windowHeight / 2) - 100, (windowWidth * 0.11), (windowHeight / 2), (windowWidth * 0.08), ((windowHeight / 2) + 100));
}
