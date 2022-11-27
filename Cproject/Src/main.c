/*!
@file       main.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA 
@date       27/11/2022 (last updated)
@brief      This is the main file to run the game
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "splashscreen.h"

int main(void)
{
	//CP_Engine_SetNextGameState(Level_Init, Level_Update, Level_Exit); // for testing
	CP_Engine_SetNextGameState(Splash_Screen_Init, Splash_Screen_Update, Splash_Screen_Exit);
	CP_Engine_Run();
	//return 0;
}