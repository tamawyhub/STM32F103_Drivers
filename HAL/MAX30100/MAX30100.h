#ifndef MAX30100_H
#define MAX30100_H

#include "MAX30100_ll.h"
#include "MAX30100_queue.h"

#define MAX30100_BEAT_THRESHOLD 20

typedef uint32_t MAX30100_TIMESTAMP;
typedef uint16_t MAX30100_BPM;

typedef struct max30100_data_t
{
	MAX30100_SAMPLE prev_sample;
	MAX30100_TIMESTAMP timestamp;
	MAX30100_TIMESTAMP prev_timestamp;
	MAX30100_BPM	bpm;
	uint16_t sample_time;
	uint8_t rising;
} MAX30100_DATA;

typedef struct max30100_t
{
	MAX30100_LL max30100_itf;
	MAX30100_QUEUE samples_queue;
	MAX30100_FILTER max30100_filter;
	MAX30100_DATA	max30100_data;
	uint8_t sr;
	uint8_t res;
	uint8_t ir_current;
	uint8_t red_current;
	uint8_t hr_spo2_mode;
	uint8_t enable_temp;
	uint8_t interrupts;
	uint8_t mode;
	uint8_t shutdown;
} MAX30100;

typedef enum t_max30100_error
{
	MAX30100_OK,
	MAX30100_FAILED,
	MAX30100_EMPTY,
} MAX30100_ERROR;

typedef enum t_max30100_res
{
        MAX30100_ADC_13,
        MAX30100_ADC_14,
        MAX30100_ADC_15,
        MAX30100_ADC_16,
        MAX30100_ADC_RES_MAX
} MAX30100_RESOLUTION;

typedef enum t_max30100_rate
{
        MAX30100_SAMPLE_RATE_50,
        MAX30100_SAMPLE_RATE_100,
        MAX30100_SAMPLE_RATE_167,
        MAX30100_SAMPLE_RATE_200,
        MAX30100_SAMPLE_RATE_400,
        MAX30100_SAMPLE_RATE_600,
        MAX30100_SAMPLE_RATE_800,
        MAX30100_SAMPLE_RATE_1000,
        MAX30100_SAMPLE_RATE_MAX,
} MAX30100_SAMPLE_RATE;

typedef enum t_max30100_mode
{
	MAX30100_MODE_HR,
	MAX30100_MODE_SPO2,
} MAX30100_MODES;


/* Functions */
int MAX30100_init(MAX30100* p_max30100);
int MAX30100_acquire_samples(MAX30100* p_max30100, uint8_t* nread);
int MAX30100_get_raw_value(MAX30100* p_max30100, MAX30100_SAMPLE* p_raw_sample);
int MAX30100_available(const MAX30100* p_max30100);
int MAX30100_process_hr(MAX30100* p_max30100);

#endif
