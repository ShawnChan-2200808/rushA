/*!
@file       enemy.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains declarations of Enemy functions
*//*_________________________________________________________________________________*/

// MAIN ENEMY STRUCT
struct Enemy {
	CP_Vector EnemyPos, tempPos, direction;
	CP_Vector weaponPos;
	CP_Color lasercolour;
	int speed, alive;
	float HP, damage;
	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
};struct Enemy quiz1, lab1, assignment1;

void quizInit(struct Enemy* quiz,float posX,float posY);
void assInit(struct Enemy* quiz, float posX, float posY);
void labInit(struct Enemy* quiz, float posX, float posY);
void isEnemyAlive(struct Enemy* enemy);
void enemyChase(struct Enemy* enemy, struct Player* player);
void damagePlayer(struct Enemy* enemy, struct Player* player);
void damageEnemy(struct Enemy* enemy, struct Player* player, float hitboxX, float hitboxY);
void respawnEnemy(struct Enemy* enemy, float posX, float posY);
void removeEnemy(struct Enemy* enemy);
void rotatenemy(struct Enemy* enemy, struct Player* player);
int bulletDamage(struct Enemy* enemy, struct Bullet bullet, float hitboxX, float hitboxY);
