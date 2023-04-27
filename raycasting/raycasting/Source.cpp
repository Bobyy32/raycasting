
#include "Game.h"
#include "TcpClient.hpp"
int main(void)
{
	TcpClient client("25.49.77.220", 46580);
	std::thread clientThread(&TcpClient::start, &client);

	std::srand(static_cast<unsigned>(time(NULL)));

	//Initiate game
	Game game(&client);

	while (game.running())
	{
		//Update
		game.update();

		//Render
		game.render();

	}

	client.killServer();
	clientThread.join();
	return 0;
}