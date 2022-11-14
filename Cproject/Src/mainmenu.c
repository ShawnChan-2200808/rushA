/*!
@file       mainmenu.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains defininition of Enemy functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "level.h"
<<<<<<< Updated upstream
=======
#include "player.h"
#include "credits.h"
//#include "enemy.h"
//#include "anim.c"
	
CP_Color gray, black, red,blue;
int windowWidth, windowHeight, currentFrame, spriteWidth, spriteHeight;
float fps;

>>>>>>> Stashed changes

CP_Image Gamename;

float totalElapsedTime, lerpIncrease, currentElapseTime;
static float deltaTime;
int time, lerpMax;
float rate, lerp, finalLerp, player_xpos, ass_xpos, player_return_xpos, ass_return_xpos, gamename_xpos;

int currentFrameP, currentFrameE, animTotalFramesP, animTotalFramesE, animationSpeedP, animationSpeedE;
float spriteWidth, SpriteHeight, displayTime;
static float animationElapsedTimeE, animationElapsedTimeP;

static float Lerp(float start, float end, float value)
{
	return (1.f - value) * start + value * end;
}


void Mainmenu_Init(void)
{
	// Load image png from assets folder
	Gamename = CP_Image_Load("Assets/SPRITES/THE DELIVERABLES.png");

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
	time = 6;
	finalLerp = 1;
	lerpMax = 1;
	

	// Getting the rate we need to get to reach 1 lerpfector in 3 seconds
	rate = finalLerp / time;
	//
	// Setting the window width and height
	windowWidth = 1920;
	windowHeight = 1080;

	// Set the colour for gray
	black = CP_Color_Create(0, 0, 0, 255);
	red = CP_Color_Create(255, 0, 0, 255);
	blue = CP_Color_Create(0, 0, 255, 255);

	// Set the window when executed to the size of the splashscreen image
	CP_System_SetWindowSize(windowWidth, windowHeight);

	CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
	CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
	CP_Sound_PlayAdvanced(mainMenuOST, 0.1f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
}

void Mainmenu_Update(void)
{
	deltaTime = CP_System_GetDt();
	totalElapsedTime += deltaTime;
	currentElapseTime = totalElapsedTime;
	if (currentElapseTime >= 1)
	{
		currentElapseTime == 0;
	}
	
	gamename_xpos = CP_Math_LerpFloat(-2000, (float)((windowHeight / 2) - 100), lerp);
	player_xpos = CP_Math_LerpFloat(-2000, (float)(windowWidth + 250), lerp);
	ass_xpos = (player_xpos - 180);
	player_return_xpos = CP_Math_LerpFloat((float)(windowWidth + 2000), -250, lerp);
	ass_return_xpos = (player_return_xpos + 180);


	SpawnBG(Floor, 6, 9);
	// Create background that is gray in colour
	CP_Graphics_ClearBackground(gray);
	CP_Settings_Fill(red);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	//draw the draw rect in the middle of the anchor point //draw play button
	CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 50, 200, 80);
	//draw the draw 2nd rect in the middle of the anchor point //draw tutorial button
	CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 200, 80);
	//draw the draw 3rd rect in the middle of the anchor point //draw credit button
	CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 250, 200, 80);
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
	CP_Font_DrawText("Credit", (float)(windowWidth / 2), (float)(windowHeight / 2) + 250);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	//text in the 4nd rect
	CP_Font_DrawText("Exit", (float)(windowWidth / 2), (float)(windowHeight / 2) + 350);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);


	//// Get the mouse position/canvas size ratio
	//float mx = (float)CP_Input_GetMouseWorldX() / (float)CP_System_GetWindowWidth();
	//float my = (float)CP_Input_GetMouseWorldY() / (float)CP_System_GetWindowHeight();

	//// Convert to 0-255 values for color
	//int r_color = CP_Math_LerpInt(0, 255, mx);
	//int b_color = CP_Math_LerpInt(0, 255, my);

	//// Clamp the values
	//r_color = CP_Math_ClampInt(r_color, 0, 255);
	//b_color = CP_Math_ClampInt(b_color, 0, 255);

	//// Set the background as the color
	//CP_Graphics_ClearBackground(CP_Color_Create(r_color, 0, b_color, 255));

		CP_Settings_ImageMode(CP_POSITION_CENTER);

		//CP_Image_Draw(Gamename, windowWidth / 2, (windowHeight / 2) - 100, (float)CP_Image_GetWidth(Gamename), (float)CP_Image_GetHeight(Gamename), 255);
		CP_Image_Draw(Gamename, (float)(windowWidth / 2), gamename_xpos, (float)CP_Image_GetWidth(Gamename) * 2, (float)CP_Image_GetHeight(Gamename) * 2, 255);

		CP_Image_DrawSubImage(playerSS,
			 //RENDERED POS AND SIZE
			player_xpos, windowHeight - 80, 160, 160,
			// POS AND SIZE FROM SPRITESHEET
			currentFrameP * spriteWidth, 0, (currentFrameP + 1) * spriteWidth, SpriteHeight, //row1col1, row1col2 ... L to R	
			255);
		if (animationElapsedTimeP >= displayTime) {
			currentFrameP = (currentFrameP + 1) % animTotalFramesP;
			animationElapsedTimeP = 0.0f;
		}
		animationElapsedTimeP += deltaTime * animationSpeedP;
		
		printf("%d ", lerp);
		printf("player lerp: %d \n", currentElapseTime);
		lerp = currentElapseTime*rate;

		//CP_Image_DrawSubImage(PlayerSS,
		//CP_Math_LerpInt(-80, windowWidth, Lerp(0, windowWidth, 10)), windowHeight - 80, 160, 160,
		//// POS AND SIZE FROM SPRITESHEET
		//currentFrame * spriteWidth, 0, (currentFrame + 1) * spriteWidth, spriteHeight, //row1col1, row1col2 ... L to R
		//255);


		//CP_Image_DrawAdvanced(PlayerSS, 160 , windowHeight-80, 160, 160, 255, -180);
	
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
		printf("Ass lerp: %d \n", currentElapseTime);
		lerp = currentElapseTime * rate;

		
		while (player_xpos >= windowWidth + 250)
		{
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
			printf("%d ", lerp);
			printf("player lerp: %d \n", currentElapseTime);
			lerp = currentElapseTime * rate;

			//CP_Image_DrawSubImage(PlayerSS,
			//CP_Math_LerpInt(-80, windowWidth, Lerp(0, windowWidth, 10)), windowHeight - 80, 160, 160,
			//// POS AND SIZE FROM SPRITESHEET
			//currentFrame * spriteWidth, 0, (currentFrame + 1) * spriteWidth, spriteHeight, //row1col1, row1col2 ... L to R
			//255);


			//CP_Image_DrawAdvanced(PlayerSS, 160 , windowHeight-80, 160, 160, 255, -180);

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
			printf("Ass lerp: %d \n", currentElapseTime);
			lerp = currentElapseTime * rate;

			player_xpos = 0;
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
		//play button light up
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) +50, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
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
		if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Settings_Fill(blue);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			//draw the draw rect in the middle of the anchor point
			CP_Graphics_DrawRect((float)(windowWidth / 2), (float)(windowHeight / 2) + 250, 220, 100);
			CP_Settings_Fill(black);
			//set font size
			CP_Settings_TextSize(70.0f);
			//text in the first rect
			CP_Font_DrawText("Credit", (float)(windowWidth / 2), (float)(windowHeight / 2) + 250);
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


		//play button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2)+50, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				CP_Engine_SetNextGameState(Level_Init, Level_Update, Level_Exit);

			}
		}
		//tutorial button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 150, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				CP_Engine_SetNextGameState(Level_Init, Level_Update, Level_Exit);

			}
		}
		//credit button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 250, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				CP_Engine_SetNextGameState(Credits_Init, Credits_Update, Credits_Exit);

			}
		}
		//exit button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
		{
			if (IsAreaClicked((float)(windowWidth / 2), (float)(windowHeight / 2) + 350, 200, 80, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
			{
				CP_Engine_Terminate();
			}
		}

}

void Mainmenu_Exit(void)
{
	// Clear the Splashscreen image upon exiting this state
	//
	CP_Image_Free(&Gamename);
}