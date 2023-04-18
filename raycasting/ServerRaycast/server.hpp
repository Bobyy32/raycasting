#pragma once
#include "bundler.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"

struct sendData 
{
	bool sendMsgFlag;
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


class server
{

public:
	server(std::string listenPort_, std::string sendPort_, std::string clientIp_);

	~server();

	//setters


	//getters

	//general functions
	void start();

	void receive();

	void send();

	void waitForCommand();


	private:
		void cleanUp();

		bool connected;
		bool keepRunning;
		std::string receivePort;
		std::string sendPort;
		std::string clientIp;

		recvData recvBuf;
		sendData sendBuf;
		sf::TcpSocket sock;

};

