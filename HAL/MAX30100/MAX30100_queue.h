#ifndef MAX30100_QUEUE_H
#define MAX30100_QUEUE_H

#include <stdint.h>

#define MAX30100_QUEUE_SIZE	64

typedef struct t_max30100_sample
{
	uint16_t sample_hr;
	uint16_t sample_spo2;
} MAX30100_SAMPLE;

typedef struct t_max30100_queue
{
	uint16_t head;
	uint16_t tail;
	uint16_t count;
	MAX30100_SAMPLE data[MAX30100_QUEUE_SIZE];
} MAX30100_QUEUE;

typedef enum t_max30100_queue_error
{
	MAX30100_QUEUE_OK,
	MAX30100_QUEUE_FAILED
} MAX30100_QUEUE_ERROR;

int MAX30100_QUEUE_init(MAX30100_QUEUE *queue);
uint8_t MAX30100_QUEUE_empty(const MAX30100_QUEUE* queue);
uint8_t MAX30100_QUEUE_full(const MAX30100_QUEUE* queue);
int MAX30100_QUEUE_enqueue(MAX30100_QUEUE* queue, const void* data);
int MAX30100_QUEUE_dequeue(MAX30100_QUEUE* queue, void* data);

#endif
