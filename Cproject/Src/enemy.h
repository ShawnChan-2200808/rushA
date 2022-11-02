/*!
@file       enemy.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains declarations of Enemy functions
*//*_________________________________________________________________________________*/
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