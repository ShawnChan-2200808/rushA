/*!
@file       weapons.h
@course     csd1401 Software Engineering Project
@section    A
@team		RushA
@date       31/10/2022 (last updated)
@brief      contains declarations of Weapon functions
*//*_________________________________________________________________________________*/




//Returns 4 states:
// 1: For when laser is tracking player
// 2: For when laser is charging up
// 3: For when laser is firing but player is not being damaged
// 4: For when laser is firing & player is being damaged
int laser(struct Enemy* enemy, struct Player* player);

//Bullets
void bulletReset(int index);
void bulletInit(int index, struct Player* player);
void bulletUpdate(int index, float deltaTime, int numOfQuiz, int numOfAssLab);