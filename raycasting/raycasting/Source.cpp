#include "Game.h"
int main(void)
{

	std::srand(static_cast<unsigned>(time(NULL)));

	//Initiate game
	Game game;

	while (game.running())
	{
		//Update
		game.update();

		//Render
		game.render();

	}

	return 0;
}