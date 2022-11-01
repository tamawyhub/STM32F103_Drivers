#ifndef MAX30100_QUEUE_H
#define MAX30100_QUEUE_H

#include <stdint.h>

#define MAX30100_QUEUE_SIZE	64

#define MAX30100_QUEUE_WINDOW_SIZE 4

typedef int32_t MAX30100_HR;
typedef int32_t MAX30100_SPO2;

typedef struct t_max30100_sample
{
	MAX30100_HR sample_hr;
	MAX30100_SPO2 sample_spo2;
} MAX30100_SAMPLE;

typedef struct t_max30100_iir
{
	float iir_alpha;
	float prev_w;
} MAX30100_IIR;

typedef struct t_max30100_butterworth
{
	float alpha1;
	float alpha2;
	float prev_v;
} MAX30100_BUTTERWORTH;

typedef struct t_max30100_signal_t
{
	MAX30100_IIR iir_filter;
	MAX30100_BUTTERWORTH bw_filter;
} MAX30100_FILTER;

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
#if 0
int MAX30100_QUEUE_obtain_heartrate(const MAX30100_QUEUE* queue, uint16_t* heartrate);
int MAX30100_QUEUE_alpha_filter(const MAX30100_QUEUE* queue);
int MAX30100_QUEUE_meandiff_filter(const MAX30100_QUEUE* queue);
int MAX30100_QUEUE_butterworth_filter(const MAX30100_QUEUE* queue);
#endif
int MAX30100_QUEUE_iir_filter(MAX30100_QUEUE* queue, MAX30100_IIR* p_iir_filter);
int MAX30100_QUEUE_meandiff(MAX30100_QUEUE* queue);
int MAX30100_QUEUE_butterworth(MAX30100_QUEUE* queue, MAX30100_BUTTERWORTH* bw);

#endif
