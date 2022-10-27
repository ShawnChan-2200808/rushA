/*!
@file       utils.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date        / /2022 (last updated)
@brief      This file contains all the shared ultilities that is global throughout
*//*_________________________________________________________________________*/

#include "cprocessing.h"

CP_Color gray,blue,green,red;
int windowWidth, windowHeight;
float fps, deltaTime;
CP_Vector Up, Down, Left, Right;


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

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	if (click_x <= circle_center_x + diameter / 2 && click_x >= circle_center_x - diameter / 2 &&
		click_y <= circle_center_y + diameter / 2 && click_y >= circle_center_y - diameter / 2)
		{
			return 1;
		}
	return 0;
}

struct player
{
	CP_Color color;
	float pointx;
	float pointy;
	float diameter;
	CP_Vector direction, temppos, playerpos;
	int speed;
	float GPA;
};
struct player player1;

// Move forward
void moveForward(struct player* player1, CP_Vector direction)
{
	(*player1).temppos = CP_Vector_Normalize(direction);
	(*player1).temppos = CP_Vector_Scale((*player1).temppos, (*player1).speed * deltaTime);
	(*player1).playerpos = CP_Vector_Add((*player1).playerpos, (*player1).temppos);
}

// Move backward
void moveBackward(struct player* player1, CP_Vector direction)
{
	(*player1).temppos = CP_Vector_Normalize(direction);
	(*player1).temppos = CP_Vector_Scale((*player1).temppos, (*player1).speed * deltaTime);
	(*player1).playerpos = CP_Vector_Subtract((*player1).playerpos, (*player1).temppos);
}




/*
CP_Vector AngleToVector(float radian_angle)
{
    // TODO 
    CP_Vector ret;
    return ret;
}
*/