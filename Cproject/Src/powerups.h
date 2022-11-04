/*!
@file       powerups.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       25/10/2022 (last updated)
@brief      contains Declarations of Player functions
*//*_________________________________________________________________________________*/
struct Item {
	CP_Vector position;
	float Width;
	float Height;
	int isActive;
	float timer;
	int Modifier;

	//animation
	int animationSpeed, currentFrame, animTotalFrames;
	float worldSizeW, worldSizeH, spriteWidth, SpriteHeight,
		animationElapsedTime, displayTime;
}; struct Item bbt, coffee, snacks;
void itemInit(struct Item* item, float posX, float posY, float width, float height, float mod);
void playerHeal(struct Item* item, struct Player* player);
void playerSpeedUp(struct Item* item, struct Player* player);
void coolDown(struct Item* item, float deltatime);
void respawnItem(struct Item* item/*, float posX, float posY*/);
