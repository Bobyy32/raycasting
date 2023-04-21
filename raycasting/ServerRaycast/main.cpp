#include "bundler.hpp"
#include "server.hpp"



int main(void) 
{
	server svr("46580", "46580");
	svr.start();
}

