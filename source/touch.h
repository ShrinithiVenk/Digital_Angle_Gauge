
#ifndef _TOUCH_H_
#define _TOUCH_H_

/*	LIBRARY FILES	*/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*	MACROS	*/
#define TOUCH_OFFSET 			550  						// offset value to be subtracted
#define TOUCH_DATA 				((TSI0->DATA) & 0xFFFF)		//macro for extracting the count from data register


/*
 * @brief		: Initializes touch sensor interface
 *
 * @parameters	: none
 *
 * @returns		: none
 */
void Touch_Init();

/*
 * @brief		: Checks for the change in capacitance of the
 * 					touch sensor
 *
 * @parameters	: none
 *
 * @returns		: Scanned value on the touch sensor
 */
uint32_t get_tsi_value(void);

#endif /*_TOUCH_H_*/
