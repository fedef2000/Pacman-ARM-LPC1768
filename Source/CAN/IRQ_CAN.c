/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC17xx with MCB1700
 * Note(s): see also http://www.port.de/engl/canprod/sv_req_form.html
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC17xx.h>                  /* LPC17xx definitions */
#include "configuration.h"
#include "game_graphics.h"
#include "CAN.h"
extern SCORE;
extern LIVES;
extern TIMER;

extern uint8_t icr ; 										//icr and result must be global in order to work with both real and simulated landtiger.
extern uint32_t result;
extern CAN_msg       CAN_TxMsg;    /* CAN message for sending */
extern CAN_msg       CAN_RxMsg;    /* CAN message for receiving */                                

static int puntiRicevuti1 = 0;
static int puntiInviati1 = 0;

static int puntiRicevuti2 = 0;
static int puntiInviati2 = 0;

uint16_t val_RxCoordX = 0;            /* Locals used for display */
uint16_t val_RxCoordY = 0;
uint16_t time;
uint16_t score;
uint16_t lives;
 

/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
void CAN_IRQHandler (void)  {

  /* check CAN controller 1 */
	icr = 0;
  icr = (LPC_CAN1->ICR | icr) & 0xFF;               /* clear interrupts */
	
  if (icr & (1 << 0)) {                          		/* CAN Controller #1 meassage is received */
		CAN_rdMsg (1, &CAN_RxMsg);	                		/* Read the message */
    LPC_CAN1->CMR = (1 << 2);                    		/* Release receive buffer */
		
		time=(CAN_RxMsg.data[0])  ;
		
		score = (CAN_RxMsg.data[1] << 8);
		score = score | CAN_RxMsg.data[2];

		lives = (CAN_RxMsg.data[3]);


		updateLifeHUD(lives);
		updateScoreHUD(score);
		updateTimeHUD(time);
		
  }
	if (icr & (1 << 1)) {                         /* CAN Controller #1 meassage is transmitted */
		// do nothing in this example
		puntiInviati1++;
	}
		
	/* check CAN controller 2 */
	icr = 0;
	icr = (LPC_CAN2->ICR | icr) & 0xFF;             /* clear interrupts */

	if (icr & (1 << 0)) {                          	/* CAN Controller #2 meassage is received */
		CAN_rdMsg (2, &CAN_RxMsg);	                		/* Read the message */
    LPC_CAN2->CMR = (1 << 2);                    		/* Release receive buffer */
		
		val_RxCoordX = (CAN_RxMsg.data[0] << 8)  ;
		val_RxCoordX = val_RxCoordX | CAN_RxMsg.data[1];
		
		val_RxCoordY = (CAN_RxMsg.data[2] << 8);
		val_RxCoordY = val_RxCoordY | CAN_RxMsg.data[3];
		
		puntiRicevuti2++;
	}
	if (icr & (1 << 1)) {                         /* CAN Controller #2 meassage is transmitted */
		// do nothing in this example
		puntiInviati2++;
	}
}
