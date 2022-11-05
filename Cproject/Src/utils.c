/*!
@file       utils.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      This file contains all the shared utilities that is global throughout
*//*_________________________________________________________________________*/

#include "cprocessing.h"

extern struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	CP_Color lasercolour;
	int speed, alive;
	float HP, damage;
	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; struct Enemy;

extern struct Player {
	CP_Vector playerPos, tempPos, direction;
	CP_Vector weaponPos, bulletPos;
	int speed, alive, damage, weapon, attacking, ammo;
	float GPA, timer, projVelocity;

	//collision
	CP_Vector playermin, playermax;
	float hitboxX, hitboxY;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; struct Player;

CP_Color black, white, gray, blue, green, red;
int windowWidth, windowHeight;
float fps;

// Get angle from enemy to player
float enemyPlayerAngle(struct Enemy* enemy, struct Player* player) {
	CP_Vector update = CP_Vector_Set((*player).playerPos.x - (*enemy).EnemyPos.x, (*player).playerPos.y - (*enemy).EnemyPos.y);
	CP_Vector normalised = CP_Vector_Normalize(update);
	printf("X vector %f, Y Vector %f \n", normalised.x, normalised.y);
	CP_Vector unitVector = CP_Vector_Set(0.0f, 1.0f);
	if (normalised.x > 0) {
		normalised.y = -normalised.y;
	}
	float angle = CP_Vector_Angle(normalised, unitVector);
	//printf("angle utils %f \n", angle);
	return normalised.x > 0 ? angle : angle + 180;
}

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

void SpawnBG(CP_Image BG, int numberRow, int numberCol) {
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

int IsRectEntered(float area_corner_x, float area_corner_y, float area_width, float area_height, float object_x, float object_y)
{
	// check if the x and y pos of the is within the width and height
	//left
	if (area_width < 0 && object_x >= area_corner_x + area_width && object_x <= area_corner_x &&
		object_y <= area_corner_y + area_height && object_y >= area_corner_y)
	{
		/*&&  &&&&
		Returns 1 if the point given by object_xand object_y is within the rectangle given by
		area_corner_x, area_corner_y, area_width and area_height. Otherwise it will return 0.
		*/
		return 1;
	}
	//up 
	else if (area_height < 0 && object_x >= area_corner_x && object_x <= area_corner_x + area_width &&
		object_y >= area_corner_y + area_height  && object_y <= area_corner_y)
	{
		/*&&  &&&&
		Returns 1 if the point given by object_xand object_y is within the rectangle given by
		area_corner_x, area_corner_y, area_width and area_height. Otherwise it will return 0.
		*/
		return 1;
	}

	//right && down
	else if (object_x <= area_corner_x + area_width && object_x >= area_corner_x &&
		object_y <= area_corner_y + area_height && object_y >= area_corner_y)
	{
		/*&&  &&&&
		Returns 1 if the point given by object_xand object_y is within the rectangle given by
		area_corner_x, area_corner_y, area_width and area_height. Otherwise it will return 0.
		*/
		return 1;
	}
	return 0;
}

int isRectEnteredadvanced(float rectX, float rectY, float rectwidth, float rectheight, float vectorX, float vectorY, struct Player* player)
{
	CP_Vector length = CP_Vector_Set(vectorX, vectorY);
	length = CP_Vector_Normalize(length);
	length = CP_Vector_Scale(length, rectheight);
	CP_Vector orthogonal = CP_Vector_Set(-(vectorX), vectorY);
	orthogonal = CP_Vector_Normalize(orthogonal);
	orthogonal = CP_Vector_Scale(orthogonal, rectwidth);

	// find Bottom left, Bottom Right, Upper right corners of rect;
	//float BLcornerX = rectX + orthogonal.x;
	//float BLcornerY = rectY + orthogonal.y;

	//float BRcornerX = BLcornerX + length.x;
	//float BRcornerY = BRcornerY + length.y;

	//float URcornerX = rectX + length.x;	
	//float URcornerY = rectY + length.y;

	//printf("length vector %f , %f \n orthogonal vector %f, %f \n", length.x, length.y, orthogonal.x, orthogonal.y);

	CP_Vector playerUL = CP_Vector_Set((*player).playerPos.x - rectX, (*player).playerPos.y - rectY);

	if (0 < CP_Vector_DotProduct(playerUL, length) && CP_Vector_DotProduct(playerUL, length) < CP_Vector_DotProduct(length, length) && 0 < CP_Vector_DotProduct(playerUL, orthogonal) && CP_Vector_DotProduct(playerUL, orthogonal) < CP_Vector_DotProduct(orthogonal, orthogonal))
	{
		return 1;
	}
	else {
		return 0;
	}
}