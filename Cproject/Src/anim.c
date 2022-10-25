/*!
@file       anim.c
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      Make prototype functions and test it here. Copy and paste from current level
			to see if it works before we integrate it into the main game
		*** AND MAKE A COPY for yourself + DONT FORGET TO MAKE .H file to test ***
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
//#include "enemy.c"

extern CP_Color gray; 
extern struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	int speed, alive;
	float HP, damage;
	//animation
	int animationSpeed,
		currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH,
		spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;

}; struct Enemy quiz1, lab1, assignment1;

void UpdateEnemyAnimation(struct Enemy* enemy, float dt) {
	(*enemy).animationElapsedTime += dt * (*enemy).animationSpeed;
}

void EnemyAnimation(CP_Image Spritesheet,struct Enemy*enemy){
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_DrawSubImage(Spritesheet,
		// RENDERED POS AND SIZE
		(*enemy).EnemyPos.x, (*enemy).EnemyPos.y, (*enemy).worldSizeW, (*enemy).worldSizeH,
		// POS AND SIZE FROM SPRITESHEET
		(*enemy).currentFrame * (*enemy).spriteWidth, 0, ((*enemy).currentFrame + 1) * (*enemy).spriteWidth, (*enemy).SpriteHeight, //row1col1, row1col2 ... L to R
		255);
	if ((*enemy).animationElapsedTime >= (*enemy).displayTime) {
		(*enemy).currentFrame = ((*enemy).currentFrame + 1) % (*enemy).animTotalFrames;
		(*enemy).animationElapsedTime = 0.0f;
	}
}