#include "ringbuffer.h"

// Initializes the ring buffer internal data structures
void RingBuffer_Init(RingBuffer* rb)
{
	rb->_head = 0;
	rb->_tail = 0;
}

// returns 1 if it’s empty and 0 if it has at least one byte
int RingBuffer_IsEmpty(RingBuffer* rb)
{
	return rb->_head == rb->_tail;
}

// returns 1 if no more bytes can be added to the ring buffer
int RingBuffer_IsFull(RingBuffer* rb)
{
	return rb->_tail == (rb->_head + 1) % RING_BUFFER_SIZE;
}

// returns the amount of free space in the buffer
int RingBuffer_FreeSpace(RingBuffer* rb)
{
	if (rb->_head >= rb->_tail) {
		return RING_BUFFER_SIZE - rb->_head + rb->_tail;
	}
	else {
		return rb->_tail - rb->_head - 1;
	}
}

// Writes the data from the input array to the ring buffer.
// If it does not have enough space returns 0 and does not write any bytes,
// otherwise writes the bytes to the ring buffer and returns 1
int RingBuffer_Write(RingBuffer* rb, uint8_t * data, size_t dataSize)
{
	if (dataSize >= RingBuffer_FreeSpace(rb)) {
		return 0;
	}

	for (size_t i = 0; i < dataSize; i++) {
		rb->_buffer[rb->_head] = *data++;
		rb->_head = (rb->_head + 1) % RING_BUFFER_SIZE;
	}
	return 1;
}

// Reads the amount of bytes specified in dataSize from the ring buffer to the data array
int RingBuffer_Read(RingBuffer* rb, uint8_t * data, size_t dataSize)
{
	int readCount = 0;
	for (size_t i = 0; i < dataSize; i++) {
		if (rb->_tail == rb->_head) {
			break;
		}

		*data++ = rb->_buffer[rb->_tail];
		rb->_tail = (rb->_tail + 1) % RING_BUFFER_SIZE;
		readCount++;
	}

	return readCount;
}
