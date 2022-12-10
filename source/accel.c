
/**********************************	LIBRARY FILES	******************************************/
#include <math.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include <MKL25Z4.H>

/******************************** HEADER FILES TO BE INCLUDED *********************************/
#include "i2c.h"
#include "accel.h"
#include "systick.h"

/*******************************	GLOBAL VARIABLE  *******************************************/
int16_t accel_X=0, accel_Y=0, accel_Z=0;
float tilt_angle=0.0, tilt_value=0.0;

extern uint32_t DATA_ACCEL_READY;

/* @brief			:	initializes MMA8451 3 axis accelerometer.
*
* @parameters		:	none
*
* @returns			:	none
*/

int init_accelerometer()
{
	Write_I2C(MMA_ADDR, REG_CTRL1, 0x01); //set active mode, 14 bit samples and 800 Hz ODR
	return 1;
}


/* @brief			:	computes the values of x, y & z axis for further
* 						computations.
*
* @parameters		:	none
*
* @returns			:	none
*/

void measure_axes()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	Start_I2C();
	Set_Read_I2C(MMA_ADDR , REG_XH); //Start_I2C


	for( i=0; i<5; i++)	{
		data[i] = Multiple_Read_I2C(0); // Read five bytes in repeated mode
	}

	data[i] = Multiple_Read_I2C(1); // Read last byte ending repeated mode

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	accel_X = temp[0]>>2;	// Align for 14 bits
	accel_Y = temp[1]>>2;
	accel_Z = temp[2]>>2;

	if(accel_X<0)
	{
		accel_X = accel_X*(-1);
	}
	if(accel_Y<0)
	{
		accel_Y = accel_Y*(-1);
	}
	if(accel_Z<0)
	{
		accel_Z = accel_Z*(-1);
	}
}

/* @brief			:	computes a tilt_angle value which is then used to compute
* 						angle.
*
* @parameters		:	none
*
* @returns			:	none
*/

void convert_axes_to_tilt(void) {
	float ax = accel_X/COUNTS_PER_G;
	float ay = accel_Y/COUNTS_PER_G;
	float az = accel_Z/COUNTS_PER_G;

	tilt_value= (az / sqrt(ax*ax + ay*ay + az*az));
	tilt_angle= acos(tilt_value)* 180/M_PI; //calculates the tilted angle
}



