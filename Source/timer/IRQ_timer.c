/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "RIT/RIT.h"
#include <stdio.h> /*for sprintf*/
#include <string.h>
#include "configuration.h"
#include "CAN/CAN.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer for update pacman movement
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern Sprite player, blinky;
extern SCORE;
extern LIVES;
extern OPEN, CLOSED;
extern TIMER, SPAWN_TIME;
extern ghostMode;
extern ghostTimer;
extern respawnMode;
extern respawnTimer;
bool hard =false; 
bool invincibility = false;
int invTimer = 2;

void TIMER0_IRQHandler (void)
{

	if(LPC_TIM0->IR &1){
		UpdatePacman(&player);
		checkCollision(&blinky, &player, invincibility);
		updateBlinky(&blinky, &player);
		checkCollision(&blinky, &player, invincibility);

		LPC_TIM0->IR = 1;			/* clear interrupt flag */
	}else if(LPC_TIM0->IR & 2){
		UpdatePacman(&player);
		checkCollision(&blinky, &player, invincibility);
		//if hard mode blinky's speed incresed
		if(hard || respawnMode){
			updateBlinky(&blinky, &player);
			checkCollision(&blinky, &player, invincibility);
		}
		LPC_TIM0->IR = 2;			/* clear interrupt flag */
	}
	if(LIVES !=0){
	// CAN
	CAN_TxMsg.data[0] = (TIMER) & 0xFF;
	CAN_TxMsg.data[1] = (SCORE & 0xFF00 ) >> 8;
	CAN_TxMsg.data[2] = SCORE & 0xFF;
	CAN_TxMsg.data[3] = LIVES & 0xFF;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 1;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (2, &CAN_TxMsg);               /* transmit message */
	}
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer for updating game time, check if it's finished and insert power pills in random time
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	//power pill spawn  
	if(TIMER == SPAWN_TIME){
		insertPowerPill();
		SPAWN_TIME = rand() % TIMER;
	}
	//update freightening timer
	if(ghostMode){
		ghostTimer--;
		if(ghostTimer==0){
			ghostMode=false;
		}
	}
	
	if(respawnMode){
		if(respawnTimer==0){
			respawnMode=false;
		}
		respawnTimer--;
	}
	
	if(invincibility){
		if(invTimer==0){
			invincibility=false;
		}
		invTimer--;
	}
	
	//UPDATE TIMER
	TIMER--;

	if(TIMER==0){
		gameOver();
	}
	
	//after 30s set hard mode
	if(TIMER<=30){
		hard= true;
	}
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
#define VOLUME 1;

uint16_t SinTable[45] =                                      
{
    410/2, 467/2, 523/2, 576/2, 627/2, 673/2, 714/2, 749/2, 778/2,
    799/2, 813/2, 819/2, 817/2, 807/2, 789/2, 764/2, 732/2, 694/2,
    650/2, 602/2, 550/2, 495/2, 438/2, 381/2, 324/2, 270/2, 217/2,
    169/2, 125/2, 87/2, 55/2, 30/2, 12/2, 2/2, 0/2, 6/2,
    20/2, 41/2, 70/2, 105/2, 146/2, 193/2, 243/2, 297/2, 353/2
};

void TIMER2_IRQHandler (void)
{
	static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	currentValue = SinTable[sineticks];
	currentValue -= 410;
	currentValue /= 1;
	currentValue += 410;
	LPC_DAC->DACR = currentValue <<6;
	sineticks++;
	if(sineticks==45) sineticks=0;

	LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	disable_timer(2);
	LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
