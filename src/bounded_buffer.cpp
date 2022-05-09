#include "bounded_buffer.h"

bounded_buffer::bounded_buffer() :
	buffer_queue(),
	buffer_semaphore(100)
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
