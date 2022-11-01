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

void drawBullet(struct Bullet* currentBullet)
{
    if ((&bullets[i]).active == 1)
    {
        CP_Settings_Fill(CP_Color_Create(255,0,0,255));
        CP_Graphics_DrawCircle((&bullets[i]).Pos.x, (&bullets[i]).Pos.y, 20);
    }
}


