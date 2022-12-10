#ifndef _CBFIFO_H_
#define _CBFIFO_H_

/*************************************	LIBRARY FILES	***********************************/
#include <stdlib.h>  // for size_t
#include <string.h>
#include <stdint.h>


enum {
	TRANS	= 0,
	REC		= 1
};

/**************************************	FUNCTIONS	***********************************/

/*
 * @brief: Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * @Parameters:
 *   buf     	Pointer to the data
 *   nbyte   	Max number of bytes to enqueue
 *   buf_type	Type of buffer (transmit or receive)
 *
 * @Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns -1.
 */
size_t cbfifo_enqueue(int buf_type, void *buf, size_t nbyte);


/*
 * @brief: Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * @Param:
 *   buf      	Destination for the dequeued data
 *   nbyte    	Bytes of data requested
 *   buf_type	Type of buffer (transmit or receive)
 *
 * @Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte.
 *
 */
size_t cbfifo_dequeue(int buf_type, void *buf, size_t nbyte);


/*
 * @brief: Returns the number of bytes currently on the FIFO.
 *
 * @Param:
 *    buf_type	Type of buffer (transmit or receive)
 *
 * @Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */

size_t cbfifo_length(int buf_type);


/*
 * @brief: Returns the FIFO's capacity
 *
 * @Param:
 *   buf_type	Type of buffer (transmit or receive)
 *
 * @Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity(int buf_type);


/*
 * Reset function: Resets the entire circular buffer values
 *
 * Parameters:
 * 	buf_type	Type of buffer (transmit or receive)
 *
 * Returns: none
*/

void cbfifo_reset(int buf_type);

#endif
