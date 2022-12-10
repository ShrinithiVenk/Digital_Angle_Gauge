#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <test_cbfifo.h>

/*	OTHER FILES TO BE INCLUDED	*/
#include "cbfifo.h"
#include "led.h"
#include "systick.h"
#include "i2c.h"
#include "accel.h"

static void self_test_accelerometer_mode(int mode);

void self_test_accelerometer()													// Testing function to verify the output thrown by the accelerometer
{
	printf("Testing Accelerometer Readings: \n\r");
	int x_test[10], y_test[10], z_test[10];
	int x_sum=0, y_sum=0, z_sum=0;
	for(int i=0;i<10;i++)											// Taking 10 samples to verify our output
	{
		self_test_accelerometer_mode(ON);											// Switching on SELF test mode and storing values
		measure_axes();
		x_test[i]=accel_X;
		y_test[i]=accel_Y;
		z_test[i]=accel_Z;


		self_test_accelerometer_mode(OFF);										// Switching off the SELF test mode and storing values
		measure_axes();
		x_test[i]-=accel_X;											// Calculating the difference between the 2 modes
		y_test[i]-=accel_Y;
		z_test[i]-=accel_Z;


		x_sum+=x_test[i];											// To calculate the average, finding their sum
		y_sum+=y_test[i];
		z_sum+=z_test[i];

	}

	if((x_sum/10 > X_REF) && (y_sum/10 > Y_REF) && (z_sum/10 > Z_REF))			// checking the average with the reference values
	{
		printf("Accelerometer Readings Verified Successfully!!!\n\r");
	}
	else
	{
		printf("Accelerometer Readings Verification FAILED\n\r");
	}
}

static void self_test_accelerometer_mode(int mode)
{
	if(mode == ON)
	{
		Write_I2C(MMA_ADDR, REG_CTRL1, 0x00);		// Putting into standby mode by clearing the active bit in REG_CTRL1
		delay(5);										// Delay given to give time for the I2c values to set
		Write_I2C(MMA_ADDR, REG_CTRL2, 0x80);		// Putting into Self_test mode by setting the ST bit as 1 in REG_CTRL2
		delay(5);										// Delay given to give time for the I2c values to set
		Write_I2C(MMA_ADDR, REG_CTRL1, 0x01);		// Putting into Active mode by setting the Active bit as 1 in REG_CTRL1
		delay(5);
	}
	else if(mode == OFF)
	{
		Write_I2C(MMA_ADDR, REG_CTRL1, 0x00);		// Putting into standby mode by clearing the active bit in REG_CTRL1
		delay(5);										// Delay given to give time for the I2c values to set
		Write_I2C(MMA_ADDR, REG_CTRL2, 0x00);		// Getting out of the Self test mode by clearing the ST bit in REG_CTRL2
		delay(5);										// Delay given to give time for the I2c values to set
		Write_I2C(MMA_ADDR, REG_CTRL1, 0x01);		// Going back to the Active mode by setting the active bit to 1 in REG_CTRL1
		delay(5);
	}

}

void test_accelerometer()															// Test function to check the MMA 'WHO AM I' register value
{
	printf("%s: Testing I2C\n\r", __FUNCTION__);// Verifies the identity of the MMA
	if(Read_I2C(MMA_ADDR, REG_WHOAMI) == WHOAMI)
	{
		printf("I2C tested Successfully!\n\r");
		printf("Accelerometer Initialized Successfully!\n\r");
	}
}
