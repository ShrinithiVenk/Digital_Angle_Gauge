
#ifndef _COMMAND_PROCESS_H_
#define _COMMAND_PROCESS_H_

/*	FUNCTION PROTOTYPES	*/
/*
 * @brief:	process command for the provided user input
 *
 * @parameters:
 *   input	  Input string provided by user
 *
 * @returns: none
 */
/*	HANDLER FUNCTION PROTOTYPES	*/

/*
 * @brief	:	this function is called after the author
 * 				command is received
 */
 void Handle_Author		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the help
 * 				command is received
 */
 void Handle_Help		(int argc, char * argv[]);


/*
 * @brief	:	this function is called after the angle
 * 				command is received
 */
 void Handle_Angle		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the calibrate
 * 				command is received
 */
 void Handle_Calibrate	(int argc, char * argv[]);
 void touch_handler(int argc, char * argv[]);
void pre_process_command(void);
void process_command(char *input);

#endif /* _COMMAND_PROCESS_H_ */
