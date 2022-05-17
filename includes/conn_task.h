#include <string>
#include <vector>
#include <iostream>
#include <curl/curl.h>
#include "task.h"

class conn_task : public task
{
private:
	std::string url;
	std::vector<char> buffer;
public:
	conn_task(std::string);

	void run();
	static std::size_t write_data(void*, std::size_t, std::size_t, void*);
	void write(char*, std::size_t);
	void output();
};
