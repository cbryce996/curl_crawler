#include "bounded_buffer.h"

bounded_buffer::bounded_buffer(std::size_t buffer_size) :
	buffer_queue(),
	full_semaphore(5),
	empty_semaphore(0)
{
}

void bounded_buffer::push(std::unique_ptr<task> element)
{
	full_semaphore.acquire();	
	{
		std::unique_lock<std::mutex> lock(buffer_mutex);
		buffer_queue.push(std::move(element));
	}
	empty_semaphore.release();
}

std::unique_ptr<task> bounded_buffer::read()
{
	empty_semaphore.acquire();
	std::unique_ptr<task> element;
	{
		std::unique_lock<std::mutex> lock(buffer_mutex);
		element = std::move(buffer_queue.front());
		buffer_queue.pop();
	}
	full_semaphore.release();
	return std::move(element);
}
