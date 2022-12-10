#ifndef _I2C_H_
#define _I2C_H_

/*****************************	LIBRARY FILES	********************************/
#include <stdint.h>

/*****************************	MACROS	****************************************/
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN		I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC			I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 		i2c_wait();

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           	I2C0->C1 &= ~I2C_C1_TXAK_MASK

/************************************	FUNCTIONS	**********************************/
/*
 * @brief			:	initializes i2c
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void Init_I2C(void);

/*
 * @brief			:	sends start sequence
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void Start_I2C(void);

/*
 * @brief			:	send device and register addresses
 *
 * @parameters		:	dev			:	device address
 * 						address		:	register address
 *
 * @returns			:	none
 */
void Set_Read_I2C(uint8_t dev, uint8_t address);

/*
 * @brief			:	read a byte and ack/nack as appropriate
 *
 * @parameters		:	LastInst: integer to nack
 *
 * @returns			:	none
 */

uint8_t Multiple_Read_I2C(uint8_t);

/*
 * @brief			:	using 7bit addressing reads a byte from dev:address
 *
 * @parameters		:	dev			:	device address
 * 						address		:	register address
 *
 * @returns			:	none
 */

uint8_t Read_I2C(uint8_t dev, uint8_t address);

/*
 * @brief			:	using 7bit addressing writes a byte data to dev:address
 *
 * @parameters		:	dev			:	device address
 * 						address		:	register address
 * 						data		:	data to write
 *
 * @returns			:	none
 */

void Write_I2C(uint8_t dev, uint8_t address, uint8_t data);

#endif
