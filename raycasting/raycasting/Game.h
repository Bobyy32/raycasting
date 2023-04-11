#ifndef GAME_H
#define GAME_H

/*
Game Wrapper Class
*/

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	void initializeVariables();
	void initializeWindow();
public:
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;


	// Functions
	void updatePollEvents();
	void update();
	void render();


};


#endif // !GAME_H