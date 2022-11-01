struct Bullet
{
    CP_Vector Pos, Vector;
    int velocity, active, ready;
};

void bulletInit(struct Bullet* currentBullet);
void updatePosition(struct Bullet* currentBullet);
void drawBullet(struct Bullet* currentBullet);
