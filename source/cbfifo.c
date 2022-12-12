

/****************************	LIBRARY FILES	*******************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <MKL25Z4.h>

/***************************	HEADER FILES TO BE INCLUDED	*********************/
#include "cbfifo.h"

/*****************************   MACROS	 ****************************************/
#define BUFFER_SIZE 256				//max size of the circular buffer

/******************************	STRUCTURE **************************************/
typedef struct {
	uint32_t BuffLen;
	uint32_t ReadAddr;
	uint32_t WriteAddr;
	uint8_t CircularBuff[BUFFER_SIZE];
}cbfifo_struct;

/****************************	GLOBAL VARIABLES	******************************/
cbfifo_struct fifo[2];		//array of structure to implement multiple instances of cbfifo_struct
uint32_t i;			        //loop variable

/***************************      FUNCTIONS         *******************************/

/*
 * @brief: Returns the FIFO's capacity
 *
 * @Param: buf_type	Type of buffer (TRANS or receive)
 *
 * @Returns:The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity(int buf_type)
{
    return BUFFER_SIZE;
}

/*
 * @brief: Returns the number of bytes currently on the FIFO.
 *
 * @Param:    buf_type	Type of buffer (TRANS or receive)
 *
 * @Returns:  Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(int buf_type)
{
    return fifo[buf_type].BuffLen;
}

/*
 * @brief: Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * @Parameters:   buf     	Pointer to the data
 *                nbyte   	Max number of bytes to enqueue
 *                buf_type	Type of buffer (TRANS or receive)
 *
 * @Returns:
 *   The number of bytes actually enqueued, which could be 0. In case of an error, returns -1.
 */

size_t cbfifo_enqueue(int buf_type, void *buf, size_t nbyte)
{
	uint32_t masking_state;
    size_t TOTAL_BYTES_ENQUEUED=0;              //a variable to check the number of bytes enqueued in one enqueue cycle
    if (fifo[buf_type].BuffLen == BUFFER_SIZE)
    {
        return 0;                               //returns 0 if buffer is full, since there are no more spaces left to fill
    }

    else if (buf == NULL)
    {
        return -1;                              //if no data is encountered, the function returns -1
    }

    else if (nbyte >= BUFFER_SIZE-fifo[buf_type].BuffLen)
    {
        nbyte = BUFFER_SIZE-fifo[buf_type].BuffLen;      	//checking for available spaces in the circular buffer.
    }                                           				//if nbytes is higher than available spaces, remaining elements
                                                				//will be discarded
    else {}

    masking_state = __get_PRIMASK();
    __disable_irq();
    for (i=0; i<nbyte; i++)
    {
    	fifo[buf_type].CircularBuff[fifo[buf_type].WriteAddr] = *(char*) buf;        //writing element in the buffer
        buf++;
        fifo[buf_type].BuffLen++;                                     //increasing buffer length
        fifo[buf_type].WriteAddr++;                                    //increasing write location
        TOTAL_BYTES_ENQUEUED++;                             //updating total bytes enqueued

        if (fifo[buf_type].WriteAddr >= BUFFER_SIZE)                   //checking if the write pointer has reached to the
        {                                                   //end of the buffer, if so, it starts pointing to 0 again
        	fifo[buf_type].WriteAddr = 0;
        }
    }
    __set_PRIMASK(masking_state);
    return TOTAL_BYTES_ENQUEUED;                            //returning the total number of bytes enqueued in this cycle
}

/*
 * @brief: Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO.
 *
 * @Param:   buf        Destination for the dequeued data
 *           nbyte    	Bytes of data requested
 *           buf_type	Type of buffer (TRANS or receive)
 *
 * @Returns: The number of bytes actually copied, which will be between 0 and nbyte.
 *
 */
size_t cbfifo_dequeue(int buf_type, void *buf, size_t nbyte)
{
	uint32_t masking_state;
    size_t TOTAL_BYTES_DEQUEUED=0;                           //a variable to check the number of bytes dequeued in one queue cycle

    if (buf == NULL)                                         //if no data is encountered, the function returns -1
    {
        return -1;
    }

    else if (fifo[buf_type].BuffLen == 0)                                //if buffer is empty, the function will return 0
    {
        return 0;
    }

    else if (nbyte > fifo[buf_type].BuffLen)                              //checking whether the number of bytes to be removed are
    {                                                           //higher than the available bytes, if so, only the bytes
        nbyte = fifo[buf_type].BuffLen;                                   //that are currently in the fifo will be removed.
    }

    else{}

    masking_state = __get_PRIMASK();
    __disable_irq();
    for (i=0; i<nbyte; i++)
    {
        *(char *) buf = fifo[buf_type].CircularBuff[fifo[buf_type].ReadAddr];             //removing the element from the buffer
        buf++;
        fifo[buf_type].BuffLen--;                                            //updating buffer length
        fifo[buf_type].ReadAddr++;                                             //updating read location
        TOTAL_BYTES_DEQUEUED++;                                     //updating total bytes dequeued

        if (fifo[buf_type].ReadAddr == BUFFER_SIZE)                        //if read location reaches the end of the buffer
        {                                                       //it will wrap around and will start pointing at 0 again
        	fifo[buf_type].ReadAddr = 0;
        }
    }
    __set_PRIMASK(masking_state);
    return TOTAL_BYTES_DEQUEUED;
}

/*
 * brief: Reset function: Resets the entire circular buffer values
 *
 * Parameters: 	buf_type  Type of buffer (TRANS or receive)
 *
 * Returns: none
*/
void cbfifo_reset(int buf_type)
{
	fifo[buf_type].BuffLen = 0;
	fifo[buf_type].ReadAddr = 0;
	fifo[buf_type].WriteAddr = 0;

	for (int i = 0; i<BUFFER_SIZE; i++)
	{
		fifo[buf_type].CircularBuff[i] = (char)0;
	}

}


