#include "MAX30100_queue.h"

#include <string.h>

int MAX30100_QUEUE_init(MAX30100_QUEUE* queue)
{
	if(!queue)
	{
		return MAX30100_QUEUE_FAILED;
	}

	queue->head = 0;
	queue->tail = 0;
	queue->count = 0;
	memset(queue, 0, sizeof(MAX30100_QUEUE));

	return MAX30100_QUEUE_OK;
}

uint8_t MAX30100_QUEUE_empty(const MAX30100_QUEUE* queue)
{
	return (queue->count == 0);
}

uint8_t MAX30100_QUEUE_full(const MAX30100_QUEUE* queue)
{
	return (queue->count >= MAX30100_QUEUE_SIZE);
}

int MAX30100_QUEUE_enqueue(MAX30100_QUEUE* queue, const void* data)
{
	const MAX30100_SAMPLE* l_p_sample;

	if( !data || !queue)
	{
		return MAX30100_QUEUE_FAILED;
	}

	if(MAX30100_QUEUE_full(queue))
	{
		return MAX30100_QUEUE_FAILED;
	}

	l_p_sample = (const MAX30100_SAMPLE*) data;
	queue->data[queue->tail] = *l_p_sample;
	queue->tail++;
	if(queue->tail >= MAX30100_QUEUE_SIZE)
	{
		queue->tail = 0;
	}
	queue->count++;

	return MAX30100_QUEUE_OK;
}

int MAX30100_QUEUE_dequeue(MAX30100_QUEUE* queue, void* data)
{
	MAX30100_SAMPLE* l_p_sample;

	if( !data || !queue)
	{
		return MAX30100_QUEUE_FAILED;
	}

	if(MAX30100_QUEUE_empty(queue))
	{
		return MAX30100_QUEUE_FAILED;
	}

	l_p_sample = (MAX30100_SAMPLE*) data;
	*l_p_sample = queue->data[queue->head];
	queue->head++;
	if(queue->head >= MAX30100_QUEUE_SIZE)
	{
		queue->head = 0;
	}
	queue->count--;

	return MAX30100_QUEUE_OK;
}

int MAX30100_QUEUE_drop(MAX30100_QUEUE* queue)
{
	if(!queue)
	{
		return MAX30100_QUEUE_FAILED;
	}

	if(MAX30100_QUEUE_empty(queue))
	{
		return MAX30100_QUEUE_FAILED;
	}

	queue->head++;
	if(queue->head >= MAX30100_QUEUE_SIZE)
	{
		queue->head = 0;
	}
	queue->count--;

	return MAX30100_QUEUE_OK;
}

int MAX30100_QUEUE_get_count(const MAX30100_QUEUE* queue)
{
	if(queue)
	{
		return queue->count;
	}

	return 0;
}
