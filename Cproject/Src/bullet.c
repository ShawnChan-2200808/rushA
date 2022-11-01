#include "CProcessing.h"
#include "bullet.h"

extern struct Enemy {
    CP_Vector EnemyPos, tempPos, direction;
    CP_Vector weaponPos;
    int speed, alive;
    float HP, damage;
    //animation
    int animationSpeed, currentFrame, animTotalFrames;
    float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
        animationElapsedTime, displayTime;

}; extern struct Enemy quiz1, lab1, assignment1;

float hitCircleSize, deltaTime;

// reference to player
extern struct Player {
    CP_Vector playerPos, tempPos, direction;
    CP_Vector weaponPos, bulletPos;
    int speed, alive, damage, weapon, attacking, ammo;
    float GPA, timer, projVelocity;

    //animation
    int animationSpeed, currentFrame, animTotalFrames;
    float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
        animationElapsedTime, displayTime;
}; extern struct Player player;

void bulletInit(struct Bullet* currentBullet)
{
    (*currentBullet).Pos = player.playerPos;
    (*currentBullet).active = 0;
    (*currentBullet).ready = 1;
    (*currentBullet).Vector = player.playerPos;
    (*currentBullet).velocity = 0;
}

void updatePosition(struct Bullet* currentBullet)
{
    if ((*currentBullet).active == 1)
    {
        (*currentBullet).Vector.x = (CP_Input_GetMouseX() - player.playerPos.x);
        (*currentBullet).Vector.y = (CP_Input_GetMouseY() - player.playerPos.y);
        (*currentBullet).Vector = CP_Vector_Normalize((*currentBullet).Vector);
        (*currentBullet).Vector = CP_Vector_Scale((*currentBullet).Pos, currentBullet->velocity * deltaTime);
        (*currentBullet).Pos = CP_Vector_Add((*currentBullet).Pos, (*currentBullet).Vector);
    }
}

void drawBullet(struct Bullet* currentBullet)
{
    if ((*currentBullet).active == 1)
    {
        CP_Settings_Fill(CP_Color_Create(255,0,0,255));
        CP_Graphics_DrawCircle((*currentBullet).Pos.x, (*currentBullet).Pos.y, 20);
    }
}


