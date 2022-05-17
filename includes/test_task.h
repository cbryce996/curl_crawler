#include <iostream>
#include <chrono>
#include <thread>
#include <curl/curl.h>
#include "task.h"

class test_task: public task
{
private:
public:
	void run()
	{
		CURL* curl = curl_easy_init();
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(200ms);
	}
};
