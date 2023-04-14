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
							-Updates the collision
									-Updates the window
										*/

	float simTime = clock.getElapsedTime().asSeconds();

	deltaTime = simTime - lastFrameTime;

	lastFrameTime = simTime;


	updatePollEvents();

	player.update(deltaTime);

	std::cout << player.getX() << " " << player.getY() << std::endl;
	
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

	drawMap();


	this->window->display();

}

void Game::drawMap()
{
	sf::Vector2u windowSize = this->window->getSize();
	float squareSize = static_cast<float>(std::min(windowSize.x, windowSize.y)) / 24.0f;

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