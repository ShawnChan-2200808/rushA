/*!
@file       splashscreen.c
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       11/10/2022 (last updated)
@brief      This file contains the splashscreen execution.
*//*_________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "level.h"
#include "mainmenu.h"
	
CP_Image splashscreenDP;
CP_Image TeamLogo;

float totalElapsedTime, alphaIncrease;
static float deltaTime;
int alpha, finalAlpha, rate, time, alphaMax;

void Splash_Screen_Init(void)
{

	CP_System_SetWindowTitle("The Deliverables");
	//initialise all assets
	initAssets();

	// Load splash screen png from assets folder
	splashscreenDP = CP_Image_Load("./Assets/SPLASHSCREEN/DigiPen_Singapore_WEB_WHITE.png");
	TeamLogo = CP_Image_Load("./Assets/SPLASHSCREEN/RushA.png");
	
	// Setting the window width and height
	windowWidth = 1920;
	windowHeight = 1080;
	//CP_System_Fullscreen();
	//CP_System_FullscreenAdvanced(1920, 1080);
	//windowWidth = CP_System_GetDisplayWidth();
	//windowHeight = CP_System_GetDisplayHeight();

	// Set the colour
	black = CP_Color_Create(0, 0, 0, 255);

	// Initialize variables
	deltaTime = 0.0f;
	alphaIncrease = 0.0f;
	time = 2; 
	finalAlpha = 255;
	alphaMax = 256;
	fps = 120.0f;
	 
	// Getting the rate we need to get to the value of 255 in 2 seconds
	rate = finalAlpha / time;

	// Set fps to 120fps
	CP_System_SetFrameRate(fps);

	// Set the window when executed to the size of the splashscreen image
	CP_System_SetWindowSize(windowWidth, windowHeight);
	
}

void Splash_Screen_Update(void)
{
	// Create background that is gray in colour
	CP_Graphics_ClearBackground(black);

	// Start time counter
	deltaTime = CP_System_GetDt();
	totalElapsedTime += deltaTime;

	if (CP_Input_KeyReleased(KEY_ENTER))
	{
		totalElapsedTime = 4;
	}

	// Rendering Digipen Splashscreen 
	if (totalElapsedTime < 2) {
		// Clamp the image to the Center 
		CP_Settings_ImageMode(CP_POSITION_CENTER);
		CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
		CP_Image_Draw(splashscreenDP, (float)(windowWidth / 2), (float)(windowHeight / 2), (float)CP_Image_GetWidth(splashscreenDP), (float)CP_Image_GetHeight(splashscreenDP), alpha);
		CP_Settings_Fill(white);
		CP_Font_DrawText("All content © 2022 DigiPen Institute of Technology Singapore. All Rights Reserved", CP_System_GetWindowWidth() / 2, 1060);
		alphaIncrease = totalElapsedTime * rate;
		alpha = (int)alphaIncrease % alphaMax;
	}

	// Rendering RUSHA Splashscreen
	
	else{
		CP_Image_Draw(TeamLogo, windowWidth / 2, windowHeight / 2, (float)CP_Image_GetWidth(TeamLogo), (float)CP_Image_GetHeight(TeamLogo), alpha);
		alphaIncrease = totalElapsedTime * rate;
		alpha = (int)alphaIncrease % 256;
	}
	

	// Change scene upon splashscreen end
	if (totalElapsedTime > 4)
	{
		// Change to state
		CP_Engine_SetNextGameState(Mainmenu_Init, Mainmenu_Update, Mainmenu_Exit);
	}
}

void Splash_Screen_Exit(void)
{
	// Clear the Splashscreen image upon exiting this state
	//
	CP_Image_Free(&splashscreenDP);
}

