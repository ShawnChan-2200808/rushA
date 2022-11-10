

CP_Image playerSS;
CP_Image QuizSS;
CP_Image AssSS;
CP_Image LabSS;
CP_Image Floor;
CP_Image bbtSS;
CP_Image BossSS;
CP_Image hitBox;
void initGame();
void SpawnBG(CP_Image BG, int numberRow, int numberCol);
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int isCircleEntered(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int IsRectEntered(float area_corner_x, float area_corner_y, float area_width, float area_height, float object_x, float object_y);

float enemyPlayerAngle(struct Enemy* enemy, struct Player* player);

int isRectEnteredadvanced(float	laserX, float laserY, float laserW, float laserH, int rotation, struct Player* player);

