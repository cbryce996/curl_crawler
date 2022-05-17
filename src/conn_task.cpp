#include "conn_task.h"

conn_task::conn_task(std::string url) :
	url("http://www.google.com"),
	buffer()
{
}

void conn_task::run()
{
	CURL* handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, "http://www.google.com");
	curl_easy_setopt(handle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, conn_task::write_data);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, this);
	curl_easy_perform(handle);
	output();
}

//Writes the data received to the buffer
void conn_task::write(char* data, std::size_t realsize)
{
	buffer.reserve(realsize);

	buffer.insert(buffer.end(), data, data + realsize);
}

//Workaround for using CURL within a C++ class, since CURL only takes static functions, make this function static, take a pointer to our class provided by CURL_WRITE_DATA  and call the write function through that pointer
std::size_t conn_task::write_data(void* data, std::size_t size, std::size_t nmemb, void* outp)
{
	std::size_t realsize = size * nmemb;
	char* ptr = static_cast<char*>(data);
	static_cast<conn_task*>(outp)->write(ptr, realsize);
	return realsize;
}

void conn_task::output()
{
	for(char c : buffer)
	{
		std::cout << c;
	}
}
