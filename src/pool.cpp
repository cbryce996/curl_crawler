#include "pool.h"

pool::~pool()
{
	stopped = true;
	for (std::thread& t : threads_vector) t.join();
}

void pool::schedule_task(std::unique_ptr<task> new_task)
{
	std::unique_lock<std::mutex> lock(tasks_mutex);
	tasks_queue.push(std::move(new_task));
	tasks_semaphore.release();
}

void pool::initialize_pool()
{
	for (int i = 0; i < THREADS; i++)
	{
		threads_vector.push_back(std::thread([&]()
			{
				while (!stopped)
				{
					std::unique_lock<std::mutex> lock(tasks_mutex);
					tasks_semaphore.acquire();
					std::unique_ptr<task> current_task;
					current_task = std::move(tasks_queue.read());
					current_task->run();	
				}
			}));
	}
}
