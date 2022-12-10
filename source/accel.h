#ifndef _ACCEL_H_
#define _ACCEL_H_

/*************************************	LIBRARY FILES   ***************************/
#include <stdint.h>

/************************************* 	MACROS	***********************************/
#define MMA_ADDR 				0x3A

#define REG_XH 				0x01
#define REG_YH 				0x03
#define REG_ZH				0x05

#define REG_WHOAMI 				0x0D
#define REG_CTRL1  				0x2A
#define REG_CTRL2  				0x2B

#define CTRL_REG1_ACTIVE		0x01
#define WHOAMI 					0x1A

#define COUNTS_PER_G 			(4096.0)
#define M_PI 					(3.14159265)

#define X_REF 			300								// Reference Value of x axis when used in Self test mode
#define Y_REF 			300								// Reference Value of y axis when used in Self test mode
#define Z_REF			3000							// Reference Value of z axis when used in Self test mode

#define ON 						1								// This is the variable to switch ON the self test mode
#define OFF 					0								// This is the variable to switch OFF the self test mode

/*********************************	GLOBAL VARIABLES	*******************************/
extern float tilt_angle, tilt_value;
extern int desired_angle;
extern int16_t accel_X, accel_Y, accel_Z;

/************************************  	FUNCTION 	****************************************/

/*
 * @brief			:	initializes MMA8451 3 axis accelerometer.
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */

int init_accelerometer(void);

/*
 * @brief			:	computes the values of x, y & z axis for further
 * 						computations.
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */

void measure_axes(void);

/*
 * @brief			:	computes a tilt_angle value which is then used to compute
 * 						angle.
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */

void convert_axes_to_tilt(void);

#endif
