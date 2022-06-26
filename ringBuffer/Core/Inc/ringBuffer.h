/*
 * ringBuffer.h
 *
 *  Created on: May 31, 2022
 *      Author: student
 */

#ifndef INC_RINGBUFFER_H_
#define INC_RINGBUFFER_H_

#include <stdint.h>
#include <stdlib.h>

void RingBuffer_Init();
int RingBuffer_IsEmpty();
int RingBuffer_IsFull();
int RingBuffer_FreeSpace();
int RingBuffer_Write(uint8_t * data, size_t dataSize);
int RingBuffer_Read(uint8_t * data, size_t dataSize);

#endif /* INC_RINGBUFFER_H_ */
