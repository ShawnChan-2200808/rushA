/*!
@file       enemy.c
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains defininition of Enemy functions
*//*_________________________________________________________________________________*/

#include "cprocessing.h"
#include "utils.h"
#include "bullet.h"

// MAIN ENEMY STRUCT
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
}; extern struct Enemy quiz1, lab1, assignment1;

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

extern CP_Color red;

void rotatenemy(struct Enemy* enemy, struct Player* player) {
	float playerangle = enemyPlayerAngle(enemy, player);

	//checking for 8 predetermined angles
	if (playerangle > 337.5 || playerangle < 22.5) {
		(*enemy).currentFrame = 4;
	}
	else if (playerangle <= 67.5) {
		(*enemy).currentFrame = 5;
	}
	else if (playerangle <= 112.5) {
		(*enemy).currentFrame = 6;
	}
	else if (playerangle <= 157.5) {
		(*enemy).currentFrame = 7;
	}
	else if (playerangle <= 202.5) {
		(*enemy).currentFrame = 0;
	}
	else if (playerangle <= 247.5) {
		(*enemy).currentFrame = 1;
	}
	else if (playerangle <= 292.5) {
		(*enemy).currentFrame = 2;
	}
	else if (playerangle <= 337.5) {
		(*enemy).currentFrame = 3;
	}
}

void quizInit(struct Enemy *enemy,float posX, float posY) {
	// QUIZ
	(*enemy).EnemyPos = CP_Vector_Set(posX, posY);
	(*enemy).speed = 50;
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

	// Set laser color for quiz
	(*enemy).lasercolour = red;
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
	(*enemy).animTotalFrames = 1; //8;
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

void damageEnemy(struct Enemy* enemy, struct Player* player, float hitboxX, float hitboxY) {
	if (IsAreaClicked((*player).weaponPos.x, (*player).weaponPos.y, hitboxX, hitboxY, (*enemy).EnemyPos.x, (*enemy).EnemyPos.y) && (*enemy).alive) {
		(*enemy).HP -= (*player).damage;
	}
}

void respawnEnemy(struct Enemy *enemy, float posX, float posY) {
	(*enemy).HP = 2;
	(*enemy).EnemyPos.x = posX;
	(*enemy).EnemyPos.y = posY;
	(*enemy).alive = 1;
}

void removeEnemy(struct Enemy* enemy) {
	(*enemy).EnemyPos.x = -100;
	(*enemy).EnemyPos.y = -100;
	(*enemy).alive = 0;
}

int bulletDamage(struct Enemy* enemy, struct Bullet bullet, float hitboxX, float hitboxY)
{
	if (((bullet.Pos.x - (bullet.diameter / 2)) >= ((*enemy).EnemyPos.x) - (hitboxX / 2)) && ((bullet.Pos.x + (bullet.diameter / 2)) <= ((*enemy).EnemyPos.x) + (hitboxX / 2)) && ((bullet.Pos.y - (bullet.diameter / 2)) >= ((*enemy).EnemyPos.y) - (hitboxY / 2)) && ((bullet.Pos.y + (bullet.diameter / 2)) <= ((*enemy).EnemyPos.y) + (hitboxY / 2)))
	{
		(*enemy).HP -= bullet.damage;
		return 1;
	}
	else return 0;
}