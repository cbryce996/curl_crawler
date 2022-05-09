#include <iostream>
#include "task.h"

class test_task: public task
{
private:
public:
	void run()
	{
		std::cout << "Task run successfully!" << std::endl;
	}
};
