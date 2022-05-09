#include <iostream>
#include <chrono>
#include <thread>
#include "task.h"

class test_task: public task
{
private:
public:
	void run()
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(200ms);
	}
};
