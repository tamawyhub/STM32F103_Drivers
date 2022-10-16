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
		uint16_t hr = x.sample_hr
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
	return MAX30100_QUEUE_SUCCESS;
}

int MAX30100_QUEUE_alpha_filter(const MAX30100_QUEUE* queue)
{
	MAX30100_SAMPLE w, prev_w, x, y;
	if (MAX30100_QUEUE_dequeue(queue, &w) == MAX30100_QUEUE_FAILED)
		return MAX30100_QUEUE_FAILED;
	x=w;
	prev_w=w;
	if (MAX30100_QUEUE_enqueue(queue, &w) == MAX30100_QUEUE_FAILED)
		return MAX30100_QUEUE_FAILED;
	
	for (uint16_t i = 1; i < (queue-> count); i++)
	{
		//acquire new x
		if (MAX30100_QUEUE_dequeue(queue, &x) == MAX30100_QUEUE_FAILED)
				return MAX30100_QUEUE_FAILED;
		//obtain new w
		w.sample_hr = x.sample_hr + ALPHA * prev_w.sample_hr;
		//obtain new y
		y.sample_spo2 = x.sample_spo2;
		y.sample_hr = w.sample_hr - prev_w.sample_hr;
		//insert filtered value
		if (MAX30100_QUEUE_enqueue(queue,&y))
			return MAX30100_QUEUE_FAILED;
		//update prev value for w
		prev_w=w;
	}
	return MAX30100_QUEUE_SUCCESS;
}

int MAX30100_QUEUE_meandiff_filter(const MAX30100_QUEUE* queue)
{
	static uint16_t values[MEAN_FILTER_SIZE] = { 0 };
	static uint32_t sum=0;
	
	//cleanup data from previous calls
	for (int idx = 0; idx < MEAN_FILTER_SIZE; idx ++)
	{
		values[idx]=0;
	}
	sum=0;
	//filter main loop
	uint16_t count = 0;
	MAX30100_SAMPLE x;
	for (int i = 0, idx = 0; i < (queue->count); i++, idx = (idx + 1) % MEAN_FILTER_SIZE)
	{
		if (MAX30100_QUEUE_dequeue(queue, &x) == MAX30100_QUEUE_FAILED)
			return MAX30100_QUEUE_FAILED;
		sum-=values[idx];
		sum+=x.sample_hr;
		values[idx] = x.sample_hr;
		if (count<MEAN_FILTER_SIZE) count++;
		x.sample_hr=sum/count-x.sample_hr;
		if (MAX30100_QUEUE_enqueue(queue, &x) == MAX30100_QUEUE_FAILED)
			return MAX30100_QUEUE_FAILED;
	}
	return MAX30100_QUEUE_OK;
}

int MAX30100_QUEUE_butterworth_filter(const MAX30100_QUEUE* queue)
{
	MAX30100_SAMPLE v, prev_v, x, y;
	if (MAX30100_QUEUE_dequeue(queue, &v) == MAX30100_QUEUE_FAILED)
		return MAX30100_QUEUE_FAILED;
	x=v;
	prev_v=v;
	if (MAX30100_QUEUE_enqueue(queue, &v) == MAX30100_QUEUE_FAILED)
		return MAX30100_QUEUE_FAILED;
	
	for (uint16_t i = 1; i < (queue-> count); i++)
	{
		//acquire new x
		if (MAX30100_QUEUE_dequeue(queue, &x) == MAX30100_QUEUE_FAILED)
				return MAX30100_QUEUE_FAILED;
		//obtain new v
		v.sample_hr = BUTTERWORTH_A1 * x.sample_hr + BUTTERWORTH_A2 * prev_v.sample_hr;
		//obtain new y
		y.sample_spo2 = x.sample_spo2;
		y.sample_hr = v.sample_hr + prev_v.sample_hr;
		//insert filtered value
		if (MAX30100_QUEUE_enqueue(queue,&y))
			return MAX30100_QUEUE_FAILED;
		//update prev value for v
		prev_v=v;
	}
	return MAX30100_QUEUE_SUCCESS;
}
