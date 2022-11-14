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
#include "weapons.h"
#include "player.h"
#include "enemy.h"
#include "collsion.h"
#include "anim.h"
#include <stdio.h>


extern float deltaTime;
extern int randomX, randomY,randomiser;
extern CP_Color red;

// rotating script for lab enemy -Eeloong
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

// initialising quiz -Shawn
void quizInit(struct Enemy *enemy) {
	// QUIZ
	(*enemy).spawnPos1 = CP_Vector_Set(CP_Random_RangeFloat(200, 400), CP_Random_RangeFloat(200, 400));
	(*enemy).spawnPos2 = CP_Vector_Set(CP_Random_RangeFloat(1400, 1700), CP_Random_RangeFloat(200, 400));
	(*enemy).spawnPos3 = CP_Vector_Set(CP_Random_RangeFloat(200, 400), CP_Random_RangeFloat(400, 800));
	(*enemy).spawnPos4 = CP_Vector_Set(CP_Random_RangeFloat(1400, 1700), CP_Random_RangeFloat(400, 800));
	randomiser = CP_Random_RangeInt(0, 3);
	switch (randomiser)
	{
	case 0: (*enemy).EnemyPos = (*enemy).spawnPos1;
		break;
	case 1: (*enemy).EnemyPos = (*enemy).spawnPos2;
		break;
	case 2:(*enemy).EnemyPos = (*enemy).spawnPos3;
		break;
	case 3:(*enemy).EnemyPos = (*enemy).spawnPos4;
		break;
	}

	(*enemy).speed = 350;
	(*enemy).alive = 1;
	(*enemy).HP = 25;
	(*enemy).damage = 0.02f;
	(*enemy).inGame = 0;
	(*enemy).timer = 3.0f;
	(*enemy).flag1 = 0;
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
	(*enemy).hitCircle = 50.0f;
	// Set laser color for quiz
	//(*enemy).lasercolour = red;
}

// initialising assignment -Shawn
void assInit(struct Enemy *enemy) {
	// ASSIGNMENT
	(*enemy).spawnPos1 = CP_Vector_Set(CP_Random_RangeFloat(200, 400), CP_Random_RangeFloat(200, 400));
	(*enemy).spawnPos2 = CP_Vector_Set(CP_Random_RangeFloat(1400, 1700), CP_Random_RangeFloat(200, 400));
	(*enemy).spawnPos3 = CP_Vector_Set(CP_Random_RangeFloat(200, 400), CP_Random_RangeFloat(400, 800));
	(*enemy).spawnPos4 = CP_Vector_Set(CP_Random_RangeFloat(1400, 1700), CP_Random_RangeFloat(400, 800));
	randomiser = CP_Random_RangeInt(0, 3);
	switch (randomiser)
	{
	case 0: (*enemy).EnemyPos = (*enemy).spawnPos1;
		break;
	case 1: (*enemy).EnemyPos = (*enemy).spawnPos2;
		break;
	case 2:(*enemy).EnemyPos = (*enemy).spawnPos3;
		break;
	case 3:(*enemy).EnemyPos = (*enemy).spawnPos4;
		break;
	}

	(*enemy).speed = 0;
	(*enemy).alive = 1;
	(*enemy).HP = 20;
	(*enemy).damage = 0.0f;
	(*enemy).inGame = 0;
	(*enemy).timer = 3.0f;
	(*enemy).flag1 = 0;
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
	(*enemy).floatbulletTime = 0;
	(*enemy).intbulletTime = 0;
	//collision
	(*enemy).hitboxX = ((*enemy).worldSizeW / 2);
	(*enemy).hitboxY = ((*enemy).worldSizeH / 2);
	(*enemy).enemymin = CP_Vector_Set(((*enemy).EnemyPos.x - ((*enemy).hitboxX)), ((*enemy).EnemyPos.y - ((*enemy).hitboxY)));
	(*enemy).enemymax = CP_Vector_Set(((*enemy).EnemyPos.x + ((*enemy).hitboxX)), ((*enemy).EnemyPos.y + ((*enemy).hitboxY)));
	//bullet
	enemybulletReset(&(*enemy));
}

void labInit(struct Enemy* enemy) {
	// LAB
	(*enemy).spawnPos1 = CP_Vector_Set(CP_Random_RangeFloat(100, 200), CP_Random_RangeFloat(100, 300));
	(*enemy).spawnPos2 = CP_Vector_Set(CP_Random_RangeFloat(1400, 1700), CP_Random_RangeFloat(200, 400));
	(*enemy).spawnPos3 = CP_Vector_Set(CP_Random_RangeFloat(100, 200), CP_Random_RangeFloat(600, 800));
	(*enemy).spawnPos4 = CP_Vector_Set(CP_Random_RangeFloat(1400, 1700), CP_Random_RangeFloat(400, 800));
	randomiser = CP_Random_RangeInt(0, 3);
	switch (randomiser)
	{
	case 0: (*enemy).EnemyPos = (*enemy).spawnPos1;
		break;
	case 1: (*enemy).EnemyPos = (*enemy).spawnPos2;
		break;
	case 2:(*enemy).EnemyPos = (*enemy).spawnPos3;
		break;
	case 3:(*enemy).EnemyPos = (*enemy).spawnPos4;
		break;
	}

	(*enemy).speed = 100;
	(*enemy).alive = 1;
	(*enemy).HP = 10;
	(*enemy).damage = 0.01f;
	(*enemy).inGame = 0;
	(*enemy).timer = 3.0f;
	(*enemy).flag1 = 0;

	//animation
	(*enemy).animationElapsedTime = 0.0f;
	(*enemy).animationSpeed = 20;
	(*enemy).currentFrame = 0;
	(*enemy).animTotalFrames = 1; //8;
	(*enemy).worldSizeW = 128.0f;
	(*enemy).worldSizeH = 128.0f;
	(*enemy).spriteWidth = 64.0f;
	(*enemy).SpriteHeight = 64.0f;
	(*enemy).displayTime = 2.0f;
	//Laser Init
	//laserL is the larger value (length)
	(*enemy).laserL = 750;
	(*enemy).laserB = 269;
	(*enemy).lasercolour = red;
	(*enemy).intlaserTime = 0;
	(*enemy).floatlaserTime = 0;
	(*enemy).hitCircle = 50.0f;
}

// initialising boss  -Shawn
void bossInit(struct Enemy* enemy) {
	// BOSS
	(*enemy).EnemyPos = CP_Vector_Set((float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetWindowHeight() / 4));

	(*enemy).speed = 150;
	(*enemy).alive = 1;
	(*enemy).HP = 100;//2;
	(*enemy).damage = 0.02f;
	(*enemy).inGame = 0;
	(*enemy).timer = 3.0f;
	(*enemy).flag1 = 2;

	// can reuse these vectors
	//(*enemy).spawnPos1 = CP_Vector_Set();
	//(*enemy).spawnPos2 = CP_Vector_Set();
	//(*enemy).spawnPos3 = CP_Vector_Set();

	//animation
	(*enemy).animationElapsedTime = 0.0f;
	(*enemy).animationSpeed = 20;
	(*enemy).currentFrame = 0;
	(*enemy).animTotalFrames = 4; //8;
	(*enemy).worldSizeW = 320.0f;
	(*enemy).worldSizeH = 320.0f;
	(*enemy).spriteWidth = 96.0f;
	(*enemy).SpriteHeight = 96.0f;
	(*enemy).displayTime = 2.0f;
	//laserL is the larger value (length)
	(*enemy).laserL = 750;
	(*enemy).laserB = 269;
	(*enemy).lasercolour = red;
	(*enemy).hitCircle = 400.0f;
}

// initialising all enemies excluding boss -Shawn
void initAllEnemies(int numOfQuiz, int numOfAss, int numOfLab) {
	for (int i = 0; i < numOfQuiz; i++)
	{
		quizInit(&quiz[i]);
	}
	for (int i = 0; i < numOfAss; i++)
	{
		assInit(&assignment[i]);
	}
	for (int i = 0; i < numOfLab; i++)
	{
		labInit(&lab[i]);
	}
}

// checking if enemy is alive -Shawn
void isEnemyAlive(struct Enemy* enemy) {
	(*enemy).alive = (*enemy).HP <= 0 ? 0 : 1;
}

// checking if the all the enemies are alive -Shawn
void checkEnemyAlive(int numOfQuiz, int numOfAss, int numOfLab) {
	for (int i = 0; i < numOfLab; i++)
	{
		isEnemyAlive(&lab[i]);
	}
	for (int i = 0; i < numOfAss; i++)
	{
		isEnemyAlive(&assignment[i]);
	}
	for (int i = 0; i < numOfQuiz; i++)
	{
		isEnemyAlive(&quiz[i]);
	}
}

// Enemy moving towards player posiiton -Shawn
void enemyChase(struct Enemy* enemy, struct Player* player) {
	CP_Vector update = CP_Vector_Set((*player).playerPos.x - (*enemy).EnemyPos.x, (*player).playerPos.y - (*enemy).EnemyPos.y);
	(*enemy).tempPos = CP_Vector_Normalize(update);
	(*enemy).tempPos = CP_Vector_Scale((*enemy).tempPos, (*enemy).speed * deltaTime);
	(*enemy).EnemyPos = CP_Vector_Add((*enemy).EnemyPos, (*enemy).tempPos);
}

// Damaging the player on collision -Shawn
void damagePlayer(struct Enemy* enemy, struct Player* player) {
	if (isCircleEntered((*enemy).EnemyPos.x, (*enemy).EnemyPos.y, (*enemy).hitCircle, (*player).playerPos.x, (*player).playerPos.y) && (*player).alive) {
		(*player).GPA -= (*enemy).damage;
		(*player).currentFrame += (*player).animTotalFrames+1;
	}
}

// Damaging the enemy on collision -Shawn
void damageEnemy(struct Enemy* enemy, struct Player* player, float hitboxX, float hitboxY, int totalFrames) {
	if ((*enemy).inGame && IsAreaClicked((*player).weaponPos.x, (*player).weaponPos.y, hitboxX, hitboxY, (*enemy).EnemyPos.x, (*enemy).EnemyPos.y) && (*enemy).alive) {
		(*enemy).HP -= (*player).damage;
		(*enemy).currentFrame += totalFrames;
	}
}

// Respawning the enemies if need to -Shawn
void respawnEnemy(struct Enemy *enemy,int hp) {
	(*enemy).HP = hp;
	randomiser = CP_Random_RangeInt(0, 3);
	switch (randomiser)
	{
	case 0: (*enemy).EnemyPos = (*enemy).spawnPos1;
		break;
	case 1: (*enemy).EnemyPos = (*enemy).spawnPos2;
		break;
	case 2:(*enemy).EnemyPos = (*enemy).spawnPos3;
		break;
	case 3:(*enemy).EnemyPos = (*enemy).spawnPos4;
		break;
	}
	(*enemy).alive = 1;
}

// Removing the enemies from the screen and setting them to dead done -Shawn
void removeEnemy(struct Enemy* enemy) {
	(*enemy).EnemyPos.x = -100;
	(*enemy).EnemyPos.y = -100;
	(*enemy).alive = 0;
}

// Bullet Damage to the enemy by the player -Justin and Eeloong
int playerbulletDamage(struct Enemy* enemy, struct playerBullet bullet, float hitboxX, float hitboxY, int totalFrames)
{
	if ((*enemy).inGame && ((bullet.Pos.x - (bullet.diameter / 2)) >= ((*enemy).EnemyPos.x) - (hitboxX / 2)) && ((bullet.Pos.x + (bullet.diameter / 2)) <= ((*enemy).EnemyPos.x) + (hitboxX / 2)) && ((bullet.Pos.y - (bullet.diameter / 2)) >= ((*enemy).EnemyPos.y) - (hitboxY / 2)) && ((bullet.Pos.y + (bullet.diameter / 2)) <= ((*enemy).EnemyPos.y) + (hitboxY / 2)))
	{
		(*enemy).HP -= bullet.damage;
		(*enemy).currentFrame += totalFrames;
		return 1;
	}
	else return 0;
}

// Bullet Damage to the player by the enemy -Justin and Eeloong
int enemybulletDamage(struct Enemy* enemy, struct Player* player, struct enemyBullet bullet)
{
	if ((*player).alive &&
		isCircleEntered(bullet.Pos.x, bullet.Pos.y, bullet.diameter, (*player).playerPos.x, (*player).playerPos.y))
		//((bullet.Pos.x - (bullet.diameter / 2)) >= ((*player).playerPos.x) - ((*enemy).hitboxX / 2)) &&
		//((bullet.Pos.x + (bullet.diameter / 2)) <= ((*player).playerPos.x) + ((*enemy).hitboxX / 2)) &&
		//((bullet.Pos.y - (bullet.diameter / 2)) >= ((*player).playerPos.y) - ((*enemy).hitboxY / 2)) &&
		//((bullet.Pos.y + (bullet.diameter / 2)) <= ((*player).playerPos.y) + ((*enemy).hitboxY / 2)))
	{
		(*player).GPA -= bullet.damage;
		return 1;
	}
	else return 0;
}
// Lab logic that runs in the game when quiz is active -Shawn and Eeloong
void labLogic(CP_Image LabSS, struct Enemy* lab, struct Player* player) {
	// Lab1 Logic
	if ((*lab).alive && (*player).alive) {
		if (1 == laser(&(*lab), &(*player))) {
			//(*player).GPA -= (*lab).damage;
			enemyChase(&(*lab), &(*player));
			enemyAnimation(LabSS, &(*lab));
			rotatenemy(&(*lab), &(*player));
		}
		else if ((4 == laser(&(*lab), &(*player)))) {
			enemyAnimation(LabSS, &(*lab));
			(*player).GPA -= (*lab).damage;
			(*player).currentFrame += (*player).animTotalFrames + 1;
		}
		else
		{
			enemyAnimation(LabSS, &(*lab));
		}
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&(*lab));
	}
}

// Quiz logic that runs in the game when quiz is active -Shawn
void quizLogic(CP_Image QuizSS, struct Enemy* quiz, struct Player* player) {
	(*quiz).timer -= deltaTime;
	// when timer is up
	if ((*quiz).timer >= 0.0f) {
		(*quiz).timer -= deltaTime;
	}
	if ((*quiz).alive && (*player).alive && (*quiz).timer <= 0.0f) {
		// If enemy come into contact with player deal damage
		enemyChase(&(*quiz), &(*player));
		damagePlayer(&(*quiz), &(*player));
	}

	if ((*quiz).alive && (*player).alive) {
		updateEnemyAnimation(&(*quiz), deltaTime);
		enemyAnimation(QuizSS, &(*quiz));
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&(*quiz));
	}

}

// Assignment Logic that runs in the game when assignment is active -Eeloong
void assLogic(CP_Image AssSS, struct Enemy* ass, struct Player* player) {
	(*ass).timer -= deltaTime;
	// when timer is up
	if ((*ass).timer >= 0.0f) {
		(*ass).timer -= deltaTime;
	}
	// for eeloong to add in when to start the attack
	//if ((*ass).alive && (*player).alive && (*ass).timer <= 0.0f) {

	//}
	 if ((*ass).alive && (*player).alive &&(*ass).timer <= 0.0f) {
		enemybulletInit(&(*ass), &(*player),deltaTime,700,70,0.5f);
		//enemybulletInit(ass->bulletIndex, &ass , &player);
		enemybulletUpdate(deltaTime, &(*ass), &(*player), CP_Color_Create(255, 170, 170, 255));
	}

	 if ((*ass).alive && (*player).alive) {
		 updateEnemyAnimation(&(*ass), deltaTime);
		 enemyAnimation(AssSS, &(*ass));
	 }
	else {
		// move dead enemy to out of screen
		removeEnemy(&(*ass));
	}
}

// Boss Logic that runs in the game when boss is in active -Shawn
void bossLogic(CP_Image BossSS, struct Enemy* boss, struct Player* player) {
	if ((*boss).alive && (*player).alive && (*boss).inGame) {
		{
			// Spawn with 3 secodns of standing still
			if ((*boss).flag1 == 2) {
				randomiser = 4;
			}
			// timer ticks down
			(*boss).timer -= deltaTime;
			// when timer is up
			if ((*boss).timer <= 0.0f) {
				(*boss).timer = 5.0f;
				(*boss).flag1 = 1;
				(*player).speed = 500;
			}
			// set rnadom number
			if ((*boss).flag1 == 1)
			{
				randomiser = CP_Random_RangeInt(0, 3);
				(*boss).flag1 = 0;
			}

			// based on random number do following case
			switch (randomiser)
			{
			case 0: // Death zone chase 
				
				boss->speed = 150;
				boss->hitCircle = 500;
				// chase the player
				enemyChase(&(*boss), &(*player));
				damagePlayer(&(*boss), &(*player));
				//if player get into the circle he slows down
				if (isCircleEntered((*boss).EnemyPos.x, (*boss).EnemyPos.y, (*boss).hitCircle, (*player).playerPos.x, (*player).playerPos.y) && (*player).alive) {
					(*player).speed = 300;
				}
				CP_Settings_Fill(CP_Color_Create(255, 170, 170, 120));
				CP_Graphics_DrawCircle(boss->EnemyPos.x, boss->EnemyPos.y, boss->hitCircle);
				break;

			case 1: // Laser
			
						
						if (1 == laser(&(*boss), &(*player))) {
						}
						else if ((4 == laser(&(*boss), &(*player)))) {
						(*player).GPA -= (*boss).damage;
						}
				boss->hitCircle = 200;
				damagePlayer(&(*boss), &(*player));
				CP_Settings_Fill(CP_Color_Create(0, 255, 0, 120));
				CP_Graphics_DrawCircle(boss->EnemyPos.x, boss->EnemyPos.y, boss->hitCircle);

				break;

			case 2: // Projectile

				enemybulletInit(&(*boss), &(*player), deltaTime, 1000, 100, 0.7f);
				//enemybulletInit(ass->bulletIndex, &ass , &player);
				enemybulletUpdate(deltaTime, &(*boss), &(*player), black);
				boss->hitCircle = 200;
				CP_Settings_Fill(CP_Color_Create(0, 0, 255, 120));
				CP_Graphics_DrawCircle(boss->EnemyPos.x, boss->EnemyPos.y, boss->hitCircle);
				damagePlayer(&(*boss), &(*player));
				break;

			case 3: // fast chase the player
				boss->speed = 300;
				boss->hitCircle = 200;
				enemyChase(&(*boss), &(*player));
				damagePlayer(&(*boss), &(*player));
				break;

			case 4: // do nothing (used for spawning)
				break;
			}
		}
		// Render the animation
		updateEnemyAnimation(&(*boss), deltaTime);
		enemyAnimation(BossSS, &(*boss));
	// Assignment1 Logic	
	if ((*ass).alive && (*player).alive) {
		updateEnemyAnimation(&(*ass), deltaTime);
		enemyAnimation(AssSS, &(*ass));
		enemybulletInit(&(*ass), &(*player));
		enemybulletUpdate(deltaTime, &(*ass), &(*player));
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&(*boss));
	}
}

// Enables logic for all the enemies in the game -Shawn
void allEnemyLogic(int QuizLoopStart, int assLoopStart, int labLoopStart,
	int numOfQuiz, int numOfAss, int numOfLab,
	CP_Image quizSS, CP_Image assSS, CP_Image labSS) {

	for (int i = labLoopStart; i < numOfLab; i++)
	{
		labLogic(labSS, &lab[i], &player);
	}
	for (int i = assLoopStart; i < numOfAss; i++)
	{
		assLogic(assSS, &assignment[i], &player);
	}
	for (int i = QuizLoopStart; i < numOfQuiz; i++)
	{
		quizLogic(quizSS, &quiz[i], &player);
	}
}

// This function decides how many enemies of which specific type to be spawned at which timing
// it will take in the value based on which enemy in the struct u want to spawn -Shawn
void spawnWeekly(float totalElapsedTime, float timeToSpawn,
	int QuizLoopStart, int assLoopStart, int labLoopStart,
	int numOfQuiz, int numOfAss, int numOfLab,
	CP_Image quizSS, CP_Image assSS, CP_Image labSS) {
	if (totalElapsedTime > timeToSpawn) {

		for (int i = labLoopStart; i < numOfLab; ++i)
		{
			lab[i].inGame = 1;
		}
		for (int i = assLoopStart; i < numOfAss; ++i)
		{
			assignment[i].inGame = 1;
		}
		for (int i = QuizLoopStart; i < numOfQuiz; ++i)
		{
			quiz[i].inGame = 1;
		}

		allEnemyLogic(QuizLoopStart, assLoopStart, labLoopStart,
			numOfQuiz, numOfAss, numOfLab,
			quizSS, assSS, labSS);

		checkEnemyAlive(numOfQuiz, numOfAss, numOfLab);
	}
}

// Spawns the boss at the specific time -Shawn
void spawnBoss(float totalElapsedTime, float timeToSpawn, CP_Image BossSS) {
	if (totalElapsedTime > timeToSpawn) {
		boss.inGame = 1;
		bossLogic(BossSS,&boss,&player);
		isEnemyAlive(&boss);
	}
}


