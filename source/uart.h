#ifndef _UART_H_
#define _UART_H_

/*****************************************	LIBRARY FILES	************************************************/
#include <stdint.h>

/***************************************	HEADER FILES TO BE INCLUDED	************************************/
#include "cbfifo.h"

/***************************************	MACROS	********************************************************/
#define UART_OVERSAMPLE_RATE 	16
#define SYS_CLOCK				24e6

/***************************************	FUNCTION PROTOTYPES	*******************************************/

/*
 * @brief: 	initializes UART0
 *
 * @parameters: baud_rate - the baud rate at which the
 * 					UART0 will run
 *
 * @returns: none
 */
void Init_UART0(uint32_t baud_rate);


#endif
