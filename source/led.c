
#include "led.h"

color_config color[TOTAL_COLORS] = {0};
int brightness = 100;

/*
 * @brief: 		Configures the colors according to their hex RGB values
 *
 * @parameters: none
 *
 * @returns: 	none
 */
void LED_Color_Config()
{
	color[RED].red 			= 0xFF;
	color[RED].green		= 0x00;
	color[RED].blue 		= 0x00;

	color[GREEN].red		= 0x00;
	color[GREEN].green 		= 0xFF;
	color[GREEN].blue 		= 0x00;

	color[BLUE].red			= 0x00;
	color[BLUE].green 		= 0x00;
	color[BLUE].blue		= 0xFF;

}


/*
 * @brief: 					Initializes the Blue LED to function in Timer and
 * 							PWM mode.
 *
 * @parameters:				None.
 *
 * @returns: 				None.
 */
void Init_Blue_LED_PWM()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;;
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(4);

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	TPM0->MOD = MAX_DUTY_CYCLE;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM0->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 1 to edge-aligned low-true PWM
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	//TPM0->CONTROLS[1].CnV = 150;
	// Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}

/* @brief: 					Initializes the Red LED to function in Timer and
* 							PWM mode.
*
* @parameters:				None.
*
* @returns: 				None.
*/
void Init_Red_LED_PWM()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(3);

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	TPM2->MOD = MAX_DUTY_CYCLE;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM2->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 0 to edge-aligned low-true PWM
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	//TPM2->CONTROLS[0].CnV = 20;
	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
}

/*
 * @brief: 					Initializes the Green LED to function in Timer and
 * 							PWM mode.
 *
 * @parameters:				None.
 *
 * @returns: 				None.
 */
 void Init_Green_LED_PWM()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(3);

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	TPM2->MOD = MAX_DUTY_CYCLE;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM2->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 0 to edge-aligned low-true PWM
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	//TPM2->CONTROLS[1].CnV = 100;
	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
}

 /*
  * @brief: 		Initializes Red, Green and Blue LED
  *
  * @parameters: none
  *
  * @returns: 	none
  */
void LED_init()
{
	Init_Blue_LED_PWM();
	Init_Green_LED_PWM();
	Init_Red_LED_PWM();
}

/*
 * @brief: 		Turns on LED with the specific color and brightness
 *
 * @parameters: color_name	: 	name of the color, the value of which is
 * 								mentioned in the enum above
 * 				factor		:	the amount of brightness intended to be seen by
 * 								user
 *
 * @returns: 	none
 */
void LED_ON(uint32_t color_name, int factor)
{
	uint32_t red, green, blue;

	if (color[color_name].red == 0)
	{
		red= 0;
	}
	else
	{
		red = (factor*color[color_name].red)/100;
	}

	if (color[color_name].green == 0)
	{
		green = 0;
	}
	else
	{
		green = (factor*color[color_name].green)/100;
	}

	if (color[color_name].blue == 0)
	{
		blue= 0;
	}
	else
	{
		blue = (factor*color[color_name].blue)/100;
	}

		TPM2->CONTROLS[0].CnV = red;
		TPM2->CONTROLS[1].CnV = green;
		TPM0->CONTROLS[1].CnV = blue;
}

/*
 * @brief: 		Turns OFF Red, Green and Blue LED
 *
 * @parameters: none
 *
 * @returns: 	none
*/
void LED_OFF(void)
{
		TPM2->CONTROLS[0].CnV = 0;
		TPM2->CONTROLS[1].CnV = 0;
		TPM0->CONTROLS[1].CnV = 0;
}

/*
 * @brief: 		Turns on LED with the specific RGB values
 *
 * @parameters: red_value	: R value for the intended color
 * 				green_value	: G value for the intended color
 * 				blue_value	: B value for the intended color
 *
 * @returns: 	none
 */
void test_LED_ON(uint32_t red, uint32_t green, uint32_t blue)
{
		TPM2->CONTROLS[0].CnV = red;
		TPM2->CONTROLS[1].CnV = green;
		TPM0->CONTROLS[1].CnV = blue;
}


