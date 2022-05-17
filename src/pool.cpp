#include "pool.h"

pool::pool(std::size_t number_threads, std::size_t buffer_size) :
	threads(number_threads),
	stopped(false),
	tasks_queue(buffer_size),
	threads_vector()
{
}

pool::~pool()
{
	stopped = true;
	for (std::thread& t : threads_vector) t.join();
}

void pool::schedule_task(std::unique_ptr<task> new_task)
{
	tasks_queue.push(std::move(new_task));
	std::cout << "Task added to queue" << std::endl;
}

void pool::initialize_pool()
{
	for (int i = 0; i < threads; i++)
	{
		threads_vector.push_back(std::thread([&]()
			{
				while (!stopped)
				{
					std::unique_ptr<task> current_task;
					current_task = std::move(tasks_queue.read());
					current_task->run();	
					std::cout << "Task executed" << std::endl;
				}
			}));
		std::cout << "Thread created" << std::endl;
	}
}
