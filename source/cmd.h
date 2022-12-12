#ifndef _CMD_H_
#define _CMD_H_

/*********************************	FUNCTION	*****************************************/


/*
 * @brief	:	this function is called after the author
 * 				command is received
 *
 * @param   :	argc, argv
 *
 * @returns :	null
 *
 *
 */
 void Handle_Author		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the help
 * 				command is received
 *
 *
 * @param   :	argc, argv
 *
 *
 * @returns :	null
 */
 void Handle_Help		(int argc, char * argv[]);


/*
 * @brief	:	this function is called after the angle
 * 				command is received
 *
 * @param   :	argc, argv
 *
 *
 * @returns:	null
 */
 void Handle_Angle		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the calibrate
 * 				command is received
 *
 * @param   :	argc, argv
 *
 *
 * @returns	:	null
 */
 void Handle_Calibrate	(int argc, char * argv[]);

 /*
  * @brief:	pre processess command for the provided user input
  *
  * @parameters: argc, argv
  *
  * @returns: null
  */
void pre_process_command(void);

/*
 * @brief:	process command for the provided user input
 *
 * @parameters:
 *   input	  Input string provided by user
 *
 * @returns: null
 */
void process_command(char *input);

/*
 * @brief	:	Resets the angle back to 0
 *
 * @param   :	null
 *
 *
 * @returns	:	null
 */
void Handle_Reset();

#endif
