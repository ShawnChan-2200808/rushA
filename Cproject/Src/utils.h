/*!
@file       utils.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       27/11/2022 (last updated)
@brief      contains assets and variables that we are reusing and  also
			declarations of utilites shared functions
*//*_________________________________________________________________________________*/
#pragma once
CP_Color black, white, gray, blue, green, red;
float windowWidth, windowHeight;
float fps;
int randomX, randomY, randomiser;

// References to Image
CP_Image playerSS;
CP_Image QuizSS;
CP_Image AssSS;
CP_Image LabSS;
CP_Image Floor;
CP_Image bbtSS;
CP_Image BossSS;
CP_Image hitBox;
CP_Image Chair;
CP_Image Table;

// Reference to Sound
CP_Sound mainMenuOST;
CP_Sound levelOST;
CP_Sound gameOverOST;
CP_Sound winOST;
CP_Sound bossOST;
CP_Sound schoolBellSFX;
CP_Sound playerMeleeSFX;
CP_Sound playerSwapRangeSFX;
CP_Sound playerSwapMeleeSFX;
CP_Sound playerRangedSFX;
CP_Sound bossSFX;

// Spawning of  - Shawn, WeiHao
void initGame();
void initAssets();
void freeAssets();
void Draw_Button(char* pre_fixtext, float x, float y);
void Toggle_Button(char* pre_fixtext, float x, float y);

// Drawing of Background - Shawn
void SpawnBG(CP_Image BG, int numberRow, int numberCol);

// Checking for if collided - Shawn, Eeloong, Weihao
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int isCircleEntered(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int IsRectEntered(float area_corner_x, float area_corner_y, float area_width, float area_height, float object_x, float object_y);
void IfMouseover(float area_center_x, float area_center_y, float area_width, float area_height, char* pre_fixtext);

// Finds the angle from enemy to player - Eeloong
float enemyPlayerAngle(struct Enemy* enemy, struct Player* player);

// collision for the laser rectangle - Eeloong
int isRectEnteredadvanced(float	laserX, float laserY, float laserW, float laserH, int rotation, struct Player* player);


