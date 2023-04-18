#include "bundler.hpp"
#include "server.hpp"

void incrementNum(int* number);

int main(void) 
{

	server svr("", "", "");
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
		awdawdawdawd

			awd
			aw
			d
			awd
			aw
			dw
			a
			wa
			daw
			d
			aw
			dw
	}
}
