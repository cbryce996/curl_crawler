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
	const int threads;
	bool stopped;
	//std::queue<std::unique_ptr<task>> tasks_queue;
	bounded_buffer tasks_queue;
	std::mutex tasks_mutex;
	std::vector<std::thread> threads_vector;
	std::counting_semaphore<10> tasks_semaphore;

public:
	pool(std::size_t, std::size_t);
	~pool();

	void schedule_task(std::unique_ptr<task>);
	void wait_thread(std::thread);
	void stop_pool();
	void initialize_pool();
};
