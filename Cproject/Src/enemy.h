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
	int speed, alive, inGame;
	float hitCircle;
	float HP, damage;
	CP_Vector spawnPos1, spawnPos2, spawnPos3, spawnPos4;
	float timer;
	int flag1;
	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
	//Laser Variables
	int intlaserTime,rotation;
	CP_Color lasercolour, lasercolourchargeup;
	float laserB, laserL, laserh, laserw, transparency, floatlaserTime;
	//Bullet Struct
	struct enemyBullet
	{
		CP_Vector Pos, Vector;
		int active, diameter;
		float velocity, bulletTimer,damage;
	} enemyBullets[10];
	//Bullet Variables
	int bulletIndex,intbulletTime,indivBullet;
	float floatbulletTime;

	//collision
	CP_Vector enemymin, enemymax;
	float hitboxX, hitboxY;
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
int playerbulletDamage(struct Enemy* enemy, struct playerBullet bullet, float hitboxX, float hitboxY, int totalFrames);
int enemybulletDamage(struct Enemy* enemy,struct Player* player, struct enemyBullet bullet);
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