#include "Game.h"
int main(void)
{
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