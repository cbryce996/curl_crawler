#pragma once
#include <queue>
#include <semaphore>
#include <mutex>
#include <thread>
#include "task.h"

class bounded_buffer
{
private:
	std::queue<std::unique_ptr<task>> buffer_queue;
	std::counting_semaphore<1> buffer_semaphore;

public:
	bounded_buffer();

	void push(std::unique_ptr<task>);
	std::unique_ptr<task> read();	
};
