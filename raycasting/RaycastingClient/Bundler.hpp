#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>

#ifndef TOOLS
#define TOOLS
namespace jvds
{


	//user interaction stuff
	void cls();
	void pause();
	void wait(int waittime);
	bool yesOrNo();
	std::string getWholeLine();
	void txtPause(std::string text);
	void clsTxtPause(std::string text);
	//std::string getDateString();



	//math stuff
	int getRandomBetween(int lowRange, int highRange);
	int findLowest(int i1, int i2);
	int findhighest(int i1, int i2);
};


//description:
	//preconditions:
	//postconditions:
	//input params:
	//return type:

#endif
