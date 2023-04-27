




#include "server.hpp"

server::server(std::string listenPort_, std::string sendPort_)
{
	receivePort = listenPort_;
	sendPort = sendPort_;

	connected = false;
	keepRunning = true;

	//inialize the buffers

	LeaderBoard.curSize = 0;
	sendBuf.sendMsgFlag = false;

	currentPrep = 0;
}

server::~server()
{

}

void server::start()
{
	/*for (int i = 0; i < 100; ++i)
	{
		LeaderBoard.scoreList[i].EntryName = "test";
	}
	for (int i = 0; i < 100; ++i)
	{
		LeaderBoard.scoreList[i].score = i * 10;
	}
	LeaderBoard.curSize = 100;
	

	insertScore(167, "insertScore");*/


	while (keepRunning)
	{
		readScores();
		sortScores();
		//wait till tcp connection established
		sf::TcpListener listen;
		listen.listen(std::stoi(receivePort));
		listen.accept(sock);

		std::cout << "client connected: " << sock.getRemoteAddress() << " port: " << receivePort << std::endl;
		connected = true;

		//std::thread commandThread(&server::waitForCommand, this);
		std::thread sendThread(&server::send, this);
		std::thread recvThread(&server::receive, this);
		//commandThread.join();
		sendThread.join();
		recvThread.join();
		storeScores();
	}
	return;
}

void server::receive()
{
	char dataIn[1024];
	size_t receivedData;
	while (connected && keepRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		auto result = sock.receive(dataIn, sizeof(dataIn) - 1, receivedData);
		if (result == sf::TcpSocket::Done)
		{
			std::cout << "recv OK\n";
		}
		if (result == sf::TcpSocket::NotReady)
		{
			std::cout << "notready\n";
		}
		if (result == sf::TcpSocket::Error)
		{
			std::cout << "error recv\n";
		}
		if (result == sf::TcpSocket::Disconnected)
		{
			std::cout << "client disconnected\n";
			connected = false;
		}

		readbufferIntoStream(dataIn, receivedData, ')');
		if (waitingPackets > 0)
		{
			readStream(')');
		}
	}
	return;
}

void server::send()
{
	while (connected && keepRunning)
	{
		prepMessage();
		if (sendBuf.sendMsgFlag == true)
		{
			size_t msg = strlen(sendBuf.sendMsg);

			std::this_thread::sleep_for(std::chrono::milliseconds(11));

			auto messageStat = sock.send(sendBuf.sendMsg, msg);
				if (messageStat == sf::TcpSocket::Done)
				{
					std::cout << "recv OK Send\n";
				}
				if (messageStat == sf::TcpSocket::NotReady)
				{
					std::cout << "notready Send\n";
				}
				if (messageStat == sf::TcpSocket::Error)
				{
					std::cout << "error recv Send\n";
				}
			if (messageStat == sf::TcpSocket::Disconnected)
			{
				std::cout << "client disconnected Send";
				connected = false;
			}
			sendBuf.sendMsgFlag = false;
		}
	}

	return;

}

void server::waitForCommand()
{
	std::string choice;
	jvds::cls();
	std::cout << "enter LEAVE to kill the server\n";
	while (keepRunning && connected)
	{
		std::cin >> choice;
		if (choice == "LEAVE")
		{
			keepRunning = false;
			return;
		}
	}

}

void server::readbufferIntoStream(char arr[], int sizearr, char packetDelim)
{
	char screener = 'a';
	for (int i = 0; i < sizearr; ++i)
	{
		screener = arr[i];
		if (screener == packetDelim)
		{
			++waitingPackets;
		}
		inStream << screener;
	}
	return;
}

void server::readStream(char delim)
{
	while (waitingPackets > 2)
	{
		std::string str;
		char throwAwayChar = 'a';

		std::string score;
		std::string name;

		inStream >> throwAwayChar;
		std::getline(inStream, score, ',');
		std::getline(inStream, name, ',');
		inStream >> throwAwayChar;

		int intScore = std::stoi(score);
		insertScore(intScore, name);
		--waitingPackets;
	}
}

void server::prepMessage()
{
	if (currentPrep >= LeaderBoard.curSize)
	{
		currentPrep = 0;
		return;
	}

	int score = LeaderBoard.scoreList[currentPrep].score;
	std::string name = LeaderBoard.scoreList[currentPrep].EntryName;
	std::string packet = '(' + std::to_string(currentPrep) + ',' + name + ',' + std::to_string(score) + ",)";
	strcpy_s(sendBuf.sendMsg, packet.c_str());
	sendBuf.sendMsgFlag = true;

	++currentPrep;
	return;
}

void server::sortScores()
{
	for (int i = 0; i < LeaderBoard.curSize - 1; ++i)
	{
		int highestIndex = i;
		for (int j = i; j < LeaderBoard.curSize; ++j)
		{
			if (LeaderBoard.scoreList[j].score > LeaderBoard.scoreList[highestIndex].score)
			{
				highestIndex = j;
			}
		}
		auto holder = LeaderBoard.scoreList[highestIndex];
		LeaderBoard.scoreList[highestIndex] = LeaderBoard.scoreList[i];
		LeaderBoard.scoreList[i] = holder;
	}

}

void server::insertScore(int score, std::string name)
{
	if (LeaderBoard.curSize < 100)
	{
		int size = LeaderBoard.curSize;
		LeaderBoard.scoreList[size + 1].score = score;
		LeaderBoard.scoreList[size + 1].EntryName = name;
		++LeaderBoard.curSize;
		sortScores();
		return;
	}
	//if cannot just dump data somewhere and sort
	else
	{
		sortScores();
		for (int i = 0; i < LeaderBoard.curSize; ++i)
		{
			if (LeaderBoard.scoreList[i].score < score)
			{
				for (int j = LeaderBoard.curSize - 1; j > i; --j)
				{
					LeaderBoard.scoreList[j] = LeaderBoard.scoreList[j - 1];
				}
				LeaderBoard.scoreList[i].score = score;
				LeaderBoard.scoreList[i].EntryName = name;
				return;
			}

		}
		return;
	}
	return;
}

void server::storeScores()
{
	std::ofstream writeFile;
	writeFile.open("scoreboard.csv");

	for (int i = 0; i < 100; ++i)
	{
		writeFile << LeaderBoard.scoreList[i].score;
		writeFile << ",";
		writeFile << LeaderBoard.scoreList[i].EntryName;
		writeFile << "\n";
	}
	LeaderBoard.curSize = 0;
	writeFile.close();
}

void server::readScores()
{
	std::ifstream readfile;
	readfile.open("scoreboard.csv");
	for (int i = 0; i < 100 && !readfile.eof(); ++i)
	{
		std::string score;
		std::string name;
		int intScore = 0;

		std::getline(readfile, score, ',');
		std::getline(readfile, name);
		intScore = std::stoi(score);

		LeaderBoard.scoreList[i].EntryName = name;
		LeaderBoard.scoreList[i].score = intScore;
		++LeaderBoard.curSize;
	}
	readfile.close();
	return;
}
