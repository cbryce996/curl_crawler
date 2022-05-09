#include "bounded_buffer.h"

template <typename T>
void bounded_buffer<T>::push(T element)
{
	buffer_semaphore.acquire();	
	buffer_queue.push(std::move(element));
}

template <typename T>
T bounded_buffer<T>::read()
{
	std::unique_ptr<T> element = buffer_queue.front();
	buffer_queue.pop();
	buffer_semaphore.release();
	return std::move(element);
}
