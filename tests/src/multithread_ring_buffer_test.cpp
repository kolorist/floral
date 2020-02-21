#include "multithread_ring_buffer_test.h"

#include <Windows.h>

#include <stdio.h>

#include <floral/thread/thread.h>

#include <floral/containers/ring_buffer.h>

floral::inplaced_ring_buffer_mt<s32, 4u>		s_interThreadRingBuffer;

void producer_thread_func(voidptr i_data)
{
	for (s32 i = 0; i < 20000000; i++)
	{
		s_interThreadRingBuffer.wait_and_push(i);
	}
	s_interThreadRingBuffer.wait_and_push(-1);
	printf("[producer] producer finished.\n");
}

void consumer_thread_func(voidptr i_data)
{
	s32 c = 0;
	while (true)
	{
		//Sleep(10);
		s32 msg = s_interThreadRingBuffer.wait_and_pop();
		if (msg == -1)
		{
			break;
		}
		c++;
	}
	printf("[consumer] consumer finished: %d\n", c);
}

void do_multithread_ring_buffer_test()
{
	floral::thread producer;
	floral::thread consumer;

	producer.entry_point = &producer_thread_func;
	producer.ptr_data = nullptr;

	consumer.entry_point = &consumer_thread_func;
	consumer.ptr_data = nullptr;

	printf("starting producer...\n");
	producer.start();
	printf("starting consumer...\n");
	consumer.start();

	wait_for_thread(producer);
	printf("producer joined.\n");
	wait_for_thread(consumer);
	printf("consumer joined.\n");
}

