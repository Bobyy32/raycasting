/////////////////////////////////////////////////////////////////////
//contributors:
//name:
//
//
//
//


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
	server(std::string listenPort_, std::string sendPort_);

	~server();

	//setters


	//getters

	//general functions
	void start();

	

	private:
		
		void receive();

		void send();

		void waitForCommand();

		void readbufferIntoStream(char arr[], int sizearr, char packetDelim);

		void readStream(char delim);

		int currentPrep;
		void prepMessage();

		void sortScores();

		void insertScore(int score, std::string name);

		void storeScores();

		void readScores();

		bool connected;
		bool keepRunning;
		std::string receivePort;
		std::string sendPort;
		std::string clientIp;

		recvData LeaderBoard;
		sendData sendBuf;
		sf::TcpSocket sock;

		int waitingPackets;
		std::stringstream inStream;

};

