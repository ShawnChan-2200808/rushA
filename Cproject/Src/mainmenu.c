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

CP_Color gray, black, red, blue;
int currentFrame;
float fps, windowWidth, windowHeight, spriteWidth, spriteHeight;

CP_Image Gamename, Background;

float totalElapsedTime, lerpIncrease, currentElapseTime, currentElapseTimeReturn, ElapseTimeGamename;
static float deltaTime;
int timeplayer, timegamename, lerpMax;
float rateplayer, lerpplayer, lerpplayerReturn, finalLerp, player_xpos, ass_xpos, player_return_xpos, ass_return_xpos, gamename_ypos, lerpgamename, rategamename;

int currentFrameP, currentFrameE, animTotalFramesP, animTotalFramesE, animationSpeedP, animationSpeedE;
float SpriteHeight, displayTime;
static float animationElapsedTimeE, animationElapsedTimeP;
BOOL firstrun, secondrun, settings, SFX = TRUE, MUSIC = TRUE, credits;


void Mainmenu_Init(void)
{
	// Load image png from assets folder
	Gamename = CP_Image_Load("Assets/SPRITES/THE DELIVERABLES.png");
	Background = CP_Image_Load("Assets/SPRITES/School Background.png");

	//animation 
	displayTime = 2;
	currentFrameP = 0, currentFrameE = 0;
	animationSpeedP = 10, animationSpeedE = 15;
	animTotalFramesP = 2, animTotalFramesE = 8;
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
		if (CP_Input_MouseClicked() == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 50, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				CP_Engine_SetNextGameState(Level_Init, Level_Update, Level_Exit);

			}
		}

		//tutorial button
		if (CP_Input_MouseClicked() == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				CP_Engine_SetNextGameState(Tutorial_Init, Tutorial_Update, Tutorial_Exit);

			}
		}
		//credit button
		if (CP_Input_MouseClicked() == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				credits = TRUE;
			}
		}
		//settings
		if (CP_Input_MouseClicked() == 1)
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
		CP_Image_Draw(Background, 0, 0, (float)(CP_Image_GetWidth(Background) * 2), (float)(CP_Image_GetHeight(Background) * 2), 255);
		// Create background that is gray in colour
		CP_Graphics_ClearBackground(gray);
		Draw_Button("Play", (float)(windowWidth / 2), (float)((windowHeight / 2) + 50));
		Draw_Button("Tutorial", (float)(windowWidth / 2), (float)((windowHeight / 2) + 150));
		Draw_Button("Credit", (float)(windowWidth / 2) - 180, (float)((windowHeight / 2) + 250));
		Draw_Button("Settings", (float)(windowWidth / 2) + 180, (float)(windowHeight / 2) + 250);
		Draw_Button("Exit", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);

		//play button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 50, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			IfMouseover((float)(windowWidth / 2), (float)(windowHeight / 2) + 50, 220, 100, "Play");
		}

		//tutorial button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			IfMouseover((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 220, 100, "Tutorial");
		}

		//credit button light up
		if (IsAreaClicked((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			IfMouseover((float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250, 220, 100, "Credit");
		}

		//settings button light up
		if (IsAreaClicked((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			IfMouseover((float)(windowWidth / 1.67), (float)(windowHeight / 2) + 250, 220, 100, "Settings");
		}

		//exit button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			IfMouseover((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 220, 100, "Exit");

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
		CP_Image_Draw(Background, 0, 0, (float)(CP_Image_GetWidth(Background) * 2), (float)(CP_Image_GetHeight(Background) * 2), 255);

		// SFX BUTTON
		//
		if (!SFX)
		{

			CP_Graphics_ClearBackground(gray);
			Toggle_Button("SFX OFF", (float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250);
			CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, 0.0f);
		}
		else
		{
			CP_Graphics_ClearBackground(gray);
			Draw_Button("SFX ON", (float)(windowWidth / 2.5), (float)(windowHeight / 2) + 250);
			CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, 1.0f);
		}

		//MUSIC BUTTON
		//
		if (!MUSIC)
		{
			CP_Graphics_ClearBackground(gray);
			Toggle_Button("MUSIC OFF", (float)(float)(windowWidth / 2)+180, (float)(windowHeight / 2) + 250);
			CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, 0.0f);
		}
		else
		{
			CP_Graphics_ClearBackground(gray);
			Draw_Button("MUSIC ON", (float)(float)(windowWidth / 2) + 180, (float)(windowHeight / 2) + 250);
			CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, 1.0f);
		}
		// BACK BUTTON
		Draw_Button("Back", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
		CP_Settings_Fill(red);
		//back button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			IfMouseover((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 220, 80, "Back");
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
		CP_Image_Draw(Background, 0, 0, (float)(CP_Image_GetWidth(Background) * 2), (float)(CP_Image_GetHeight(Background) * 2), 255);
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
		CP_Font_DrawText("Back", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
		//back button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			IfMouseover((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 220, 80, "Back");

		}
	}

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_DrawSubImage(playerSS,
		//RENDERED POS AND SIZE
		player_xpos, (float)(windowHeight - 80), 160, 160,
		// POS AND SIZE FROM SPRITESHEET
		(float)(currentFrameP * spriteWidth), 0, (float)((currentFrameP + 1) * spriteWidth), SpriteHeight, //row1col1, row1col2 ... L to R	
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
		ass_xpos, (float)(windowHeight - 80), 160.f, 160.f,
		// POS AND SIZE FROM SPRITESHEET
		(float)(currentFrameE * spriteWidth), 0, (float)((currentFrameE + 1) * spriteWidth), SpriteHeight, //row1col1, row1col2 ... L to R
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
			player_return_xpos, (float)(windowHeight - 80), 160.f, 160.f,
			// POS AND SIZE FROM SPRITESHEET
			(float)(currentFrameP * spriteWidth), 0, (float)((currentFrameP + 1) * spriteWidth), SpriteHeight, //row1col1, row1col2 ... L to R	
			255);
		if (animationElapsedTimeP >= displayTime) {
			currentFrameP = (currentFrameP + 1) % animTotalFramesP;
			animationElapsedTimeP = 0.0f;
		}
		animationElapsedTimeP += deltaTime * animationSpeedP;


		CP_Image_DrawSubImage(AssSS,
			// RENDERED POS AND SIZE
			ass_return_xpos, (float)(windowHeight - 80), 160, 160,
			// POS AND SIZE FROM SPRITESHEET
			(float)(currentFrameE * spriteWidth), 0, (float)((currentFrameE + 1) * spriteWidth), SpriteHeight, //row1col1, row1col2 ... L to R
			255);
		if (animationElapsedTimeE >= displayTime) {
			currentFrameE = (currentFrameE + 1) % animTotalFramesE;
			animationElapsedTimeE = 0.0f;
		}
		animationElapsedTimeE += deltaTime * animationSpeedE;


		//switch BOOL once secondrun reach end
		if (player_return_xpos <= (float)-249 && !secondrun)
		{
			secondrun = TRUE;
		}
	}
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