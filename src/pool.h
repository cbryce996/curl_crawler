#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <semaphore>
#include "task.h"
#include "bounded_buffer.h"

class pool
{
private:
	const int THREADS = 8;
	bool stopped = false;
	bounded_buffer<std::unique_ptr<task>> tasks_queue;
	std::mutex tasks_mutex;
	std::vector<std::thread> threads_vector;
	std::counting_semaphore<0> tasks_semaphore;

public:
	pool();
	~pool();

	void schedule_task(std::unique_ptr<task>);
	void wait_thread(std::thread);
	void stop_pool();
	void initialize_pool();
};
