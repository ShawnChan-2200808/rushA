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
	
extern CP_Color gray;
extern int windowWidth, windowHeight;
extern float fps;

CP_Image splashscreenDP;
//CP_Image splashscreenRA;

float totalElapsedTime, alphaIncrease;
static float deltaTime;
int alpha, finalAlpha, rate, time, alphaMax;

void Splash_Screen_Init(void)
{
	//initAssets();

	// Load splash screen png from assets folder
	splashscreenDP = CP_Image_Load("./Assets/SPLASHSCREEN/DigiPen_Singapore_WEB_RED.png");
	//splashscreenRA = CP_Image_Load("./Assets/DigiPen_Singapore_WEB_RED.png");
	
	// Setting the window width and height
	windowWidth = 1920;
	windowHeight = 1080;

	// Set the colour for gray
	gray = CP_Color_Create(120, 120, 120, 255);

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
	CP_Graphics_ClearBackground(gray);

	// Start time counter
	deltaTime = CP_System_GetDt();
	totalElapsedTime += deltaTime;

	if (CP_Input_KeyReleased(KEY_ESCAPE))
	{
		totalElapsedTime = 2;
	}

	// Rendering Digipen Splashscreen 
	if (totalElapsedTime < 2) {
		// Clamp the image to the Center 
		CP_Settings_ImageMode(CP_POSITION_CENTER);
		CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
		CP_Image_Draw(splashscreenDP, windowWidth/2, windowHeight/2, (float)CP_Image_GetWidth(splashscreenDP), (float)CP_Image_GetHeight(splashscreenDP), alpha);
		alphaIncrease = totalElapsedTime * rate;
		alpha = (int)alphaIncrease % alphaMax;
	}


	// Rendering RUSHA Splashscreen
	/*
	else{
		CP_Image_Draw(splashscreenRA, windowWidth / 2, windowHeight / 2, (float)CP_Image_GetWidth(splashscreenRA), (float)CP_Image_GetHeight(splashscreenRA), alpha);
		alphaIncrease = totalElapsedTime * rate;
		alpha = (int)alphaIncrease % 256;
	}
	*/

	/*
	elapsedtime is constantly increasing every second
	one cycle of "fading in" is the alpha value increasing from 0 to 255 at a constant rate
	we find the rate of increase from 0 to 255 in 2 seconds by dividing the final value by the time taken
	then we find the increase of alpha each second by multiplying the rate by the constant elapsed time
	after which we set the alpha value to the initial alpha value + the increase
	since 0 % 255 = 0, 255 % 256 = 255 and 256 % 256 = 0
	modulo will cap the alpha value and reset to 0 after it reached the amount its divided by
	*/

	// Change scene upon splashscreen end
	//if (totalElapsedTime > 4)
	if (totalElapsedTime > 2)
	{
		//CP_Engine_Terminate();

		// Change to state
		//CP_Engine_SetNextGameState(Main_Menu_init, Main_Menu_update, Main_Menu_exit);
		CP_Engine_SetNextGameState(Mainmenu_Init, Mainmenu_Update, Mainmenu_Exit);
	}
}

void Splash_Screen_Exit(void)
{
	// Clear the Splashscreen image upon exiting this state
	//
	CP_Image_Free(&splashscreenDP);
	//CP_Image_Free(&splashscreenRA);
}