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
	int speed, alive, inGame;
	float hitCircle;
	float HP, damage, laserB, laserL;
	CP_Vector spawnPos1, spawnPos2, spawnPos3, spawnPos4;
	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
};struct Enemy quiz[10], lab[8], assignment[8],boss;

void quizInit(struct Enemy* enemy);
void assInit(struct Enemy* enemy);
void labInit(struct Enemy* enemy);
void bossInit(struct Enemy* enemy);
void initAllEnemies(int numOfQuiz, int numOfAss, int numOfLab);
void isEnemyAlive(struct Enemy* enemy);
void checkEnemyAlive(numOfQuiz, numOfAss, numOfLab);
void enemyChase(struct Enemy* enemy, struct Player* player);
void damagePlayer(struct Enemy* enemy, struct Player* player);
void damageEnemy(struct Enemy* enemy, struct Player* player, float hitboxX, float hitboxY,int totalFrames);
void respawnEnemy(struct Enemy* enemy, int hp);
void removeEnemy(struct Enemy* enemy);
void rotatenemy(struct Enemy* enemy, struct Player* player);
int bulletDamage(struct Enemy* enemy, struct Bullet bullet, float hitboxX, float hitboxY,int totalFrames);
void labLogic(CP_Image LabSS, struct Enemy* lab, struct Player* player);
void quizLogic(CP_Image QuizSS, struct Enemy* quiz, struct Player* player);
void assLogic(CP_Image AssSS, struct Enemy* ass, struct Player* player);
void bossLogic(CP_Image BossSS, struct Enemy* boss, struct Player* player);
void allEnemyLogic(int QuizLoopStart, int assLoopStart, int labLoopStart,
	int numOfQuiz, int numOfAss, int numOfLab,
	CP_Image quizSS, CP_Image assSS, CP_Image labSS);
void spawnWeekly(float totalElapsedTime, float timeToSpawn,
	int QuizLoopStart, int assLoopStart, int labLoopStart,
	int numOfQuiz, int numOfAss, int numOfLab,
	CP_Image quizSS, CP_Image assSS, CP_Image labSS);
void spawnBoss(float totalElapsedTime, float timeToSpawn, CP_Image BossSS);