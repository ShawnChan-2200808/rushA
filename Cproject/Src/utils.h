#pragma once


int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

int isCircleEntered(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

void moveForward(struct Player* player, CP_Vector direction);
void moveBack(struct Player* player, CP_Vector direction);
void enemyChase(struct Enemy* enemy, struct Player* player);
