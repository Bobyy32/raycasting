#ifndef GAME_H
#define GAME_H

/*
Game Wrapper Class
*/

#include "Header.h"
#include "Player.h"
#include "Raycast.h"


class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	sf::Clock clock;

	float deltaTime;

	float lastFrameTime;

	void initializeVariables();
	void initializeWindow();

	Player player;

	Raycast raycast;


public:
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;


	// Functions
	void updatePollEvents();
	void update();
	void render();

	void drawMap();

};


#endif // !GAME_H