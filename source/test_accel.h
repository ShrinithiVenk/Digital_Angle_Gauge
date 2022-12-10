#ifndef _TEST_ACCEL_H_
#define _TEST_ACCEL_H_
/*
 * @brief			:	test suite for accelerometer
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void self_test_accelerometer();

/*
 * @brief			:	checks whether I2C and MMA8451 are initialized
 * 						correctly or not
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void test_accelerometer();

#endif
