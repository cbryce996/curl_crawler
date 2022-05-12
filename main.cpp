#include <iostream>
#include <chrono>
#include "pool.h"
#include "test_task.h"

int main()
{
	pool thread_pool(4, 20);
	thread_pool.initialize_pool();	

	for (int i = 0; i < 100; i++)
	{
		std::unique_ptr<test_task> task1 = std::make_unique<test_task>();
		thread_pool.pool::schedule_task(std::move(task1));
	}
}
