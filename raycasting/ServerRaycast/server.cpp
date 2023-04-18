#include "server.hpp"

server::server(std::string listenPort_, std::string sendPort_, std::string clientIp_)
{
	receivePort = listenPort_;
	sendPort = sendPort_;
	clientIp = clientIp_;

	connected = false;
	keepRunning = true;


	//inialize the buffers

	recvBuf.curSize = 0;
	sendBuf.sendMsgFlag = false;

	//initalize the tcp stream

}

server::~server()
{
	cleanUp();
}

void server::start()
{

	while (keepRunning)
	{
		//wait till tcp connection established
		//sf::TcpListener listen;
		//listen.listen(std::stoi(receivePort));
		//
		//listen.accept(sock);

		//std::cout << "client connected: " << sock.getRemoteAddress() << " port: " << receivePort;


		std::thread commandThread(&server::waitForCommand, this);
		std::thread sendThread(&server::send, this);
		std::thread recvThread(&server::receive, this);
		commandThread.join();
		sendThread.join();
		recvThread.join();
	}
	return;
}

void server::receive()
{
	while (connected && keepRunning) 
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return;
}

void server::send()
{

	while(connected && keepRunning)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (sendBuf.sendMsgFlag == true) 
		{
		
		}
	}

	return;
}

void server::waitForCommand()
{
	std::string choice;
	jvds::cls();
	std::cout << "enter LEAVE to kill the server\n";
	while (true) 
	{
		std::cin >> choice;
		if (choice == "LEAVE")
		{
			keepRunning = false;
			return;
		}
		else if(connected)
		{
			return;
		}
	}

}

void server::cleanUp()
{
}
