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
#include "player.h"
#include "enemy.h"
#include "collsion.h"
#include "anim.h"
#include "level.h"

extern float hitCircleSize, deltaTime;
extern int randomX, randomY,randomiser;
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
	(*enemy).damage = 0.05f;
	(*enemy).inGame = 0;
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
	//(*enemy).lasercolour = red;
}

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

void labInit(struct Enemy *enemy) {
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

	(*enemy).speed = 0;
	(*enemy).alive = 1;
	(*enemy).HP = 20;
	(*enemy).damage = 0.01f;
	(*enemy).inGame = 0;

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
	(*enemy).lasercolour = red;
	hitCircleSize = 50.0f;
}

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

void isEnemyAlive(struct Enemy* enemy) {
	(*enemy).alive = (*enemy).HP <= 0 ? 0 : 1;
}

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
// Move forward
void enemyChase(struct Enemy* enemy, struct Player* player) {
	CP_Vector update = CP_Vector_Set((*player).playerPos.x - (*enemy).EnemyPos.x, (*player).playerPos.y - (*enemy).EnemyPos.y);
	(*enemy).tempPos = CP_Vector_Normalize(update);
	(*enemy).tempPos = CP_Vector_Scale((*enemy).tempPos, (*enemy).speed * deltaTime);
	(*enemy).EnemyPos = CP_Vector_Add((*enemy).EnemyPos, (*enemy).tempPos);
}

void damagePlayer(struct Enemy* enemy, struct Player* player) {
	if (isCircleEntered((*enemy).EnemyPos.x, (*enemy).EnemyPos.y, hitCircleSize, (*player).playerPos.x, (*player).playerPos.y) && (*player).alive) {
		(*player).GPA -= (*enemy).damage;
	}
}

void damageEnemy(struct Enemy* enemy, struct Player* player, float hitboxX, float hitboxY) {
	if (IsAreaClicked((*player).weaponPos.x, (*player).weaponPos.y, hitboxX, hitboxY, (*enemy).EnemyPos.x, (*enemy).EnemyPos.y) && (*enemy).alive) {
		(*enemy).HP -= (*player).damage;
	}
}

void respawnEnemy(struct Enemy *enemy,int hp) {
	(*enemy).HP = hp;
	randomX = CP_Random_RangeFloat(200, 1700);
	randomY = CP_Random_RangeFloat(200, 800);
	(*enemy).EnemyPos.x = randomX;
	(*enemy).EnemyPos.y = randomY;
	(*enemy).alive = 1;
}

void removeEnemy(struct Enemy* enemy) {
	(*enemy).EnemyPos.x = -100;
	(*enemy).EnemyPos.y = -100;
	(*enemy).alive = 0;
}

int bulletDamage(struct Enemy* enemy, struct Bullet bullet, float hitboxX, float hitboxY)
{
	if ((*enemy).inGame &&((bullet.Pos.x - (bullet.diameter / 2)) >= ((*enemy).EnemyPos.x) - (hitboxX / 2)) && ((bullet.Pos.x + (bullet.diameter / 2)) <= ((*enemy).EnemyPos.x) + (hitboxX / 2)) && ((bullet.Pos.y - (bullet.diameter / 2)) >= ((*enemy).EnemyPos.y) - (hitboxY / 2)) && ((bullet.Pos.y + (bullet.diameter / 2)) <= ((*enemy).EnemyPos.y) + (hitboxY / 2)))
	{
		(*enemy).HP -= bullet.damage;
		return 1;
	}
	else return 0;
}

void labLogic(CP_Image LabSS, struct Enemy *lab, struct Player *player) {
	// Lab1 Logic
	if ((*lab).alive && (*player).alive) {
		if (1 == laser(&(*lab), &(*player))) {
			(*player).GPA -= (*lab).damage;
		}
		enemyAnimation(LabSS, &(*lab));
		rotatenemy(&(*lab), &(*player));
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&(*lab));
	}
}
void quizLogic(CP_Image QuizSS, struct Enemy* quiz, struct Player* player) {
	if ((*quiz).alive && (*player).alive) {
		// If enemy come into contact with player deal damage

		updateEnemyAnimation(&(*quiz), deltaTime);
		enemyAnimation(QuizSS, &(*quiz));
		enemyChase(&(*quiz), &(*player));
		damagePlayer(&(*quiz), &(*player));
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&(*quiz));
	}

}
void assLogic(CP_Image AssSS, struct Enemy* ass, struct Player* player) {
	// Assignment1 Logic
	if ((*ass).alive && (*player).alive) {
		updateEnemyAnimation(&(*ass), deltaTime);
		enemyAnimation(AssSS, &(*ass));
	}
	else {
		// move dead enemy to out of screen
		removeEnemy(&(*ass));
	}
}

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

void spawnWeekly(float totalElapsedTime, float timeToSpawn,
	int QuizLoopStart, int assLoopStart, int labLoopStart,
	int numOfQuiz, int numOfAss, int numOfLab,
	CP_Image quizSS, CP_Image assSS, CP_Image labSS) {	
	if (totalElapsedTime > timeToSpawn){

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

