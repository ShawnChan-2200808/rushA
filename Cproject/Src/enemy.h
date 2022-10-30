void quizInit(struct Enemy* quiz,float posX,float posY);
void assInit(struct Enemy* quiz, float posX, float posY);
void labInit(struct Enemy* quiz, float posX, float posY);
void isEnemyAlive(struct Enemy* enemy);
void enemyChase(struct Enemy* enemy, struct Player* player);
void damagePlayer(struct Enemy* enemy, struct Player* player);