
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#inclde <avr/io.h>

#define MAXSIZE 7

typedef struct
{

	uint8_t ring[MAXSIZE];

	uint8_t track;

	uint8_t readHead;

	uint8_t writeHead;
	
}ringbuffer_t;

void rb_init(ringbuffer_t *);

void addToRing(ringbuffer_t *, uint8_t);

void readFromRing(ringbuffer_t *);

uint8_t removeFromRing(ringbuffer_t *);

uint8_t isEmpty(ringbuffer_t *);

#endif //RINGBUFFER_H
