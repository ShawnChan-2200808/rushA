/*!
@file       mainmenu.c
@course     csd1401 Software Engineering Project
@author		Sun Wei Hao
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains defininition of Enemy functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "level.h"
#include "player.h"
#include "credits.h"
#include "Tutorial.h"
//#include "enemy.h"
//#include "anim.c"
	
CP_Color gray, black, red,blue;
int windowWidth, windowHeight, currentFrame, spriteWidth, spriteHeight;
float fps;
CP_Image Gamename;

CP_Image Gamename, Background;

float totalElapsedTime, lerpIncrease, currentElapseTime, currentElapseTimeReturn, ElapseTimeGamename;
static float deltaTime;
int timeplayer, timegamename, lerpMax;
float rateplayer, lerpplayer, lerpplayerReturn, finalLerp, player_xpos, ass_xpos, player_return_xpos, ass_return_xpos, gamename_ypos,lerpgamename, rategamename;

int currentFrameP, currentFrameE, animTotalFramesP, animTotalFramesE, animationSpeedP, animationSpeedE;
float spriteWidth, SpriteHeight, displayTime;
static float animationElapsedTimeE, animationElapsedTimeP;
BOOL firstrun, secondrun, settings,SFX = TRUE, MUSIC = TRUE, credits;


void Mainmenu_Init(void)
{
	// Load image png from assets folder
	Gamename = CP_Image_Load("Assets/SPRITES/THE DELIVERABLES.png");
	Background = CP_Image_Load("Assets/SPRITES/School Background.png");

	//animation 
	displayTime = 2;
	currentFrameP = 0, currentFrameE = 0;
	animationSpeedP = 10, animationSpeedE = 15;
	animTotalFramesP =2, animTotalFramesE = 8;
	spriteWidth = 64.0f, SpriteHeight = 64.0f;
	animationElapsedTimeP = 0.0f, animationElapsedTimeE = 0.0f;


	// Initialize variables
	deltaTime = 0.0f;
	lerpIncrease = 0.0f;
	timeplayer = 5;
	timegamename = 2;
	finalLerp = 1;
	lerpMax = 1;

	//BOOL
	firstrun = FALSE;
	secondrun = FALSE;
	credits = FALSE;

	// Getting the rate we need to get to reach 1 lerpfector in seconds
	rateplayer = finalLerp / timeplayer;
	rategamename = finalLerp / timegamename;
	
	// Setting the window width and height
	//windowWidth = 1920;
	//windowHeight = 1080;

	// Set the colour 
	gray = CP_Color_Create(120, 120, 120, 255);
	red = CP_Color_Create(255, 0, 0, 255);
	blue = CP_Color_Create(0, 0, 255, 255);

	// Set the window when executed to the size of the splashscreen image
	CP_System_SetWindowSize(windowWidth, windowHeight);

	CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
	CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
	CP_Sound_PlayAdvanced(mainMenuOST, 0.1f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);

	settings = FALSE;
}

void Mainmenu_Update(void)
{
	deltaTime = CP_System_GetDt();
	totalElapsedTime += deltaTime;
	currentElapseTime += deltaTime;
	ElapseTimeGamename += deltaTime;


	gamename_ypos = CP_Math_LerpFloat(0, (float)(windowHeight / 3.2), lerpgamename);
	player_xpos = CP_Math_LerpFloat(-500, (float)(windowWidth + 250), lerpplayer);
	ass_xpos = (player_xpos - 180);
	player_return_xpos = CP_Math_LerpFloat((float)(windowWidth + 500), -250, lerpplayerReturn);
	ass_return_xpos = (player_return_xpos - 180);
	lerpplayer = currentElapseTime * rateplayer;
	lerpgamename = ElapseTimeGamename * rategamename;

	if (!settings && !credits) {

		//play button
		if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 50, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				CP_Engine_SetNextGameState(Level_Init, Level_Update, Level_Exit);

			}
		}
		//tutorial button
		if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				CP_Engine_SetNextGameState(Tutorial_Init, Tutorial_Update, Tutorial_Exit);

			}
		}
		//credit button
		if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				credits = TRUE;
			}
		}
		//settings
		if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1 && !settings)
			{
				settings = TRUE;
			}
		}
		//exit button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				freeAssets();
				CP_Engine_Terminate();
			}
		}
		CP_Settings_ImageMode(CP_POSITION_CORNER);
		CP_Image_Draw(Background, 0, 0, CP_Image_GetWidth(Background) * 2, CP_Image_GetHeight(Background) * 2, 255);

		// Create background that is gray in colour
		CP_Graphics_ClearBackground(gray);
		CP_Settings_Fill(red);
		CP_Settings_RectMode(CP_POSITION_CENTER);
		//draw the draw rect in the middle of the anchor point //draw play button
		CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 50, 200, 80);
		//draw the draw 2nd rect in the middle of the anchor point //draw tutorial button
		CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 200, 80);
		//draw the draw 3rd rect in the middle of the anchor point //draw credit button
		CP_Graphics_DrawRect((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 200, 80);
		//draw the draw rect in the middle of the anchor point //draw settings button
		CP_Graphics_DrawRect((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 200, 80);
		//draw the draw 4th rect in the middle of the anchor point //draw exit button
		CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80);

		//set colour of text black
		CP_Settings_Fill(black);
		//set font size
		CP_Settings_TextSize(50.0f);
		//text in the first rect 
		CP_Font_DrawText("Play", (float)(windowWidth / 2), (float)(windowHeight / 2) + 50);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		//text in the 2nd rect
		CP_Font_DrawText("Tutorial", (float)(windowWidth / 2), (float)(windowHeight / 2) + 150);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		//text in the 3nd rect
		CP_Font_DrawText("Credit", (float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		//text in the settings rect
		CP_Font_DrawText("Settings", (float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		//text in the 4nd rect
		CP_Font_DrawText("Exit", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

		//play button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 50, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Settings_Fill(blue);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw the draw rect in the middle of the anchor point
			CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 50, 220, 100);
			CP_Settings_Fill(black);
			//set font size
			CP_Settings_TextSize(70.0f);
			//text in the first rect
			CP_Font_DrawText("Play", (float)(windowWidth / 2), (float)(windowHeight / 2) + 50);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}

		//tutorial button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Settings_Fill(blue);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw the draw rect in the middle of the anchor point
			CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 220, 100);
			CP_Settings_Fill(black);
			//set font size
			CP_Settings_TextSize(70.0f);
			//text in the first rect
			CP_Font_DrawText("Tutorial", (float)(windowWidth / 2), (float)(windowHeight / 2) + 150);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}

		//credit button light up
		if (IsAreaClicked((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Settings_Fill(blue);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw the draw rect in the middle of the anchor point
			CP_Graphics_DrawRect((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 220, 100);
			CP_Settings_Fill(black);
			//set font size
			CP_Settings_TextSize(70.0f);
			//text in the first rect
			CP_Font_DrawText("Credit", (float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}

		//settings button light up
		if (IsAreaClicked((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Settings_Fill(blue);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw the draw rect in the middle of the anchor point
			CP_Graphics_DrawRect((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 220, 100);
			CP_Settings_Fill(black);
			//set font size
			CP_Settings_TextSize(70.0f);
			//text in the first rect
			CP_Font_DrawText("Settings", (float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}

		//exit button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Settings_Fill(blue);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw the draw rect in the middle of the anchor point
			CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 220, 100);
			CP_Settings_Fill(black);
			//set font size
			CP_Settings_TextSize(70.0f);
			//text in the first rect
			CP_Font_DrawText("Exit", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}
	}

	// SETTINGS
	//
	if (settings) {
		//credit button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				SFX = !SFX;

			}
		}
		//settings
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1 && settings)
			{
				MUSIC = !MUSIC;
			}
		}
		// BACK button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				settings = FALSE;
			}
		}

		//Draw BG
		CP_Graphics_ClearBackground(gray);
		CP_Settings_ImageMode(CP_POSITION_CORNER);
		CP_Image_Draw(Background, 0, 0, CP_Image_GetWidth(Background) * 2, CP_Image_GetHeight(Background) * 2, 255);

		// SFX BUTTON
		//
		if (!SFX)
		{
			CP_Graphics_ClearBackground(gray);
			//rect in the SFX
			CP_Settings_Fill(blue);
			CP_Graphics_DrawRect((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 200, 80);
			//text in the SFX
			CP_Settings_TextSize(50.0f);
			CP_Settings_Fill(black);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			CP_Font_DrawText("SFX OFF", (float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250);
			CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, 0.0f);
		}
		else
		{
			CP_Graphics_ClearBackground(gray);
			//rect in the SFX
			CP_Settings_Fill(red);
			CP_Graphics_DrawRect((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 200, 80);
			//text in the SFX
			CP_Settings_TextSize(50.0f);
			CP_Settings_Fill(black);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			CP_Font_DrawText("SFX ON", (float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250);
			CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, 1.0f);
		}

		//MUSIC BUTTON
		//
		if (!MUSIC)
		{
			CP_Graphics_ClearBackground(gray);
			//rect in the music 
			CP_Settings_Fill(blue);
			CP_Graphics_DrawRect((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 200, 80);
			//text in the music
			CP_Settings_Fill(black);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			CP_Font_DrawText("MUSIC OFF", (float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250);
			CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, 0.0f);
		}
		else
		{
			CP_Graphics_ClearBackground(gray);
			//rect in the music 
			CP_Settings_Fill(red);
			CP_Graphics_DrawRect((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 200, 80);
			//text in the music
			CP_Settings_Fill(black);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			CP_Font_DrawText("MUSIC ON", (float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250);
			CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, 1.0f);
		}
		// BACK BUTTON
		//
		CP_Settings_Fill(red);
		//draw the draw 4th rect in the middle of the anchor point //draw exit button
		CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80);
		CP_Settings_TextSize(50.0f);
		CP_Settings_Fill(black);
		CP_Font_DrawText("back", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
		//back button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Settings_Fill(blue);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw the draw rect in the middle of the anchor point
			CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 220, 100);
			CP_Settings_Fill(black);
			//set font size
			CP_Settings_TextSize(70.0f);
			//text in the first rect
			CP_Font_DrawText("back", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}
	}

	// GAME TITLE
	//
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	//CP_Image_Draw(Gamename, windowWidth / 2, (windowHeight / 2) - 100, (float)CP_Image_GetWidth(Gamename), (float)CP_Image_GetHeight(Gamename), 255);
	CP_Image_Draw(Gamename, (float)(windowWidth / 2), gamename_ypos, (float)CP_Image_GetWidth(Gamename) * 2, (float)CP_Image_GetHeight(Gamename) * 2, 255);


	// CREDITS BUTTON
	//
	if (credits) {
		CP_Graphics_ClearBackground(gray);
		CP_Settings_ImageMode(CP_POSITION_CORNER);
		CP_Image_Draw(Background, 0, 0, CP_Image_GetWidth(Background) * 2, CP_Image_GetHeight(Background) * 2, 255);
		CreditsWords();
		// BACK button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				credits = FALSE;
			}
		}
		// BACK BUTTON
		//
		CP_Settings_Fill(red);
		//draw the draw 4th rect in the middle of the anchor point //draw exit button
		CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80);
		CP_Settings_TextSize(50.0f);
		CP_Settings_Fill(black);
		CP_Font_DrawText("back", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
		//back button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Settings_Fill(blue);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw the draw rect in the middle of the anchor point
			CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 220, 100);
			CP_Settings_Fill(black);
			//set font size
			CP_Settings_TextSize(70.0f);
			//text in the first rect
			CP_Font_DrawText("back", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}
	}

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_DrawSubImage(playerSS,
		//RENDERED POS AND SIZE
		player_xpos, windowHeight - 80, 160, 160,
		// POS AND SIZE FROM SPRITESHEET
		currentFrameP* spriteWidth, 0, (currentFrameP + 1)* spriteWidth, SpriteHeight, //row1col1, row1col2 ... L to R	
		255);
	if (animationElapsedTimeP >= displayTime) {
		currentFrameP = (currentFrameP + 1) % animTotalFramesP;
		animationElapsedTimeP = 0.0f;
	}
	animationElapsedTimeP += deltaTime * animationSpeedP;

	//switch BOOL once firstrun reach end
	if (player_xpos >= (float)(windowWidth + 249) && !firstrun)
	{
		firstrun = TRUE;
	}

	//printf("%d ", lerpplayer);
	//printf("player lerp: %d \n", currentElapseTime);

	CP_Image_DrawSubImage(AssSS,
		// RENDERED POS AND SIZE
		ass_xpos, windowHeight - 80, 160, 160,
		// POS AND SIZE FROM SPRITESHEET
		currentFrameE * spriteWidth, 0, (currentFrameE + 1) * spriteWidth, SpriteHeight, //row1col1, row1col2 ... L to R
		255);
	if (animationElapsedTimeE >= displayTime) {
		currentFrameE = (currentFrameE + 1) % animTotalFramesE;
		animationElapsedTimeE = 0.0f;
	}
	animationElapsedTimeE += deltaTime * animationSpeedE;
	//printf("Ass lerp: %d \n", currentElapseTime);


	//running back
	if (firstrun == TRUE)
	{
		lerpplayerReturn = currentElapseTimeReturn * rateplayer;
		currentElapseTimeReturn += deltaTime;
		CP_Image_DrawSubImage(playerSS,
			//RENDERED POS AND SIZE
			player_return_xpos, windowHeight - 80, 160, 160,
			// POS AND SIZE FROM SPRITESHEET
			currentFrameP * spriteWidth, 0, (currentFrameP + 1) * spriteWidth, SpriteHeight, //row1col1, row1col2 ... L to R	
			255);
		if (animationElapsedTimeP >= displayTime) {
			currentFrameP = (currentFrameP + 1) % animTotalFramesP;
			animationElapsedTimeP = 0.0f;
		}
		animationElapsedTimeP += deltaTime * animationSpeedP;


		CP_Image_DrawSubImage(AssSS,
			// RENDERED POS AND SIZE
			ass_return_xpos, windowHeight - 80, 160, 160,
			// POS AND SIZE FROM SPRITESHEET
			currentFrameE * spriteWidth, 0, (currentFrameE + 1) * spriteWidth, SpriteHeight, //row1col1, row1col2 ... L to R
			255);
		if (animationElapsedTimeE >= displayTime) {
			currentFrameE = (currentFrameE + 1) % animTotalFramesE;
			animationElapsedTimeE = 0.0f;
		}
		animationElapsedTimeE += deltaTime * animationSpeedE;


		//switch BOOL once secondrun reach end
		if (player_return_xpos <= (float)-249 && !secondrun)
		{
			printf(" called\n");
			secondrun = TRUE;
		}
	}
	printf("player_xpos: %f", player_xpos);
	if (firstrun == TRUE && secondrun == TRUE)
	{
		player_xpos = (float)-500;
		player_return_xpos = (float)(windowWidth + 500);
		firstrun = FALSE;
		secondrun = FALSE;
		lerpplayer = 0;
		lerpplayerReturn = 0;
		currentElapseTime = 0;
		currentElapseTimeReturn = 0;

	}
}

void Mainmenu_Exit(void)
{
	// Clear the Splashscreen image upon exiting this state
	//
	CP_Image_Free(&Gamename);
	CP_Image_Free(&Background);

}