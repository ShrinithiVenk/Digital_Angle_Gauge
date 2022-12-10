#ifndef _SYSTICK_H_
#define _SYSTICK_H_
/******************************	LIBRARY FILES	**************************************/
#include "MKL25Z4.h"

/*********************************	MACROS	******************************************/
#define ONE_MILLISECOND 3000L

#define SYSCLOCK_FREQUENCY (24000000U)

/*****************************	FUNCTION PROTOTYPES	********************************/
/*
 * @brief   :  Initializes the system clock. You should call this first in your
 * program.
 *
 * @parameters	:	none
 *
 * @returns		: 	none
 *
 */
void sysclock_init();


typedef uint32_t ticktime_t;


/*
 * @brief		: 	Initializes systick timer to generate an interrupt
 * 					every 1 millisecond
 *
 * @parameters	:	none
 *
 * @returns		: 	none
 */
void Init_SysTick(void);

/*
 * @brief		: 	generates a delay of given time
 *
 * @parameters	:	milliseconds: total delay to be generated in milliseconds
 *
 * @returns		: 	none
 */
void delay (int milliseconds);
/*
 * @brief: resets the timer
 *
 * @parameters: none
 *
 * @returns: none
 */
void reset_timer();

#endif
