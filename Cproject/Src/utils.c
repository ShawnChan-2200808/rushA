/*!
@file       utils.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      This file contains all the shared utilities that is global throughout
*//*_________________________________________________________________________*/

#include "cprocessing.h"

CP_Color black,white,gray ,blue, green, red;
int windowWidth, windowHeight;
float fps;
int randomX, randomY;

void initGame() {
	// Setting the window width and height
	windowWidth = 1920;
	windowHeight = 1080;

	// Set the colour for gray
	black = CP_Color_Create(0, 0, 0, 255);
	white = CP_Color_Create(255, 255, 255, 255);
	gray = CP_Color_Create(120, 120, 120, 255);
	blue = CP_Color_Create(50, 50, 255, 255);
	green = CP_Color_Create(0, 255, 0, 255);
	red = CP_Color_Create(255, 0, 0, 255);

	fps = 120.0f;
	// Set fps to 120fps
	CP_System_SetFrameRate(fps);

	// Set the window when executed to the size of the splashscreen image
	CP_System_SetWindowSize(windowWidth, windowHeight);
}

void SpawnBG(CP_Image BG,int numberRow,int numberCol) {
	for (int row = 0; row < numberRow; row++)
	{
		for (int col = 0; col < numberCol; col++)
		{
			CP_Settings_ImageMode(CP_POSITION_CORNER);
			CP_Image_Draw(BG, col * (CP_System_GetWindowWidth() / numberCol), row * (CP_System_GetWindowHeight() / numberRow), CP_Image_GetWidth(BG), CP_Image_GetHeight(BG), 255);
		}
	}
}

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	// check if the x and y pos of the is within the width and height
	if (click_x <= area_center_x + area_width / 2 && click_x >= area_center_x - area_width / 2 &&
		click_y <= area_center_y + area_height / 2 && click_y >= area_center_y - area_height / 2)
		{
			/*
			Returns 1 if the point given by click_xand click_y is within the rectangle given by
			area_center_x, area_center_y, area_width and area_height. Otherwise it will return 0.
			*/
			return 1;
		}
	return 0;
}

int isCircleEntered(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	if (click_x <= circle_center_x + diameter / 2 && click_x >= circle_center_x - diameter / 2 &&
		click_y <= circle_center_y + diameter / 2 && click_y >= circle_center_y - diameter / 2)
		{
			return 1;
		}
	return 0;
}


