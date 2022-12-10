#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <test_cbfifo.h>

/*************************************	HEADER FILES TO BE INCLUDED	*************************/
#include "cbfifo.h"
#include "led.h"
#include "systick.h"
#include "i2c.h"
#include "accel.h"

static void self_test_accelerometer_mode(int mode);

/*
 * @brief			:	test suite for accelerometer
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void self_test_accelerometer()
{
	printf("Testing Accelerometer Readings: \n\r");
	int x_test[10], y_test[10], z_test[10];
	int x_sum=0, y_sum=0, z_sum=0;
	for(int i=0;i<10;i++)
	{
		self_test_accelerometer_mode(ON);
		measure_axes();
		x_test[i]=accel_X;
		y_test[i]=accel_Y;
		z_test[i]=accel_Z;


		self_test_accelerometer_mode(OFF);
		measure_axes();
		x_test[i]-=accel_X;
		y_test[i]-=accel_Y;
		z_test[i]-=accel_Z;


		x_sum+=x_test[i];
		y_sum+=y_test[i];
		z_sum+=z_test[i];

	}

	if((x_sum/10 > X_REF) && (y_sum/10 > Y_REF) && (z_sum/10 > Z_REF))
	{
		printf("Accelerometer Readings Verified Successfully!!!\n\r");
	}
	else
	{
		printf("Accelerometer Readings Verification FAILED\n\r");
	}
}

/*
 * @brief			:	test suite for accelerometer
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
static void self_test_accelerometer_mode(int mode)
{
	if(mode == ON)
	{
		Write_I2C(MMA_ADDR, REG_CTRL1, 0x00);
		delay(5);
		Write_I2C(MMA_ADDR, REG_CTRL2, 0x80);
		delay(5);
		Write_I2C(MMA_ADDR, REG_CTRL1, 0x01);
		delay(5);
	}
	else if(mode == OFF)
	{
		Write_I2C(MMA_ADDR, REG_CTRL1, 0x00);
		delay(5);
		Write_I2C(MMA_ADDR, REG_CTRL2, 0x00);
		delay(5);
		Write_I2C(MMA_ADDR, REG_CTRL1, 0x01);
		delay(5);
	}

}

/*
 * @brief			:	checks whether I2C and MMA8451 are initialized
 * 						correctly or not
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void test_accelerometer()
{
	printf("%s: Testing I2C\n\r", __FUNCTION__);
	if(Read_I2C(MMA_ADDR, REG_WHOAMI) == WHOAMI)
	{
		printf("I2C tested Successfully!\n\r");
		printf("Accelerometer Initialized Successfully!\n\r");
	}
}
