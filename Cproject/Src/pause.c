/*!
@file       pause.c
@course     csd1401 Software Engineering Project
@author		Justin Yeo
@section    A
@team		RushA
@date       14/11/2022 (last updated)
@brief      This file contains the implementation of the pause function
*//*_________________________________________________________________________*/

#include "cprocessing.h"

void pauseScreen(void)
{
	CP_Color black, red, blue;
	black = CP_Color_Create(0, 0, 0, 255);
	red = CP_Color_Create(255, 0, 0, 255);
	blue = CP_Color_Create(0, 0, 255, 255);


	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect((float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) - 110), 400, 90);
	CP_Graphics_DrawRect((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2), 400, 90);
	CP_Graphics_DrawRect((float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) + 110), 400, 90);
	CP_Graphics_DrawRect((float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) + 220), 400, 90);
	//	CP_Settings_TextSize(150.0f);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("GAME PAUSED", (float)(CP_System_GetWindowWidth() / 2), (float)(150));
	//	CP_Settings_TextSize(150.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Resume", (float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) - 110));
	CP_Font_DrawText("Retry", (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 2));
	CP_Font_DrawText("Return to Menu", (float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) + 110));
	CP_Font_DrawText("Quit Game", (float)(CP_System_GetWindowWidth() / 2), (float)((CP_System_GetWindowHeight() / 2) + 220));
	//	CP_Font_DrawText("Press Esc to resume studying SPACE to Drop Out", (float)(CP_System_GetWindowWidth() / 3), (float)(CP_System_GetWindowHeight() / 3));
}
