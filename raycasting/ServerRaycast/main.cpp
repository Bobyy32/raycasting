#include "bundler.hpp"
#include "server.hpp"

void incrementNum(int* number);

int main(void) 
{

	server svr("46580", "46580", "test");
	svr.start();
	int num = 0;
	std::thread increment(incrementNum, &num);
	while (true) 
	{
		std::cout << num << std::endl;
	}
	increment.join();

}

void incrementNum(int* number)
{
	while (true) 
	{
		*(number) = *number + 1;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
