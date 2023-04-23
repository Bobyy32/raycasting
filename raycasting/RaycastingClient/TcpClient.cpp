#include "TcpClient.hpp"

TcpClient::TcpClient(std::string Ip, int port_)
{
	serverIp = Ip;
	port = port_;

	//inialize sendbuf
	sendBuf.sizeMsg = 0;
	sendBuf.sendMsgFlag = false;

	//initialize recvdata
	recvBuf.curSize = 0;

	waitingPackets = 0;

}

TcpClient::~TcpClient()
{
}

void TcpClient::start()
{
	connected = true;
	keepRunning = true;
	while (connected && keepRunning)
	{
		auto status = sock.connect(serverIp, port);

		if (status == sf::Socket::Done) 
		{
			std::cout << "socket was correct\n";
		}
		else
		{
			std::cout << "socket had a issue\n";
			continue;
		}

		std::thread SendThread(&TcpClient::receive, this);
		std::thread ReceiveThread(&TcpClient::send, this);

		SendThread.join();
		ReceiveThread.join();
	}

}

void TcpClient::killServer()
{
	keepRunning = false;
}

void TcpClient::readbufferIntoStream(char arr[], int sizearr, char packetDelim)
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

void TcpClient::receive()
{
	char dataBuf[1024];
	size_t bytesReceived = 0;
	while (connected && keepRunning) 
	{
		auto result = sock.receive(dataBuf, 1023, bytesReceived);
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
			connected = false;
			std::cout << "client disconnected\n";
		}

		readbufferIntoStream(dataBuf, bytesReceived, ')');
		if (waitingPackets > 0)
		{
			readStream(')');
		}
	}
}

void TcpClient::send()
{
	int incrementer = 0;
	while (connected && keepRunning) 
	{
		size_t sizemsg = strlen(sendBuf.sendMsg);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (sendBuf.sendMsgFlag == true) 
		{
			sock.send(sendBuf.sendMsg, sizemsg);
			sendBuf.sendMsgFlag == false;
		}
		//std::cout << "incrementer is:" << incrementer << std::endl;
		++incrementer;
	}
}

void TcpClient::readStream(char delim)
{
	while (waitingPackets > 0) 
	{
		std::string score;
		std::string index;
		std::string name;
		int IntScore = 0;
		int intIndex = 0;

		char throwaway = 'a';
		inStream >> throwaway;
		std::getline(inStream, index, ',');
		std::getline(inStream, name, ',');
		std::getline(inStream, score, ',');
		inStream >> throwaway;

		IntScore = std::stoi(score);
		intIndex = std::stoi(index);

		recvBuf.scoreList[intIndex].EntryName = name;
		recvBuf.scoreList[intIndex].score = IntScore;
		--waitingPackets;
	}
	
	return;
}
