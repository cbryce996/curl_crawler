#include "bounded_buffer.h"

bounded_buffer::bounded_buffer(std::size_t buffer_size) :
	buffer_queue(),
	buffer_semaphore(buffer_size)
{
}

void bounded_buffer::push(std::unique_ptr<task> element)
{
	buffer_semaphore.acquire();	
	buffer_queue.push(std::move(element));
}

std::unique_ptr<task> bounded_buffer::read()
{
	std::unique_ptr<task> element = std::move(buffer_queue.front());
	buffer_queue.pop();
	buffer_semaphore.release();
	return std::move(element);
}
