#pragma once
void initGame();

void SpawnBG(CP_Image BG, int numberRow, int numberCol);

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

int isCircleEntered(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
