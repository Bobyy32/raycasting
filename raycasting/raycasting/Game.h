#ifndef GAME_H
#define GAME_H

/*
Game Wrapper Class
*/

#include "Header.h"
#include "Player.h"
#include "Raycast.h"
#include "EntityPool.h"
#include "Entity.h"
#include "Entity_1.h"
#include "Gun.h"
#include "TcpClient.hpp"
#include "UnitTesting.h"

class Game
{
private:

	
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	sf::Clock clock;

	float deltaTime;

	float lastFrameTime;

	int round;

	void initializeVariables();
	void initializeWindow();

	Player player;

	EntityPool entityPool;

	Raycast raycast;

	Gun gun;

	UnitTesting unitTesting;


	// for shooting mechanic
	float delay = 0.3f; // Delay in seconds
	float timer = 0.0f;


	int currentScore;
	int topScore1;
	int topScore2;
	int topScore3;


public:
	Game(TcpClient* client_);
	virtual ~Game();

	//Accessors
	const bool running() const;


	// Functions
	void updatePollEvents();
	void update();
	void render();

	void drawMap();

	void drawScore();

	void updateTopScores();
	TcpClient* ptrClient;
};


#endif // !GAME_H