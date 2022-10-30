/*!
@file       player.c
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      contains defininition of Player functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"

// MAIN ENEMY STRUCT
struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	int speed, alive;
	float HP, damage;
	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;

}; struct Enemy quiz1, lab1, assignment1;

float hitCircleSize, deltaTime;

// reference to player
extern struct Player {
	CP_Vector playerPos, tempPos, direction;
	CP_Vector weaponPos, bulletPos;
	int speed, alive, damage, weapon, attacking, ammo;
	float GPA, timer, projVelocity;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; extern struct Player player;

void quizInit(struct Enemy *enemy,float posX, float posY) {
	// QUIZ
	(*enemy).EnemyPos = CP_Vector_Set(posX, posY);
	(*enemy).speed = 400;
	(*enemy).alive = 1;
	(*enemy).HP = 3;
	(*enemy).damage = 0.05f;
	//animation
	(*enemy).animationElapsedTime = 0.0f;
	(*enemy).animationSpeed = 15;
	(*enemy).currentFrame = 0;
	(*enemy).animTotalFrames = 6;
	(*enemy).worldSizeW = 96.0f;
	(*enemy).worldSizeH = 96.0f;
	(*enemy).spriteWidth = 64.0f;
	(*enemy).SpriteHeight = 64.0f;
	(*enemy).displayTime = 2.0f;
	hitCircleSize = 50.0f;
}

void assInit(struct Enemy *enemy, float posX, float posY) {
	// ASSIGNMENT
	(*enemy).EnemyPos = CP_Vector_Set(posX, posY);
	(*enemy).speed = 0;
	(*enemy).alive = 1;
	(*enemy).HP = 3;
	(*enemy).damage = 0.0f;
	//animation
	(*enemy).animationElapsedTime = 0.0f;
	(*enemy).animationSpeed = 15;
	(*enemy).currentFrame = 0;
	(*enemy).animTotalFrames = 8;
	(*enemy).worldSizeW = 96.0f;
	(*enemy).worldSizeH = 96.0f;
	(*enemy).spriteWidth = 64.0f;
	(*enemy).SpriteHeight = 64.0f;
	(*enemy).displayTime = 2.0f;
	hitCircleSize = 50.0f;
}

void labInit(struct Enemy *enemy, float posX, float posY) {
	// LAB
	(*enemy).EnemyPos = CP_Vector_Set(posX, posY);
	(*enemy).speed = 0;
	(*enemy).alive = 1;
	(*enemy).HP = 3;
	(*enemy).damage = 0.00f;
	//animation
	(*enemy).animationElapsedTime = 0.0f;
	(*enemy).animationSpeed = 5;
	(*enemy).currentFrame = 0;
	(*enemy).animTotalFrames = 8;
	(*enemy).worldSizeW = 128.0f;
	(*enemy).worldSizeH = 128.0f;
	(*enemy).spriteWidth = 64.0f;
	(*enemy).SpriteHeight = 64.0f;
	(*enemy).displayTime = 2.0f;
	hitCircleSize = 50.0f;
}

void isEnemyAlive(struct Enemy* enemy) {
	(*enemy).alive = (*enemy).HP <= 0 ? 0 : 1;
}

// Move forward
void enemyChase(struct Enemy* enemy, struct Player* player) {
	CP_Vector update = CP_Vector_Set((*player).playerPos.x - (*enemy).EnemyPos.x, (*player).playerPos.y - (*enemy).EnemyPos.y);
	(*enemy).tempPos = CP_Vector_Normalize(update);
	(*enemy).tempPos = CP_Vector_Scale((*enemy).tempPos, (*enemy).speed * deltaTime);
	(*enemy).EnemyPos = CP_Vector_Add((*enemy).EnemyPos, (*enemy).tempPos);
}

void damagePlayer(struct Enemy* enemy, struct Player* player) {
	if (isCircleEntered((*enemy).EnemyPos.x, (*enemy).EnemyPos.y, hitCircleSize, (*player).playerPos.x, (*player).playerPos.y) && (*player).alive) {
		(*player).GPA -= quiz1.damage;
	}
}

