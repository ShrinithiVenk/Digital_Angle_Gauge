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

/*
 * @brief			:	test suite for RGB LED
 *
 * @parameters		:	none
 *
 * @returns			:	none
 */
void test_tpm_led()
{
	printf("%s: Testing RGB LED by changing PWM duty cycle\n\r", __FUNCTION__);

	for (int i = 0; i<MAX_DUTY_CYCLE; i+=0x10)
	{
		test_LED_ON(i,0,0);
		delay(10);
	}
	delay(100);

	for (int i = 0; i<MAX_DUTY_CYCLE; i+=0x10)
	{
		test_LED_ON(0,i,0);
		delay(10);
	}
	delay(100);

	for (int i = 0; i<MAX_DUTY_CYCLE; i+=0x10)
	{
		test_LED_ON(0,0,i);
		delay(10);
	}
	delay(100);


}
