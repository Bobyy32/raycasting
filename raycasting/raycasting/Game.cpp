#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr;

}

void Game::initializeWindow()
{
	this->videoMode.height = WINDOW_HEIGHT;
	this->videoMode.width = WINDOW_WIDTH;

	this->window = new sf::RenderWindow(this->videoMode, "Raycasting");

	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
}

Game::~Game()
{
	delete this->window;
}


//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}


void Game::updatePollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

//Funcitons
void Game::update()
{
	/*
			-Updates the poll events
			-Updates the player
			-Updates the collision (not implemented yet)
			-Updates the window
	*/

	float simTime = clock.getElapsedTime().asSeconds();

	deltaTime = simTime - lastFrameTime;

	lastFrameTime = simTime;


	updatePollEvents();

	player.update(deltaTime);

	/*raycast.raycast(player);*/
	
}

void Game::render()
{
	/*
		-Clear old frame
		-Renders Game Objects
		-Display frame in window

	*/

	this->window->clear();

	//Draw game 

	player.draw(*this->window);

	std::vector<sf::Vector2f> intersections = raycast.raycast(player, 360, FOV);
	raycast.drawRays(*window, sf::Vector2f(player.getX(), player.getY()), intersections);

	drawMap();



	this->window->display();

}


//draws map onto screen
void Game::drawMap()
{
	sf::Vector2u windowSize = this->window->getSize();
	float squareSize = TILE_SIZE;

	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (worldMap[i][j] != 0)
			{
				sf::RectangleShape wall;
				wall.setSize(sf::Vector2f(squareSize, squareSize));
				wall.setFillColor(sf::Color::Red);
				wall.setOutlineColor(sf::Color::White);
				wall.setOutlineThickness(1);
				wall.setPosition(sf::Vector2f(j * squareSize, i * squareSize));
				this->window->draw(wall);
			}
		}
	}
}