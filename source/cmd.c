
/* 	LIBRARY FILES	*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* 	OTHER FILES TO BE INCLUDED	*/
#include "cmd.h"
#include "led.h"
#include "accel.h"
#include "systick.h"

/*	GENERIC PROTOTYPE FOR HANDLE FUNCTIONS	*/
typedef void (*cmd_handler_t)(int, char * argv[]);

/*		STRUCTURE OF COMMANDS AND THEIR DATA	*/
typedef struct{
	const char *cmd_name;
	cmd_handler_t handler;
	uint32_t led_color;
}cmd_table_t;

int desired_angle = 45;
int calibrated_angle = 0;

enum commands {
	command_author,
	command_help,
	command_brightness,
	command_angle,
	command_calibrate
};



/*	TABLE OF COMMANDS EXECUTED IN RESPONSE TO THE USER INPUT 	*/
static cmd_table_t commands[] =
{
		{"author",Handle_Author, GREEN},

		{"help",Handle_Help},


		{"angle", Handle_Angle, RED},


		{"calibrate", Handle_Calibrate, GREEN},
};

static const int no_of_command = sizeof(commands) / sizeof(cmd_table_t);	//computing number of commands


void pre_process_command(void)
{
	uint8_t c=0;
	uint8_t buffer[80];
	uint8_t bp = 0;

	while((c != '\r' ) && (c != '\n'))
	{
		c = getchar();
		if(c == '\b')		//check for backspace
		{
			if(bp==0)
			{
				//do nothing if bp=0
				//ignore any more backspaces at this moment
			}
			else
			{
				//if backspace is present, overwrite
				bp--;
				printf("\b \b");
			}
		}
		else
		{
			buffer[bp] = c;
			bp++;
			printf("%c",(char)c);
			//printf("%d",(int)c);
		}
	}
	buffer[bp] = '\0';
	printf("\r\n");
	bp = 0;
	process_command((char *)buffer);
	printf("\n\r? ");
	c = 0;
}


void process_command(char *input)
{
	bool in_token = false;
	char *argv[10];
	int argc = 0;

	bool command = false;						//variable to check whether a command
												//is present or not

	char *p = input;
	char *end;

	for(end=input ; *end!= '\0' ; end++)		//computing the end of the string
				;
	memset(argv,0,sizeof(argv)); 				//setting argv[] to 0

	for(p = input; p < end; p++)
	{
		switch(in_token)
		{
			case false:

				/*
				 * @brief: if the token state is false, we check for a valid character
				 * 			if we find a valid character, we look for first available white space,
				 * 			LF, CR or TAB.
				 */
				if(
						((*p>='a')&&(*p<='z')) ||
						((*p>='A')&&(*p<='Z')) ||
						((*p>='0')&&(*p<='9'))
				  )
				{
					argv[argc] = p;		//storing the word in argv
					argc++;				//incrementing argc index
					in_token = true;	//advance to next state
				}

			break;
			case true:

				/*
				 * @brief: in this state, we check for the first available white space,
				 * 			LF, CR, TAB, and then replace the character with null character.
				 */
				if(
						(*p == ' ')  ||
						(*p == '\t') ||
						(*p == '\n') ||
						(*p == '\r')
				  )
				{
					*p = '\0';
					in_token = false;		//advance to previous state
				}

			break;
		}
	}
	if(argc == 0)
	{
		return;		//no command found
	}

	//Todo:Handle the command
	for (int i=0; i < no_of_command; i++)
	{
	    if (strcasecmp(argv[0], commands[i].cmd_name) == 0)
	    {
	      commands[i].handler(argc, argv);
	      command = true;
	      break;
	    }
	}
	 if(!command) 						//if no command is found, we print a message indicating that
	 {									//invalid command has been entered
		 LED_ON(RED, brightness);
		 printf("Invalid command: %s\r\n",argv[0]);
	 }
}

 void Handle_Author(int argc, char * argv[])
{
	printf("Shrinithi Venkatesan\r\n");
	LED_ON(commands[command_author].led_color, brightness);
}

 void Handle_Help(int argc,char * argv[])
{
	LED_ON(commands[command_help].led_color, brightness);

	printf("1. author          |   Prints the name of the Author\r\n");

	printf("2. angle<angle>    |   Allows user to set a desired angle and \n\r LED glows alters to maximum brightness once the angle reaches\r\n");

	printf("3. calibrate<angle>|   Calibrates the accelerometer to a certain value.\n\r For ex, if	we calibrate the accelerometer at 90 degrees, then 90 degrees become a reference axis (0 degrees) for the accelerometer and all the readings will be taken relative to 90.\r\n");

	printf("4. help            |   Reprint this help message again\r\n");
}



 void Handle_Angle(int argc, char * argv[])
{
	uint32_t user_angle;		//a variable to store the value entered by user
	int angle=0;

	if (argv[1]==0)				//if user does not enter a number or a value
	{							//this error message will be printed
		printf("Too few arguments for angle command.\n\r");
		printf("Type Angle <angle> to measure your desired angle. \n\r Enter 'Help' for more information");
		return;
	}
	else
	{
		sscanf(argv[1], "%d", &user_angle);
		desired_angle = user_angle; 		//updating the global variable
		while (1)
		{									//this loop will keep running unless the desired
											//angle is reached
			//compute values of x, y and z axes
		   	measure_axes();
		   	//convert it to tilt_angle value
		  	convert_axes_to_tilt();
		  	//compute angle
		   	angle = fabs(tilt_angle)-calibrated_angle;
		   	//change the sign of the variable if angle is negative
		    angle = (angle<0)? angle*-1 : angle;
		    //print angle for user
		   	printf("Angle: %d\n\r", angle);
		   	//LED will be blinking unless the desired angle is reached
		   	LED_ON(commands[command_angle].led_color, brightness);
		   	delay(50);
		   	LED_OFF();
		   	delay(50);
		   	if (angle == desired_angle)
		   	{
		   		printf("Desired angle reached. Current Angle: %d\n\r", angle);
		   		LED_ON(commands[command_angle].led_color, brightness);
		   		break;
		   	}
		}
	}
}



 void Handle_Calibrate(int argc, char * argv[])
{
	int angle=0;

	if (argv[1]==0) 			//if user does not enter a number or a value
	{							//this error message will be printed
		printf("Too few arguments to proceed.\n\r");
		printf("Type calibrate <angle> to set reference at that angle. \n\r Enter 'Help' for more information");
		return;
	}

	else
	{
		sscanf(argv[1], "%d", &angle);
		calibrated_angle = angle;
	}
	LED_ON(commands[command_calibrate].led_color, brightness);
}


