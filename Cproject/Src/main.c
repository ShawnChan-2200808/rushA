/*!
@file       main.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA 
@date        / /2022 (last updated)
@brief      This is the main file to run the game
		*** REVERT BACK AFTER TESTING ***
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "shawn.h"
#include "splashscreen.h"

int main(void)
{
	CP_Engine_SetNextGameState(shawn_Level_Init, shawn_Level_Update, shawn_Level_Exit);
	//CP_Engine_SetNextGameState(Level_Init, Level_Update, Level_Exit);
	//CP_Engine_SetNextGameState(Splash_Screen_Init, Splash_Screen_Update, Splash_Screen_Exit);
	CP_Engine_Run();
	return 0;
}