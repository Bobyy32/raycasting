#include "Bundler.hpp"

void jvds::cls()
{
	system("cls");
}

void jvds::pause()
{
	system("pause");
}

void jvds::wait(int waittime)
{
	Sleep(waittime);
}

bool jvds::yesOrNo()
{
	char gotchar = '\n';
	while (gotchar == '\n')
	{
		std::cin >> gotchar;
		if (gotchar == 'y' || gotchar == 'Y')
		{
			return true;
		}
		else if (gotchar == 'n' || gotchar == 'N')
		{
			return false;
		}
		cls();
		std::cout << "output was invalid please try again\n";
		pause();
	}
	return false;
}

std::string jvds::getWholeLine()
{
	std::string data;
	std::cin.ignore();
	std::getline(std::cin, data, '\n');
	return data;
}

void jvds::txtPause(std::string text)
{
	std::cout << text << std::endl;
	pause();
	return;
}

void jvds::clsTxtPause(std::string text)
{
	cls();
	std::cout << text << std::endl;
	pause();
	cls();
	return;
}

bool jvds::doesStreamhaveChar(std::stringstream& ss, char delim)
{
	auto streampos = ss.tellg();
	char checker = '\n';

	/*auto result = ss.find(')');*/

//	std::streampos endPos;
	while (!ss.eof())
	{
		ss >> checker;
		if (checker == ')')
		{
			ss.clear();
			ss.seekg(streampos);
			return true;
		}
	}
	ss.clear();
	ss.seekg(streampos);
	return false;
}

void jvds::charArrtoStream(char arr[], int sizeArr, std::stringstream& ss)
{
	for (int i = 0; i < sizeArr; ++i)
	{
		ss << arr[i];
	}
	return;
}

//stupid code needs define _CRT_SECURE_NO_WARNING
//std::string jvds::getDateString()
//{
//	std::string date;
//	auto current = std::chrono::system_clock::now();
//	auto time = std::chrono::system_clock::to_time_t(current);
//
//	std::tm timeT = *std::localtime(&time);
//
//	std::stringstream strm;
//	strm << std::put_time(&timeT, "%d-%m-%Y");
//	date = strm.str();
//	return date;
//}

int jvds::getRandomBetween(int lowRange, int highRange)
{
	int random = lowRange + (std::rand() % (highRange - lowRange + 1));
	return random;
}

int jvds::findLowest(int i1, int i2)
{
	if (i1 > i2)
	{
		return i2;
	}
	else
	{
		return i1;
	}
}

int jvds::findhighest(int i1, int i2)
{
	if (i1 > i2)
	{
		return i1;
	}
	else
	{
		return i2;
	}
}


