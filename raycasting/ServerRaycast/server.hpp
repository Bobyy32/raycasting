///////////////////////////////////////////////////////////////////////
//contributors: Justin Van Der Sluys, Eland Sisson					 //
//date last edited: 4/26/2023										 //
//file: Server.hpp													 //
//description: class that manages a TCP server client that manages	 //
//a array of scores names basically its a high score server			 //
//																	 //
///////////////////////////////////////////////////////////////////////


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

	


	//description:main start for the tcp server calls threads onto send and receive also manages the persistent connections
	//params:none
	//return:none
	//pre conditions:none
	//post conditions:none
	void start();

	

	private:
		
		//description:threaded funciton that continuously waits for to receive something 
		//params:none
		//return:none
		//pre conditions: connected socket
		//post conditions:none
		void receive();

		//description:threaded function that continuously checks to see if a sendflag is checked and if so sends whats inside the buffer
		//params:none
		//return:none
		//pre conditions:none
		//post conditions:none
		void send();

		//description:DEPRECATED DO NOT USE
		//params:none
		//return:none
		//pre conditions:none
		//post conditions:none
		void waitForCommand();

		//description:reads the char buffer into the instream and additionaly increments the waiting packets if it encounters a ")"
		//params:char arr[], int sizearr, char packetDelim
		//return:none
		//pre conditions:none
		//post conditions:none
		void readbufferIntoStream(char arr[], int sizearr, char packetDelim);

		//description:read the stread and handles the data that arrives the delim tells it what the end of a fully defined packet
		//params:char delim
		//return:none
		//pre conditions:none
		//post conditions:none
		void readStream(char delim);

		//description:preps the messages it wants to send so the packets arrive in a continuous order 
		//params:none
		//return:none
		//pre conditions:none
		//post conditions:none
		int currentPrep;
		void prepMessage();

		//description:sorts the scores in the leader board with biggest scores first
		//params:none
		//return:none
		//pre conditions:none
		//post conditions:leaderboard should be sorted
		void sortScores();

		//description:inserts a score into the scoreboard array
		//params:int score, std::string name
		//return:none
		//pre conditions:none
		//post conditions:score is inserted
		void insertScore(int score, std::string name);

		//description:stores the scores it has to a csv file so the leaderboard stays consistent
		//params:none
		//return:none
		//pre conditions:none
		//post conditions:none
		void storeScores();

		//description:reads the scores from the csv into the scoreboard array
		//params:none
		//return:none
		//pre conditions:none
		//post conditions:none
		void readScores();

		bool connected;
		bool keepRunning;
		std::string receivePort;
		std::string sendPort;
		std::string clientIp;

		recvData LeaderBoard;
		sendData sendBuf;
		sf::TcpSocket sock;
		
		//packets waiting in the buffer to be read
		int waitingPackets;
		//incoming buffer
		std::stringstream inStream;

};

