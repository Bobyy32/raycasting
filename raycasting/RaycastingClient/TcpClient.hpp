//////////////////////////////////////////////////////////////////
//contributors: Justin Van Der Sluys, Elang Sisson				//
//date:4/26/2023												//
//file: TcpClient.hpp											//
//description:client tcp handler for raycasting game basically	//
//provides communication to the raycasting highscore server		//
//																//
//////////////////////////////////////////////////////////////////


//down to the wire once again :(
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

	//description:main start for the tcp client calls threads onto send and receive also manages the persistent connections
	//params:none
	//return:none
	//pre conditions:none
	//post conditions:none
	void start();


	//description: sets the bools telling the server to continue to stop also disconnects the socket
	//params:none
	//return:none
	//pre conditions:none
	//post conditions:server and threads terminate
	void killServer();

	//description:getter for a recvData array DO NOT EDIT THE CONTENTS OF THIS ONLY COPY AND READ
	//params:none
	//return:recvData*
	//pre conditions:none
	//post conditions:none
	recvData* getscoreArr();

	//description:gets the send buf so the user can c style copy a char arr in then set the flag to send to send it through
	//params:none
	//return:sendData*
	//pre conditions:
	//post conditions:
	sendData* getSendBuf();

	//description:DEPRECATED DO NOT USE 
	//params:std::string& RHS
	//return:none
	//pre conditions:none
	//post conditions:none
	void operator<<(std::string& rhs);


private:

	//description:
	//params:
	//return:
	//pre conditions:
	//post conditions:
	void readbufferIntoStream(char arr[], int sizearr, char packetDelim);

	//description:function that is called threaded continuously sees if there is incoming data on the socket and if so reads and 
	//handles it
	//params:none
	//return:none
	//pre conditions:none
	//post conditions:none
	void receive();

	//description:function that is called threaded continuously sees if the sendflag is ready and if so sends the databuf
	//params:none
	//return:none
	//pre conditions:none
	//post conditions:none
	void send();

	//description:reads the data on the incoming stream and then handles the data inside
	//params:char of the delimiter to look for usually ")"
	//return:none
	//pre conditions:none
	//post conditions:none
	void readStream(char delim);

	//not in use abandonded dreams of threading
	std::mutex mutex;

	bool connected;
	bool keepRunning;

	std::string serverIp;
	int port;

	//in and out buffers
	sendData sendBuf;
	recvData recvBuf;

	int waitingPackets;
	sf::TcpSocket sock;

	std::stringstream outFlowStream;
	//stringstream isnt threadsafe this is deprecated 
	std::stringstream inStream;

};

