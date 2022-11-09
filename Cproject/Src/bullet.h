struct Bullet
{
    CP_Vector Pos, Vector;
    int active, diameter, damage;
    float velocity;
}; struct Bullet bullets[10];
int bulletIndex;
void bulletReset( int index);
void bulletInit(int index, struct Player* player);
void bulletUpdate(int index, float deltaTime, int numOfQuiz, int numOfAssLab);