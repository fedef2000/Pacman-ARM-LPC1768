/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               sample.c
** Descriptions:            
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Federico Ferrari
** Modified date:           23/12/2024
** Version:                 v2.0
** Descriptions:            Pacman game
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "button.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Configurations/configuration.h"
#include "game_graphics.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

extern SPAWN_TIME;
extern TIMER;
extern LIVES;
extern Sprite player, blinky;
bool gameNotStarted = true;

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	//srand(time(NULL));
	srand(1200);
	player.x = 11;
	player.y = 16;
	player.direction = EAST;
	blinky.x = 10;
	blinky.y =14;
	blinky.direction = NORTH;
	SPAWN_TIME = rand() % TIMER + 1;
		
  LCD_Initialization();
	LCD_Clear(Black);
	joystick_init();

	init_RIT(0x002C4B40); 
	init_timer(1, 0x17D7840);	
	init_timer(0, 0x4FFFFF); 						    

	
	DrawMaze();
	insertPowerPill();
	DrawPacman(player.x, player.y);
	DrawBlinky(blinky.x, blinky.y, Red);
	
	//TIME HUD
	GUI_Text(5, TEXT_Y, (uint8_t *) "TIME", White, Black);
	updateTimeHUD(TIMER);
	
	//SCORE HUD
	GUI_Text(90, TEXT_Y, (uint8_t *) "Score", White, Black);
	GUI_Text(SCORE_X, STATS_Y, (uint8_t *) "0", White, Black);
		
	//LIVES HUD
	GUI_Text(190, TEXT_Y, (uint8_t *) "Lives", White, Black);
	updateLifeHUD(LIVES);
		
	GUI_Text(70, 120, (uint8_t *) "PRESS INT0", Yellow, Black);
	GUI_Text(70, 134, (uint8_t *) " TO START ", Yellow, Black);

	BUTTON_init();
	CAN_Init();
	ADC_init();
  enable_RIT();	


	LPC_SC->PCON |= 0x1;				
	LPC_SC->PCON &= ~(0x2);						
	
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);

	while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
