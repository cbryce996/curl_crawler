#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <semaphore>
#include <iostream>
#include "task.h"
#include "bounded_buffer.h"

class pool
{
private:
	const int THREADS;
	bool stopped;
	std::queue<std::unique_ptr<task>> tasks_queue;
	std::mutex tasks_mutex;
	std::vector<std::thread> threads_vector;
	std::counting_semaphore<1> tasks_semaphore;

public:
	pool();
	~pool();

	void schedule_task(std::unique_ptr<task>);
	void wait_thread(std::thread);
	void stop_pool();
	void initialize_pool();
};
