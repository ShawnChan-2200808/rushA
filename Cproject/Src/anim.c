/*!
@file       anim.c
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      Definition of animation functions for player, enemy and boss.
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "player.h"
#include "enemy.h"

// Updates the elapsed time of the animation for enemies.
void updateEnemyAnimation(struct Enemy* enemy, float dt) {
	(*enemy).animationElapsedTime += dt * (*enemy).animationSpeed;
}

// Renders enemy animation from the spritesheet in the order of left to right
void enemyAnimation(CP_Image Spritesheet,struct Enemy*enemy){
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_DrawSubImage(Spritesheet,
		// RENDERED POS AND SIZE IN GAME
		(*enemy).EnemyPos.x, (*enemy).EnemyPos.y, (*enemy).worldSizeW, (*enemy).worldSizeH,
		// POS AND SIZE FROM SPRITESHEET 
		(*enemy).currentFrame * (*enemy).spriteWidth, 0, ((*enemy).currentFrame + 1) * (*enemy).spriteWidth, (*enemy).SpriteHeight, //row1col1, row1col2 ... L to R
		255);
	if ((*enemy).animationElapsedTime >= (*enemy).displayTime) {
		// RESET THE FRAME BACK TO FIRST FRAME
		(*enemy).currentFrame = ((*enemy).currentFrame + 1) % (*enemy).animTotalFrames;
		(*enemy).animationElapsedTime = 0.0f;
	}
}

// Updates the elapsed time of the animation for player.
void updatePlayerAnimation(struct Player* player, float dt) {
	(*player).animationElapsedTime += dt * (*player).animationSpeed;
}

// Renders player animation from the spritesheet in the order of left to right
void playerAnimation(CP_Image Spritesheet, struct Player* player) {
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_DrawSubImage(Spritesheet,
		// RENDERED POS AND SIZE IN GAME
		(*player).playerPos.x, (*player).playerPos.y, (*player).worldSizeW, (*player).worldSizeH,
		// POS AND SIZE FROM SPRITESHEET
		(*player).currentFrame * (*player).spriteWidth, 0, ((*player).currentFrame + 1) * (*player).spriteWidth, (*player).SpriteHeight, //row1col1, row1col2 ... L to R
		255);
	if ((*player).animationElapsedTime >= (*player).displayTime) {
		// RESET THE FRAME BACK TO FIRST FRAME
		(*player).currentFrame = ((*player).currentFrame + 1) % (*player).animTotalFrames;
		(*player).animationElapsedTime = 0.0f;
	}
}



