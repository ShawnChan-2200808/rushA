/*!
@file       player.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      contains Declarations of Player functions
*//*_________________________________________________________________________________*/



#pragma once
// MAIN PLAYER STRUCT
struct Player {
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
	//Bullet Variables
	struct playerBullet
	{
		CP_Vector Pos, Vector;
		int active, diameter, damage;
		float velocity;
	} playerBullets[10];
	int bulletIndex;
}; struct Player player;
void playerInit(struct Player* player);
void isPlayerAlive(struct Player* player);
void moveForward(struct Player* player, CP_Vector direction);
void moveBack(struct Player* player, CP_Vector direction);
void meleeVec(struct Player* player,int scale);
int switchWeapon(int weapon);
float mouseToplayerAngle(struct Player* player);