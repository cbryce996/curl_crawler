#include <iostream>
#include <chrono>
#include "pool.h"
#include "conn_task.h"

int main()
{
	pool thread_pool(4, 20);
	thread_pool.initialize_pool();	

	for (int i = 0; i < 100; i++)
	{
		std::unique_ptr<conn_task> task1 = std::make_unique<conn_task>("Test");
		thread_pool.pool::schedule_task(std::move(task1));
	}
}
