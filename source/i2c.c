/********************************	LIBRARY FILES	******************************/
#include <MKL25Z4.H>

/********************************	HEADER FILES TO BE INCLUDED	******************/
#include "i2c.h"

/********************************  GLOBAL VARIABLES *******************************/
int lock_func=0;
int i2c_lock=0;

/*
 * @brief			:	initializes i2c
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void Init_I2C(void)
{
	//clock i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);

	//set pins to I2C function
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	PORTE->PCR[25] |= PORT_PCR_MUX(5);

	//set to 100k baud

 	I2C0->F = (I2C_F_ICR(0x10) | I2C_F_MULT(0));

	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);
}

/*
 * @brief			:	send device and register addresses
 *
 * @parameters		:	dev			:	device address
 * 						address		:	register address
 *
 * @returns			:	none
 */
void Set_I2C(void)
{
	// Start Signal
	lock_func=0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	I2C0->C1 |=  I2C_C1_IICEN_MASK;
	// Write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK; 			//set MASTER mode
	I2C0->C1 |= I2C_C1_TX_MASK; 			//Set transmit (TX) mode
	I2C0->D = 0xFF;
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U)
					;						//wait for interrupt
	I2C0->S |= I2C_S_IICIF_MASK; 			//clear interrupt bit
	I2C0->S |= I2C_S_ARBL_MASK;				//Clear arbitration error flag
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;			//Send start
	I2C0->C1 |= I2C_C1_TX_MASK; 			//Set transmit (TX) mode
	I2C0->C1 |= I2C_C1_MST_MASK; 			//START signal generated
	I2C0->C1 |= I2C_C1_IICEN_MASK;
											//Wait until start is send
											//Send stop
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK; 			//set SLAVE mode
	I2C0->C1 &= ~I2C_C1_TX_MASK; 			//Set Rx
	I2C0->C1 |= I2C_C1_IICEN_MASK;
											//wait
											//Clear arbitration error & interrupt flag
	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;
	lock_func=0;
	i2c_lock=1;
}

void i2c_wait(void)
{
	lock_func = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK)==0) & (lock_func < 200)) {
		lock_func++;
	}
	if (lock_func >= 200)
		Set_I2C();
	I2C0->S |= I2C_S_IICIF_MASK;
}

/*
 * @brief			:	sends start sequence
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void Start_I2C()
{
	I2C_TRAN;							//set to transmit mode
	I2C_M_START;						//send start
}


/*
 * @brief			:	send device and register addresses
 *
 * @parameters		:	dev			:	device address
 * 						address		:	register address
 *
 * @returns			:	none
 */

void Set_Read_I2C(uint8_t dev, uint8_t address)
{
	I2C0->D = dev;			  			//send dev address
	I2C_WAIT							//wait for completion

	I2C0->D =  address;					//send read address
	I2C_WAIT							//wait for completion

	I2C_M_RSTART;				   		//repeated start
	I2C0->D = (dev|0x1);	 			//send dev address (read)
	I2C_WAIT							//wait for completion

	I2C_REC;						   	//set to receive mode

}
/*
 * @brief			:	read a byte and ack/nack as appropriate
 *
 * @parameters		:	LastInst		: integer to nack
 *
 * @returns			:	none
 */

uint8_t Multiple_Read_I2C(uint8_t LastInst)
{
	uint8_t data;

	lock_func = 0;

	if(LastInst)
	{
		NACK;							//set NACK after read
	} else
	{
		ACK;							//ACK after read
	}

	data = I2C0->D;						//dummy read
	I2C_WAIT							//wait for completion

	if(LastInst)	{
		I2C_M_STOP;						//send stop
	}
	data = I2C0->D;						//read data

	return  data;
}

/*
 * @brief			:	using 7bit addressing reads a byte from dev:address
 *
 * @parameters		:	dev			:	device address
 * 						address		:	register address
 *
 * @returns			:	none
 */

uint8_t Read_I2C(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C_TRAN;						//set to transmit mode
	I2C_M_START;					//send start
	I2C0->D = dev;			  		//send dev address
	I2C_WAIT						//wait for completion

	I2C0->D =  address;				//send read address
	I2C_WAIT						//wait for completion

	I2C_M_RSTART;				  	//repeated start
	I2C0->D = (dev|0x1);	 		//send dev address (read)
	I2C_WAIT						//wait for completion

	I2C_REC;						//set to receive mode
	NACK;							//set NACK after read

	data = I2C0->D;					//dummy read
	I2C_WAIT						//wait for completion

	I2C_M_STOP;						//send stop
	data = I2C0->D;					//read data

	return data;
}

/*
 * @brief			:	using 7bit addressing writes a byte data to dev:address
 *
 * @parameters		:	dev			:	device address
 * 						address		:	register address
 * 						data		:	data to write
 *
 * @returns			:	none
 */
void Write_I2C(uint8_t dev, uint8_t address, uint8_t data)
{

	I2C_TRAN;						//set to transmit mode
	I2C_M_START;					//send start
	I2C0->D = dev;			  		//send dev address
	I2C_WAIT						//wait for ack

	I2C0->D =  address;				//send write address
	I2C_WAIT

	I2C0->D = data;					//send data
	I2C_WAIT
	I2C_M_STOP;

}


