/*******************************************************************************************************                         
**--------------File Info-------------------------------------------------------------------------------
** File name:			game_graphics.h
** Descriptions:		
**------------------------------------------------------------------------------------------------------
** Created by:			Federico ferrari
** Created date:		23-12-2024
** Version:					1.0
** Descriptions:		main game graphic function declarations
********************************************************************************************************/

void DrawMaze();
void DrawPowerPill(int x, int y);
void DrawPixel(int x, int y, int color);
void DrawPacman(int x, int y);
void DrawPause();
void EreasePause();
void RestoreMaze(int x, int y);
void DrawBlinky(int x, int y, int color);
void updateLifeHUD(int lives);
void updateScoreHUD(int score);
void updateTimeHUD(int time);
void DrawGameOver();