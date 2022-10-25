void playerInit(struct Player* player);
void isPlayerAlive(struct Player* player);
void moveForward(struct Player* player, CP_Vector direction);
void moveBack(struct Player* player, CP_Vector direction);
void meleeVec(struct Player* player);
int switchWeapon(int weapon);