#include "server.hpp"

server::server(std::string listenPort_, std::string sendPort_)
{
	receivePort = listenPort_;
	sendPort = sendPort_;

	connected = false;
	keepRunning = true;

	//inialize the buffers

	recvBuf.curSize = 0;
	sendBuf.sendMsgFlag = false;

}

server::~server()
{

}

void server::start()
{
	while (keepRunning)
	{

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
	}
	return;
}

void server::receive()
{
	char dataIn[1024];
	size_t receivedData;
	while (connected && keepRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		auto result = sock.receive(dataIn, sizeof(dataIn), receivedData);
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
		sendBuf.sendMsgFlag = true;
		if (sendBuf.sendMsgFlag == true)
		{
			strcpy_s(sendBuf.sendMsg, "(sendTest1)");
			size_t msg = strlen(sendBuf.sendMsg);

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
	std::string str;
	std::getline(inStream, str, ')');
	std::cout << "read something\n";
}
