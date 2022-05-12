#pragma once
#include <queue>
#include <semaphore>
#include <mutex>
#include <thread>
#include <iostream>
#include "task.h"

class bounded_buffer
{
private:
	std::queue<std::unique_ptr<task>> buffer_queue;
	std::counting_semaphore<0> full_semaphore;
	std::counting_semaphore<0> empty_semaphore;
	std::mutex buffer_mutex;

public:
	bounded_buffer(std::size_t);

	void push(std::unique_ptr<task>);
	std::unique_ptr<task> read();	
};
