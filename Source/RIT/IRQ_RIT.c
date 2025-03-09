/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage joystick polling and button de-bouncing
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "timer.h"
#include "GLCD.h"
#include "configuration.h"
#include <stdbool.h>
#include "music.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1
extern bool gameOverBool;

NOTE collision_sound[] = {
	{c3b, time_semibreve},
	{a2b, time_three_quarters},
};

NOTE gameover_music[] = {
    // Initial dramatic notes
    {b4, time_semicroma},
    {a4, time_semicroma},
    {g4, time_semiminima},
    
    // Sad descending pattern
    {f4, time_semicroma},
    {e4, time_semicroma},
    {d4, time_semicroma},
    {c4, time_semiminima},
    
    // Final dramatic notes
    {b3, time_semicroma},
    {a3, time_semicroma},
    {g3, time_minima},
    
    // Optional "bloop" ending
    {b2, time_three_quarters}
};

NOTE intro_music[] = {
{e3, time_semiminima},
{a3, time_semiminima}        ,
{b3, time_semiminima}        ,
{c3, time_semiminima}        ,
{a3, time_three_quarters}    ,
{pause, time_semiminima},
{e3, time_semiminima},
{a3, time_semiminima},
{b3, time_semiminima},
{c3, time_semiminima},
{a3,  time_three_quarters}    ,
{pause, time_semiminima    },
{e3, time_semiminima}        ,
{a3, time_semiminima}        ,
{b3, time_semiminima}        ,
{c3, time_minima            }    ,
{b3, time_semiminima}        ,
{a3, time_semiminima}        ,
{c3, time_minima            }    ,
{b3, time_semiminima}        ,
{a3, time_semiminima}        ,
{e4, time_minima       }         ,
{e4, time_minima        }        ,
{e4, time_semiminima   }    ,
{e4, time_semiminima   }    ,
{d4, time_semiminima   }    ,
{e4, time_semiminima   }    ,
{f4, time_semiminima   }    ,
{f4, time_three_quarters           }         ,
{pause, time_semiminima    },
{f4, time_semiminima   }    ,
{e4, time_semiminima   }    ,
{d4, time_semiminima   }    ,
{f4, time_semiminima   }    ,
{e4, time_three_quarters               }    ,
{pause, time_semiminima    },
{e4, time_semiminima  }     ,
{d4, time_semiminima   }    ,
{c4, time_semiminima   }    ,
{b3, time_minima,           }    ,
{e4, time_minima       }         ,
{c3, time_minima            }    ,
{b3, time_minima            }     ,
{a3, time_semibreve         }     
};

NOTE song[] = {
    // Main melody part 1
    {e4, time_semicroma},
    {e4, time_semicroma},
    {pause, time_semicroma},
    {e4, time_semicroma},
    {pause, time_semicroma},
    {c4, time_semicroma},
    {e4, time_croma},
    
    // Part 2
    {g4, time_croma},
    {pause, time_croma},
    {g3, time_croma},
    {pause, time_croma},
    
    // Part 3 (repeat of melody with variation)
    {c4, time_semicroma},
    {pause, time_semicroma},
    {g3, time_semicroma},
    {pause, time_semicroma},
    {e3, time_semicroma},
    {pause, time_semicroma},
    
    // Part 4
    {a3, time_semicroma},
    {pause, time_semicroma},
    {b3, time_semicroma},
    {pause, time_semicroma},
    {b3, time_semicroma},
    {a3, time_semicroma},
    
    // Part 5 (iconic run)
    {g3, time_semicroma},
    {e4, time_semicroma},
    {g4, time_semicroma},
    {a4, time_semicroma},
    {f4, time_semicroma},
    {g4, time_semicroma},
    
    // Part 6 (ending phrase)
    {e4, time_semicroma},
    {c4, time_semicroma},
    {d4, time_semicroma},
    {b3, time_semicroma},
    {pause, time_semicroma}
};

extern Sprite player;
extern bool PAUSE;
extern bool collision, gameNotStarted;
int downk1 = 0;

void RIT_IRQHandler (void)
{
	if(gameNotStarted){
		if(downk1>=1){ 
			if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* INT0 pressed */ 
				switch(downk1){				
					case 2:			 
						handlePause();
						reset_RIT();
						break;
					default:
						break;
				}
				downk1++;
			}
			else {	 /* button released */
				downk1=0;
				reset_RIT();
				NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
			}
		}
		//PLAY INTRO MUSIC
		static int currentNote = 0;
		static int ticks = 0;
		if(!isNotePlaying())
		{
			++ticks;
			if(ticks == UPTICKS)
			{
				ticks = 0;
				playNote(intro_music[currentNote++]);
			}
		}
		if(currentNote == (sizeof(intro_music) / sizeof(intro_music[0])))
		{
			currentNote = 0;
		}
		
		
	}else
	{
		if(!gameOverBool){
			if(!PAUSE){
				if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
					/* Joytick UP pressed */
					Sprite_setDirection(&player, NORTH);
				}
				else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
					/* Joytick DOWN pressed */
					Sprite_setDirection(&player, SOUTH);
				}
				else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
					/* Joytick LEFT pressed */
					Sprite_setDirection(&player, WEST);
				}
				else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
					/* Joytick RIGHT pressed */
					Sprite_setDirection(&player, EAST);
				}
			}			
		
			/* button management */
			if(downk1>=1){ 
				if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* INT0 pressed */ 
					switch(downk1){				
						case 2:			 
							handlePause();
							reset_RIT();
							break;
						default:
							break;
					}
					downk1++;
				}
				else {	 /* button released */
					downk1=0;
					reset_RIT();
					NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
					LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
				}
			}
			
			//MUSIC
	
			static int currentNote = 0;
			static int collisionNote = 0;
			static int ticks = 0;
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(song[currentNote++]);
				}
				if(collision){
					playNote(collision_sound[collisionNote++]);
				}
			}
			
			if(currentNote == (sizeof(song) / sizeof(song[0])))
			{
				currentNote=0;
			}
			if(collisionNote == (sizeof(collision_sound) / sizeof(collision_sound[0])))
			{
				collisionNote=0;
				collision=false;
			}	
		}else{
			//GAME OVER MUSIC
			static int currentNote = 0;
			static int ticks = 0;
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(gameover_music[currentNote++]);
				}
			}
			if(currentNote == (sizeof(gameover_music) / sizeof(gameover_music[0])))
			{
				disable_RIT();
			}
		}
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
