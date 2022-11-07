#include "CProcessing.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"

void bulletReset(int index) {
	for (index = 0; index < 10; ++index)
	{
		bullets[index].active = 0;
		bullets[index].velocity = 0;
	}
}


void bulletInit(int index, struct Player *player) {
	for (index = 0; index < 10; ++index)
	{
		if (bullets[index].active == 0)
		{
			bullets[index].active = 1;
			bullets[index].velocity = 1000;
			bullets[index].diameter = 20;
			bullets[index].damage = 100;
			bullets[index].Pos = (*player).playerPos;
			bullets[index].Vector = CP_Vector_Set((CP_Input_GetMouseX() - (*player).playerPos.x), (CP_Input_GetMouseY() - (*player).playerPos.y));
			bullets[index].Vector = CP_Vector_Normalize(bullets[index].Vector);
			bullets[index].Vector = CP_Vector_Scale(bullets[index].Vector, bullets[index].velocity);
			break;
		}
	}
}

void bulletUpdate(int index,float deltaTime, int numOfQuiz,int numOfAssLab) {
	for (index = 0; index < 10; ++index)
	{
		if (bullets[index].active == 1)
		{
			bullets[index].Pos.x += bullets[index].Vector.x * deltaTime;
			bullets[index].Pos.y += bullets[index].Vector.y * deltaTime;
			if (bullets[index].Pos.x < 0 || bullets[index].Pos.x >= CP_System_GetWindowWidth() || bullets[index].Pos.y < 0 || bullets[index].Pos.y >= CP_System_GetWindowHeight())
			{
				bullets[index].active = 0;
			}
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawCircle(bullets[index].Pos.x, bullets[index].Pos.y, bullets[index].diameter);
			// need to update
			for (int i = 0; i < numOfQuiz; i++)
			{
				if (bulletDamage(&quiz[i], bullets[index], 130, 130) == 1)
				{
					bullets[index].active = 0;
				}
			}
			for (int i = 0; i < numOfAssLab; i++)
			{
				if (bulletDamage(&assignment[i], bullets[index], 130, 130) == 1)
				{
					bullets[index].active = 0;
				}
				if (bulletDamage(&lab[i], bullets[index], 130, 130) == 1)
				{
					bullets[index].active = 0;
				}
			}
		}

	}
}

