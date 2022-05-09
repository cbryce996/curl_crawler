#include <queue>
#include <semaphore>
#include <mutex>
#include <thread>

template<typename T>
class bounded_buffer
{
private:
	std::queue<T> buffer_queue;
	std::counting_semaphore<100> buffer_semaphore;

public:
	void push(T);
	T read();	
};
