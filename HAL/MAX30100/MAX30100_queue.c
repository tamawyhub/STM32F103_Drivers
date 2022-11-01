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

#if 0
int MAX30100_QUEUE_obtain_heartrate(const MAX30100_QUEUE* queue, uint16_t* heartrate)
{
	//filter samples
	if (MAX30100_QUEUE_alpha_filter(queue) == MAX30100_QUEUE_FAILED)
		return MAX30100_QUEUE_FAILED;
	if (MAX30100_QUEUE_meandiff_filter(queue) == MAX30100_QUEUE_FAILED)
		return MAX30100_QUEUE_FAILED;
	if (MAX30100_QUEUE_butterworth_filter(queue) == MAX30100_QUEUE_FAILED)
		return MAX30100_QUEUE_FAILED;

	//calculate hr based on only the first two successive beats, for now
	uint8_t rising = 0; //flag for rising state over time
	uint16_t fst_pulse_ts = 0; //first pulse timestamp
	uint16_t snd_pulse_ts = 0; //second pulse timestamp
	MAX30100_SAMPLE x;
	//get first sample
	if (MAX30100_QUEUE_dequeue(queue, &x) == MAX30100_QUEUE_FAILED)
			return MAX30100_QUEUE_FAILED;
	uint16_t last_hr = x.sample_hr;
	if (MAX30100_QUEUE_enqueue(queue, &x) == MAX30100_QUEUE_FAILED)
			return MAX30100_QUEUE_FAILED;
	for (uint16_t i = 1; i < (queue->count); i ++)
	{
		//get next heartrate
		if (MAX30100_QUEUE_dequeue(queue, &x) == MAX30100_QUEUE_FAILED)
				return MAX30100_QUEUE_FAILED;
		uint16_t hr = x.sample_hr;
		if (MAX30100_QUEUE_enqueue(queue, &x) == MAX30100_QUEUE_FAILED)
				return MAX30100_QUEUE_FAILED;

		if (last_hr >= BEAT_THRESHOLD && rising && hr < last_hr) //heart beat detection logic: signal peak detected whose value exceeds threshold
		{
			if (fst_pulse_ts == 0) //make sure that no pulse has been detected yet; this becomes your first pulse
			{
				fst_pulse_ts = i;
			}
			else //otherwise, this must be the second pulse
			{
				snd_pulse_ts = i;
				break;
			}
		}
		rising = (hr > last_hr);
		last_hr = hr;
	}
	if (snd_pulse_ts <= fst_pulse_ts)
		return MAX30100_QUEUE_FAILED;
	//todo: complete heart rate evaluation : hr = 60 seconds / ( (snd_pulse_ts-fst_pulse_ts) * sample time )
	return MAX30100_QUEUE_OK;
}
#endif

int MAX30100_QUEUE_iir_filter(MAX30100_QUEUE* queue, MAX30100_IIR* p_iir_filter)
{
	/* Implement the following equations
	 * 1) w(t) = x + alpha * w(t - 1)
	 * 2) y = w(t) - w(t -1)
	 */

	MAX30100_SAMPLE current_sample;
	float w, prev_w, alpha;

	if(!queue || !p_iir_filter)
	{
		return MAX30100_QUEUE_FAILED;
	}

	alpha = p_iir_filter->iir_alpha;
	prev_w = p_iir_filter->prev_w;

	for(uint16_t i = 0; i < queue->count; i++)
	{
		if(MAX30100_QUEUE_dequeue(queue, &current_sample) == MAX30100_QUEUE_FAILED)
		{
			return MAX30100_QUEUE_FAILED;
		}

		w = (float) current_sample.sample_hr + alpha * prev_w;
		current_sample.sample_hr = (MAX30100_HR) (w - prev_w);
		prev_w = w;

		if(MAX30100_QUEUE_enqueue(queue, &current_sample) == MAX30100_QUEUE_FAILED)
		{
			return MAX30100_QUEUE_FAILED;
		}
	}

	p_iir_filter->prev_w = prev_w;

	return MAX30100_QUEUE_OK;
}

int MAX30100_QUEUE_meandiff(MAX30100_QUEUE* queue)
{
	MAX30100_HR window_arr[MAX30100_QUEUE_WINDOW_SIZE];
	int32_t sum;
	uint16_t queue_len;
	uint16_t window_idx;
	uint16_t count;
	MAX30100_SAMPLE sample;

	if(!queue)
	{
		return MAX30100_QUEUE_FAILED;
	}

	sum = 0;
	window_idx = 0;
	count = 0;
	queue_len = queue->count;
	memset(window_arr, 0, sizeof(window_arr));

	for(uint16_t i = 0; i < queue_len; i++)
	{
		if(MAX30100_QUEUE_dequeue(queue, &sample) == MAX30100_QUEUE_FAILED)
		{
			return MAX30100_QUEUE_FAILED;
		}

		sum -= window_arr[window_idx];
		window_arr[window_idx] = sample.sample_hr;
		sum += sample.sample_hr;

		window_idx++;
		if(window_idx >= MAX30100_QUEUE_WINDOW_SIZE)
		{
			window_idx = 0;
		}

		if(count < MAX30100_QUEUE_WINDOW_SIZE)
		{
			count++;
		}

		sample.sample_hr = (sum / count) - sample.sample_hr;
		if(MAX30100_QUEUE_enqueue(queue, &sample) == MAX30100_QUEUE_FAILED)
		{
			return MAX30100_QUEUE_FAILED;
		}
	}

	return MAX30100_QUEUE_OK;
}

int MAX30100_QUEUE_butterworth(MAX30100_QUEUE* queue, MAX30100_BUTTERWORTH* bw)
{
	float v;
	MAX30100_SAMPLE sample;

	if(!queue || !bw)
	{
		return MAX30100_QUEUE_FAILED;
	}

	for(uint16_t i = 0; i < queue->count; i++)
	{
		if(MAX30100_QUEUE_dequeue(queue, &sample) == MAX30100_QUEUE_FAILED)
		{
			return MAX30100_QUEUE_FAILED;
		}

		v = (bw->alpha1 * sample.sample_hr) + (bw->alpha2 * bw->prev_v);
		sample.sample_hr = bw->prev_v + v;
		bw->prev_v = v;
		
		if(MAX30100_QUEUE_enqueue(queue, &sample) == MAX30100_QUEUE_FAILED)
		{
			return MAX30100_QUEUE_FAILED;
		}
	}

	return MAX30100_QUEUE_OK;	
}

