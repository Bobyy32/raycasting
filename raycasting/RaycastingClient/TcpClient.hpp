#pragma once
#include "Bundler.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"

struct sendData
{
	bool sendMsgFlag;
	int sizeMsg;
	char sendMsg[100];
};

struct ScoreEntry
{
	std::string EntryName;
	int score;
};

struct recvData
{
	ScoreEntry scoreList[100];
	int curSize;
};



class TcpClient
{
public:
	TcpClient(std::string Ip, int port);
	~TcpClient();

	void start();

	void killServer();

	


private:

	void readbufferIntoStream(char arr[], int sizearr, char packetDelim);

	void receive();

	void send();

	void readStream(char delim);

	bool connected;
	bool keepRunning;

	std::string serverIp;
	int port;

	sendData sendBuf;
	recvData recvBuf;

	int waitingPackets;
	sf::TcpSocket sock;

	std::stringstream inStream;

};

