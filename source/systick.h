

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

/*	LIBRARY FILES	*/
#include "MKL25Z4.h"

/*	MACROS	*/
#define ONE_MILLISECOND 3000L

typedef uint32_t ticktime_t;

/*	FUNCTION PROTOTYPES	*/
/*-------------------------------------------------------------------------------
 * @brief		: 	Initializes systick timer to generate an interrupt
 * 					every 1 millisecond
 *
 * @parameters	:	none
 *
 * @returns		: 	none
 -------------------------------------------------------------------------------*/
void Init_SysTick(void);

/*-------------------------------------------------------------------------------
 * @brief		: 	generates a delay of given time
 *
 * @parameters	:	milliseconds: total delay to be generated in milliseconds
 *
 * @returns		: 	none
 -------------------------------------------------------------------------------*/
void delay (int milliseconds);

#endif /*_SYSTICK_H_*/
