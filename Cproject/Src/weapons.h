/*!
@file       weapons.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       27/11/2022 (last updated)
@brief      contains declarations of Weapon functions
*//*_________________________________________________________________________________*/
#pragma once



//Returns 4 states:
// 1: For when laser is tracking player
// 2: For when laser is charging up
// 3: For when laser is firing but player is not being damaged
// 4: For when laser is firing & player is being damaged
int laser(struct Enemy* enemy, struct Player* player);

//Bullets

//player Bullets
void playerbulletReset(int index);
void playerbulletInit(int index, struct Player* player);
void playerbulletUpdate(int index, float deltaTime, int numOfQuiz, int numOfAssLab);

//enemy Bullets
void enemybulletReset(struct Enemy* enemy);
void enemybulletInit(struct Enemy* enemy, struct Player* player, float bulletSpeed, float bulletSize,float bulletDamage);
void enemybulletUpdate(float deltaTime,struct Enemy* enemy, struct Player* player);