#inclde <avr/io.h>
#include "ringbuffer.h"

#define CHECK_WRITE ((rb->writeHead) % (MAXSIZE)) == 0
#define CHECK_READ ((rb->readHead) % (MAXSIZE)) == 0


void rb_init(ringbuffer_t *rb)
{
	rb->track = 0;
	
	rb->writeHead = 0;
	
	rb->readHead = 0;	
}

void addToRing(ringbuffer_t *rb, uint8_t c) //constantly writes to the buffer
{
		
	if(CHECK_WRITE) //moves the write to the beginning once it gets to the end of the buffer
	{
		rb->writeHead = 0;
	}
	
	if(rb->track == 0) //checks if the buffer is empty
	{
		rb->ring[rb->writeHead] = c;
	
		rb->writeHead++;	
	}
	else
	{
		if(rb->track == MAXSIZE) //checks for to see if the buffer is full
		{
			if(CHECK_READ && rb->readHead != 0) //checks if the read is near the end of the buffer
			{
				rb->readHead = 0;
			}
			else if(((rb->writeHead+1) % MAXSIZE) == rb->readHead)
			{
				rb->readHead++;
			}
		}
		
		rb->ring[rb->writeHead] = c;
	
		rb->writeHead++;
	}
	
	if(rb->track < MAXSIZE)
	{
		rb->track++;
	}		
}

uint8_t removeFromRing(ringbuffer_t *rb)
{	
	uint8_t c = 0;
	
	if(rb->track != 0)
	{
		c = rb->ring[rb->readHead];
		
		--(rb->track);
		
		rb->readHead = (rb->readHead +1) % MAXSIZE;
	}
	
	return c;	
}

uint8_t isEmpty(ringbuffer_t *rb) //checks to see if there are any elements in the queue
{
	return (rb->track == 0);
}
