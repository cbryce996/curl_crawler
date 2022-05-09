#include "pool.h"

pool::pool() :
	THREADS(8),
	stopped(false),
	tasks_queue(),
	tasks_mutex(),
	threads_vector(),
	tasks_semaphore(100)
{
}

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
	std::cout << "Task added to queue" << std::endl;
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
					if (!tasks_queue.empty())
					{
						tasks_semaphore.acquire();
						std::unique_ptr<task> current_task;
						current_task = std::move(tasks_queue.front());
						tasks_queue.pop();
						current_task->run();	
						std::cout << "Task executed" << std::endl;
					}
				}
			}));
		std::cout << "Thread created" << std::endl;
	}
}
