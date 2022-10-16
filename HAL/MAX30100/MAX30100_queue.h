#ifndef MAX30100_QUEUE_H
#define MAX30100_QUEUE_H

#define ALPHA 0.95
#define MEANDIFF_FILTER_SIZE 4
#define BUTTERWORTH_A1 2.452372752527856026e-1
#define BUTTERWORTH_A2 0.50952544949442879485
#define BEAT_THRESHOLD 200

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
int MAX30100_QUEUE_drop(MAX30100_QUEUE* queue);
int MAX30100_QUEUE_get_count(const MAX30100_QUEUE* queue);
int MAX30100_QUEUE_obtain_heartrate(const MAX30100_QUEUE* queue, uint16_t* heartrate);
int MAX30100_QUEUE_alpha_filter(const MAX30100_QUEUE* queue, float alpha);
int MAX30100_QUEUE_meandiff_filter(const MAX30100_QUEUE* queue);
int MAX30100_QUEUE_butterworth_filter(const MAX30100_QUEUE* queue);

#endif
