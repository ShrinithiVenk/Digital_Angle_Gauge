

/********************************	LIBRARY FILES	**************************************/
#include <MKL25Z4.h>

/********************************	HEADER FILES TO BE INCLUDED	****************************/
#include "uart.h"

/*
 * @brief: 	Initializes UART0
 *
 * @parameters: baud_rate - the baud rate at which the
 * 					UART0 will run
 *
 * @returns: none
 */
void Init_UART0(uint32_t baud_rate)
{
	uint16_t sbr;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;


	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);//mcg or mcg/2 clock
	//SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;//mcg/2 clock

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select two stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(1) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert TRANS data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	// Enable interrupts. Listing 8.11 on p. 234

	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not TRANS interrupts yet
	UART0->C2 |= UART_C2_RIE(1);
	//UART0->C2 |= UART_C2_TIE(1);//enable for test-dont do this here

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	//temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

}
/*
 * @brief: ISR Routine of UART0
 *
 * @parameters: none
 *
 * @returns: none
 */
void UART0_IRQHandler(void)
{

	uint8_t ch;
	uint8_t ch_tx;

	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// clear the error flags
			UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;
			// read the data register to clear RDRF
			ch = UART0->D;
	}
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		ch = UART0->D;

		if(!(cbfifo_capacity(REC) == cbfifo_length(REC))){
			cbfifo_enqueue(REC,&ch,1);
		}else {

		}

	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
		// can send another character
		if(cbfifo_length(TRANS)!=0){//not empty
			 cbfifo_dequeue(TRANS, &ch_tx, 1);
			 UART0->D = ch_tx;
		}else
			UART0->C2 &= ~UART0_C2_TIE_MASK;
	}
}
/*
 * @brief: This function enables transmission.
 *
 * @parameters: handle, buf and size
 *
 * @returns: none
 */
int __sys_write(int handle, char * buf, int size)
{

	while(cbfifo_length(TRANS) == cbfifo_capacity(TRANS))
		;

	while (size > 0) {
	  size_t bytes_written = cbfifo_enqueue(TRANS, buf, size);
	  size -= bytes_written;
	  buf += bytes_written;
	}

	if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
		UART0->C2 |= UART0_C2_TIE(1);
	}

	return 0;
}

/*
 * @brief: This function enables reception.
 *
 * @parameters: none
 *
 * @returns: none
 */
int __sys_readc(void)
{

	int character;

	while(cbfifo_length(REC)==0)
			;

	if(cbfifo_dequeue(REC,&character,1))
		{
			return character;
		}
	else
		{
			return -1;
		}
}



