#include "bundler.hpp"
#include "server.hpp"



int main(void) 
{
	server svr("46580", "46580");

	std::thread svrThread(&server::start, &svr);
	/*svr.start();*/
	std::cout << "passed the thread\n";
	svrThread.join();
}

