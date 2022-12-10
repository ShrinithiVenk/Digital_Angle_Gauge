/*
 * sysclock.c - configuration routines for KL25Z system clock
 *
 * Author Howdy Pierce, howdy.pierce@colorado.edu
 *
 * See section 24 of the KL25Z Reference Manual to understand this code
 *
 * Inspired by https://learningmicro.wordpress.com/configuring-device-clock-and-using-systick-system-tick-timer-module-to-generate-software-timings/
 */
/************************************	HEADER FILES TO BE INCLUDED	**************************/
#include "systick.h"
#include "MKL25Z4.h"

/************************************* GLOBAL VARIABLES **************************************/

/*
 *      @brief:
 * 		timer_interrupt_count	: A variable that is returned in get_timer()
 * 								function, and is reset every time when a state
 * 								transition occurs.
 * 		systick_count			: A variable that returns the value of the time
 * 								elapsed since last reset in 1/20 of a second.
 */
uint32_t timer_interrupt_count=0, systick_count=0;

/*
 * @brief   :  Initializes the system clock.
 *
 * @parameters	:	none
 *
 * @returns		: 	none
 *
 */
void Init_SysTick()
{
	SysTick->LOAD = ONE_MILLISECOND;  	//initialize systick with top value corresponding to 1mSec
	NVIC_SetPriority (SysTick_IRQn, 3);		//set interrupt priority to 3
	SysTick->VAL = 0;						//force the systick counter to reload
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

/*
 * @brief		: 	Initializes systick timer to generate an interrupt every 1 millisecond
 *
 * @parameters	:	none
 *
 * @returns		: 	none
 */
void sysclock_init()
{
  // Corresponds to FEI mode as shown in sec 24.4.1

  // Select PLL/FLL as clock source
  MCG->C1 &= ~(MCG_C1_CLKS_MASK);
  MCG->C1 |= MCG_C1_CLKS(0);

  // Use internal reference clock as source for the FLL
  MCG->C1 |= MCG_C1_IREFS(1);

  // Select the FLL (by setting "PLL select" to 0)
  MCG->C6 &= ~(MCG_C6_PLLS_MASK);
  MCG->C6 |= MCG_C6_PLLS(0);

  // Select 24 MHz - see table for MCG_C4[DMX32]
  MCG->C4 &= ~(MCG_C4_DRST_DRS_MASK & MCG_C4_DMX32_MASK);
  MCG->C4 |= MCG_C4_DRST_DRS(0);
  MCG->C4 |= MCG_C4_DMX32(1);
}

void SysTick_Handler()
{
	timer_interrupt_count++;
	systick_count++;
}

/*
 * @brief: resets the timer
 *
 * @parameters: none
 *
 * @returns: none
 */
void reset_timer()
{
	systick_count = 0;
	timer_interrupt_count = 0;
}

/*
 * @brief		: 	generates a delay of given time
 *
 * @parameters	:	milliseconds: total delay to be generated in milliseconds
 *
 * @returns		: 	none
 */
void delay (int milliseconds)
{
	reset_timer();
	while (timer_interrupt_count < milliseconds)
		;
}


