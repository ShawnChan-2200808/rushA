/*!
@file       anim.h
@author		Shawn Chan Weng Kwang (shawnwengkwang.chan@digipen.edu)
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      Declaration of animation functions for player, enemy and boss.
*//*_________________________________________________________________________________*/
void updateEnemyAnimation(struct Enemy* enemy, float dt);
void enemyAnimation(CP_Image Spritesheet, struct Enemy* enemy);
void updatePlayerAnimation(struct Player* player, float dt);
void playerAnimation(CP_Image Spritesheet, struct Player* player);