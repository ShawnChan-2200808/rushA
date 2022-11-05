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



