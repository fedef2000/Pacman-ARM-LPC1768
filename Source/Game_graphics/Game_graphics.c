/*******************************************************************************************************                         
**--------------File Info-------------------------------------------------------------------------------
** File name:			Game_graphics.c
** Descriptions:		
**------------------------------------------------------------------------------------------------------
** Created by:			Federico ferrari
** Created date:		23-12-2024
** Version:					1.0
** Descriptions:		contains functions for drawing all the game's objects
********************************************************************************************************/
#include "GLCD.h"
#include "configuration.h"
#include <inttypes.h>
#define PIXEL_SIZE 10

//GAME VARIABLES AND COSTANTS
extern int SCORE, LIVES, TIMER, MAX_SCORE;
extern SCORE_THRESHOLD;
extern int Matrix[];

/******************************************************************************
* Function Name  : DrawPixel
* Description    : Given x and y coordinates in the matrix, draws a square of PIXEL_SIZE size with the given color
* Input          : x - x-coordinate in the matrix
*                 y - y-coordinate in the matrix
*                 color - color value for the pixel
* Output         : None
* Return         : None
*******************************************************************************/
void DrawPixel(int x, int y, int color)
{
	x = x*PIXEL_SIZE;
	y = y*PIXEL_SIZE;
	int i, j;
	for(i=0; i<PIXEL_SIZE; i++){
		for(j=0; j<PIXEL_SIZE; j++){
				LCD_SetPoint(x + i, j + y, color);
		}
	}
}

/******************************************************************************
* Function Name  : DrawPill
* Description    : Draws a 2x2 white pill at specified coordinates for Pacman to collect
* Input          : x - x-coordinate on LCD
*                 y - y-coordinate on LCD
* Output         : None
* Return         : None
*******************************************************************************/
void DrawPill(int x, int y)
{
	x=x*PIXEL_SIZE;
	y=y*PIXEL_SIZE;
	LCD_SetPoint(x + 4, y + 4, White);
	LCD_SetPoint(x + 4, y + 5, White);
	LCD_SetPoint(x + 5, y + 4, White);
	LCD_SetPoint(x + 5, y + 5, White);
}

/******************************************************************************
* Function Name  : DrawPowerPill
* Description    : Draws a 4x4 red power pill at specified coordinates
* Input          : x - x-coordinate on LCD
*                 y - y-coordinate on LCD
* Output         : None
* Return         : None
*******************************************************************************/
void DrawPowerPill(int x, int y)
{
	x=x*PIXEL_SIZE;
	y=y*PIXEL_SIZE;
	
    // Left dome of pill
    LCD_SetPoint(x + 2, y + 3, Red);
    LCD_SetPoint(x + 1, y + 4, Red);
    LCD_SetPoint(x + 1, y + 5, Red);
    LCD_SetPoint(x + 2, y + 6, Red);
    uint16_t i;
    // Main body of pill
    for(i = 3; i <= 6; i++) {
        LCD_SetPoint(x + 2, y + i, Red);
        LCD_SetPoint(x + 3, y + i, Red);
        LCD_SetPoint(x + 4, y + i, Red);
        LCD_SetPoint(x + 5, y + i, Red);
        LCD_SetPoint(x + 6, y + i, Red);
        LCD_SetPoint(x + 7, y + i, Red);
    }
    
    // Right dome of pill
    LCD_SetPoint(x + 7, y + 3, Red);
    LCD_SetPoint(x + 8, y + 4, Red);
    LCD_SetPoint(x + 8, y + 5, Red);
    LCD_SetPoint(x + 7, y + 6, Red);
    
    // White highlight (to give 3D effect)
    LCD_SetPoint(x + 2, y + 3, White);
    LCD_SetPoint(x + 3, y + 3, White);
    LCD_SetPoint(x + 4, y + 3, White);
}

/******************************************************************************
* Function Name  : DrawMaze
* Description    : Draws the complete Pacman maze using the Matrix array
*                 Matrix values: 1=wall, 2=pill, 3=power pill
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DrawMaze()
{
	volatile int x,y, i, j;
	for(i=0; i<MAZE_ROWS*MAZE_COLUMNS; i++){
		x = i%MAZE_COLUMNS;
		y = i/MAZE_COLUMNS;
		if(Matrix[i] == 1){			
			DrawPixel(x, y, Blue);
		}else if(Matrix[i]==2){
			DrawPill(x, y);
		}else if(Matrix[i]==3){
			DrawPowerPill(x, y);
		}
	}
}

/******************************************************************************
* Function Name  : DrawPacman
* Description    : Draws a 10x10 yellow circle representing Pacman at specified coordinates
* Input          : x - x-coordinate in matrix
*                 y - y-coordinate in matrix
* Output         : None
* Return         : None
*******************************************************************************/
extern bool invincibility;
void DrawPacman(int x, int y){
	x = x*PIXEL_SIZE;
	y = y*PIXEL_SIZE;
	LCD_DrawCirle(x, y, Yellow);	
}

/******************************************************************************
* Function Name  : DrawPause
* Description    : Displays "PAUSE" text in black color on red background
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DrawPause(){
	DrawPixel(7, 12, Red);
	DrawPixel(8, 12, Red);
	DrawPixel(9, 12, Red);
	DrawPixel(10, 12, Red);
	DrawPixel(11, 12, Red);
	DrawPixel(12, 12, Red);
	DrawPixel(13, 12, Red);
	DrawPixel(14, 12, Red);
	
	DrawPixel(7, 13, Red);
	DrawPixel(8, 13, Red);
	DrawPixel(9, 13, Red);
	DrawPixel(10, 13, Red);
	DrawPixel(11, 13, Red);
	DrawPixel(12, 13, Red);
	DrawPixel(13, 13, Red);
	DrawPixel(14, 13, Red);
	
	DrawPixel(7, 14, Red);
	DrawPixel(8, 14, Red);
	DrawPixel(9, 14, Red);
	DrawPixel(10, 14, Red);
	DrawPixel(11, 14, Red);
	DrawPixel(12, 14, Red);
	DrawPixel(13, 14, Red);
	DrawPixel(14, 14, Red);
	GUI_Text(90, 125, (uint8_t *) "PAUSE", Black, Red);
}

/******************************************************************************
* Function Name  : EreasePause
* Description    : Erases the pause text by drawing black rectangles over specified area
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EreasePause(){
	DrawPixel(7, 12, Black);
	DrawPixel(8, 12, Black);
	DrawPixel(9, 12, Black);
	DrawPixel(10, 12, Black);
	DrawPixel(11, 12, Black);
	DrawPixel(12, 12, Black);
	DrawPixel(13, 12, Black);
	DrawPixel(14, 12, Black);
	
	DrawPixel(7, 13, Black);
	DrawPixel(8, 13, Black);
	DrawPixel(9, 13, Black);
	DrawPixel(10, 13, Black);
	DrawPixel(11, 13, Black);
	DrawPixel(12, 13, Black);
	DrawPixel(13, 13, Black);
	DrawPixel(14, 13, Black);
	
	DrawPixel(7, 14, Black);
	DrawPixel(8, 14, Black);
	DrawPixel(9, 14, Black);
	DrawPixel(10, 14, Black);
	DrawPixel(11, 14, Black);
	DrawPixel(12, 14, Black);
	DrawPixel(13, 14, Black);
	DrawPixel(14, 14, Black);
}

/******************************************************************************
* Function Name  : updateLifeHUD
* Description    : update life counter shown on screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void updateLifeHUD(int lives){
 	char result[12];
 	snprintf(result, sizeof(result), "%d%s", lives, " ");
 	GUI_Text(LIVES_X, STATS_Y, (uint8_t *) result, White, Black);
}

/******************************************************************************
* Function Name  : updateScoreHUD
* Description    : update score counter shown on screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void updateScoreHUD(int score){
 	char result[12];
 	snprintf(result, sizeof(result), "%d%s", score, " ");
 	GUI_Text(SCORE_X, STATS_Y, (uint8_t *) result, White, Black);
}

/******************************************************************************
* Function Name  : updateTimeHUD
* Description    : update time counter shown on screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void updateTimeHUD(int time){
 	char result[20];
	snprintf(result, sizeof(result), "%d%s", time, "s ");
	GUI_Text(TIME_X, STATS_Y, (uint8_t *) result, White, Black);
}

/******************************************************************************
* Function Name  : DrawVictory
* Description    : Displays "Victory" text in yellow color
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void drawVictory(){
	GUI_Text(80, 125, (uint8_t *) "Victory!", Yellow, Black);
}

void RestoreMaze(int x, int y){
	int index = y*MAZE_COLUMNS + x;
	DrawPixel(x, y, Black);
	if(Matrix[index]==2){
		DrawPill(x, y);
	}else if(Matrix[index]==3){
		DrawPowerPill(x, y);
	}
}

extern bool respawnMode;
void DrawBlinky(int x, int y, int color){
	x = x*PIXEL_SIZE;
	y = y*PIXEL_SIZE;
	if(respawnMode){
		LCD_DrawEyes(x, y, color);
	}else{
		LCD_DrawGhost(x, y, color);
	}
}

void DrawGameOver() {
	LCD_Clear(Black);
 	GUI_Text(80, 130, (uint8_t *) "   GAME   ", Red, Black);
	GUI_Text(80, 145, (uint8_t *) "   OVER   ", Red, Black);
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/