/*******************************************************************************************************                         
**--------------File Info-------------------------------------------------------------------------------
** File name:			configurations.h
** Descriptions:		
**------------------------------------------------------------------------------------------------------
** Created by:			Federico ferrari
** Created date:		23-12-2024
** Version:					1.0
** Descriptions:		contains game's costants, Sprite struct definition and main game's function declarations
********************************************************************************************************/
#include <stdbool.h>
//DIRECTIONS
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

//Matrix
#define MAZE_COLUMNS 24
#define MAZE_ROWS 28

//HUD
#define SCORE_X 100
#define LIVES_X 200
#define TIME_X 10
#define TEXT_Y 280 // MAZE_ROWS*PIXEL_SIZE
#define STATS_Y 300 // TEXT_Y +20

typedef struct{
	int x;
	int y;
	int direction;
} Sprite;

void insertPowerPill();
void UpdatePacman(Sprite *player);
void updateBlinky(Sprite *blinky, Sprite *pacman);
void Sprite_setDirection(Sprite *player, int direction);
void Sprite_setXY(Sprite *player, int x, int y);
void checkVictory();
void checkNewLife();
bool Teleport(Sprite *player, bool isPacman);
void checkPills(int nextX, int nextY);
void gameOver();
void handlePause();
void checkMode();
bool checkCollision(Sprite *blinky, Sprite *pacman, bool inv);

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/