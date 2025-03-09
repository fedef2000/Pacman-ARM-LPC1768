/*******************************************************************************************************                         
**--------------File Info-------------------------------------------------------------------------------
** File name:			configurations.c
** Descriptions:		
**------------------------------------------------------------------------------------------------------
** Created by:			Federico ferrari
** Created date:		23-12-2024
** Version:					1.0
** Descriptions:		contains game's variables and main game's function definitions
********************************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "configuration.h"
#include "GLCD.h"
int Matrix[672] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
    1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1,
    1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0, 0,
    1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1,
		0, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 2, 0,
    1, 1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 2, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 2, 1, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1,
    1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1,
    1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1,
    1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1,
    1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};


Sprite player, blinky;
bool ghostMode = false;
int ghostTimer=1;
bool respawnMode = false;
int respawnTimer = 3;
bool collision = false;
bool gameOverBool = false;

//Game Variables
int SCORE = 0;
int NUMBER_OF_PILLS = 240;
int MAX_POWER_PILLS=6;
int pills_indicies[240];
int SPAWN_TIME;
int LIVES = 1;
uint16_t TIMER = 60;
int SCORE_THRESHOLD=1000; // one life each 1000 points
bool PAUSE = true;

/******************************************************************************
* Function Name  : insertPowerPill
* Description    : Randomly places a power pill at a location containing a normal pill,
*                 up to a maximum defined by MAX_POWER_PILLS
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void insertPowerPill(){
   static int spawned = 0;
   if(spawned>=MAX_POWER_PILLS) return;
   
   int i, j=0;
   for(i=0; i<MAZE_COLUMNS*MAZE_ROWS; i++){
   	if(Matrix[i] == 2){
   		pills_indicies[j] = i;
   		j++;
   		//if(j==NUMBER_OF_PILLS) break;
   	}
   }
   int randomIndex = rand() % (j + 1);
   int index = pills_indicies[randomIndex];
   Matrix[index] = 3 ;
   spawned++;
   
   //Draw new power pill
   int x = index%MAZE_COLUMNS;
   int y = index/MAZE_COLUMNS;
   DrawPowerPill(x, y);
}

/******************************************************************************
* Function Name  : UpdatePacman
* Description    : Updates Pacman's position based on current direction, handles
*                 collisions, teleporting, and pill collection
* Input          : player - Pointer to Pacman structure
* Output         : None
* Return         : None
*******************************************************************************/
void UpdatePacman(Sprite *player)
{
   bool teleport = Teleport(player, true);
   if(teleport) return;
   
   int oldX = (*player).x;
   int oldY = (*player).y;
   
   volatile int nextX, nextY;
   if((*player).direction==NORTH){
   	nextX=(*player).x;
   	nextY=(*player).y-1;
   }else if((*player).direction==SOUTH){
   	nextX=(*player).x;
   	nextY=(*player).y+1;
   }else if((*player).direction==EAST){
   	nextX=(*player).x+1;
   	nextY=(*player).y;	
   }else if((*player).direction==WEST){
   	nextX=(*player).x-1;
   	nextY=(*player).y;
   }
   if(Matrix[nextX+MAZE_COLUMNS*nextY]==1) return; //if there's a wall then return
   
   Sprite_setXY(player, nextX, nextY);
   
   checkPills(nextX, nextY);
   checkNewLife();
   checkVictory();
   
   //EREASE PACMAN FROM OLD POSITION
   DrawPixel(oldX, oldY, Black);
   //DRAW PACMAN IN NEW POSITION
   DrawPacman(nextX, nextY);
}

/******************************************************************************
* Function Name  : Sprite_setXY
* Description    : Updates Sprite's position coordinates
* Input          : player - Pointer to Sprite structure
*                 x - New x coordinate
*                 y - New y coordinate
* Output         : None
* Return         : None
*******************************************************************************/
void Sprite_setXY(Sprite *player, int x, int y){
   (*player).x = x;
   (*player).y = y;
}

/******************************************************************************
* Function Name  : Sprite_setDirection
* Description    : Updates Sprite's movement direction
* Input          : player - Pointer to Sprite structure
*                 direction - New direction (NORTH, SOUTH, EAST, WEST)
* Output         : None
* Return         : None
*******************************************************************************/
void Sprite_setDirection(Sprite *player, int direction){
   (*player).direction = direction;
}

/******************************************************************************
* Function Name  : Teleport
* Description    : Checks if Sprite should teleport at maze edges (y=12, x=0 or x=23)
* Input          : player - Pointer to Sprite structure
* Output         : None
* Return         : true if teleported, false otherwise
*******************************************************************************/
bool Teleport(Sprite *sprite, bool isPacman){
   if((*sprite).y==12){
   	if((*sprite).x==0 && (*sprite).direction==WEST){
   		DrawPixel((*sprite).x, (*sprite).y, Black);
   		(*sprite).x=23;
			if(isPacman){
				DrawPacman(23, 12);
			}else{
				DrawBlinky(23, 12);
			} 
   		return true;
   	}else if((*sprite).x==23 && (*sprite).direction==EAST){
   		DrawPixel((*sprite).x, (*sprite).y, Black);
   		(*sprite).x=0;
			if(isPacman){
				DrawPacman(0, 12);
			}else{
				if(ghostMode){
					DrawBlinky(0, 12, Cyan);
				}else{
					DrawBlinky(0, 12, Red);
				}
			} 
   		return true;
   	}
   }
   return false;
}

/******************************************************************************
* Function Name  : checkVictory
* Description    : Checks if all pills have been collected and stops game timers
*                 if victory condition is met
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void checkVictory(){
   //CHECK VICTORY
   if(NUMBER_OF_PILLS==0){
   	disable_timer(1);
   	disable_timer(0);
   	disable_RIT();
		drawVictory();
   }
}

/******************************************************************************
* Function Name  : checkNewLife
* Description    : Awards extra life when score reaches threshold and updates
*                 lives display
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void checkNewLife(){
   if(SCORE/SCORE_THRESHOLD==1){
   	SCORE_THRESHOLD+=1000;
   	LIVES++;
		//updateLifeHUD();
   }
}

/******************************************************************************
* Function Name  : checkPills
* Description    : Checks if Pacman collected a pill or power pill at given
*                 coordinates and updates score accordingly
* Input          : nextX - x coordinate to check
*                 nextY - y coordinate to check
* Output         : None
* Return         : None
*******************************************************************************/
void checkPills(int nextX, int nextY){
   if(Matrix[nextX+MAZE_COLUMNS*nextY]==2){ //NORMAL PILL
   	NUMBER_OF_PILLS--;
   	SCORE += 10;
   	Matrix[nextX+MAZE_COLUMNS*nextY]=0;
		//updateScoreHUD();
   }else if(Matrix[nextX+MAZE_COLUMNS*nextY]==3){ //POWER PILL
		if(!respawnMode){
			ghostMode = true;
			ghostTimer = 10;
   	}
		NUMBER_OF_PILLS--;
   	SCORE += 50;
   	Matrix[nextX+MAZE_COLUMNS*nextY]=0;
   	//updateScoreHUD();
   }
}


/******************************************************************************
* Function Name  : gameOver
* Description    : called when time's finished, stops timers
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void gameOver(){
	disable_timer(1);
	disable_timer(0);
	//disable_RIT();
	gameOverBool=true;
	DrawGameOver();
}

/******************************************************************************
* Function Name  : handlePause
* Description    : Toggles game pause state, enables/disables timers and updates
*                  pause display accordingly
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern bool gameNotStarted;
void handlePause(){
	if(PAUSE){
		enable_timer(0);
		enable_timer(1);
		EreasePause();
		PAUSE=false;
		gameNotStarted=false;
	}else{
		disable_timer(0);
		disable_timer(1);
		DrawPause();	
		PAUSE=true;
	}
}

void updateBlinky(Sprite *blinky, Sprite *pacman){
	int target_x = (*pacman).x;
	int target_y = (*pacman).y;
	int oldX = (*blinky).x;
	int oldY = (*blinky).y;
	
	bool teleport = Teleport(blinky, false);
	if(teleport) return;
	
	//AVOID BLINKY TO STALL IN CENTRAL BOX
	if((*blinky).x<=14 && (*blinky).x>=7 && (*blinky).y<=14 && (*blinky).y>=11){
		target_x= 10;
		target_y= 10;
	}
	
	if(respawnMode){
		target_x= 10;
		target_y= 12;
	}
	
	if((*blinky).y==12 && (*blinky).x==10 && respawnMode){
		//return;
	}

	
	volatile bool n=true, s=true, e=true, w=true;
	volatile float n_dist, s_dist, e_dist, w_dist;
	//Avoid to go in the central box
	if(((*blinky).x<=14 && (*blinky).x>=7 && (*blinky).y==10) && !respawnMode){ //add and to assure that pacman is not in the box
		s=false;
	}
	
	//avoid opposite direction
	if((*blinky).direction==NORTH) s=false;
	if((*blinky).direction==SOUTH) n=false;
	if((*blinky).direction==WEST) e=false;
	if((*blinky).direction==EAST) w=false;
	//avoid walls
	if(Matrix[(*blinky).x+MAZE_COLUMNS*((*blinky).y-1)]==1) n=false;
	if(Matrix[(*blinky).x+MAZE_COLUMNS*((*blinky).y+1)]==1) s=false;
	if(Matrix[((*blinky).x+1)+MAZE_COLUMNS*(*blinky).y]==1) e=false;
	if(Matrix[((*blinky).x-1)+MAZE_COLUMNS*(*blinky).y]==1) w=false;

	//CHASE MODE
	if(!ghostMode){
	if(!n){ n_dist=FLT_MAX;}
	else{
		n_dist = sqrt(pow(target_x-((*blinky).x),2)+ pow(target_y-((*blinky).y-1), 2));
	}
	if(!s){ s_dist=FLT_MAX;}
	else{
		s_dist = sqrt(pow(target_x-((*blinky).x),2)+ pow(target_y-((*blinky).y+1), 2));
	}
	if(!w){ w_dist=FLT_MAX;}
	else{
		w_dist = sqrt(pow(target_x-((*blinky).x-1),2)+ pow(target_y-((*blinky).y), 2));
	}
	if(!e){ e_dist=FLT_MAX;}
	else{
		e_dist = sqrt(pow(target_x-((*blinky).x+1),2)+ pow(target_y-((*blinky).y), 2));
	}
	//search min distance
	float min = FLT_MAX;
	if(n_dist<min){
		min=n_dist;
	}
	if(s_dist<min){
		min=s_dist;
	}
	if(e_dist<min){
		min=e_dist;
	}
	if(w_dist<min){
		min=w_dist;
	}
	//set new direction
	if(n_dist==min){
		Sprite_setDirection(blinky, NORTH);
	}
	if(s_dist==min){
		Sprite_setDirection(blinky, SOUTH);
	}
	if(e_dist==min){
		Sprite_setDirection(blinky, EAST);
	}
	if(w_dist==min){
		Sprite_setDirection(blinky, WEST);
	}
	
	
	//GHOSTMODE
	}else{
	if(!n){ n_dist=-1;}
	else{
		n_dist = sqrt(pow(target_x-((*blinky).x),2)+ pow(target_y-((*blinky).y-1), 2));
	}
	if(!s){ s_dist=-1;}
	else{
		s_dist = sqrt(pow(target_x-((*blinky).x),2)+ pow(target_y-((*blinky).y+1), 2));
	}
	if(!w){ w_dist=-1;}
	else{
		w_dist = sqrt(pow(target_x-((*blinky).x-1),2)+ pow(target_y-((*blinky).y), 2));
	}
	if(!e){ e_dist=-1;}
	else{
		e_dist = sqrt(pow(target_x-((*blinky).x+1),2)+ pow(target_y-((*blinky).y), 2));
	}
	//search max distance
	float max = -1;
	if(n_dist>max){
		max=n_dist;
	}
	if(s_dist>max){
		max=s_dist;
	}
	if(e_dist>max){
		max=e_dist;
	}
	if(w_dist>max){
		max=w_dist;
	}
	//set new direction
	if(n_dist==max){
		Sprite_setDirection(blinky, NORTH);
	}
	if(s_dist==max){
		Sprite_setDirection(blinky, SOUTH);
	}
	if(e_dist==max){
		Sprite_setDirection(blinky, EAST);
	}
	if(w_dist==max){
		Sprite_setDirection(blinky, WEST);
	}	
	}

	volatile int newX, newY;
	if((*blinky).direction==NORTH){
		newX=(*blinky).x;
		newY=(*blinky).y-1;
	}else if((*blinky).direction==SOUTH){
		newX=(*blinky).x;
		newY=(*blinky).y+1;
	}else if((*blinky).direction==EAST){
		newX=(*blinky).x+1;
		newY=(*blinky).y;	
	}else if((*blinky).direction==WEST){
		newX=(*blinky).x-1;
		newY=(*blinky).y;
	}

	Sprite_setXY(blinky, newX, newY);
	
	//RESTORE MAZE IN OLD POSITION
	if(oldX==(*pacman).x && oldY==(*pacman).y){
		//DrawPacman(oldX,oldY);
	}else{
		RestoreMaze(oldX, oldY);
	}
	//DRAW BLINKY IN NEW POSITION
	if(ghostMode){
		DrawBlinky(newX, newY, Cyan);
	}else{
		DrawBlinky(newX, newY, Red);
	}
}
extern bool invincibility;
extern int invTimer;
bool checkCollision(Sprite *blinky, Sprite *pacman, bool inv){
	if(inv || respawnMode) return false;
	if((*blinky).x == (*pacman).x && (*blinky).y==(*pacman).y){
		if(ghostMode){	
			//(*blinky).x=10;
			//(*blinky).y=14;
			SCORE += 100;
			//updateScoreHUD();
			checkNewLife();
			ghostMode = false;
			respawnMode = true;
			respawnTimer = 7;
		}else{
			LIVES--;
			invincibility=true;
			invTimer = 1;
			(*pacman).x=11;
			(*pacman).y=16;
			(*pacman).direction=SOUTH;
			DrawPacman((*pacman).x,(*pacman).y);
			collision=true;
			if(LIVES==0){
				gameOver();
			}
		}
		return true;
	}
	return false;
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/