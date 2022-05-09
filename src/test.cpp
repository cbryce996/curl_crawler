#include <iostream>
#include "pool.h"
#include "test_task.cpp"

int main()
{
	// Make pool and initialize threads
	pool thread_pool;
	thread_pool.initialize_pool();

	// Make test task
	std::unique_ptr<test_task> task1 = std::make_unique<test_task>();

	// Push task onto pool
	for (int i = 0; i < 10; i++)
	{
		thread_pool.schedule_task(std::move(task1));
	}
}
