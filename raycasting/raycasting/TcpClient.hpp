//commented file is in the raycasting tcp client file
//author Justin Van Der Sluys

#pragma once
#include <mutex>
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

	recvData* getscoreArr();

	sendData* getSendBuf();

	void operator<<(std::string& rhs);


private:

	void readbufferIntoStream(char arr[], int sizearr, char packetDelim);

	void receive();

	void send();

	void readStream(char delim);

	std::mutex mutex;

	bool connected;
	bool keepRunning;

	std::string serverIp;
	int port;

	sendData sendBuf;
	recvData recvBuf;

	int waitingPackets;
	sf::TcpSocket sock;

	std::stringstream outFlowStream;
	std::stringstream inStream;

};

