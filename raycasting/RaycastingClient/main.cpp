#include "Bundler.hpp"
#include "TcpClient.hpp"
#define chosenport 46580

int main(void) 
{
	TcpClient client("25.49.77.220", chosenport);
	client.start();
	std::cout << "threading works fine";
	return 0;
}
